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
    set_long(BSN("You find yourself in some kind of control room, a place where packets flit about like over-excited bees, "+
                 "zipping to and fro with the urgency of an office worker late for a meeting. The walls are adorned with "+
                 "colorful flowcharts that seem to mock you with their complexity, hinting at the tangled web of protocols "+
                 "governing this digital realm. The faint rustle of paperwork from an overburdened admin desk drifts in the air, "+
                 "mixed with the distant hum of overworked data. It feels like a chaotic symphony, composed by someone who's "+
                 "had far too much coffee and not enough sleep. A well-worn ladder leads downward through a hatch in the "+
                 "floor, while a spiral staircase curls upward, beckoning you to venture further."));

    add_item(({"flowcharts", "colorful flowcharts", "diagrams"}),
        BSN("The flowcharts plastered across the walls are a tangle of lines, arrows, and cryptic abbreviations, designed more "+
            "to confuse than to clarify. They weave and twist like the mind of someone who has long lost the plot of whatever "+
            "problem they were trying to solve, yet they persist, mocking you with their indecipherable complexity."));

    add_item(({"packets", "data packets", "digital messengers"}),
        BSN("Packets whiz by like tiny messengers caught in a never-ending delivery service, some with the frenetic energy of "+
            "first-day-on-the-job interns, while others drag along wearily, as though they've been running the same route for "+
            "far too long. They each carry precious loads of data, yet seem completely unaware of the chaos swirling around them."));

    add_item(({"admin desk", "desk", "overburdened admin desk"}),
        BSN("The admin desk is a chaotic masterpiece of procrastination, laden with half-finished projects, hastily scrawled "+
            "sticky notes, and an impressive collection of coffee mugs, each in a different state of emptiness. A keyboard sits "+
            "like a battle-worn soldier, its keys having endured years of furious typing, debugging, and what can only be "+
            "described as frustrated bashing."));

    add_item(({"ladder", "hatch", "floor hatch"}),
        BSN("The ladder looks like it's been climbed many times, its rungs worn smooth by the frequent trips of whoever calls "+
            "this chaotic corner of the network home. It leads down through a hatch in the floor, where perhaps more mysteries "+
            "(or more paperwork) await."));

    add_item(({"spiral staircase", "staircase", "spiral stairs"}),
        BSN("The spiral staircase looks ancient and slightly askew, winding upward in a fashion that suggests whoever designed "+
            "it was probably in the middle of debugging something and thought, 'Good enough.' It beckons you to climb, though "+
            "one can't help but feel it might lead to yet more confusion and frantic, coffee-fueled coding sessions."));

    add_exit(NODES + "admin_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "admin_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "admin_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x10,0xE3,0x8C,0xEA,0x51}));
    set_ip(({198,51,100,194,255}));
    set_hostname("admin");
}


