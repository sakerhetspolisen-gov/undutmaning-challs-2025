/*
 * /std/player.c
 *
 * This file is the basis of all players.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/living";

/* This order is on purpose to limit the number of prototypes necessary. */
#include "/std/player/savevars_sec.c"
#include "/std/player/quicktyper.c"
#include "/std/player/getmsg_sec.c"
#include "/std/player/cmd_sec.c"
#include "/std/player/stats_sec.c"
#include "/std/player/death_sec.c"
#include "/std/player/querys_sec.c"
#include "/std/player/more.c"

#include <cooldowns.h>
#include <hooks.h>
#include <const.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <mail.h>
#include <money.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>

#define LINKDEATH_TIME          (180.0)         /* three minutes */
#define RETURN_TO_LOCATION_TIME (60 * 15)       /* 15 minutes */
#define AUTOLOAD_INTERVAL       (0.0)
#define RECOVERY_INTERVAL       (0.20)

/*
 * Global variables. They are not saved.
 */
private static int    ld_alarm;    /* The alarm used when a player linkdies. */
private static object magic_map;  /* the magic map object. */

/*
 * Function name: query_def_start
 * Description  : This function returns the very basic starting location
 *                for people of this race. Notice that we use query_race
 *                and not query_race_name since query_race always returns
 *                a valid race name. To alter the starting location of the
 *                player, use set_default_start_location.
 */
public nomask string
query_def_start()
{
    return query_default_start_location();
}

/*
 * Function name: query_orig_learn
 * Description:   Return the default starting stats of a player
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public int *
query_orig_learn()
{
    /*        STR, DEX, CON, INT, WIS, DIS */
    return ({  17,  16,  16,  17,  17,  17 });
}

#ifndef NO_ALIGN_TITLE
/*
 * Function name: query_new_al_title
 * Description:   Return the default starting title of a player
 *                This function is supposed to be replaced in inheriting
 *                player objects.
 */
public string
query_new_al_title()
{
    return "neutral";
}
#endif NO_ALIGN_TITLE

/*
 * Function name: fixup_screen
 * Description:   Restore the players screen width. Normally called
 *                during login.
 */
public nomask void
fixup_screen()
{
    int width = query_option(OPT_SCREEN_WIDTH);

    /* Value 0 means unset, so default to 80. */
    if (!width)
    {
        width = 80;
    }
    /* Value -1 means no screen width, ergo no wrapping. */
    if (width == -1)
    {
        width = 0;
    }

    set_screen_width(width);
}

/*
 * Function name: move_living
 * Description  : Redefinition of move_living to handle the player exclusive
 *                interface to the magic map.
 * Arguments    : see 'sman /std/living move_living'
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int result = ::move_living(how, to_dest, dont_follow, no_glance);

    if (!result)
    {
        if (!objectp(magic_map))
        {
	    magic_map = present(MAGIC_MAP_ID);
        }
        catch(magic_map->notify_new_room(to_dest));
    }

    return result;
}

/*
 * Function name: reset_userids
 * Description  : Called to set the euid of this player. Wizards get their own
 *                name as effective user id.
 */
public void
reset_userids()
{
    seteuid(0);
    seteuid(getuid());
}

/*
 * Function:     init_vars_before_load
 * Description:  Initialises all variables to default conditions.
 */
static nomask void
init_vars_before_load()
{
    int i = -1;
    while(++i < SS_NO_EXP_STATS)
    {
        set_base_stat(i, 1);
    }

    stats_to_acc_exp();
    set_learn_pref(query_orig_learn());

#ifndef NO_ALIGN_TITLE
    set_al_title(query_new_al_title());
#endif NO_ALIGN_TITLE
}

static object
clone_recover_object(string entry, string type, function init)
{
    string file, argument;

    if (!stringp(entry) || !strlen(entry))
        return 0;

    if (sscanf(entry, "%s:%s", file, argument) != 2)
    {
        file = entry;
        argument = 0;
    }

    set_this_player(this_object());

    object ob;
    catch(ob = clone_object(file));
    if (!objectp(ob))
    {
#ifdef LOG_FAILED_RECOVERY
        SECURITY->log_syslog(LOG_FAILED_RECOVERY,
            sprintf("%s %-11s %-8s %s\n", ctime(time()),
                capitalize(this_object()->query_real_name()), type, entry));
#endif
        return 0;
    }

    /* Note that we don't check for strlen() since we also want to call
     * init_recover() if the format is 'filename:'.
     */
    if (stringp(argument))
    {
        /*
         * Call the provided init function
         * If init returns true the object is removed. If the return value is
         * an object that object is return instead, allowing recovered items to
         * be replaced.
         */
        mixed ret;

        try {
            if (ret = init(ob, argument))
            {
                ob->remove_object();

                if (objectp(ret)) {
                    return ret;
                }

                return 0;
            }
        } catch (mixed ex) {
#ifdef LOG_FAILED_RECOVERY
            SECURITY->log_syslog(LOG_FAILED_RECOVERY,
                    sprintf("%s %-11s %-8s %s\n", ctime(time()),
                        capitalize(this_object()->query_real_name()), type, entry));
#endif
            ob->remove_object();
            return 0;
        }
    }

    return ob;
}

/*
 * Function name: load_auto_shadows
 * Description  : This function loads and initialises all shadows that the
 *                player should have when he logs in. No special measures are
 *                taken for shadows at login time.
 */
nomask static void
load_auto_shadows()
{
    string *load_arr;
    string file;
    string argument;
    object ob;
    int    index;
    int    size;

    load_arr = query_autoshadow_list();
    if (!sizeof(load_arr))
    {
        return;
    }

    index = -1;
    size = sizeof(load_arr);
    while(++index < size)
    {
        if (sscanf(load_arr[index], "%s:%s", file, argument) != 2)
        {
            write("Shadow load string corrupt: " + load_arr[index] + "\n");
            continue;
        }
        if (LOAD_ERR(file) ||
            !objectp(ob = find_object(file)))
        {
            write("Shadow not available: " + file + "\n");
            continue;
        }

        try {
            ob = clone_object(file);

            if (argument)
            {
                ob->autoload_shadow(argument);
            }
            else
            {
                ob->autoload_shadow(0);
            }
        }
        catch (mixed err)
        {
            write("An error occured while loading a shadow.\n");
            SECURITY->log_syslog(LOG_FAILED_RECOVERY,
                    sprintf("%s %-11s %-8s %s / %s\n", ctime(time()),
                        capitalize(this_object()->query_real_name()), "SHADOW", load_arr[index], err));
        }
    }
}

/*
 * Function name: setup_player
 * Description:   Restore player variables from the player file and go through
 *                startup routines.
 * Arguments:     (string) pl_name - The player's name
 * Returns:       True if setup completed normally
 */
private static nomask int
setup_player(string pl_name)
{
    set_name(pl_name);

    /* No adjectives and no default */
    ::set_adj(({ }));
    /* All variables to default condition before loading. */
    init_vars_before_load();

    seteuid(0);
    reset_userids();

    /* Set the adjectives as loaded */
    set_adj(0);
    fixup_screen();

    set_living_name(pl_name);
    cmd_sec_reset();
    player_save_vars_reset();

    /* Check the accumulated experience and then set the stats. */
    check_acc_exp();
    acc_exp_to_stats();
    reset_exp_gain_desc();

    /* Restore the saved properties and add a default one. */
    add_prop(PLAYER_I_MORE_LEN, 20);
 
    /* Get the autoloading shadows and the autoloading objects. Start the
     * recovery with a little alarm to make it safe. */
    load_auto_shadows();
}

/*
 * Function name: start_player
 * Description  : Final set starting the player.
 */
public void
start_player()
{
    /* Get the soul commands */
    this_object()->load_command_souls();
    command("$look");
    say(QCNAME(this_object()) + " comes into existance.\n");
}

#ifdef CHANGE_PLAYEROB_OBJECT
/*
 * Function name: change_player_object
 * Description:   Initialize this player object based on an existing one.
 * Arguments:     (object) old_plob - the player object to be used to initialize
 *                                   this one.
 * Returns:       True if initialization was successful
 */
public nomask int
change_player_object(object old_plob)
{
    if (MASTER_OB(previous_object()) != CHANGE_PLAYEROB_OBJECT)
    {
        return 0;
    }

    set_name(old_plob->query_real_name());

    setup_player(old_plob->query_real_name());

    this_object()->start_player();

    /* Reset the experience counters. */
    reset_exp_gain_desc();

    return 1;
}
#endif CHANGE_PLAYEROB_OBJECT

/*
 * Function name: try_start_location
 * Description  : Attempt to make the player start in a start location.
 * Arguments    : string path - the path to try.
 */
static nomask void
try_start_location(string path)
{
    object room;

    /* Sanity check. */
    if (!strlen(path))
    {
        return;
    }
    /* Strip any .c if present. */
    sscanf(path, "%s.c", path);
    if (file_size(path + ".c") <= 0)
    {
        return;
    }

    /* Try to load the room, and then try to move the player. */
    LOAD_ERR(path);
    if (objectp(room = find_object(path)))
    {
        catch(move_living(0, room));
    }
}

/*
 * Function name: enter_game
 * Description  : Enter the player into the game.
 * Arguments    : string pl_name - the name of the player.
 * Returns      : int 1/0 - login succeeded/failed.
 */
public nomask int
enter_game(string pl_name)
{
    string path;
    string wname;
    object room;
    int    savetime;

    if ((MASTER_OB(previous_object()) != LOGIN_OBJECT) &&
        (MASTER_OB(previous_object()) != LOGIN_NEW_PLAYER))
    {
        write("Bad login object: " + file_name(previous_object()) + "\n");
        return 0;
    }

    setup_player(pl_name);

    /* Try the default start location if necessary. */
    if (!environment())
    {
        try_start_location(query_default_start_location());
    }

    /* Start him up */
    this_object()->start_player();

    /* Let players start even if their start location is bad */
    if (!environment())
    {
        if (catch(move_living(0, query_def_start())))
        {
            /* If this start location is corrupt too, destruct the player */
            write("PANIC, your starting location is corrupt! Tell someone!\n");
            destruct();
        }
    }

    return 1;
}

/*
 * Function name: open_player
 * Description  : This function may only be called by SECURITY or by the
 *                login object to reset the euid of this object.
 */
public nomask void
open_player()
{
    if ((previous_object() == find_object(SECURITY)) ||
        (MASTER_OB(previous_object()) == LOGIN_OBJECT))
    {
        seteuid(0);
    }
}

/*
 * Function name: save_player
 * Description  : This function actually saves the player object.
 * Arguments    : string pl_name - the name of the player
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
save_player(string pl_name)
{
    return 1;
}

/*
 * Function name: linkdie
 * Description  : When a player linkdies, this function is called.
 */
nomask public void
linkdie()
{
    if (previous_object() != find_object(SECURITY))
    {
        return;
    }

    if(environment(this_object()))
    {
        tell_room(environment(), 
            ({
                C(QRN) + " loses touch with reality.\n",
                "The " + C(QRN) + " loses touch with reality.\n",
                "" }),
                ({ this_object() }) );
    }

    destruct();
}

/*
 * Function name: cooldown_expired_hook
 * Description  : Used to display messages to the player when a cooldowns
 *                expire.
 */
static void
cooldown_expired_hook(string cooldown)
{
    switch (cooldown)
    {
    case HERB_COOLDOWN:
        this_object()->catch_tell("You feel ready to consume another herb.\n");
        break;
    case PEEK_COOLDOWN:
        this_object()->catch_tell("You feel ready to rifle through someone's belongings again.\n");
        break;
    case STEAL_COOLDOWN:
        this_object()->catch_tell("You feel ready to steal something again.\n");
        break;
    }
}

/*
 * Function name: create_living
 * Description  : Called to create the player. It initializes some variables.
 */
public nomask void
create_living()
{
    /* Must initialize the variable before loading because it can be queried
     * in ghosts. */
    player_save_vars_reset();
    add_hook(HOOK_COOLDOWN_EXPIRED, cooldown_expired_hook);
}

/*
 * Function name: reset_living
 * Description  : We don't want people to mask this function.
 */
public nomask void
reset_living()
{
    return;
}

/*
 * Function name: command
 * Description  : Makes the player object execute a command, as if it was typed
 *                on the command line. For wizards, we have to test whether the
 *                euid of the caller allows to force the person.
 * Arguments    : string cmd - the command with arguments to perform. For players
 *                    this should always be prefixed with a "$".
 * Returns      : int - the amount of eval-cost ticks if the command was
 *                    successful, or 0 if unsuccessfull.
 */
public nomask int
command(string cmd)
{
    /* Automatically add the "$" if it isn't added already to the command. This
     * to prevent people from using the quicktyper to circumvent being forced
     * to do particular commands.
     */
    if (!wildmatch("$*", cmd) &&
        (previous_object() != this_object()))
    {
        cmd = "$" + cmd;
    }

    return ::command(cmd);
}

/*
 * Function name: id
 * Description  : Returns whether this object can be identified by a certain
 *                name. That isn't the case if the player hasn't met you
 *                while the real name is used.
 * Arguments    : string str - the name to test
 * Returns      : int 1/0 - true if the name is valid.
 */
public int
id(string str)
{
    if(str == query_real_name())
        return 1;
    
    return ::id(str);
}

/*
 * Function name: parse_command_id_list
 * Description  : Mask of player_command_id_list() in /std/object.c to make sure
 *                that players cannot use the name of an NPC or player when that
 *                person hasn't been introduced to them.
 * Returns      : string * - the original parse_command_id_list() without the
 *                    lower case name of the person.
 */
public string *
parse_command_id_list()
{
    string *ids = ::parse_command_id_list();

    if (sizeof(ids) && notmet_me(this_player()))
    {
        ids -= ({ query_real_name() });
    }

    return ids;
}
