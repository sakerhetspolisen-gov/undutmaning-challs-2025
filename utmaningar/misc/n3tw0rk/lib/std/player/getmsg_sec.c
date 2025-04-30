/*
 * /std/player/getmsg_sec.c
 *
 * This is a subpart of player_sec.c
 *
 * All incoming messages to the player should come through here.
 * All non combat interaction with other players are also here.
 */

#include <options.h>
#include <macros.h>
#include <mail.h>
#include <living_desc.h>
#include <state_desc.h>
#include <stdproperties.h>

/************************************************************************
 *
 * Introduction and met routines
 */

/*
 * Function name: query_met
 * Description  : Tells if we know a certain living's name.
 * Arguments    : mixed who: name or object of living.
 * Returns      : int 1/0 - if true, we know the person.
 */
public int
query_met(mixed who)
{
    return 1;
}

/*
 * Function name: catch_tell
 * Description  : All text printed to this living via either write() or
 *                tell_object() will end up here. Here we do the actual
 *                printing to the player in the form of a write_socket()
 *                that will send the message to the host.
 * Arguments    : string msg - the message to print.
 */
public void
catch_tell(string msg)
{
    write_socket(msg);
}

