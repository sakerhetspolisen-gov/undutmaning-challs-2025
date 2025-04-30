#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer, Gi0/2 interface");
    set_long(BSN("You find yourself at the base of the firewall, where the flames dance and shimmer above. "+
        "Here at the bottom of the network stack, everything feels solid and foundational. The floor beneath "+
        "you is made of sturdy metal, giving a sense of stability and reliability. To one side, a wide, inviting "+
        "tunnel beckons, its mouth open and welcoming, suggesting a smooth transition to other parts of the network. "+
        "A staircase, wide and robust, leads upward, disappearing into the brighter layers above. It's a place where "+
        "the crucial but often overlooked tasks of data transmission take place, and there's a quiet satisfaction in "+
        "being part of this essential infrastructure."));

    add_item(({"platform","room","foot","ground","location"}),
        BSN("The platform here is sturdy, crafted from the same utilitarian metal as the rest of the structure. It's "+
            "the foundation of the network, solid and reliable, where every connection begins its journey. It might "+
            "not be glamorous, but it's essential."));

    add_item(({"wall","firewall","wall of fire","flames"}),
        BSN("The wall of fire looms above, an ever-present reminder of the network's defenses. From here, it's more of "+
            "a reassuring presence than a menacing one, providing a sense of security against the unknown beyond."));

    add_item(({"staircase","staircase up","wide staircase"}),
        BSN("A wide staircase leads upwards from the platform, its steps solid and well-worn. It's a clear path to the "+
            "more complex layers of the network above, offering a sense of progress and upward mobility."));

    add_item(({"tunnel","network cable","cable","inviting tunnel","tunnel entrance"}),
        BSN("The tunnel ahead is wide and welcoming, its entrance open and inviting. It suggests a smooth and easy "+
            "pathway leading off to other parts of the network, a transition from this foundational layer to other areas "+
            "that may hold more intricate operations."));

    add_item(({"hum","electrical hum","currents","electricity"}),
        BSN("The steady hum of electrical currents is a constant background presence here, like the purring of a very "+
            "contented machine. It's a soothing sound, indicative of the flow of data and power that drives the network's "+
            "operations."));


    add_exit(NODES + "fw1_gi02_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link7", "downstream", "@@downstream_check", 0);

    create_admin(NPC + "fw1_gi02_layer1");
    
    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x23}));
    set_ip(({198,51,100,129,255}));

    set_hostname("fw1");
}
