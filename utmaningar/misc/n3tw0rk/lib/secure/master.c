/*
 * /secure/master.c
 *
 * This is the LPmud master object, used from version 3.0.
 *
 * It is the first object loaded, save the simul_efun object, but that
 * isn't a real object rather set of simulated efuns that have to be
 * somewhere.
 *
 * Everything written with 'write()' at startup will be printed on
 * stdout.
 *
 * 1. create() will be called first.
 * 2. flag() will be called once for every argument to the flag -f
 *         supplied to the driver.
 * 3. start_boot() will be called.
 * 4. preload_boot() will be called for each file to preload.
 * 5. final_boot() will be called.
 * 6. The game will enter multiuser mode, and enable log in.
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

/*
 * This is the only object in the game in which we have to use absolute path'
 * to the inclusion files. The reason for this is that the function that
 * contains the search-path for inclusion files is defined in this object.
 */
#include "/sys/config.h"
#include "/sys/files.h"
#include "/sys/language.h"
#include "/sys/living_desc.h"
#include "/sys/log.h"
#include "/sys/mail.h"
#include "/sys/macros.h"
#include "/sys/std.h"
#include "/sys/stdproperties.h"
#include "/sys/time.h"
#include "/sys/udp.h"

#define GAME_START ("/GAME_START")
#define DEBUG_RESTRICTED ( ({ "mudstatus", "swap", "shutdown", "send_udp", "update snoops", "dump_alarms", "dump_objects", "trace_calls" }) )
#define DEBUG_BLOCKED    ( ({ }) )
#define RESET_TIME (900.0) /* 15 minutes */

/* All prototypes have been placed in /secure/master.h */
#include "/secure/master.h"

/* This order is related to how functions may be called internally. */
#include "/secure/master/language.c"
#include "/secure/master/player.c"

/*
 * The global variables that are saved in the SAVEFILE.
 */
private int     game_started;

/*
 * The global variables that are not saved.
 */
private static int     mem_fail_flag;
private static int     memory_limit;
private static mapping command_substitute;
private static mapping move_opposites;
private static string  udp_manager;
private static int     uptime_limit;
private static string  mudlib_version;
private static int     game_start_time;

/*
 * Function name: create
 * Description  : This is the first function called in this object.
 */
void
create()
{
    /* Using a global variable for this is exactly TWICE as fast as using a
     * defined mapping. At this point we only have the default direction
     * commands here because they are all over the game in add_action()s.
     * The other abbreviations can easily be added to the respective souls.
     */
    command_substitute = ([
        "n"  : "north",
        "s"  : "south",
        "w"  : "west",
        "e"  : "east",
        "u"  : "up",
        "d"  : "down",
        "sw" : "southwest",
        "se" : "southeast",
        "nw" : "northwest",
        "ne" : "northeast",
        ]);

    move_opposites = ([
        "north"     : "the south",
        "south"     : "the north",
        "west"      : "the east",
        "east"      : "the west",
        "northwest" : "the southeast",
        "southwest" : "the northeast",
        "northeast" : "the southwest",
        "southeast" : "the northwest",
        "up"        : "below",
        "down"      : "above",
        "in"        : "outside",
        "out"       : "inside",
        ]);

    mem_fail_flag = 0;
#ifdef LARGE_MEMORY_LIMIT
    memory_limit = LARGE_MEMORY_LIMIT;
#else
    memory_limit = 28000000;
#endif
    set_auth(this_object(), "root:root");

    /* We reset the master every RESET time seconds, initially synchronizing
     * it at exactly 1 second after that occurance. I.e. if RESET_TIME is
     * 1 hour, it will be started exactly one second after the top of the
     * hour.
     */
    set_alarm(((RESET_TIME + 1.0) - (itof(time() % ftoi(RESET_TIME)))),
        RESET_TIME, reset_master);

    /* Compute the uptime for this reboot. */
#ifdef REGULAR_UPTIME
    uptime_limit = (REGULAR_UPTIME * 3600);
#ifdef UPTIME_VARIATION
    uptime_limit +=
        (random(UPTIME_VARIATION * 3600) - (UPTIME_VARIATION * 1800));
#endif UPTIME_VARIATION
#endif REGULAR_UPTIME
}

/*
 * Function name: reset_master
 * Description  : This function will be called regularly, each RESET_TIME
 *                seconds. Since we want only one alarm running, from this
 *                function we can make calls to other modules that need it.
 */
static void
reset_master()
{
    /* Check whether there is still enough memory to run the game. The
     * argument 1 means decay the domain experience.
     */
    check_memory(1);
}

/*
 * Function name: short
 * Description  : This function returns the short description of this object.
 * Returns      : string - the short description.
 */
string
short()
{
    return "the hole of the donut";
}

/*********************************************************************
 *
 * GD - INTERFACE LFUNS
 *
 * The below lfuns are called from the Gamedriver for various reasons.
 */

/*
 * Function name: flag
 * Description  : Called on startup of game if '-f' is given on the commandline.
 *                Recognised flag commands:
 *                    echo <text> - display <text> on stdout.
 *                    call <file> <fun> - call function <fun> in <file>.
 *                    shutdown - cause the game to shut down.
 *                To test a new function xx in object yy, do
 *                    driver "-fcall yy xx" "-fshutdown"
 * Arguments    : string str - the command (minus the '-f' prefix).
 */
static void
flag(string str)
{
    string file, arg;

    if (game_started)
        return;

    if (sscanf(str, "for %d", arg) == 1)
    {
        return;
    }

    if (str == "shutdown")
    {
        do_debug("shutdown");
        return;
    }

    if (sscanf(str, "echo %s", arg) == 1)
    {
        write(arg + "\n");
        return;
    }

    if (sscanf(str, "call %s %s", file, arg) == 2)
    {
        arg = (string)call_other(file, arg);
        write("Got " + arg + " back.\n");
        return;
    }
    write("master: Unknown flag " + str + "\n");
}

/*
 * Function name:   get_mud_name
 * Description:     Gives the name of the mud. The name will be #defined in
 *                  all files compiled in the mud. It can not contain spaces.
 * Returns:         Name of the mud.
 *                  We always return a string but we must declare it mixed
 *                  otherwise the type checker gets allergic reactions.
 */
mixed
get_mud_name()
{
#ifdef MUD_NAME
    mixed n;

    n = MUD_NAME;
    if (mappingp(n))
    {
        if (stringp(n[debug("mud_port")]))
            return n[debug("mud_port")];
        else
            return n[0];
    }
    else if (stringp(MUD_NAME))
    {
        return MUD_NAME;
    }
#endif
    return "LPmud(" + debug("version") + ":" + MUDLIB_VERSION + ")";
}

/*
 * Function name: get_mudlib_version
 * Description  : Obtain the mudlib version of the current mudlib. If the
 *                version is not set yet, it will find out.
 * Returns      : string - the version string.
 */
public string
get_mudlib_version()
{
    string *files;
    string filename;
    int ftime, fdate, release;

    /* If we have a caches version, use that. */
    if (strlen(mudlib_version))
    {
        return mudlib_version;
    }

    /* We take the last file in the /svn directory that starts with "mudlib".
     * This assumes that get_dir() returns a sorted list of file names. */
    mudlib_version = MUDLIB_VERSION;
    set_auth(this_object(), "root:root");
    files = get_dir("/svn/mudlib*");
    if (!sizeof(files))
    {
        return mudlib_version;
    }

    /* Parse the file name to get the release number and use the file date
     * as the moment the mudlib was last updated. The date as reported in
     * the file name is ignored. */
    filename = files[-1..][0];
    ftime = file_time("/svn/" + filename);
    sscanf(filename, "mudlib_%i-R%i.txt", fdate, release);
    if ((ftime > 0) && (release > 0))
    {
        mudlib_version += TIME2FORMAT(ftime, " mmm -d yyyy ") +
            ctime(ftime)[11..18] + " - Update " + release;
    }
    return mudlib_version;
}

/*
 * Function name: get_root_uid
 * Description  : Gives the uid of the root user.
 * Returns      : string - the name of the 'root' user.
 */
string
get_root_uid()
{
    return ROOT_UID;
}

/*
 * Function name: get_bb_uid
 * Description  : Gives the uid of the backbone user. That is, each user
 *                that does not have an uid of its own. Apart from backbone
 *                all wizard names and domain names are valid uids. And
 *                root naturally.
 * Returns      : string - the name of the 'backbone' user.
 */
string
get_bb_uid()
{
    return BACKBONE_UID;
}

/*
 * Function name: get_vbfc_object
 * Description  : This function returns the objectpointer to the VBFC
 *                object.
 * Returns      : object - the objectpointer to the VBFC object.
 */
object
get_vbfc_object()
{
    return VBFC_OBJECT->ob_pointer();
}

/* Dummy, we have no wizards and no security */
string 
creator_object(object ob)
{
    return ROOT_UID;
}

/* Dummy, we have no wizards and no security */
string 
creator_file(object ob)
{
    return ROOT_UID;
}


/*
 * Function name: connect
 * Description  : This function is called every time a player connects. We
 *                return a clone of the login object through which the socket
 *                of the new player is connected.
 *                The efun input_to() cannot be called from here.
 * Returns      : object - the login object.
 */
static object
connect()
{
    write("\n");
    set_auth(this_object(), "root:root");

    return clone_object(LOGIN_OBJECT);
}


static string *null_auth = ({ "0", "0"});
/*
 * Function name: valid_set_auth
 * Description  : Whenever the hidden authorization information of an object,
 *                i.e. the uid or the euid, is altered this function is being
 *                called. It checks the format of the new autorization
 *                information and makes sure that the change is valid.
 * Arguments    : object setter      - the object forcing the change.
 *                object getting_set - the object being changed.
 *                string value       - the new value.
 * Returns      : string - the new value.
 */
string
valid_set_auth(object setter, object getting_set, string value)
{
    string auth = query_auth(getting_set);

    if (!stringp(value) || value == auth ||
        ((setter != this_object()) && (setter != find_object(SIMUL_EFUN))))
    {
        return auth;
    }

    string *newauth = explode(value, ":");
    if (sizeof(newauth) != 2)
    {
        return auth;
    }

    if (newauth[0] == "#" || newauth[1] == "#")
    {
        string *oldauth = (stringp(auth) ? explode(auth, ":") : null_auth);

        if (newauth[0] == "#")
        {
            newauth[0] = oldauth[0];
        }
        if (newauth[1] == "#")
        {
            newauth[1] = oldauth[1];
        }
    }

    return implode(newauth, ":");
}

/*
 * Function name: valid_seteuid
 * Description:   Checks if a certain user has the right to set a certain
 *                objects effective 'userid'. All objects has two 'uid'
 *                - Owner userid: Wizard who caused the creation.
 *                - Effective userid: Wizard responsible for the objects
 *                  actions.
 *                When an object creates a new object, the new objects
 *                'Owner userid' is set to creating objects 'Effective
 *                userid'.
 * Arguments:     ob:   Object to set 'effective' user id in.
 *                str:  The effuserid to be set.
 * Returns:       True if set is allowed.
 * Note:          Setting of effuserid to userid is allowed in the GD as
 *                well as setting effuserid to 0.
 */
int
valid_seteuid(object ob, string str)
{
    string uid = getuid(ob);

    /* Root can be anyone it pleases. */
    if (uid == ROOT_UID)
    {
        return 1;
    }

    /* We can be ourselves. That is... set the euid to our uid. */
    if (uid == str)
    {
        return 1;
    }

    /* No one else can be anything. */
    return 0;
}

/*
 * Function name: valid_write
 * Description  : Checks whether a certain user has the right to write a
 *                particular file.
 * Arguments    : string path  - the path name of the file to be write.
 *                mixed writer - the name or object of the writer.
 *                string func  - the calling function.
 * Returns      : int 1/0 - allowed/disallowed.
 */
int
valid_write(string file, mixed writer, string func)
{
    string *dirs, *wpath;
    string wname;
  
    if (objectp(writer))
    {
	    wpath = explode(file_name(writer), "/") - ({ "" });
        writer = geteuid(writer);
    }

    /* Root may do as he please. */
    if (writer == ROOT_UID)
    {
        return 1;
    }

    /* Anonymous objects cannot do anything. */
    if (!strlen(writer))
    {
        return 0;
    }

    return 1;
}

/*
 * Function name: valid_read
 * Description  : Checks if a certain user has the right to read a file.
 * Arguments    : string path  - path name of the file to be read.
 *                mixed reader - the object or name of the reader.
 *                string func  - the calling function.
 * Returns      : int 1/0 - allowed/disallowed.
 */
int
valid_read(string file, mixed reader, string func)
{
    return 1;
}

/*
 * Function name: valid_debug
 * Description  : This function is called to see whether the object is allowed
 *                to call the efun debug() if the object is anything but this
 *                object SECURITY. Since we don't want other objects to call
 *                debug other than via SECURITY->do_debug(), we disallow it
 *                for all.
 * Arguments    : object ob - the object calling valid_debug
 *                string cmd - the debug command.
 *                mixed arg1 - the argument 1 to debug.
 *                mixed arg2 - the argument 2 to debug.
 *                mixed arg3 - the argument 3 to debug.
 * Returns      : int 1/0 - allowed/ disallowed.
 */
varargs int
valid_debug(object ob, string cmd, mixed arg1, mixed arg2, mixed arg3)
{
    return 0;
}

/*
 * Convert a possibly relative path to an absolute path. We can assume
 * that there is a this_player(). This is called from within the editor.
 */
string
make_path_absolute(string path)
{
    return FTPATH(this_player()->query_path(), path);
}

/*
 * Function name: start_boot()
 * Description  : Loads master data, including list of all domains and
 *                wizards. Then make a list of preload stuff
 * Arguments    : int no_preload - If true start_boot() does no preloading
 * Return       : string * - List of files to preload
 */
static string *
start_boot(int no_preload)
{
    string *prefiles, *links;
    object simf;
    int size;

    if (game_started)
        return 0;

    set_auth(this_object(), "root:root");

    /* Fix the userids of the simul_efun object */
    if (objectp(simf = find_object(SIMUL_EFUN)))
    {
        set_auth(simf, "root:root");
    }

    /* Game started variable is set in keepersave ... we crashed before. */
    if (game_started && (time() < query_start_time() + 60))
    {
        write("Crash detected.\n");
        game_started = 0;
    }

    if (no_preload)
    {
        write("Not preloading.\n");
        return 0;
    }

#ifdef PRELOAD_FIRST
    /* In case PRELOAD_FIRST is a single string, it contains the path to a
     * file with the paths to the files to preload, separated by newlines.
     */
    mixed preload_first = PRELOAD_FIRST;
    if (stringp(preload_first) &&
        (file_size(preload_first) > 1))
    {
        prefiles = explode(read_file(preload_first), "\n");
    }
    /* In case PRELOAD_FIRST is an array, it should be an array of the paths
     * of the files to preload.
     */
    else if (pointerp(preload_first))
    {
        prefiles = preload_first + ({ });
    }
#endif PRELOAD_FIRST

    return prefiles;
}


/*
 * Function name: preload_boot
 * Description  : Called at game start time for every file that needs to be
 *                preloaded to load it into memory.
 * Arguments    : string file - the file to preload (without ".c" suffix).
 */
static void
preload_boot(string file)
{
    string err;

    if (file_size(file + ".c") == -1)
    {
        return;
    }

    if (err = (string)LOAD_ERR(file))
    {
        write("\tCan not load: " + file + ":\n     " + err + "\n");
    }
    else
    {
        write("\tPreloading: " + file + ".c\n");
        if (strlen(file = catch(file->teleledningsanka())))
        {
            write("\tError: " + file + ".c\n");
        }
    }
}

/*
 * Function name: final_boot
 * Description  : This function will be called from the gamedriver when the
 *                game is started, after start_boot() and preload_boot() are
 *                called. Note that this function is not called when the
 *                master is updated.
 */
static void
final_boot()
{
    int theport;

    game_started = 1;
    game_start_time = time();
    theport = debug("mud_port");
    if (theport)
    {
        set_auth(this_object(), "root:root");
        write_file((GAME_START + "." + theport), ctime(time()) + "\n");
    }

    debug("set_swap",
          ({
              SWAP_MEM_MIN,
              SWAP_MEM_MAX,
              SWAP_TIME_MIN,
              SWAP_TIME_MAX
              }) );

}

/*
 * Function name: start_shutdown
 * Description  : This function is called by the gamedriver to get a list
 *                of all interactive objects that need to be disconnected
 *                from the game when it is shutting down.
 * Returns      : object * - the interactive users in the game.
 */
object *
start_shutdown()
{
    return users();
}

/*
 * Function name: cleanup_shutdown
 * Description  : This function is called for each interactive object when
 *                the game is shutting down. It makes all those players
 *                quit the game.
 * Arguments    : object ob - the object to force to quit.
 */
static void
cleanup_shutdown(object ob)
{
    set_this_player(ob);
    ob->quit();
}

/*
 * Function name: final_shutdown
 * Description  : When all mortals are kicked out of the game, this function
 *                is called last by the gamedriver before the game closes.
 */
static void
final_shutdown()
{
    /* It's a proper shutdown, so we are not started. */
    game_started = 0;
}

/*
 * Function name: log_error
 * Description  : This function is called from the game driver if there is
 *                an error while compiling an object.
 * Arguments    : string path  - the path of the object having the error.
 *                string error - the error message.
 */
static void
log_error(string path, string error)
{
    int tme;

    set_auth(this_object(), "root:root");

    /* Display the message to interactive wizards. */
    if (this_interactive())
    {
#ifdef DEBUG_MODE_ENABLED
        this_interactive()->catch_tell(error);
#endif
    }

    /* Create the log directory if necessary. */
    path = "/log";
    if (file_size(path) != -2)
    {
        mkdir(path);
    }
    path += "/errors";

    /* Put a time stamp if it's the first entry of the day. */
    if (file_time(path) < (time() - (time() % 86400)))
    {
        write_file(path, ctime(time()) + "\n");
    }

    write_file(path, error);
}

/*
 * This function is called from GD when rooms are destructed so that master
 * can move players to safety.
 */
void
destruct_environment_of(object ob)
{
    if (environment(ob))
    {
        catch(ob->move(environment(ob)));
    }

    if (!query_interactive(ob))
    {
        return;
    }
    ob->move_living("X", ob->query_default_start_location());
}

/*
 * Function name: define_include_dirs
 * Description  : Define  where the '#include' statement is supposed to
 *                search for files. "." will automatically be searched
 *                first, followed in order as given below. The path should
 *                contain a '%s', which will be replaced by the file
 *                searched for.
 * Returns      : string * - the array of path to search.
 */
string *
define_include_dirs()
{
    return ({ "/sys/%s" });
}

/*
 * Function name: query_allow_shadow
 * Description  : This function is called from the game driver to find out
 *                whether it is allowed to shadow a particular object. The
 *                object that wants to shadow is previous_object(). To
 *                prevent shadowing, the target object will have to define
 *                the function query_prevent_shadow() to return 1.
 * Arguments    : object target - the object targeted for shadowing.
 * Returns      : int 1/0 - allowed/disallowed.
 */
int
query_allow_shadow(object target)
{
    return !(target->query_prevent_shadow(previous_object()));
}

/*
 * Function name: valid_exec
 * Description:   Checks if a certain 'program' has the right to use exec()
 * Arguments:     name: Name of the 'program' that attempts to use exec()
 *                      Note that this is different from file_name(),
 *                      The program name is what calling_program returns.
 *                to:   destination of socket
 *                from: target of the socket
 * Returns:       True if exec() is allowed.
 */
int
valid_exec(string name, object to, object from)
{
    name = "/" + name;
    if ((name == (LOGIN_OBJECT + ".c")) ||
        (name == (POSSESSION_OBJECT + ".c")) ||
        (name == (LOGIN_NEW_PLAYER + ".c")))
    {
        return 1;
    }

    /* Allow shapeshift to occur. */
    /*
    if ((name == "/d/Genesis/newmagic/spells/shapeshift_obj.c") ||
        (name == "/d/Genesis/specials/std/spells/obj/shapeshift_obj.c"))
    {
        if (IS_PLAYER_OBJECT(from) && IS_CREATE_SOME(to, "create_creature", "/d/Genesis/race/shapeshift/shapeshift_creature"))
            return 1;
        if (IS_PLAYER_OBJECT(to) && IS_CREATE_SOME(from, "create_creature", "/d/Genesis/race/shapeshift/shapeshift_creature"))
            return 1;
    }
    */
    return 0;
}

/*
 * Function name: simul_efun_reload
 * Description  : This function sets the authorisation variables for the
 *                simul_efun object.
 */
void
simul_efun_reload()
{
    set_auth(find_object(SIMUL_EFUN), "root:root");
}

/*
 * Function name: loaded_object
 * Description  : This function is called when an object is loaded into
 *                memory by another object. It tests whether it was valid
 *                to load the object and sets the authorisation variables
 *                in the loaded object. If the load was not valid, throw()
 *                will terminate the execution.
 * Arguments    : object lob - the loading object.
 *                object ob  - the loaded object.
 */
void
loaded_object(object lob, object ob)
{
}

/*
 * Function name: cloned_object
 * Description  : This function is called when an object is cloned. It tests
 *                whether the clone was valid. It also sets the authorisation
 *                variable in the cloned object. If the clone was not valid,
 *                it will be destroyed and throw() terminates the execution.
 * Arguments    : object cob - the cloning object.
 *                object ob  - the cloned object.
 */
void
cloned_object(object cob, object ob)
{
}

/*
 * Function name: modify_command
 * Description  : Modify a command given by a certain living object. This can
 *                be used for many quicktyper-like functions. There are also
 *                some master.c defined substitutions. Commands that start
 *                with a dollar ($) are not substututed.
 * Arguments    : string cmd - the command to modify.
 *                object ob - the object for which to modify the command.
 * Returns      : string - the modified command to execute.
 */
string
modify_command(string cmd, object ob)
{
    string str;
    string domain;
    int no_subst;

    if (!strlen(cmd))
    {
	return cmd;
    }

    while(cmd[0] == '$')
    {
        cmd = extract(cmd, 1);
        no_subst = 1;
    }

    while(cmd[0] == ' ')
    {
        cmd = extract(cmd, 1);
    }

    if (strlen(str = command_substitute[cmd]))
    {
        cmd = str;
    }

    /* No modification for NPC's */
    if (!query_interactive(ob))
    {
        return cmd;
    }

    /* Allow modification if it does not start with a "$". */
    if (!no_subst)
    {
        cmd = (string)ob->modify_command(readable_string(cmd));
    }

    /* We can not allow any handwritten VBFC */
    while(wildmatch("*@@*", cmd))
    {
        cmd = implode(explode(cmd, "@@"), "#");
    }

    return cmd;
}

/*
 * Function name: query_move_opposites
 * Description  : Returns the exact pointer to the mapping move_opposites.
 * Arguments    : mapping - the mapping.
 */
mapping
query_move_opposites()
{
    /* We intentionally return the unmodified mapping! */
    return move_opposites;
}

/*
 * Function name: query_command_stubstitute
 * Description  : Get a long substitute for a command.
 * Arguments    : string cmd - the short command.
 * Returns      : string - the long substitute.
 */
string
query_command_substitute(string cmd)
{
    return command_substitute[cmd];
}

/*
 * Function name: query_memory_percentage
 * Description  : This function will return the percentage of memory usage
 *                of the game so far. When the counter reaches 100, it is
 *                time to reboot.
 * Returns      : int - the relative memory usage.
 */
nomask public int
query_memory_percentage()
{
    string data = SECURITY->do_debug("malloc");
    string *rows = explode(data, "\n");
    int used = 0;

    if (data[0] == '<' && sizeof(rows) >= 5) {
        /* This might not be reliable across systems. We'll see */
        sscanf(rows[-5], "<system type=\"current\" size=\"%d\"/>", used);
    } else if (sizeof(rows)) {
        sscanf(rows[-1], "Total heap size: %d", used);
    }

	return (used / (memory_limit / 100));
}

/*
 * Function name: memory_failure
 * Description:   This function is called when the gamedriver considers
 *                itself in trouble and need the game shut down in a graceful
 *                manner. This function _must_ be called via a call_other. It
 *                may only be called by root itself or by a member of the
 *                administration.
 */
static void
memory_failure()
{
    if (!mem_fail_flag)
    {
        mem_fail_flag = 1;

        set_auth(this_object(), "root:root");
    }
}

/*
 * Function name: memory_reconfigure
 * Description  : This function is called when the gamedriver receives
 *                an external signal, denoting that the memory status
 *                has changed.
 * Arguments    : int mem - Memory size, 0 small, 1 large.
 */
static void
memory_reconfigure(int mem)
{
    string mess = "a different";
    object *list;

#ifdef LARGE_MEMORY_LIMIT
    if (((mem == 0) &&
         (memory_limit == SMALL_MEMORY_LIMIT)) ||
        ((mem == 1) &&
         (memory_limit == LARGE_MEMORY_LIMIT)))
    {
        return;
    }

    if (mem == 0)
    {
        memory_limit = SMALL_MEMORY_LIMIT;
        mess = "small";
    }
    else
    {
        memory_limit = LARGE_MEMORY_LIMIT;
        mess = "large";
    }
    check_memory(0);
#endif LARGE_MEMORY_LIMIT

    list = filter(users(), &->query_wiz_level());
    list->catch_tell("@ Armageddon: I have switched to " + mess + " memory mode.\n");
}

/*
 * Function name: external_signal
 * Description  : This function is called if the driver gets sent a signal that
 *                it catches. Usually not a good sign ...
 * Arguments    : string sig_name - the signal received.
 */
static void
external_signal(string sig_name)
{
    write("Received " + sig_name + " signal.\n");
    switch (sig_name)
    {
    case "INT":
        // Just shut down!
        debug("shutdown");
        break;
    case "HUP":
    case "KILL":
    case "QUIT":
    case "TERM":
        debug("shutdown");
        break;
    case "USR1":
        memory_reconfigure(0);
        break;
    case "USR2":
        memory_reconfigure(1);
        break;
    case "TSTP":
    case "CONT":
        break;
    case "UNKNOWN":
    default:
        write("Unknown signal \"" + sig_name + "\"received!\n");
    }
}

/*
 * Function name: query_memory_limit
 * Description:   This function returns the current memory limit.
 */
public int
query_memory_limit()
{
    return memory_limit;
}

/*
 * Function name: query_memory_failure
 * Description:   This function returns 1 if memory failure is detected.
 */
public int
query_memory_failure()
{
    return mem_fail_flag;
}

/*
 * Function name: log_incoming_service
 * Description  : This function will make a log of the incomming service.
 * Arguments    : string request - the request to log.
 *                string wname   - the wizard name.
 *                string path    - the path to log.
 */
#ifdef LOG_FTP
static string
log_incoming_service(string request, string wname, string path)
{
    string *parts;
    string fname = "Lib";

    parts = explode(path, "/") - ({ "" });

    if ((sizeof(parts) > 1) &&
        ((parts[0] == "w") ||
         (parts[0] == "d")))
    {
        fname = parts[1];
    }

    log_file(("ftplog/" + fname),
        sprintf("%s %-7s %-11s %s\n", ctime(time()), request, wname, path),
        500000);
}
#endif LOG_FTP

/*
 * Function name: incoming_service
 * Description  : Handle incoming request from other programs. This function
 *                may only be called from the gamedriver.
 * Arguments    : string request - the request.
 * Returns      : string - the answer to the request.
 */
static string
incoming_service(string request)
{
    string *tmp;
    string str;
    string path;
    string rval;
    object ob;

    /* There must be a request, or we cannot answer it ;-) */
    if (!strlen(request))
    {
        return "ERROR Bad request\n";
    }

    /* The request may be separated by \n, \r or space. */
    tmp = explode(request, "\n");
    if (sizeof(tmp))
        request = tmp[0];

    tmp = explode(request, "\r");
    if (sizeof(tmp))
        request = tmp[0];

    tmp = explode(request, " ");

    tmp[0] = lower_case(tmp[0]);

    /* Switch on the request command. */
    switch (tmp[0])
    {
    default:
        return "ERROR Unknown request\n";
	break;
    }
}

/*
 * Function Name: valid_incoming_service
 * Description  : This function is called when a new connection arrives on the
 *                service port. If the function returns 1 the connection is accepted
 *                otherwise it is closed.
 * Argumnents   : string ip - The source ip address
 *                int port  - The source port
 */
int
valid_incoming_service(string host, int port)
{
    if (host == "::1" || host == "127.0.0.1")
        return 1;
    return 0;
}

#if 0
/*
 * Function name: valid_save_binary
 * Description  : This function is called when a file has ordered the GD
 *                to save a binary image of the program. This might not
 *                be allowed by any and every file so master is asked.
 * Arguments    : string filename - the filename of the object.
 */
int
valid_save_binary(string filename)
{
    return 1;
}

/*
 * Function name: valid_save_binary
 * Description  : This function is called when a file has asked to inherit
 *                object. This might not be allowed by any and every file so
 *                master is asked.
 * Arguments    : object ob - the object to inherit withing to inherit.
 *                string inherit_filename - the filename to be inherited.
 */
int
valid_inherit(object ob, string inherit_file)
{
    return 1;
}

/* ob trying to load file */
int
valid_load(object ob, string file)
{
    return 1;
}
#endif

/*
 * Function name:   master_reload
 * Description:     Called from GD after a reload of the master object
 */
void
master_reload()
{
}

/*
 * Function name: recreate
 * Description  : Re-initializes the gamedriver and reloads the data file.
 *                It is called from the gamedriver when the MASTER object
 *                is reloaded (e.g. by an archwizard doing development).
 *                It will not not preload the preload files.
 */
void
recreate(object old_master)
{
    create();
    game_started = 0;
    start_boot(1); /* Do not preload. */
    game_started = 1;
#ifdef UDP_ENABLED
#ifdef UDP_MANAGER
    udp_manager = UDP_MANAGER;
#endif UDP_MANAGER
#endif UDP_ENABLED
}

/*
 * Function name: incoming_udp
 * Description:   Called from GD if a udp message has been received. This
 *                can only happen if CATCH_UDP_PORT has been defined in
 *                the GD's config.h file.
 * Arguments:     from_host: The IP number of the sending host
 *                message:   The message sent.
 */
void
incoming_udp(string from_host, string message)
{
#ifdef UDP_ENABLED
    if (stringp(udp_manager))
    {
        udp_manager->incoming_udp(from_host, message);
    }
#ifdef LOG_LOST_UDP
    else
    {
        set_auth(this_object(), "#:root");
        log_file(LOG_LOST_UDP, "(" + from_host + ") " + message + "\n", -1);
    }
#endif LOG_LOST_UDP
#endif UDP_ENABLED
}


/*
 * Function name: incoming_mssp
 * Arguments    : MSSP protocol request
 * Returns      : Mapping with MSSP data
 */
mapping
incoming_mssp(object ob)
{
    // No MSSP for you!
    return ([ ]);
    // return MSSP->mssp_data(ob);
}


/*
 * Function name: remove_interactive
 * Description  : Called from GD if a player logs out or goes linkdead. If
 *                the player quit the game, we don't do anything.
 * Arguments    : object ob    - the player that leaves the game.
 *                int linkdead - true if the player linkdied.
 */
static void
remove_interactive(object ob, int linkdied)
{
    ob->remove_object();
    return;
}

/*
 * Function name: gamedriver_message
 * Description  : This function may (only) be called by the gamedriver to
 *                give a message to all players if that is necessary.
 * Arguments    : string str - the message to tell the people
 */
static void
gamedriver_message(string str)
{
    users()->catch_tell(str);
}

/*
 * Function name: runtime_error
 * Description  : In case a runtime error occurs, we tell the message to
 *                the people who need to hear it.
 * Arguments    : string error   - the error message.
 *                object ob      - the object that has the error.
 *                string program - the program name of the error.
 *                string file    - the filename of the error.
 */
static void
runtime_error(string error, object ob, string prog, string file)
{
    string fmt_error;
    string path = "";
    string fname = "<???>";

    fmt_error =
        "Runtime error: " + error +
        "       Object: " + fname +
        "\n      Program: " + prog +
        "\n         File: " + file + "\n";

    if (this_interactive())
    {
#ifdef DEBUG_MODE_ENABLED
        this_interactive()->catch_tell("\n\n" + fmt_error + "\n");
        return;
#else
        /* Tell the mortal player an error occured, but not which error. */
        this_interactive()->catch_tell("Your sensitive mind notices " +
            "a wrongness in the fabric of space.\n");
#endif
    }

    set_auth(this_object(), "root:root");

    path += "/log";
    if (file_size(path) != -2)
    {
        mkdir(path);
    }
    path += "/runtime";

    write_file(path, ctime(time()) + "\n" + fmt_error + "\n");
}

/*
 *    ----------------------------------------------------------------
 *    The code below this divisor is never called from the gamedriver.
 *    ----------------------------------------------------------------
 */

/*
 * Function name: remove_binary
 * Description  : This function removes a binary file from the game. This
 *                is (presently) necessary when updating a file because
 *                otherwise the binary isn't updated when you move an older
 *                file over it.
 * Arguments    : string path - the fully qualified path to the file,
 *                     excluding the "/binaries" part.
 * Returns      : int 1/0 - success/failure.
 */
public int
remove_binary(string path)
{
    /* Add the .c suffix if necessary. */
    if (!wildmatch("*.c", path))
    {
        path = path + ".c";
    }

    /* We don't have to check for .. constructs here, since the gamedriver
     * will not allow those.
     */
    return rm("/binaries" + path);
}

/*
 * Function name: log_syslog
 * Description  : Write a message to a log in the system log file. It may
 *                only be called from code in the /secure, /cmd and /std
 *                directories.
 * Arguments    : string file - the path to the log file to write into.
 *                string text - the message to record.
 *                int length: The cycle size to apply to the log. The limit
 *                    may be maximized in the local.h settings of the mud.
 *                 -1 : maximum/unlimited cycle size is used.
 *                  0 : default cycle size is used.
 *                 >0 : specified cycle size is used.
 */
public varargs void
log_syslog(string file, string text, int length = 0)
{
    string fname = calling_program();

    if ((fname[0..6] != "secure/") &&
        (fname[0..3] != "cmd/") &&
        (fname[0..3] != "std/"))
    {
        return;
    }

    log_file(file, text, length);
}

/*
 * Function name: log_public
 * Description  : Write a message to a log in the public log file. It may
 *                only be called from code in the /secure and /std
 *                directories. Cycling logging is applied as per default.
 * Arguments    : string file - the path to the log file to write into.
 *                string text - the message to record.
 */
void
log_public(string file, string text)
{
    int msize;
    string fname = calling_program();

    file = OPEN_LOG_DIR + "/" + file;

    if ((fname[0..6] != "secure/") &&
        (fname[0..3] != "std/"))
    {
        return;
    }

#ifdef CYCLIC_LOG_SIZE
    msize = CYCLIC_LOG_SIZE["root"];

    if (msize > 0 && (file_size(file) > msize))
        rename(file, file + ".old");
#endif /* CYCLIC_LOG_SIZE */

    set_auth(this_object(), "#:root");
    write_file(file, text);
}

/*
 * Function name: query_start_time
 * Description  : Return the time when the game started.
 * Returns      : int - the time.
 */
public int
query_start_time()
{
    if (game_start_time)
    {
        return game_start_time;
    }

    /* Find the time-stamp from the log file that marks the game starts. */
    int theport = debug("mud_port");
    if (theport != 0)
    {
        string game_start = GAME_START + "." + theport;
        if (file_size(game_start) > 0)
        {
            game_start_time = file_time(game_start);
            return game_start_time;
        }
    }

    /* This value will be wrong if the master has been updated. */
    game_start_time = object_time(this_object());
    return game_start_time;
}

/*
 * Function name: query_uptime_limit
 * Description  : The (irregular) uptime after which this game is being
 *                rebooted. This uptime is counted from the start of the
 *                game.
 * Returns      : int - the (irregular) uptime, or 0.
 */
public int
query_uptime_limit()
{
    return uptime_limit;
}

/*
 * Function name: set_uptime_limit
 * Description  : Schedules a reboot in the future. This function may only be
 *                called from the normal wizard soul, i.e. from the 'shutdown'
 *                command.
 * Arguments    : int t - the time() value to reboot at.
 */
public void
set_uptime_limit(int t)
{
    /* Must be at least 1 hour to go. */
    uptime_limit = max((t - query_start_time()), 3600);
}

/*
 * Function name: master_shutdown
 * Description  : Perform the final shutdown. This function may only be
 *                called from the armageddon object.
 * Returns      : 1 - Ok, 0 - No shutdown performed.
 */
public int
master_shutdown(string reason)
{
    /* This MUST be a this_object()->
     * If it is removed the game wont go down, so hands off!
     */
    this_object()->do_debug("shutdown");
    return 1;
}

/*
 * Function name: request_shutdown
 * Description  : When a wizard wants to shut down the game, this
 *                function is called to invoke Armageddon. The function
 *                should be called from the shutdown command in
 *                WIZ_CMD_NORMAL.
 * Arguments    : string reason - the reason to shut down the game.
 *                int    delay  - the delay in minutes.
 */
public void
request_shutdown(string reason, int delay)
{
    // No armageddon object just shutdown...
}

/*
 * Function name: calcel_shutdown
 * Description  : When the wizard has second thoughts and does not want
 *                to shut the game down after all, this function is
 *                called. The function should be called from
 *                WIZ_CMD_NORMAL.
 */
public void
cancel_shutdown()
{
    // No armageddon just shutdown...
}

/*
 * Function name: do_debug
 * Description  : This function is a front for the efun debug(). You are
 *                only allowed to call debug() through this object because we
 *                need to make some security checks.
 * Arguments    : string icmd - the debug command.
 *                mixed a1    - a possible argument to debug().
 *                mixed a2    - a possible argument to debug().
 *                mixed a3    - a possible argument to debug().
 * Returns      : mixed - the relevant return value for the particular
 *                        debug command.
 */
varargs mixed
do_debug(string icmd, mixed a1, mixed a2, mixed a3)
{
    string euid = geteuid(previous_object());

    /*
     * Some debug() commands are blocked entirely.
     * Usually when they are broken in the GD etc.
     */
    if (IN_ARRAY(icmd, DEBUG_BLOCKED))
    {
        return 0;
    }

    /* Some debug() commands are not meant to be called by just anybody. Only
     * 'root' and the administration may call them.
     */
    if (IN_ARRAY(icmd, DEBUG_RESTRICTED))
    {
        if ((euid != ROOT_UID) &&
            (previous_object() != this_object()) &&
            (previous_object() != find_object(SIMUL_EFUN)))
        {
            return 0;
        }
    }

    /* Since debug() returns arrays and mappings by reference, we need to
     * process the value to make it secure, so people cannot alter it.
     */
    return secure_var(debug(icmd, a1, a2, a3));
}

/*
 * Function name:  check_memory
 * Description:    Checks with 'debug malloc' if it is time to reboot
 * Arguments:      dodecay - decay xp or nto.
 *                   The limit can be defined in config.h as MEMORY_LIMIT
 */
public void
check_memory(int dodecay)
{
    int uptime;

    /* Is the game too big? */
    if (query_memory_percentage() >= 100)
    {
        memory_failure();
    }
}

/*
 * Function name: query_prevent_shadow
 * Description  : This function will prevent shadowing of this object.
 * Returns      : int 1 - always.
 */
nomask int
query_prevent_shadow()
{
    return 1;
}
