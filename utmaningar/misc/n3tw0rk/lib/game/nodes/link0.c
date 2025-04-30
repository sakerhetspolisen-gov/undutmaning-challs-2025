#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void
create_node()
{
    ::create_node();
    set_short("In a network cable");

    set_long(BSN("In the form of electrons, surging forward through a narrow copper cable, you and other bits "+
                 "of data are floating along. Cramped though it may be, there's still a noticeable amount of "+
                 "space around you. The electrical impulses driving you onward are relentless, pushing you to "+
                 "keep moving along. The cable, an ethereal tunnel of sorts, stretches out into the distance, "+
                 "vanishing in both directions."));

    add_item(({"cable", "tunnel"}),
        BSN("The cable encases you and your fellow packets as you journey through it. It extends endlessly in both directions, "+
            "its form as indistinct as your own nebulous state of consciousness. This is the network's lifeline, guiding you onward."));
    
    add_item(({"data","peer","peers"}),
        BSN("Other packets accompany you on this journey, each varying in content and size. They rush alongside you, "+
            "their destinations unknown but their movement unwavering."));
    
    add_item(({"impulse","impulses"}),
        BSN("You can't see the impulses, but you can certainly feel them, an unseen force propelling you ever forward. "+
            "Their urgency is undeniable, compelling you to continue your journey."));
    
    add_item(({"space"}),
        BSN("There's still a surprising amount of space in this cable, suggesting that this section of the network isn't heavily trafficked. "+
            "It gives you the fleeting impression that you're in a quieter, more neutral zone, far from the chaotic computer downstream."));

    add_exit(NODES + "evil_layer1", "downstream", 0, 0);
    add_exit(NODES + "hub1", "upstream", 0, 0);
}
