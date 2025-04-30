#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER2;

public void
create_node()
{
    ::create_node();
    set_short("In the network layer");
   set_long(BSN("You find yourself in what can only be described as the digital equivalent of a nightclub's wardrobe area. "+
        "It's an enormous space, brimming with the frenetic energy of packets shedding their bytes and picking up new ones "+
        "as though they were swapping outfits. Every time a packet passes through, it's as if it's changing costumes for the "+
        "next big event, leaving a trail of discarded data like confetti. "+
        "Busy digital entities scurry about, performing their duties with the sort of efficiency that suggests they've had a "+
        "strict code of conduct drilled into them since they were mere bytes. Above you, a circular staircase winds its way "+
        "upward, promising more of the same dazzling chaos and excitement, while lights and sounds hint at the revelry beyond."));

    add_item(({"wardrobe","room"}),
        BSN("This isn't a wardrobe in the traditional sense, but the way packets are constantly swapping their bits and bytes "+
            "feels a bit like the bustling cloakroom of a particularly fashionable nightclub. There's no coat rack, but the "+
            "sense of busy, transformative activity is very much the same.")); 

    add_item(({"packets","packet"}),
        BSN("Packets are everywhere, like excited club-goers in a queue. They come and go, shedding their old selves and "+
            "adopting new ones with a flair that's almost theatrical. The whole scene is a display of digital choreography.")); 

    add_item(({"stairs","exit"}),
        BSN("The exit, or rather the way down, is marked by a staircase that leads back to where you came from. It's like a "+
            "staircase in a grand theatre, taking you back to the mundane world from the world of flashing lights and noise.")); 

    add_item(({"clothes","coats"}),
        BSN("There aren't any actual clothes here, but the resemblance to a wardrobe is uncanny. It's as if the packets are "+
            "dressing up or down in their digital attire.")); 

    add_item(({"entities","entity"}),
        BSN("The entities buzzing around are like the club's efficient staff, making sure every packet is dressed just right for "+
            "its journey. They work with a purpose that's almost admirable, if somewhat lacking in enthusiasm.")); 

    add_item(({"staircase"}),
        BSN("The circular staircase leading upwards is like the grand entrance to the next level of the nightclub. The sounds "+
            "and lights coming from above suggest a lively and exciting scene waiting just out of sight.")); 

    add_exit(NODES + "web_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "web_layer1", "down", "@@down_check", 0);

    create_admin(NPC + "web_layer2");

    set_mac(({0x00,0x14,0x22,0x03,0x5A,0xB2}));
    set_ip(({198,51,100,15,127}));
    set_hostname("web");
}


