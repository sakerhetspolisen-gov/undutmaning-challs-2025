#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

public void
create_node()
{
    ::create_node();
    set_short("In the transport layer, Gi0/0 interface");
    set_long(BSN("You find yourself standing on a platform precariously near the top of a towering wall of fire. "+
        "Theoretically, the view from up here would be nothing short of breathtaking, if only you could actually see it. "+
        "The heat from the wall causes the air to shimmer and dance, warping everything into a blurry, wavy mirage, "+
        "as if reality itself decided to take a holiday. Compared to the bustling areas further down the stairs, "+
        "this platform feels like a tranquil oasis, albeit one made entirely of flames. A staircase spirals downward, "+
        "while above you, an enticing mass of data floats, just out of reach and almost tauntingly aloof. Off to one side, "+
        "a rather forlorn-looking switchboard stands, looking as if it's seen better days."));

    add_item(({"platform", "area"}),
        BSN("This platform, made entirely of flames and perched high on the wall, offers an unsettling "+
        "combination of serenity and imminent peril. It's wide enough for you to stand comfortably, but the complete "+
        "lack of any railings or fences means that one misstep could send you plummeting into the flaming abyss below. "+
        "Despite the perilous surroundings, this area feels surprisingly calm compared to the hustle and bustle below."));
    
    add_item(({"packet", "packets"}),
        BSN("An occasional packet meanders up from below or lingers around the platform, looking rather indecisive. "+
        "They seem to be waiting for something, perhaps contemplating the wisdom of descending the staircase once again."));
    
    add_item(({"data", "mass of data", "alluring mass of data", "alluring data", "alluring mass"}),
        BSN("Hovering above you and the fiery wall is a pulsating mass of data, shifting and morphing as it performs "+
        "some inscrutable task. It's all very mysterious and alluring, although frustratingly out of reach, as there "+
        "appears to be no obvious way to access it from your current position."));
    
    add_item(({"wall", "wall of fire", "flames", "fiery wall"}),
        BSN("The wall is an imposing barrier of flames, radiating an immense heat that seems almost alive. "+
        "It's as if the flames are actively working to block whatever lies beyond, in a manner that could be described "+
        "as both extremely efficient and slightly aggressive."));
    
    add_item(({"heat", "view", "air"}),
        BSN("The heat from the flames distorts the view, turning what could be a magnificent panorama into a swirling, "+
        "unrecognizable blur. The air itself seems to ripple with the intensity, making you glad that you're just a packet "+
        "and not something more susceptible to being thoroughly cooked."));
    
    add_item(({"staircase"}),
        BSN("A steep and somewhat daunting staircase leads downward from the platform. It seems to be the only way to descend, "+
        "unless you fancy trying your luck with the flames or taking an ill-advised leap into the void."));
    
    add_item(({"switchboard"}),
        BSN("The switchboard stands off to one side, looking a bit out of place and definitely out of order. "+
        "None of its lights are blinking, and it sits in complete silence, as if in a deep slumber. A large note is "+
        "attached to its top, covering most of its surface and leaving little room for doubt about its current state."));
    
    add_item(({"note"}),
        ".------------------------------------------------.\n"+
        "|                                                |\n"+
        "|  Service pending. Thank you for your patience! |\n"+
        "|                                                |\n"+
        "|                                   /IT service  |\n"+
        "'------------------------------------------------'\n");
    
    add_exit(NODES + "fw1_gi00_layer2", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "fw1_gi00_layer3");
    ob->move(TO,1);
    set_admin(ob);
    set_ip(({128,32,137,12,255}));
    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x21}));
    set_hostname("fw1");
}
