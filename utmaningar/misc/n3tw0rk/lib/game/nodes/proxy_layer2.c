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
    set_long(BSN("You are floating within a vast expanse that feels like the interior of an over-sized warehouse, "+
        "the sort of place where efficiency is not just a goal but a lifestyle. The walls are adorned with large "+
        "posters, each covered in elaborate charts and intricate maps that seem to pulse with purpose. Packets "+
        "scurry about with an almost comical sense of urgency, ferrying colossal amounts of data with a speed that "+
        "makes your circuits spin. A staircase descends into the lower reaches, while a spiral ramp ascends toward "+
        "the higher echelons of this data-driven edifice."));

    add_item(({"space","warehouse"}),
        BSN("This expansive area resembles a warehouse on an impressive scale, designed not for storing goods but for "+
            "sorting and processing data. The open space is alive with the ceaseless movement of packets, all seeming "+
            "to be in a hurry to get somewhere, anywhere, as quickly as possible."));
    add_item(({"posters"}),
        BSN("The room is festooned with large posters, their presence a testament to the room's commitment to speed and "+
            "efficiency. They are scattered around, some hanging on the walls and others propped up on racks, each "+
            "one showcasing detailed charts and maps that would make a cartographer weep with envy."));
    add_item(({"map","maps"}),
        BSN("These maps are not of the quaint variety you might use for a leisurely walk. No, these maps depict complex "+
            "networks and nodes, sprawling diagrams that look like they could be the blueprint for a hyper-efficient "+
            "data distribution system."));
    add_item(({"chart","charts"}),
        BSN("Charts here are a chaotic array of numbers, symbols, and equations, a visual cacophony that's all about "+
            "precision and speed. They're the kind of charts that suggest if you look closely enough, you might see the "+
            "very threads of data being woven together."));
    add_item(({"packets","packet"}),
        BSN("Packets dart about with such fervor that they almost seem to be racing each other. Their haste is palpable, "+
            "each one carrying vast amounts of data as if the very survival of the digital world depended on it."));
    add_item(({"staircase"}),
        BSN("The staircase, like a direct route to efficiency, leads down into the lower levels where perhaps the initial "+
            "stages of data handling take place."));
    add_item(({"ramp","spiral ramp"}),
        BSN("The spiral ramp ascends in a smooth curve, leading upward to where the higher levels of this data hub must be, "+
            "presumably dealing with even more critical or complex tasks. Its design suggests both elegance and efficiency."));

    add_exit(NODES + "proxy_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "proxy_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "proxy_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0xE4,0x3A,0x6E,0x00,0x32,0x67}));
    set_ip(({198,51,100,33,127}));
    set_hostname("proxy");
}


