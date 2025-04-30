#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

object clerk;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("In the transportation layer");
    set_long(BSN("You find yourself in what might be mistaken for a bustling shipping depot, if only "+
        "instead of boxes there were bundles of bits and bytes. The entire room hums with activity, a "+
        "constant whirlwind of packets moving with purpose. A team of meticulous entities, overseen by "+
        "a grumpy administrator with an air of absolute authority, ensure that every packet is in its "+
        "proper place. Amidst this controlled chaos, a circular ramp leads downwards while two impressive "+
        "tubes rise upwards. One tube, looking well-travelled and slightly tarnished, seems to have been "+
        "in use for quite some time, while the other, gleaming with a recent polish, suggests a more "+
        "modern route.")); 

    add_item(({"shipping depot","depot","staging area","area","room"}),
        BSN("The staging area is a hive of activity. Packets are constantly coming and going, with entities "+
            "flitting about to ensure smooth operations. The air buzzes with the relentless motion of packets, "+
            "their energy palpable and slightly dizzying."));
    add_item(({"entities","overseers"}),
        BSN("These entities are the epitome of efficiency, floating about with a clear sense of duty. They ensure "+
            "that packets are adhering to their designated paths, their movements precise and calculated."));
    add_item(({"packets","packet"}),
        BSN("Packets are darting around with impressive speed. They flow up the tubes, down the ramp, and all around "+
            "the room in a ceaseless ballet of data delivery."));
    add_item(({"ramp"}),
        BSN("A circular ramp descends from this frenetic hub, leading to the lower levels where the groundwork is laid."));
    add_item(({"tubes","tube"}),
        BSN("Two prominent tubes rise from the floor, each marked with a sign. One tube, showing its age with a "+
            "slightly worn exterior, is marked \"1080\". The other, sparkling and newly installed, is labeled \"22493\"."));
    add_item(({"old tube","older tube","worn tube"}),
        BSN("The older tube is a testament to reliability, marked with \"1080\". It looks well-used and dependable, "+
            "leading to destinations known only to those who venture upwards."));
    add_item(({"new tube","newer tube","sparkling tube"}),
        BSN("The newer tube, marked with \"22493\", gleams with recent installation. It offers a modern conduit, "+
            "leading to destinations that are likely the latest in data routing."));
    add_item(({"sign","signs"}),
        BSN("The signs on the tubes clearly mark their routes: \"1080\" for the older tube and \"22493\" for the newer tube."));
    add_item(({"clipboard","clipboards"}),
        "@@netinfo");
    
    // Several different connections to the same procsss...
    add_exit(NODES + "proxy_layer4", "1080", "@@up_check", 0);
    add_port(1080,"TCP");
    // Listening port 1080 captures the established connection as well
    // add_port(1080,({ ({ 198,51,100,199 }), 43891 }));
    add_exit(NODES + "proxy_layer4", "22493", "@@up_check", 0);
    add_port(22493,({ ({ 23,253,58,227 }), 443 })); 

    add_exit(NODES + "proxy_layer2", "down", "@@down_check", 0);

    clerk = clone_object("/game/npc/proxy_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_hostname("proxy");
    set_mac(({0xE4,0x3A,0x6E,0x00,0x32,0x67}));
    set_ip(({198,51,100,33,127}));
    set_extra_msg_netinfo(BSN("While the administrator seems to be a bit extra occupied you take the oppertunity "+
        "to sneak a peek of its clipboard:"));
}
