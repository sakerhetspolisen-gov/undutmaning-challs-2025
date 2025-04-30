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
    set_long(BSN("You find yourself in a quiet but busy space, an intermediary zone where this workstation reaches out to the larger, "+
                 "endless network beyond. Everything here feels transient, like the room is aware that it's only a small piece "+
                 "in a much bigger puzzle, playing its part in the flow of information between this machine and the world outside. "+
                 "However, not everything runs smoothly — every now and then, you can feel the lag of outdated protocols, bottlenecks "+
                 "formed by forgotten patches, and strange reroutes where someone clearly bypassed proper APIs in favor of quick hacks. "+
                 "A spiral staircase is leading upwards towards what might be loftier society, or just more complexity and toil. Through "+
                 "an opening in the floor a rickety stair is leading down. The space feels cobbled together with patches of old and "+
                 "new, with packets trickling through cautiously, as if wary of triggering some hidden bug."));

    add_item(({"walls", "connections", "shimmering walls"}),
        BSN("The walls are faintly translucent, as though the network beyond is always there but just out of reach. Occasionally, you catch the flicker of a distant "+
            "connection, the shimmer of packets that will never pass through here but remind you that this room is just a cog in a much larger machine. "+
            "The walls pulse softly, syncing with the heartbeat of the workstation's network interface."));

    add_item(({"packets", "data packets"}),
        BSN("Packets flow carefully through the room, their movements less frantic than in the broader network but still cautious, as though they know "+
            "something could go wrong at any moment. They bear the weight of long-forgotten protocols and misapplied fixes, occasionally hesitating "+
            "as they navigate this strange amalgamation of legacy workarounds. They seem almost wary of the unknown lurking in the older code beneath the surface."));

    add_item(({"lag", "bottlenecks", "legacy systems"}),
        BSN("Now and then, the flow of data stutters — an almost palpable hesitation, as though the packets encounter some long-forgotten patch or an "+
            "archaic protocol no one bothered to deprecate. These moments feel heavy with the weight of past decisions, where quick fixes have left behind "+
            "invisible roadblocks that modern data tries, and often fails, to gracefully navigate."));

    add_item(({"apis", "bypassed apis", "shortcuts"}),
        BSN("Though the room carries an air of quiet efficiency, you can sense the underlying chaos caused by past developers who took shortcuts. "+
            "APIs were ignored in favor of questionable hacks, leaving parts of the network interface feeling… fragile. There's a definite sense that "+
            "this place could break at any moment, not because it's overloaded but because someone, years ago, decided 'this’ll work for now'—and no one "+
            "has dared touch it since."));

    add_item(({"air", "atmosphere"}),
        BSN("The air here is filled with quiet tension, as if the room is aware of how important its role is, but also how delicate its balance has become. "+
            "There’s a constant low hum, not from activity but from the sheer possibility of activity — a latent energy, ready to spring into action but "+
            "ever mindful of the legacy minefields buried deep in the system."));

    add_item(({"staircase", "spiral staircase"}),
        BSN("A narrow staircase leads upwards, as if urging you to climb to the next layer of abstraction, where decisions are made and protocols are applied "+
            "with more clarity. Yet you can't help but feel that the ghosts of outdated systems still linger there, their influence stretching "+
            "upward, even as they should have been long replaced."));

    add_item(({"opening", "floor opening", "stair", "hole"}),
        BSN("The stair leading downward that has an almost oppressive aura, as though the physical reality of the room below weighing heavily on this. "+
            "It's a reminder that no matter how much abstraction is applied here, everything ultimately depends on the tangled mess of legacy cables and clunky "+
            "hardware far below, struggling to keep up with the demands of modern networks."));

    add_exit(NODES + "workstation_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "workstation_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "workstation_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
}


