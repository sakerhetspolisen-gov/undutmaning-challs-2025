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
    set_long(BSN("This is the bottom layer of the tower-like structure where you find yourself. "+
        "All around you are pipe-like constructions, hissing engines, blinking lamps, spinning wheels, "+
        "and an assortment of buttons in every shape, size, and color imaginable. The floor beneath you "+
        "is disturbingly sticky, with patches covered by an unidentifiable, somewhat sinister substance. "+
        "A creaky ladder leads upward, and an opening in one wall offers an escape into what appears to be "+
        "a rounded corridor. Overseeing the frenetic activity in the room is a somewhat frazzled technician, "+
        "who mutters darkly under its breath, clearly burdened by the questionable operations at hand."));

    add_item(({"tower","tower-like structure","structure"}),
        BSN("You quickly gather that this tower-like structure is the network stack of the somewhat disreputable "+
            "computer you're currently inside. It's a marvel of sophisticated code, busily enabling the computer "+
            "to communicate with other devices on the network — though you can't shake the feeling that these "+
            "communications might involve activities best not mentioned in polite company."));
    
    add_item(({"packet", "packets","crowd"}),
        BSN("Packets of data zip up and down the ladder, and shoot in and out through the opening with an urgency "+
            "that suggests they're on missions of dubious legality — if not outright skulduggery."));
    
    add_item(({"computer"}),
        BSN("You're deep within the memory of a computer that radiates an air of malevolent intent. "+
            "You can't see much of its broader workings from your current vantage point, but you know enough to "+
            "sense that this machine is up to something that definitely wouldn't pass a moral audit."));
    
    add_item(({"layer","room","wall","walls"}),
        BSN("The room is hemmed in by a chaotic tangle of pipe-like constructions, cables, and strange gizmos. "+
            "It's crowded, with packets pushing through as they rush off on whatever mission they've been assigned, "+
            "many of which likely involve activities of questionable ethics."));
    
   add_item(({"floor", "sticky substance", "substance"}),
        BSN("The floor is unpleasantly sticky, covered in places by a mysterious, unidentifiable substance "+
            "that gives off a faintly sinister vibe. It feels like it's something best avoided, "+
            "both literally and metaphorically."));


    add_item(({"opening"}),
        BSN("An opening in the wall of pipes and cables leads away from this room into a tubelike corridor. "+
            "This corridor stretches away into the distance in a direction that, for reasons you can't quite explain, "+
            "feels like ‘upstream.'"));
    
    add_item(({"tubelike corridor","corridor"}),
        BSN("The corridor extends away from the room, beyond the opening, heading upstream towards who-knows-what "+
            "nefarious destination."));
    
    add_item(({"construction","constructions","pipe-like construction","pipe-like constructions","engine","engines",
               "lamp","lamps","wheel","wheels","gizmo","gizmos","installation","installations"}),
        BSN("All around you, the various gizmos and installations hiss, blink, flash, and beep with frenetic energy. "+
            "It's a hive of constant activity, with packets rushing through, intent on carrying out operations that "+
            "you suspect would make most law-abiding citizens very uncomfortable."));

    add_exit(NODES + "evil_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link0", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "evil_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0xE0,0x2C,0xB2,0x01,0xC0,0xA2}));
    set_ip(({128,32,137,251,255}));
    set_hostname("evil");
}
