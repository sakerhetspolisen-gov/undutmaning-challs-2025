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
    set_long(BSN("You find yourself standing on a platform that clings to the side of a steel-beam tower "+
        "like an unwelcome parasite. The platform, much like the rest of the tower, exudes an aura of "+
        "hostility. The railing that runs along the edge is topped with vicious spikes, as if the structure "+
        "itself is telling you to stay back — or else. The few packets that drift through here move with a "+
        "grim determination, their digital faces set in expressions that range from anxious to outright "+
        "terrified. Occasionally, an official-looking packet descends from above, only to quickly vanish "+
        "down the staircase that spirals into the shadowy depths below. A ladder, bolted unceremoniously "+
        "to the side of the tower, leads up to another equally unwelcoming platform above."));

    add_item(({"tower","platform","room"}),
        BSN("The platform circles the tower like a forgotten appendage, its function unclear, "+
            "but its intent unmistakable. It feels like a checkpoint, a place where packets are "+
            "scrutinized, perhaps even judged, before being allowed to continue. The spikes atop "+
            "the railing are not just for show — they're a clear warning: proceed with caution, if at all."));

    add_item(({"perimeter","rim","outer rim","railing","spikes"}),
        BSN("The railing encircles the platform, not so much for safety as for deterrence. "+
            "The spikes are sharp, cruel, and unapologetic. This is not a place that wants visitors, "+
            "and the railing ensures that even the most foolhardy of packets think twice before "+
            "venturing too close to the edge."));

    add_item(({"packet","packets"}),
        BSN("The few packets that dare to linger here seem to be in a hurry, as if the very air is "+
            "pushing them onwards. Their expressions tell a story of fear, of a place where one "+
            "lingers only when they have no other choice."));

    add_item(({"official packet","official looking packet","official","entity"}),
        BSN("Every so often, a packet in a crisp uniform arrives from above. These official "+
            "packets have an air of authority, moving quickly and purposefully as if they have "+
            "no time to waste in a place like this. They vanish down the staircase almost as soon "+
            "as they appear, leaving behind a lingering sense of unease."));

    add_item(({"staircase"}),
        BSN("The staircase spirals downwards, its steps disappearing into the darkness below. "+
            "It's not an inviting path, but it's the only way down — and you can't help but feel that "+
            "whatever lies beneath is watching, waiting."));

    add_item(({"ladder"}),
        BSN("The ladder is bolted to the side of the tower with all the charm of a no-nonsense "+
            "executioner. It leads upwards to another platform, equally hostile and foreboding, "+
            "promising no respite from the pervasive sense of danger that hangs over this place."));
        
    add_exit(NODES + "ips_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "ips_layer1", "down", "@@down_check", 0);

    create_admin(NPC + "ips_layer2");

    set_mac(({0x3C,0x7D,0x1C,0xF3,0x44,0x0C}));
    set_ip(({198,51,100,5,127}));
    set_hostname("ips");
}


