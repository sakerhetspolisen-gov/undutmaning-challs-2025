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
    set_long(BSN("You find yourself in a room that feels oddly spacious yet suffocating, like it's waiting for something to happen. "+
                 "Thin, shimmering threads of connectivity drift from wall to wall, each one trembling nervously as if they might "+
                 "snap at any moment. The place has a certain quiet tension about it, the way a gallery waits for the critics to "+
                 "arrive — or a piece of abstract art waits for someone to understand it. Every corner of the room feels like it's "+
                 "just shy of reaching out, trying to make contact with something far beyond the room itself, yet somehow failing to "+
                 "fully grasp the world outside. Through an opening in the floor a ladder is leading downwards and another ladder "+
                 "is leading upwards through a similar opening in the ceiling."));

    add_item(({"threads", "shimmering threads", "connections"}),
        BSN("The threads of connection shimmer faintly, casting tiny sparks as data tries, and often fails, to glide smoothly along. "+
            "Some of these threads are tangled, caught up in knots that no one has dared to untangle in years. They jitter and flicker like "+
            "a nervous artist presenting their latest chaotic masterpiece to an audience that just doesn't quite get it. Each thread carries "+
            "the weight of packets that seem uncertain of their destination, some wandering off-course only to circle back in frustration."));

    add_item(({"walls", "corners"}),
        BSN("The walls of this place are oddly non-committal, stretching into what feels like the void, as if they know they're supposed to be "+
            "connected to something bigger but can't quite make up their minds. In one corner, an old, dust-covered port blinks occasionally, "+
            "as though it's trying to remember the last time it successfully routed anything without tripping over a legacy protocol."));

    add_item(({"room"}),
        BSN("The room feels like it's waiting for something. The air is thick with potential, but also with that creeping dread you feel "+
            "when you're about to hit 'Send' on a massive print job, unsure if the printer will embrace it or explode in a puff of smoke. "+
            "There's a faint smell of ozone, the sort of scent that hangs around in places where electricity has been forced to perform "+
            "unnatural acrobatics just to keep a half-functional connection alive."));

    add_item(({"ports", "connections", "link"}),
        BSN("There are a few ancient ports embedded in the walls, some blinking lazily as if they're considering whether to let data through "+
            "or not. Others are completely dead, like forgotten attempts to modernize that were abandoned after a few too many 'temporary' fixes. "+
            "These connections seem reluctant, as if they've been burned before and now trust no one."));

    add_item(({"ladder", "opening", "openings", "ladders", "opening in the floor", "opening in the ceiling"}),
        BSN("Two rusted ladders cling to the openings in the floor and ceiling, their metal frames bent and twisted as if they've been "+
            "climbed far too many times. The ladder downwards seems especially worn, like it's been forced to carry a great deal more "+
            "traffic than it was designed for. The one leading up creaks slightly, as though unsure whether it's worth the effort to support "+
            "yet another packet of data or soul seeking higher ground."));


    add_exit(NODES + "printer_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "printer_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "printer_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0xC0,0xFB,0xF9,0x0B,0x72,0x9E}));
    set_ip(({198,51,100,182,255}));
    set_hostname("printer");
}


