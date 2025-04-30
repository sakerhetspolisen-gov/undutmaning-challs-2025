/*
 * /secure/login.c
 *
 * This is the object called from the GameDriver to log people into
 * the Game. This object decides which player object is to be used by
 * the player and swaps the socket to that object.
 */
#pragma no_inherit
#pragma strict_types

#include <composite.h>
#include <const.h>
#include <files.h>
#include <language.h>
#include <log.h>
#include <login.h>
#include <macros.h>
#include <mail.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>

#include "/config/sys/local.h"

/*
 * These are the necessary variables stored in the save file.
 */
private int data = 0;
private mapping m_vars;          /* Some less used variables. */

#define ATTEMPT_LOG  "/open/attempt_while_at_runlevel"
#define CLEANUP_TIME 300.0 /* five minutes */
#define TIMEOUT_TIME 300.0 /* five minutes */
#define ONE_DAY      86400 /* one day in seconds */
#define LOG_COMMANDS    "LOGIN_COMMANDS"

/*
 * Global variables that aren't in the save-file.
 */
static int time_out_alarm;   /* The id of the alarm used for timeout.   */
static int login_type = CONNECT_LOGIN; /* Login/revive LD/switch terminal */

/*
 * Prototypes.
 */
static void confirm_use_data(string str);
static void who();

/*
 * Function name: clean_up
 * Description  : This function is called every several minutes and if the
 *                player lost or broke connection, we destruct the object.
 */
static void
clean_up()
{
    if (!query_interactive(this_object()))
    {
        destruct();
    }
    else
    {
        set_alarm(CLEANUP_TIME, 0.0, clean_up);
    }
}

/*
 * Function name: create_object
 * Description  : Called to construct this object.
 */
static void
create()
{
    set_alarm(CLEANUP_TIME, 0.0, clean_up);

    setuid();
    seteuid(getuid());
}

static void
log(string fun, string message)
{
    SECURITY->log_syslog(LOG_COMMANDS, sprintf("%s - %s:%-5d [%s] %s: %s\n",
                                               ctime(time()),
					       query_ip_number(this_object()),
                                               query_remote_port(this_object()),
                                               query_ip_name(this_object()),
                                               fun, message));
}


/*
 * Function name: short
 * Description  : This function returns the short description of this object.
 * Returns      : string - the short description.
 */
string
short()
{
    string name = "";
    if(data != 0)
        name = sprintf("0x%02X",data);
    return "login"  + (name ? " (" + name + ")" : "");
}


/*
 * Function name: query_pl_name
 * Description  : Return the real name of the player who is trying to log in.
 * Returns      : string - the name.
 */
string
query_pl_name()
{
    string name = "";
    if(data != 0)
        name = sprintf("0x%02X",data);
    return name;
}

/*
 * Function name: query_real_name
 * Description  : Return the real name of this object: "logon"
 * Returns      : string - "logon".
 */
string
query_real_name()
{
    return "logon";
}

/*
 * Function name: time_out
 * Description  : Called when the player takes too much time to type a line.
 *                It destructs the object.
 */
static void
time_out()
{
    write_socket("\nTime out! Welcome back another time.\n");
    destruct();
}

/*
 * Function name: swap_to_player
 * Description  : Swapsocket to player object. Two options:
 *                1) swap to already active player object.
 *                2) swap to empty body at login.
 * Arguments    : object ob - the playerobject to swap to.
 */
static void
swap_to_player(object ob)
{
    object dump;

    /* Print possible news to the player before we alter his/her euid.
     * Since cat() doesn't seem to work, we have to use this construct to
     * make sure the person gets to read the message.
     */
    // write_socket(read_file(LOGIN_FILE_NEWS));

    /* Swap to the playerobject. */
    exec(ob, this_object());

    /* If we are not in the game, enter it. */
    if (!environment(ob))
    {
        if (!(ob->enter_game(data)))
        {
            write_socket("Failed to enter game.\n");
            ob->remove_object();
        }
    }
    ob->update_hooks();
    destruct();
}


/*
 * Function name: move_player_into_game
 * Description  : The next step in the startup process. If everything works,
 *                we're good to go.
 */
static void
move_player_into_game()
{
    object ob;

    ob = clone_object(LOGIN_NEW_PLAYER);

    ob->open_player();
    seteuid(BACKBONE_UID);
    export_uid(ob);
    ob->set_trusted(1);
    exec(ob, this_object());
    ob->enter_new_player(data);
    destruct();
    return;
}

/*
 * Function name: date
 * Description  : Before people are asked to queue, we give them some
 *                information on the uptime of the game, so they won't
 *                have to wait a long time to get into a game that is
 *                about to reboot.
 */
public void
date()
{
    write_socket("Local time  : " + ctime(time()) +
        "\nStart time  : " + ctime(SECURITY->query_start_time()) +
        "\nUp time     : " +
        CONVTIME(time() - SECURITY->query_start_time()) +
        "\nMemory usage: " + SECURITY->query_memory_percentage() + "%\n");
}

/*
 * Function name: generic_commands
 * Description  : Handles commands which should always be available such
 *                as 'quit'.
 * Arguments    : str - the input
 *                function - to call when input was handled to, ususally
 *                           set to &input_to
 * Returns      : True if the command was handled
 */
public int
generic_command(string str, function input, string message)
{
    int done = 0;
    str = lower_case(str);

    if (str == "quit")
    {
        write_socket("\nWelcome another time then!\n");
        destruct();
        return 1;
    }

    if (str == "who")
    {
        who();
        done = 1;
    }

    if (done) {
        input();

        if (message)
            write_socket(message);

        return 1;
    }

    return 0;
}

/*
 * Function name: valid_name
 * Description  : Check that a player name is valid. The name must be at
 *                least two characters long and at most eleven characters.
 *                We only allow lowercase letters. Also, generally offensive
 *                names are not allowed.
 * Arguments    : string str - the name to check.
 * Returns      : int 1/0 - true if the name is allowed.
 */
int
valid_data(string str)
{
    int index = -1;
    int tmp_data = 0;
    int length = strlen(str);

    if (length < 1)
    {
        write_socket("\nToo little data. Need one byte to exist.\n");
        return 0;
    }

    /* The names of characters is limited to 11 characters, though allow jr's
     * or xx-characters with a longer name.
     */
    if (length > 3)
    {
        write_socket("\nToo much data. One byte is enough to exist.\n");
        return 0;
    }

    if(sscanf(str,"%d",tmp_data) != 1 || tmp_data < 0 || tmp_data > 255)
    {
        write_socket("\nOne byte is all you are. Enter your data as a number between 0 and 255.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: new_player_name
 * Description  : This routine handles the creation of a new player with a new
 *                name.
 * Arguments    : string str - the name the player wants to use.
 */
static void
new_player_data(string str)
{
    remove_alarm(time_out_alarm);
    time_out_alarm = set_alarm(TIMEOUT_TIME, 0.0, time_out);

    log("new_player_data", str);

    str = lower_case(str);

    if (generic_command(str, &input_to(new_player_data), "Give data again: "))
        return;

    if (!valid_data(str))
    {
        input_to(new_player_data);
        write_socket("Give data again: ");
        return;
    }

    sscanf(str,"%d",data);    

    write_socket("Do you really want to use " + capitalize(query_pl_name()) + " as your data" +
        "? y[es], n[o] or q[uit]: ");

    
    input_to(confirm_use_data);
}

/*
 * Function name: confirm_use_name
 * Description  : When a player first connects, we give him a little message
 *                about the user of proper names, and then ask him to confirm
 *                the use of the name.
 * Arguments    : string str - the entered text.
 */
static void
confirm_use_data(string str)
{
    log("confirm_use_data", str);

    if (generic_command(str, &input_to(confirm_use_data),
                        "Please answer with either y[es], n[o] or q[uit].\n" +
                        "Would you really like to use " +
                        capitalize(query_pl_name()) + " as your data? "))
        return;

    /* Only allow valid answers. */
    str = lower_case(str);
    if (str[0] == 'q')
    {
        write_socket("\nWelcome another time then!\n");
        destruct();
        return;
    }

    remove_alarm(time_out_alarm);
    time_out_alarm = set_alarm(TIMEOUT_TIME, 0.0, time_out);

    if (str[0] == 'n')
    {
        write_socket("\nThen please select different data, or use 'quit' " +
            "to disconnect.\n\nPlease enter the data you wish to use: ");
        input_to(new_player_data);
        return;
    }

    if (str[0] != 'y')
    {
        write_socket("\nPlease answer with either y[es], n[o] or q[uit].\n" +
            "Would you really like to use " + capitalize(query_pl_name()) + " as your data? ");
        input_to(confirm_use_data);
        return;
    }

    write_socket("Welcome to the network, " + capitalize(query_pl_name()) + ". Have fun!\n\n");

    move_player_into_game();
}

/*
 * Function name: login
 * Description  : This function is called when a player wants to login. A lot
 *                of checks are made. This is called from the game driver.
 * Returns      : int 1/0 - true if login is allowed.
 */
public int
logon()
{
    set_screen_width(80);

    if (!query_interactive(this_object()))
    {
        destruct();
        return 0;
    }

    log("logon", "connect");

    seteuid(creator(this_object()));

    write_socket(read_file(LOGIN_FILE_WELCOME));

    write_socket("What data do you wish to contain: ");

    time_out_alarm = set_alarm(TIMEOUT_TIME, 0.0, time_out);

    input_to(new_player_data);

    return 1;
}

/*
 * Function name: query_race_name
 * Description  : Return the race name of this object.
 * Returns      : string - "logon".
 */
public string
query_race_name()
{
    return "logon";
}

/*
 * Function name: catch_tell
 * Description  : This function can be called externally to print a text to
 *                the logon-player.
 * Arugments    : string msg - the text to print.
 */
public void
catch_tell(string msg)
{
    write_socket(msg);
}

/*
 * Function name: who
 * Description  : Called when the player wants to see which other players
 *                are logged on.
 */
static void
who()
{
    object *list = users();

    /* This filters out players logging in and such. */
    list = FILTER_LIVING_OBJECTS(list);
    int size = sizeof(list);

    if (size == 1)
    {
        write("You are the only player present.\n");
    }
    else
    {
        write("There are " + size + " players in the game.\n");
    }
    return;
}



/*
 * Function name: query_prevent_shadow
 * Description  : This function prevents shadowing of this object.
 * Returns      : int 1 - always.
 */
nomask public int
query_prevent_shadow()
{
    return 1;
}
