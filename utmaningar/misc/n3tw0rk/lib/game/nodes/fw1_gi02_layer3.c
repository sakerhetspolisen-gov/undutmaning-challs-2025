#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

public void
create_node()
{
    ::create_node();
    set_short("In the transport layer, Gi0/2 interface");
    set_long(BSN("You find yourself on a rather spacious platform near the top of the fiery wall, "+
        "where the flames seem almost decorative. Above you, a cloud of swirling data drifts lazily, as if it's "+
        "taking a break from more important tasks elsewhere. Despite the relative quiet, the atmosphere here is one "+
        "of calm focus, a place where things happen without much fanfare. A narrow staircase winds down from the "+
        "platform, and a switchboard stands nearby, its screen pulsating with a steady, reassuring glow."));

    add_item(({"platform","room","location"}),
        BSN("The platform is wide and open, giving a sense of space that's rare in such a networked environment. "+
            "It's not exactly bustling with activity, but there's a comforting order to it all. If tumbleweeds "+
            "were digital, you might expect one to roll by, just to complete the picture."));

    add_item(({"wall","wall of flames","flames","fire","wall of fire","firewall","fiery wall"}),
        BSN("The firewall looms as impressively as ever, its flames flickering with a kind of restrained energy. "+
            "They ripple and dance, but seem content to simply exist rather than devour anything in their path."));

    add_item(({"staircase"}),
        BSN("The narrow staircase leads downward, inviting you to explore further. It's a bit less traveled, "+
            "but it's clearly well-maintained and ready for use."));

    add_item(({"cloud","data","swirling cloud"}),
        BSN("The swirling cloud of data above you shifts and pulses with the rhythm of mysterious processes. "+
            "It seems to be in no particular hurry, floating there as if enjoying a moment of peace."));

    add_item(({"switchboard"}),
        BSN("The switchboard stands to one side, its screen pulsating softly. It seems almost content in its role, "+
            "continuing its work whether or not anyone is paying attention."));

    add_item(({"screen","pulsating screen"}),
        "@@netinfo");

    add_exit(NODES + "fw1_gi02_layer2", "down", "@@down_check", 0);

    create_admin(NPC + "fw1_gi02_layer3");
    
    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x23}));
    set_ip(({198,51,100,129,255}));

    set_hostname("fw1");
    set_extra_msg_netinfo("You look at the pulsating screen:\n");
}
