/*
 * /cmd/live/info.c
 *
 * General commands for giving and getting game information.
 * The following commands are defined:
 *
 * - bug
 * - date
 * - done
 * - help
 * - idea
 * - praise
 * - sysbug
 * - sysidea
 * - syspraise
 * - systypo
 * - typo
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <log.h>
#include <macros.h>
#include <std.h>
#include <time.h>

/* These properties are only internal to this module, so we define them
 * here rather than in the properties file stdproperties.h.
 */
#define PLAYER_I_LOG_TYPE   "_player_i_log_type"
#define PLAYER_O_LOG_OBJECT "_player_o_log_object"

/* **************************************************************************
 * The constructor.
 */
void 
create()
{
    setuid();
    seteuid(getuid()); 
}

/* **************************************************************************
 * Return a proper name of the soul in order to get a nice printout.
 */
string
get_soul_id()
{
    return "info";
}

/* **************************************************************************
 * This is a command soul.
 */
int
query_cmd_soul()
{
    return 1;
}

/* **************************************************************************
 * The list of verbs and functions. Please add new in alfabetical order.
 */
mapping
query_cmdlist()
{
    return ([
	"date"     : "date",

	"help"     : "help"
     ]);
}

/*
 * Function name: using_soul
 * Description:   Called once by the living object using this soul. Adds
 *		  sublocations responsible for extra descriptions of the
 *		  living object.
 */
public void 
using_soul(object live)
{
}

/* **************************************************************************
 * Here follow some support functions. 
 * **************************************************************************/

/*
 * Function name: done_reporting
 * Descripiton  : This function is called from the editor when the player
 *                has finished the report he or she was writing. If any
 *                text was entered it is logged and the player is thanked.
 * Arguments    : string str - the text entered into the editor.
 */
public void
done_reporting(string str)
{
    int type = this_player()->query_prop(PLAYER_I_LOG_TYPE);
    object target = this_player()->query_prop(PLAYER_O_LOG_OBJECT);

    if (!strlen(str))
    {
	write(LOG_ABORT_MSG(LOG_MSG(type)));
	return;
    }

    /* When making a log about an object, add the room the player is in. */
    if (!target->query_prop(ROOM_I_IS) && environment(this_player()))
    {
        str = "Environment: " + file_name(environment(this_player())) + "\n" + str;
    }

    /* Log the note, thank the player and then clean up after ourselves. */
    SECURITY->note_something(str, type, target);
    write(LOG_THANK_MSG(LOG_MSG(type)));

    this_player()->remove_prop(PLAYER_I_LOG_TYPE);
    this_player()->remove_prop(PLAYER_O_LOG_OBJECT);
}

/* **************************************************************************
 * Now the actual commands. Please add new in the alphabetical order.
 * **************************************************************************/

/*
 * date - get local time & date + uptime information
 */
int
date()
{
    int runlevel;
    int delay, interval;

    write("Local time    : " + ctime(time()) + "\n");
    write("Start time    : " + ctime(SECURITY->query_start_time()) + "\n");
    write("Up time       : " + CONVTIME(time() -
	SECURITY->query_start_time()) + "\n");

    /* Calculate the delay if there's an uptime limit ... */
    if (delay = SECURITY->query_uptime_limit())
    {
        delay += (SECURITY->query_start_time() - time());
    }

    write("Memory usage  : " + SECURITY->query_memory_percentage() + "%\n");

    return 1;
}

/*
 * help - Get help on a subject
 */
int
help(string topic)
{
    string category;
    string *parts;

    if (!strlen(topic))
    {
        topic = "help";
    }
    parts = explode(topic, " ");
    switch(sizeof(parts))
    {
    case 1:
        break;
    case 2:
        category = parts[0];
        topic = parts[1];
        break;
    default:
        notify_fail("Syntax: help <topic>\n");
        return 0;
    }

    setuid();
    seteuid(getuid()); 

    if (file_size(LOCAL_HELP_PATH + "general/" + topic) > 0)
    {
    this_player()->more(read_file(LOCAL_HELP_PATH + "general/" + topic));
    return 1;
    }
    if (file_size("/doc/help/general/" + topic) > 0)
    {
    this_player()->more(read_file("/doc/help/general/" + topic));
    return 1;
    }

    /* Check for a help hook in the room the player is in. */
    if (environment(this_player())->process_help(category, topic))
    {
        return 1;
    }
    /* Check all the objects in the environment of the player. As a side effect
     * this also check this_player() itself, and thus allows the help to exist
     * in a shadow. */
    foreach(object obj: all_inventory(environment(this_player())))
    {
        if (obj->process_help(category, topic))
        {
            return 1;
        }
    }
    /* Check the inventory of the player. */
    foreach(object obj: all_inventory(this_player()))
    {
        if (obj->process_help(category, topic))
        {
            return 1;
        }
    }

    notify_fail("No help on \"" + topic + "\" available" +
        (category ? " in category \"" + category + "\"": "") + ".\n");
    return 0;
}

/*
 * Report - make a report of some kind.
 */
int
report(string str)
{
    object *oblist;
    object target;
    int type = LOG_TYPES[query_verb()];

    /* This should never happen for it means the LOG_TYPES mapping has not
     * been properly setup.
     */
    if (!type)
    {
	notify_fail("Illegal log type \"" + query_verb() +
	    "\". Please report this to an archwizard.\n");
	return 0;
    }

    /* Player may describe the object to make a report about. */
    if (stringp(str))
    {
	/* If there is an argument to the 'done', take it as the message. */
	if (type == LOG_DONE_ID)
	{
	    this_player()->add_prop(PLAYER_I_LOG_TYPE, type);
            this_player()->add_prop(PLAYER_O_LOG_OBJECT,
                environment(this_player()));

	    done_reporting(str + "\n");
	    return 1;
	}

	/* Find the target. */
	if (!parse_command(str, environment(this_player()), "[the] %i", oblist) ||
	    (!sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0))))
	{
	    notify_fail("Make a " + query_verb() + " report about what?\n");
	    return 0;
	}

	/* One target at a time. */
	if (sizeof(oblist) > 1)
	{
	    notify_fail("Select only one target to make a " + query_verb() +
		" report about.\n");
	    return 0;
	}

	target = oblist[0];
	write("Making a " + query_verb() + " report about " +
	    LANG_THESHORT(target)+ ".\n");
    }
    else
    {
	target = environment(this_player());
    }

    /* Add the relevant data to the player. */
    this_player()->add_prop(PLAYER_I_LOG_TYPE, type);
    this_player()->add_prop(PLAYER_O_LOG_OBJECT, target);

    setuid();
    seteuid(getuid());

    clone_object(EDITOR_OBJECT)->edit("done_reporting", "");
    return 1;
}

/*
 * report_done - Report something as done (wizards only)
 */
int
report_done(string str)
{
    /* To mortal players, the command done does not exist so we do not
     * have to give a notify_fail message. Apprentices, pilgrims and
     * retired wizards cannot 'do' anything either.
     */
    
    return 0;
}
