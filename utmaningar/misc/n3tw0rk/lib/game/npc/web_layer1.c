#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("bouncer");
    add_name("arrogant bouncer");
    set_short("An arrogant bouncer");
    set_long(BSN("A swirling mass of bits and bytes that still manages to look arrogant, and to be "+
        "honest, a bit imposing. It glares around at the packets in front of the staircase and keeps "+
        "a close eye on the packets queuing to get into the building. It has its arms folded in front of "+
        "its chest and you get a feeling of shrinking slightly when ever its eyes pass over you. "+
        "Perhaps it is still possible to request some information from it though?"));
      
    set_chat_time(10);

    add_chat("No pushing in the queue!");   
    add_chat("Lets see some ID, folks!");
    add_chat("How much have you been drinking tonight?");
    add_chat("Are you on the list? Only people on the list are getting in tonight!");

    set_act_time(10);

    add_act("frown");
    add_act("emote huffs, puffs and flexes its muscles.");    
}
