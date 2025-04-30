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
    set_long(BSN("You find yourself near the summit of the steel beam tower, standing on a platform "+
        "that seems to vibrate with barely-contained tension. Above you, a swirling mass of smokelike "+
        "material pulses ominously, its dark form roiling with an unsettling energy. The platform itself "+
        "is barren, save for a switchboard affixed to the tower's skeletal structure. The floor is pockmarked "+
        "with blackened patches, each one a silent testament to the violent forces that seem to haunt this place. "+
        "The air is thick with the scent of burnt circuits, and the occasional flash of red lightning within "+
        "the cloud above casts eerie shadows across the platform. A ladder leads downwards through a gap in the "+
        "floor, offering the only escape from this malevolent height."));

    add_item(({"platform","room","area"}),
        BSN("The platform is eerily empty, save for a few trembling packets clustered near the ladder, "+
            "as if seeking shelter from the oppressive atmosphere. Scattered across the surface are "+
            "numerous blackened patches, as if the platform itself has borne witness to countless unseen conflicts."));

    add_item(({"tower","body"}),
        BSN("The steel beam tower rises just a short distance further before ending abruptly, as if "+
            "even it dares not reach into the seething mass above. The beams are forged from some "+
            "strange, dull metal that seems to absorb the light around it, adding to the sense of unease."));

    add_item(({"metal"}),
        BSN("The metal is lifeless and dull, almost as if it exists only in some half-real state. "+
            "It feels as though it's not fully anchored in this world, much like everything else here."));

    add_item(({"cloud","swirling cloud"}),
        BSN("The swirling cloud of smokelike material hangs menacingly above, constantly shifting "+
            "and churning as though it harbors some dark, violent secret. Flashes of red lightning "+
            "crackle through its depths, each burst of light a reminder that this is a place where "+
            "even the air itself might turn against you."));

    add_item(({"red light","light","flashes","flashes of light","flashes of red light"}),
        BSN("The red lightning is sharp and malevolent, cutting through the cloud like a knife "+
            "through flesh. Whatever is happening inside that cloud, it is not something you want "+
            "to be part of. The very sight of it makes your digital form quiver."));

    add_item(({"patch","patches","black patch","black patches"}),
        BSN("The blackened patches are scattered across the platform like the remnants of some "+
            "dark ritual. They reek of burnt circuits and despair, as though each one marks the "+
            "spot where something — perhaps someone — met a violent end."));

    add_item(({"switchboard"}),
        BSN("The switchboard is bolted to the tower's frame, its screen glowing faintly. It's the "+
            "only source of light here apart from the ominous flashes from the cloud above. The "+
            "screen displays information, but what it shows might be more than you want to know."));

    add_item(({"screen","switchboard screen","information"}),
        "@@netinfo");

    add_exit(NODES + "ips_layer2", "down", "@@down_check", 0);

    create_admin("/game/npc/ips_layer3");

    set_hostname("ips");
    set_mac(({0x3C,0x7D,0x1C,0xF3,0x44,0x0C}));
    set_ip(({198,51,100,5,127}));
    set_extra_msg_netinfo("You look at what the screen on the switchboard is showing:\n");
}
