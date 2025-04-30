#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer, Gi0/0 interface");
    set_long(BSN("You find yourself at the foot of an enormous wall of roaring flames, the kind that would "+
            "make even the bravest packet think twice before proceeding. The heat pulses in waves, making you "+
            "feel like you're sweating, though it's all very metaphorical, of course. All around you, "+
            "stern-looking entities hover, casting suspicious glances at every passing packet as if expecting "+
            "someone to suddenly burst into flames (which, given the surroundings, seems quite plausible). "+
            "The atmosphere is tense, and at the base of a towering staircase leading upwards, a queue of "+
            "jittery packets stands nervously, waiting for their turn to ascend to loftier levels."));

    add_item(({"wall", "flames", "wall of flames", "light"}),
        BSN("The wall stretches endlessly in every direction, a blazing barrier that seems intent on keeping "+
            "whatever lies beyond it well protected. A staircase runs alongside the wall, disappearing into "+
            "the blinding brightness of the flames, though where it leads is anyone's guess."));

    add_item(({"packet", "packets", "queue"}),
        BSN("The packets here are a jittery bunch, lined up with all the enthusiasm of someone waiting to "+
            "see the dentist. Despite the crowded space, there's a nervous hush, as if everyone's too afraid "+
            "to breathe too loudly in case they draw unwanted attention."));

    add_item(({"entities"}),
        BSN("These are the data world's equivalent of the stern headmaster, floating around with an air of "+
            "strict authority. Their job is to ensure that everything is in order and that no packet steps "+
            "out of line — literally or metaphorically."));

    add_item(({"stair", "stairs", "staircase", "side", "flame wall side"}),
        BSN("A daunting staircase climbs alongside the wall of flames, leading upwards into the unknown. The "+
            "light from the flames is so intense that it's hard to see where the stairs end, but the guard at "+
            "the bottom is meticulously checking each packet's credentials, ensuring that only those deemed "+
            "worthy can pass."));

    add_item(({"higher levels", "higher level", "level", "levels"}),
        BSN("The higher levels are obscured by the intense light of the flames. Whatever lies up there remains "+
            "hidden, shrouded in mystery and more than a little heat."));

    add_exit(NODES + "fw1_gi00_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link0", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "fw1_gi00_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x21}));
    set_ip(({128,32,137,12,255}));
    set_hostname("fw1");
}
