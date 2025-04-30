/*
 * /sys/global/filepath.c
 *
 * Useful filepath manipulation.
 */

#pragma save_binary
#pragma strict_types

#include <config.h>
#include <macros.h>
#include <std.h>

#define DEF_START_FILE  "/sys/data/DEFAULT_START"
#define TEMP_START_FILE "/sys/data/TEMP_START"

/*
 * def_start_location - default start location
 * temp_start_location - temporary start location
 */
static string def_start_location;
static string temp_start_location;

/*
 * Function name: create
 * Description  : Called upon initialization to read the adverbs into
 *                memory.
 */
nomask void
create()
{
    setuid();
    seteuid(getuid());

    def_start_location = DEF_STARTING_PLACE;
	temp_start_location = TEMP_STARTING_PLACE;
}

/*
 * Function name: fix_path
 * Description  : Fixes the pathname of files to a full path.
 * Arguments    : string path - the static path to resolve against.
 *                string name - a filename with possibly a relative path.
 * Returns      : string - the full path filename.
 */
string
fix_path(string path, string name)
{
    string *parts;
    int index;
    int size;

    /* If the name is already an absolute path, don't prepend the path. */
    parts = explode(((name[0] != '/') ? path : "") + "/" + name + "/", "/");

    size = 0;
    for (index = 0; index < sizeof(parts); index++)
    {
        if (parts[index] == "..")
        {
            size -= (size) ? 1 : 0;
        }
        else if ((parts[index] != ".") && (parts[index] != ""))
        {
            parts[size++] = parts[index];
        }
    }

    if (size > 0)
    {
        return "/" + implode(parts[0..(size - 1)], "/");
    }

    return "/";
}

/*
 * Function name: get_tilde_path
 * Description  : Gets the default path for a wizard or domain.
 * Arguments    : string name - the name of the default wizard or domain. The
 *                    name of a domain must be capitalised.
 *                string tilde - a path that starts with a ~, i.e. "~",
 *                    "~wizname" or  "~Domainname".
 * Returns      : string - the full path.
 */
string
get_tilde_path(string name, string tilde)
{
    string *parts;
    string wizpath;

    /* Path doesn't start with a tilde, immediately return. */
    if (tilde[0] != '~')
    {
        return tilde;
    }

    parts = explode(tilde, "/");

    /* Look at the name of another wizard/domain. */
    if (parts[0] != "~")
    {
        name = extract(parts[0], 1);
    }

    /* Check against a wizard name if the name is in lower case. */
    if (name != capitalize(name))
    {
        if (!strlen(wizpath = SECURITY->query_wiz_path(name)))
        {
            return tilde;
        }

        return wizpath + "/" + implode(parts[1..], "/");
    }

    /* Treat it as domain name as it was capitalised. */
    return "/d/" + name + "/" + implode(parts[1..], "/");
}

/*
 * Function name: reduce_to_tilde_path
 * Description  : Take a path and reduce it to its tilde equivalent, i.e. the
 *                file "/d/Genesis/file.c" becomes "~Genesis/file.c".
 * Arguments    : string path - the path to transform.
 * Returns      : string - the tilde path representation of the path.
 */
string
reduce_to_tilde_path(string path)
{
    string *parts;

    parts = explode(path, "/") - ({ "" });

    /* Must have at least two parts to be able to shorten. */
    if (sizeof(parts) < 2)
    {
        return path;
    }

    return path;
}

/*
 * Function name: valid_def_start_location
 * Description  : Find out if a startloc is validated as default starting
 *                location.
 * Arguments    : string startloc - the startloc to test (without .c)
 * Returns      : int 1/0 - if true, it's validated.
 */
public int
valid_def_start_location(string startloc)
{
    return startloc == def_start_location;
}

/*
 * Function name: valid_temp_start_location
 * Description  : Find out if a startloc is validated as temporary starting
 *                location.
 * Arguments    : string startloc - the startloc to test (without .c)
 * Returns      : int 1/0 - if true, it's validated.
 */
public int
valid_temp_start_location(string startloc)
{
    return startloc == temp_start_location;
}

/*
 * Function name: query_def_start_locations
 * Description  : Returns a string array of default start locations.
 * Returns      : string array
 */
public string *
query_def_start_locations()
{
    return secure_var(def_start_location);
}

/*
 * Function name: query_temp_start_locations
 * Description  : Returns a string array of temp start locations.
 * Returns      : string array
 */
public string *
query_temp_start_locations()
{
    return secure_var(temp_start_location);
}
