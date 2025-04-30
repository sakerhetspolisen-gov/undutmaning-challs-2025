/*
 * /std/player/savevars_sec.c
 *
 * This is a subpart of player_sec.c
 *
 * All the variables that are to be saved to the players save file
 * are defined here.
 */

#include <files.h>
#include <formulas.h>
#include <language.h>
#include <log.h>
#include <macros.h>
#include <options.h>
#include <ss_types.h>
#include <std.h>

/*
 * Non-static global variables. These variables are stored in the players
 * savefile.
 */
private string  name,                   /* Name of the player */
                path,                   /* Current directory path */
                adj_desc,               /* The adjectives describing player */
                default_start_location, /* Start location of player */
                temp_start_location,    /* Temp start location */
                login_from,             /* Host wherefrom last logged in */
                options,                /* Options for the player */
                *auto_shadow;           /* Our loyal shadows */

private mixed   saved_props;            /* List of saved properties */

private int     age_heart,              /* # of heartbeats (== 2 seconds) */
                creation_time,          /* Player creation time() */
                login_time,             /* Last time logging in */
                logout_time;            /* Last time logging out / saving */
private object  logout_location;        /* The last logout / saving location */
private mapping m_vars,                 /* Some less used variables. */
                m_nick_list;            /* Nick(name)s for the quicktyper */

/*
 * Static global variables. These variables are used internally and are not
 * stored in the players savefile.
 */
private static string   cap_name;       /* Capitalized name of the player */
private static int      age_time,       /* the last time the age was updated */
                        cl_width,       /* width of the client. */
                        cl_height;      /* height of the client. */

/*
 * Prototypes.
 */
nomask public int remove_autoshadow(mixed shadowfile);
public nomask void fixup_screen();

// Needed since we have no player file to restore
void save_vars_sec_init(void)
{
}


/*
 * Function name: player_save_vars_reset
 * Description  : Reset the private time-related functions.
 */
static nomask void
player_save_vars_reset()
{
    age_time = time();
}

/*
 * Name of the player.
 * This can only be called from player_sec.
 
static nomask void
set_name(string n)
{
    name = n;
    cap_name = capitalize(n);

    ::set_name(name, 1);
}
*/
static varargs void
add_name(mixed name, int noplural)
{
    ::add_name(name, noplural);
}

/*
 * Function name:   remove_name
 * Description:     Remove a certain name
 * Arguments:       n: A string or a pointer of strings of names
 */
nomask void
remove_name(mixed n)
{
    ::remove_name(n);
}

/*
 * Function name:   set_adj
 * Description:     'go through function' for storing the adjectives. Also
 *                  sets the adjectives to 'adj_desc' if no arg given.
 *                  No more than 2 adjectives of a total length of 35
 *                  characters is allowed.
 * Arguments:       str: Adjectives to pass to ::set_adj() or 0.
 * Returns:         1 if setting was succesfull, 0 otherwise
 */
public int
set_adj(string *arr)
{
    string *adj;
    int i, len;

    if (arr)
    {
        adj = query_adj(1);

        if (sizeof(adj) + sizeof(arr) > 2)
            return 0;

        for (i = 0; i < sizeof(adj); i++)
            len += strlen(adj[i]);
        for (i = 0; i < sizeof(arr); i++)
            len += strlen(arr[i]);
        if (len > 33)
            return 0;

        ::set_adj(arr);
        adj_desc = query_adj(1);
        return 1;
    }
    else
        ::set_adj(adj_desc);

    return 1;
}

/*
 * Function name:   remove_adj
 * Description:     'go through function' for removing the adjectives.
 * Arguments:       str: The adjective string to remove.
 */
public void
remove_adj(string str)
{
    ::remove_adj(str);

    adj_desc = query_adj(1);
}

/*
 * Function name: query_real_name
 * Description  : Gives back the real name of a player, e.g. "fatty". The
 *                capitalized version can be found with query_cap_name().
 *                Note that query_name() should not be used for identification
 *                purposes as it may return a name as "ghost of X".
 * Returns      : string - the lower case name of the player.
 */
nomask public string
query_real_name()
{
    return lower_case(name);
}


/*
 * Function name:   query_path
 * Description:     Gives back the path of the current directory.
 * Returns:         The path string
 */
public string
query_path()
{
    if (path)
        return path;
    return path;
}

/*
 * Function name: query_cap_name
 * Description  : Gives back the capitalized name of a player. By definition
 *                this is the same as capitalize(query_real_name()). The
 *                result is buffered for speed reasons.
 * Returns      : string - the capitalized name string.
 */
public nomask string
query_cap_name()
{
    return cap_name;
}

/*
 * Function name:   query_default_start_location
 * Description:     Gives back the default start location of a player when
 *                  she enters the game.
 * Returns:         The string with the filename of the startup-room.
 */
public string
query_default_start_location()
{
    return default_start_location;
}

/*
 * Function name:   query_temp_start_location
 * Description:     Gives back the temporary start location of a player when
 *                  she enters the game.
 * Returns:         The string with the filename of the startup-room.
 */
public nomask string
query_temp_start_location()
{
    return temp_start_location;
}

/*
 * Function name:   query_age
 * Description:     Gives the age of the living in heart_beats.
 * Returns:         The age.
 */
public nomask int
query_age()
{
    int age_delta = (time() - age_time) / 2;
    age_heart += age_delta;
    age_time += age_delta * 2;
    return age_heart;
}

/*
 * Function name:   set_path
 * Description:     Sets the current path of a player.
 * Arguments:       str: Pathstring
 */
public nomask void
set_path(string str)
{
    path = str;
}

/*
 * Function name:   set_cap_name
 * Description:     Sets the capitalized name of a player. This is derived
 *                  from query_real_name(), which returns a lowercase name.
 */
public nomask void
set_cap_name()
{
    cap_name = capitalize(query_real_name());
}

/*
 * Function name:   set_default_start_location
 * Description:     Sets a new default startup location for a player. The
 *                  default startup-location must have been approved of by
 *                  an archwizard or keeper.
 *                  The path must be _without_ the trailing .c of the filename.
 * Arguments:       str: the startup room's filename string
 * Returns:         0 if the string was not an accepted location,
 *                  1 when set.
 */
public nomask int
set_default_start_location(string str)
{
    if (!VALID_DEF_START_LOCATION(str))
    {
        return 0;
    }

    default_start_location = str;
    return 1;
}

/*
 * Function name:   set_temp_start_location
 * Description:     Sets a new temporary startup location for a player. The
 *                  next time the player logs in, she will enter the game at
 *                  the set temporary location, which is then discarded. The
 *                  temporary startup-location must have been approved of by
 *                  an archwizard or keeper.
 *                  The path must be _without_ the trailing .c of the filename.
 * Arguments:       str: the startup room's filename string
 * Returns:         0 if the string was not an accepted location,
 *                  1 when set.
 */
public nomask int
set_temp_start_location(string str)
{
    if (strlen(str) && !VALID_TEMP_START_LOCATION(str))
    {
        return 0;
    }
    temp_start_location = str;
    return 1;
}

/*
 * Function name: set_notify
 * Description  : Set notify status
 * Arguments    : int flag - The current status
 */
public nomask void
set_notify(int flag)
{
    if (flag)
        m_vars[SAVEVAR_NOTIFY] = flag;
    else
        m_delkey(m_vars, SAVEVAR_NOTIFY);
}

/*
 * Function name: query_notify
 * Description  : Query the notify status.
 * Returns      : int - the setting
 */
public nomask int
query_notify()
{
    return m_vars[SAVEVAR_NOTIFY];
}

/*
 * Function name: set_creation_time
 * Description  : Sets the creation time of the player to now.
 */
static nomask void
set_creation_time()
{
    if (!creation_time)
        creation_time = time();
}

/*
 * Function name: query_creation_time
 * Description  : Gives back the creation time of the player.
 * Returns      : int - the time.
 */
public nomask int
query_creation_time()
{
    return creation_time;
}

/*
 * Function name:   set_login_time
 * Description:     sets the time of the login
 * Arguments:       (int) t: the login time
 */
static nomask varargs void
set_login_time(int t = time())
{
    login_time = t;
}

/*
 * Function name:   query_login_time
 * Description:     Gives back the login-time.
 * Returns:         The login-time.
 */
public nomask int
query_login_time()
{
    return login_time;
}

/*
 * Function name:   set_login_from
 * Description:     Sets from which site the player is logged in.
 */
public nomask void
set_login_from()
{
    login_from = query_ip_name(this_object());
}

/*
 * Function name:   query_login_from
 * Description:     shows from which site the player is logged in
 * Returns:         A string with the site name.
 */
public nomask string
query_login_from()
{
    return login_from;
}

/*************************************************************************
 *
 * Auto shadow routines.
 *
 */

/*
 * Function name: add_autoshadow
 * Description  : Add a shadow to the shadow list. In string form the shadow
 *                has the syntax <filename>:<argument> and the <argument> may
 *                not exceed a length of 80 characters.
 * Arguments    : mixed shadowfile - the shadow-object or the filename of the
 *                   shadow-object.
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
add_autoshadow(mixed shadowfile)
{
    string *sh;

    if (objectp(shadowfile))
        shadowfile = MASTER_OB(shadowfile) + ":";

    sh = explode(shadowfile, ":");
    if (sizeof(sh) > 1 && strlen(sh[1]) > 80)
        return 0;

    /* There can only be one. */
    while(remove_autoshadow(shadowfile));

    if (!sizeof(auto_shadow))
        auto_shadow = ({ shadowfile });
    else
        auto_shadow += ({ shadowfile });
    return 1;
}

/*
 * Function name:   remove_autoshadow
 * Description:            Remove a shadow from the shadow list
 * Arguments:       shadowfile: The shadow-object or the filename of the
 *                              shadow_object.
 * Returns:         1 if the removing was successfull,
 *                  0 otherwise
 */
nomask public int
remove_autoshadow(mixed shadowfile)
{
    string *sh;
    int i;

    if (objectp(shadowfile))
        shadowfile = MASTER_OB(shadowfile);

    sh = explode(shadowfile, ":");

    for (i = 0 ; i < sizeof(auto_shadow) ; i++)
    {
        if (sh[0] == explode(auto_shadow[i], ":")[0])
        {
            auto_shadow = exclude_array(auto_shadow, i, i);
            return 1;
        }
    }
    return 0;
}

/*
 * Function name:   query_autoshadow_list
 * Description:            Gives back the list of autoshadow object filenames.
 * Returns:         The autoshadow list
 */
nomask public string *
query_autoshadow_list()
{
    return secure_var(auto_shadow);
}

/*
 * Function name: set_option
 * Description  : Set a player option.
 * Arguments    : int opt - the option to set (use <options.h>).
 *                int val - the value to set the option to.
 * Returns      : int 1 - success, 0 - fail.
 */
public nomask int
set_option(int opt, int val)
{
    switch (opt)
    {
    case OPT_MORE_LEN:
        if ((val > 100) || (val < 1))
            return 0;

        options = sprintf("%3d", val) + options[3..];
        /* Backward compatibility. */
        add_prop(PLAYER_I_MORE_LEN, val);
        return 1;

    case OPT_SCREEN_WIDTH:
        if ((val != -1) && ((val > 200) || (val < 40)))
            return 0;

        options = options[..2] + sprintf("%3d", val) + options[6..];
        fixup_screen();
        return 1;

    case OPT_ALWAYS_KNOWN:
        add_prop(LIVE_I_ALWAYSKNOWN, val);
        /* Intentional fallthrough. */

    case OPT_ALL_COMMUNE:
    case OPT_AUTO_PWD:
    case OPT_AUTOLINECMD:
    case OPT_AUTOWRAP:
    case OPT_BLOCK_INTIMATE:
    case OPT_BRIEF:
    case OPT_ECHO:
    case OPT_GAG_MISSES:
    case OPT_GIFT_FILTER:
    case OPT_MERCIFUL_COMBAT:
    case OPT_NO_FIGHTS:
    case OPT_SHOW_UNMET:
    case OPT_SILENT_SHIPS:
    case OPT_TABLE_INVENTORY:
    case OPT_TIMESTAMP:
    case OPT_UNARMED_OFF:
    case OPT_WEB_PERMISSION:
        if (val)
            options = efun::set_bit(options, OPT_BASE + opt);
        else
            options = efun::clear_bit(options, OPT_BASE + opt);
        return 1;

    default:
        return 0;
    }

    /* Not reached. */
    return 1;
}

/*
 * Function name: query_option
 * Description  : Return a player option.
 * Arguments    : int opt - the option (use defines in <options.h>).
 *                int setting - if true, return the unmodified value.
 * Returns      : int - the value of the option.
 */
public nomask varargs int
query_option(int opt, int setting)
{
    if (!strlen(options))
        options = OPT_DEFAULT_STRING;

    switch (opt)
    {
    case OPT_MORE_LEN:
        /* Use the live value from the client, if it exists. */
        if (cl_height && !setting)
            return cl_height;
        return atoi(options[..2]);

    case OPT_SCREEN_WIDTH:
        /* Use the live value from the client, if it exists. */
        if (cl_width && !setting)
            return cl_width;
        return atoi(options[3..5]);

    case OPT_WHIMPY:
        return atoi(options[6..7]);

    case OPT_ALL_COMMUNE:
    case OPT_AUTO_PWD:
    case OPT_AUTOLINECMD:
    case OPT_AUTOWRAP:
    case OPT_BLOCK_INTIMATE:
    case OPT_BRIEF:
    case OPT_ECHO:
    case OPT_GAG_MISSES:
    case OPT_GIFT_FILTER:
    case OPT_MERCIFUL_COMBAT:
    case OPT_NO_FIGHTS:
    case OPT_SHOW_UNMET:
    case OPT_SILENT_SHIPS:
    case OPT_TABLE_INVENTORY:
    case OPT_TIMESTAMP:
    case OPT_UNARMED_OFF:
    case OPT_WEB_PERMISSION:
    case OPT_ALWAYS_KNOWN:
        return efun::test_bit(options, OPT_BASE + opt);

    default:
        return 0;
    }

    /* Not reached. */
    return 0;
}
