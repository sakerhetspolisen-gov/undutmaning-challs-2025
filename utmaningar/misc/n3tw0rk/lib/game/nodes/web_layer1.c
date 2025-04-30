#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer");
     set_long(BSN("You've found yourself at the lively entrance of what might be the hottest nightclub in the network. "+
        "The building before you exudes an irresistible allure, with flashing lights and pulsating beats echoing from within. "+
        "Packets, like eager party-goers, are lined up in a queue, each one wriggling with anticipation to join the festivities inside. "+
        "The staircase leading up is flanked by shimmering lights and a vibrant crowd of packets waiting their turn to be admitted. "+
        "The buzz of excitement is palpable, and you can almost feel the rhythm of the digital beats even from here."));

    add_item(({"queue","line","waiting line"}),
        BSN("A vibrant queue of packets stretches before you, each one fizzing with anticipation. They wait their turn to enter "+
            "the dazzling nightclub above, their eagerness palpable as they shuffle and sway in time with the distant music.")); 

    add_item(({"staircase","stairs"}),
        BSN("A grand, elegant staircase ascends from the entrance, illuminated by dazzling lights. It's the gateway to the digital party, "+
            "where every step closer means one step nearer to the high-energy scene above.")); 

    add_item(({"entrance"}),
        BSN("The entrance at the top of the staircase promises a world of excitement and revelry. Through the glowing archway, you can "+
            "hear the thumping beats and see flashing lights, a siren call for packets eager to join the celebration.")); 

    add_item(({"lights","flashing lights"}),
        BSN("Flashing lights of every hue dance across the entrance, creating a dazzling spectacle. They pulse and shimmer in rhythm with "+
            "the music, setting the stage for the excitement that awaits inside.")); 

    add_item(({"packets","packet"}),
        BSN("Packets drift around the queue, each one vibrating with the excitement of the impending revelry. They seem almost alive, "+
            "their journey a blend of anticipation and eagerness as they await their chance to join the digital festivities.")); 

    add_exit(NODES + "web_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link5", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "web_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x14,0x22,0x03,0x5A,0xB2}));
    set_ip(({198,51,100,15,127}));
    set_hostname("web");
}
