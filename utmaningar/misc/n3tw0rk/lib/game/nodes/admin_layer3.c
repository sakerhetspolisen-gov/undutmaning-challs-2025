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
    set_long(BSN("The room feels like a workshop hastily converted into a shrine to network efficiency, with wires and "+
                 "cables snaking about in a way that could only make sense to someone who considers 'neatness' an insult to "+
                 "their technical prowess. A rickety, spiral staircase leads downwards — clearly built without any thoughts of "+
                 "health and safety, but it's probably fine if you have the agility of a ferret. Meanwhile, a sturdy-looking "+
                 "tube, marked with the number '21456' for no apparent reason, extends upwards. In one corner, a blackboard is "+
                 "covered in chalk-dusted network diagrams, connections, and cryptic notes that only the truly initiated "+
                 "would dare to comprehend. The place is a chaotic blend of brilliance and haphazard construction — exactly "+
                 "what you'd expect from a someone who despises GUIs and believes that the terminal is the one true interface.")); 

    add_item(({"cables", "wires", "room", "workshop", "shrine"}),
        BSN("Wires and cables snake across the room, connecting various thingamajigs and whatchamacallits in a way that looks "+
            "almost haphazard, yet everything seems to works with seamless efficiency. It's a testament to the system owner's "+
            "belief that if it's not at least a little chaotic, then you're probably doing it wrong. Each cable is carefully "+
            "labeled, though the labels themselves are cryptic enough to cause confusion for anyone but the owner."));

    add_item(({"thingamajigs", "thingamajig", "whatchamacallits", "whatchamacallit", "lights", "patterns", "machines"}),
        BSN("You can't help but feel dwarfed by the array of thingamajigs and whatchamacallits scattered about the room. Each "+
            "one hums, ticks, or occasionally belches out a puff of something that smells suspiciously like burnt logic. Wires "+
            "coil like serpents, lights blink in patterns far too complex to be accidental, and there's a general sense that "+
            "these machines know exactly what they're doing — though you are completely in the dark."));

    add_item(({"chalkboard", "blackboard", "board"}),
        BSN("The blackboard is covered in white chalk, diagramming the flow of packets through the network with a level of "+
            "abstraction and complexity that only the most dedicated technician would find artistic. You get the impression "+
            "that understanding it fully would take several years of dedicated study — or at least a strong pot of coffee "+
            "and a disdain for simplicity. But perhaps a closer look at the diagrams might enlighten you."));

    add_item(({"stairs", "spiral staircase", "rickety staircase"}),
        BSN("The spiral staircase looks like it was cobbled together from spare parts — which, frankly, it probably was. It "+
            "sways slightly, but it seems to have held up so far. It leads downward to the lower levels, and there's a distinct "+
            "sense that it was designed with the same care one might give to choosing a random password: functionally secure, "+
            "but not exactly elegant."));

    add_item(({"tube", "upward tube"}),
        BSN("The tube leading upwards is marked with the unmistakable declaration: '21456'. There's something about its sturdy, "+
            "no-nonsense construction that suggests it was built to withstand the rigors of proper, command-line-fueled "+
            "connectivity — none of that bloated, inefficient nonsense you'd expect from certain 'other' operating systems."));

    add_item(({"diagram","diagrams"}),
        "@@netinfo");
    
    add_exit(NODES + "admin_layer4_ssh", "21456", "@@up_check", 0);
    add_port(21456,({ ({ 198,51,100,15 }), 22 }));
    
    add_exit(NODES + "admin_layer2", "down", "@@down_check", 0);

    clerk = clone_object(NPC + "admin_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_mac(({0x00,0x10,0xE3,0x8C,0xEA,0x51}));
    set_ip(({198,51,100,194,255}));
    set_hostname("admin");
    set_extra_msg_netinfo(BSN("You ponder the diagrams trying to make sense of it all:"));
}
