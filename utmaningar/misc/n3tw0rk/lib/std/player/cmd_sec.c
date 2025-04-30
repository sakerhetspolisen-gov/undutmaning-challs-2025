/*
 * player/cmd_sec.c
 *
 * This is a subpart of player_sec.c
 *
 * Some standard commands that should always exist are defined here.
 * This is also the place for the quicktyper command hook.
 */

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <log.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <time.h>

/*
 * Prototypes.
 */
nomask int quit(string str);
nomask int dbg_mess(string msg);

/*
 * Function name: cmd_sec_reset
 * Description  : When the player logs in, this function is called to link
 *                some essential commands to him.
 */
static nomask void
cmd_sec_reset()
{
    add_action(quit,            "quit");
    
    // add_action(dbg_mess,        "msg"); - DBG-message disabled

    init_cmdmodify();

}

/*
 * Function name: check_valid_startloc
 * Description  : This function checks if the player is standing on a spot
 *                where recover may happend
 * Returns      : int - if TRUE, it's allowed to recover.
 *                 (1 start location, 2 armageddon, 3 wizard)
 */
nomask int
check_valid_startloc()
{
    object obj;
    string env;

    /* Check for recoverable surroundings */
    if (objectp(obj = environment(this_object())))
    	env = MASTER_OB(obj);
    else
	    return 0;

    if (IN_ARRAY(env, SECURITY->query_list_def_start()) ||
        IN_ARRAY(env, SECURITY->query_list_temp_start()))
    {
	    return 1;
    }

    return 0;
}

/*
 * Function name: quit
 * Description:	  The standard routine when quitting. You cannot quit while
 *                you are in direct combat.
 * Returns:	  1 - always.
 */
nomask int
quit(string str)
{
    object *inv;
    int    startloc, seconds, manual;
    string pname;

    /* Consider all items in the deep inventory of the player. If something is
     * in a container, it's considered individually and moved to the top of
     * the inventory if it needs to be dropped. */
    inv = deep_inventory(this_object());
    
    /* Give the message before resetting the race name (but after dropping of
     * items). */
    say( ({ QN + " leaves the network.\n",
	    QN + " leaves the network.\n",
	    "" }) );

    tell_object(this_object(), "Goodbye. Until next time.\n");

    /* Remove the objects. If there are some persistant objects left,
     * hammer hard and they will go away eventually.
     */
    inv->remove_object();
    inv = filter(inv, objectp);

    foreach(object item: inv)
    {
        /* This is the hammer. */
        SECURITY->do_debug("destroy", item);
    }

    this_object()->add_prop("_mark_quit", 1);
    this_object()->remove_object();
    return 1;
}

/*
 * Function name: block_action
 * Description:   Players can block certain actions on being performed on them.
 * Arguments:     string cmd    - the name of the executed command
 *                object target - the target in your inventory, if 0 it's you.
 *                object actor  - the command performer
 *                int cmd_type  - the command attributes (from cmdparse.h)
 * Returns:       0 - command allowed
 *                1 - command blocked, no error message provided
 *                string - command blocked, use string as error message.
 */
public mixed
block_action(string cmd, object target, object actor, int cmd_type)
{
    if ((cmd_type & ACTION_INTIMATE) && query_option(OPT_BLOCK_INTIMATE))
    {
        return actor->QN + " is not in the mood for intimate behaviour.\n";
    }
    return 0;
}

int dbg_mess(string msg)
{
    if(!msg)
    {
        return notify_fail("You must specify a message.\n");
    }

    string report;
    tell_object(this_object(),"You leave some feedback. Thank you!\n");

    report = "----" + ctime(time()) + " " + query_ip_name() + " [" + file_name(environment(this_object())) + "]\n" + msg + "\n"; 

    write_file("/log/feedback.log",report);   
    return 1; 
}