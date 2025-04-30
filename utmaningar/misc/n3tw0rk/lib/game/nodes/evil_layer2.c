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
    set_long(BSN("For a moment, your senses are overwhelmed by a disorienting swirl of impressions. "+
             "Gradually, a strange order begins to emerge from the chaos. You find yourself in a place "+
             "where the very fabric of reality seems dedicated to weaving vast, intricate webs of addresses "+
             "and pathways. Fleeting images, like ghostly maps, flicker in and out of existence, while tables "+
             "appear before you, their fields flashing with numbers that seem to mean everything and nothing "+
             "all at once, before vanishing just as suddenly. All around you, lumps of data are either bundled "+
             "together or split apart, only to be whisked away upwards or downwards into the unknown."));
    
    add_item(({"stack","network stack"}),
        BSN("You quickly grasp that you're in the network stack of a rather dubious computer. This stack "+
            "is a sophisticated construct, teeming with code that's busily enabling the computer to communicate "+
            "with other machines on the network. And by the look of it, these communications might not all be "+
            "entirely above board."));
    
    add_item(({"packet", "packets"}),
        BSN("Packets of data appear out of thin air before you, or float in from above and below. They hover for "+
        "just an instant, as if deciding their fate, before darting off in various directions with an urgency that "+
        "suggests they're on a mission — perhaps one best kept secret."));
    
    add_item(({"computer"}),
        BSN("You're deep within the memory of a computer that exudes an air of mischief. Although you can't see "+
            "much of its broader workings from where you are, you can sense that this machine is up to something "+
            "that might not be entirely legitimate."));
    
    add_item(({"surroundings","data"}),
        BSN("You're enveloped by a tumultuous sea of data, constantly appearing, disappearing, and shifting in form. "+
        "There's a palpable sense of purpose and order here, though it's clear that this order is tightly controlled—"+
        "and possibly aimed at something that lies in a moral gray area."));
    
    add_item(({"structures","pathways"}),
        BSN("The sensation of vast, imaginary structures and pathways is almost overwhelming, though they remain "+
        "just beyond the edge of your perception, as if they represent something much larger, existing somewhere "+
        "else — or perhaps something that shouldn't exist at all."));
    
    add_item(({"maps","tables"}),
        BSN("Ethereal maps and tables flicker into existence around you, only to dissolve moments later. Their "+
        "constant forming and reforming is both awe-inspiring and a bit nauseating, as if the very structure of "+
        "this place is in flux, never quite settling into something concrete and trustworthy."));
    
    add_exit(NODES + "evil_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "evil_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "evil_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_ip(({128,32,137,251,255}));
    set_mac(({0xE0,0x2C,0xB2,0x01,0xC0,0xA2}));

    set_hostname("evil");
}


