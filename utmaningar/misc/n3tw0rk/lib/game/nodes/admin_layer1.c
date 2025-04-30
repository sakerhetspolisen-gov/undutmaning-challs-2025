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
    set_long(BSN("You find yourself in a cluttered, tangled mess of cables, discarded command prompts, and "+
                 "a slight smell of coffee that's been left sitting far too long. The data flows here with an "+
                 "irregular rhythm, as if begrudgingly obeying orders while muttering under its breath. The whole "+
                 "area feels a bit like several half-hearted projects that never quite saw the light of day. Packets "+
                 "that shuffle through seem to be grumbling about the injustice of it all, occasionally stopping to "+
                 "give you the digital equivalent of a weary sigh. A cluttered desk stands in the middle of an open "+
                 "area, with a bright yellow line drawn on the floor in front of it, a few feet away. A ladder leads "+
                 "upwards through a hole in the ceiling, and an opening in the tangle of cables leads into a tunnel leading "+
                 "upstream."));

    add_item(({"cables", "tangled cables", "wires", "mess", "tangled mess", "mess of cables"}),
        BSN("The cables here are not so much neatly arranged as they are actively avoiding organization. "+
            "They wind in and out of each other, forming knots that would baffle even the most seasoned sailor. "+
            "It's clear that someone, somewhere, has lost control of this situation a long time ago — and simply "+
            "decided to live with it."));

    add_item(({"packets", "data", "digital entities"}),
        BSN("The packets here move sluggishly, with an air of frustration and a sense that they've been here far "+
            "longer than they'd like to admit. Some shuffle along as though resigned to their fate, while others "+
            "seem to be making mental notes to lodge a formal complaint at the first opportunity."));

    add_item(({"coffee", "coffee mugs", "mugs", "mug"}),
        BSN("There's an omnipresent smell of old coffee, the kind that's been left too long on a desk, forgotten "+
            "while some network emergency was being half-heartedly attended to. It's the smell of determination, "+
            "mixed with procrastination, and it lingers like a badge of honor in this corner of the network."));

    add_item(({"desk", "cluttered desk"}),
        BSN("The desk is a monument to organized chaos, strewn with bits of paper, empty coffee mugs, and the "+
            "occasional suspicious snack that has long since given up hope of being eaten. It stands defiantly in "+
            "the center of the room, a bastion of productivity that seems to have never quite reached its full potential."));

    add_item(({"yellow line", "bright yellow line"}),
        BSN("The bright yellow line drawn on the floor is a peculiar sight, as if it was meant to signify some important "+
            "boundary, though it seems to have been ignored by every packet and human alike. Perhaps it was drawn by "+
            "someone in a fit of enthusiasm, or just to confuse newcomers."));

    add_item(({"ladder", "upwards ladder"}),
        BSN("A ladder leads upwards through a hole in the ceiling, offering a route to places unknown. It looks as "+
            "though it has seen better days, much like the administrator's last attempt at cleaning this workspace. "+
            "It beckons you to climb it, though one might question what lies at the top."));

    add_item(({"opening", "opening in the cables"}),
        BSN("An opening in the tangle of cables leads into a tunnel that seems to promise something more organized, or "+
            "perhaps just a different kind of chaos. It's a path taken by packets eager to escape the current chaos, "+
            "though who knows what awaits them downstream?"));

    add_item(({"command prompts", "discarded command prompts", "prompts", "prompt"}),
        BSN("Scattered throughout the room, you see remnants of command prompts abandoned mid-thought, as though the "+
            "administrator had been summoned to a more pressing, or perhaps just more interesting, task. Some of them "+
            "flicker lazily on the floor, as if unsure whether they still have a job to do or if they've been retired "+
            "without notice."));

    add_exit(NODES + "admin_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link9", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "admin_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x10,0xE3,0x8C,0xEA,0x51}));
    set_ip(({198,51,100,194,255}));
    set_hostname("admin");
}
