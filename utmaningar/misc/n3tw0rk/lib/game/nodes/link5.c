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
    set_long(BSN("You find yourself speeding through a network cable that hums with the energy of anticipation. "+
        "Packets whiz by you in a blur, each one carrying a sense of urgency as they make their way towards their "+
        "destinations. The tunnel around you feels alive with a palpable buzz, as if something exciting is about "+
        "to happen. Downstream, you catch glimpses of a vibrant structure that resembles a lively entertainment "+
        "venue, full of dazzling lights and sounds. Upstream, a bustling intersection hints at the dynamic flow of "+
        "data converging from various directions."));

    add_item(({"tunnel","pipe"}),
        BSN("The tunnel is a high-speed conduit where packets zip past in a frenzied dance, their sheer velocity "+
            "giving you a sense of the excitement they're carrying towards their destinations.")); 

    add_item(({"packet","packets"}),
        BSN("The packets, each a small bundle of data with a purpose, streak through the tunnel with a sense of "+
            "urgency. They carry with them a hint of what's to come, as if the real action is just around the corner.")); 

    add_item(({"structure","entertainment venue"}),
        BSN("Downstream, a lively structure beckons with the allure of an entertainment venue. The flashing lights "+
            "and distant sounds hint at the thrill and spectacle waiting beyond the tunnel.")); 

    add_item(({"intersection"}),
        BSN("Upstream, the busy intersection is a hub of activity where data streams converge, creating a sense "+
            "of buildup and excitement. The dynamic flow here suggests that something significant is in the works.")); 

    add_exit(NODES + "switch1", "upstream", 0, 0);
    add_exit(NODES + "web_layer1", "downstream", 0, 0);

    object ob = clone_object(NPC + "ips_packet_link5");
    ob->move(TO,1);
}
