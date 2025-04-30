#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
    add_action("do_listen","listen");
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the Edge process");
    set_long(BSN("You find yourself in a cavernous, neon-lit room that buzzes with the frenetic energy of constant distraction. "+
                 "Huge, floating panels display rapidly changing images — some sharp, colorful, and inviting, others flashing "+
                 "so quickly you barely have time to register them before they're replaced. Voices drift in from invisible "+
                 "speakers, an overlapping cacophony of adverts, music, and disembodied narrators enthusiastically explaining "+
                 "the benefits of products you never knew you needed. It's a place built for entertainment and information, "+
                 "where the user's attention is a commodity to be constantly courted, and every pixel is working overtime to "+
                 "keep you here just a little longer. Packets come and go in a constant flow through an opening in the floor. "+
                 "Somewhere, likely through the tube leading away downwards, lies the content itself — remote, distant, but somehow "+
                 "feeding into this dazzling spectacle you find yourself immersed in."));

    add_item(({"room", "space", "place"}), 
        BSN("The room feels less like a coherent space and more like a labyrinth of glowing panels and disembodied sounds, each "+
            "fighting for your attention. It's as though the very air hums with data, constantly shifting and rearranging to suit "+
            "the whims of some distant, unseen user. You almost forget that you're inside a process, with its own logic and "+
            "purpose — instead, it feels like you've wandered into a sensory carnival where everything is bright, loud, "+
            "and fleeting."));

    add_item(({"panels", "floating panels", "screens", "images"}), 
        BSN("These large, floating panels shift constantly, displaying everything from cooking tutorials to cat videos. They "+
            "seem almost alive, feeding on the user's clicks and scrolls, as if vying for your attention, each one trying to "+
            "be more colorful or louder than the next."));

    add_item(({"text", "scrolling text"}), 
        BSN("A wall of scrolling text provides a never-ending stream of information — some of it useful, most of it not. It's "+
            "the kind of information you never knew you needed to know, and yet now that you're seeing it, you somehow feel "+
            "compelled to read just a little bit more."));

    add_item(({"neon lights", "glow", "lights"}), 
        BSN("The room is bathed in a soft, unnatural neon glow that seems designed to keep you alert and engaged, even though "+
            "it makes everything look a little too shiny, a little too artificial, and perhaps a little too much like an "+
            "amusement park for data."));

    add_item(({"opening", "tube", "opening in the floor"}), 
        BSN("The opening in the floor is a gaping maw that leads into the unknown, with a tube descending downwards into the "+
            "dark, far below the glitzy spectacle of this room. The tube is a conduit, not for show but for purpose, ferrying "+
            "data and content back and forth from a place far away."));

    add_item(({"packets", "data packets", "flow of packets"}), 
        BSN("Packets zip in and out of the room with dizzying speed, little pulses of information, each with a mission of its "+
            "own. Some appear to hurry eagerly, as if bursting with importance, while others seem to lag, perhaps confused or "+
            "overwhelmed by the spectacle."));

    add_item(({"user", "unseen user"}), 
        BSN("The user is an unseen presence, a shadowy figure whose influence is felt in the rapid changes and flashing "+
            "distractions that fill the room. Somewhere beyond this space, they sit in front of a screen, clicking, scrolling, "+
            "and absorbing whatever fleeting entertainment or information catches their eye. Though never physically present, "+
            "the room exists for them — an elaborate performance aimed at holding their attention for just a few moments longer."));
    
    add_exit(NODES + "workstation_layer3", "down", 0, 0);
    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
}

int do_listen(string str)
{
    if(!str || str == "to voices" || str == "to sounds" || str == "to music" || str == "to adverts")
    { 
        write(BSN("The room is filled with an endless stream of voices, sound effects, and music tracks that come and go with "+
                  "every flicker of the display panels. They seem to echo from nowhere in particular, blending into an incoherent "+
                  "but oddly hypnotic din that makes focusing on anything else rather difficult."));
        return 1;
    }
    return notify_fail("Listen to what?\n");
}