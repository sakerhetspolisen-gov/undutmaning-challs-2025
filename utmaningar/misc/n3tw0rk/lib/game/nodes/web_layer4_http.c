#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the HTTP process");
        set_long(BSN("You have stepped into what can only be described as the frenetic heart of the digital revelry. "+
        "This place is less a room and more an entire universe of sensory overload, where reality seems to have taken "+
        "a holiday. Gigantic screens loom overhead, each displaying an unending parade of video clips that range from "+
        "the riveting to the absurd. Monstrous speakers, which appear to have been stolen from a dragon's lair, blast "+
        "out music that oscillates between 'epic' and 'slightly deranged.' In the midst of this cacophony, teleprompters "+
        "whirl by, scrolling text at speeds that suggest they're in a hurry to get somewhere else. Packets, those "+
        "elusive digital wanderers, dart in and out of the room through an enormous, gaping hole in the floor. "+
        "New arrivals are pint-sized and chipper, while the departing packets are bloated and groaning under the weight "+
        "of their newfound information. The scene is an exhilarating chaos, where order might exist but is likely "+
        "disguised as one of the revelers."));

    add_item(({"scene","room","entertainment"}),
        BSN("The environment is a sensory assault, with video clips of every imaginable genre playing simultaneously. "+
            "The lights from the screens flash and dance in a manner that would make a disco ball green with envy, "+
            "while the music thunders like an over-caffeinated thunderstorm. It feels like a dance floor where the only "+
            "drink is data and the dance moves are purely algorithmic."));

    add_item(({"information"}),
        BSN("Information is being hurled at you from all directions, as if the very concept of coherence has been "+
            "put on vacation. Trying to focus is like trying to catch a cloud with a butterfly net – the more you "+
            "try, the more it slips away."));

    add_item(({"screens","screen","videos","video"}),
        BSN("The screens display a relentless barrage of video clips, each more captivatingly distracting than the last. "+
            "They range from the mildly interesting to the bizarrely esoteric, making it impossible to concentrate on "+
            "any one thing for more than a moment."));

    add_item(({"speakers","huge speakers"}),
        BSN("The speakers are enormous, as if they were fashioned by someone with a very serious vendetta against "+
            "peace and quiet. They blare a mix of sounds that have no apparent connection to each other, creating a "+
            "cacophony that is both exhilarating and mildly unsettling."));

    add_item(({"teleprompter","teleprompters","text"}),
        BSN("The teleprompters scroll text so fast that it seems to be in a constant state of escape. "+
            "You can catch only glimpses of the text before it vanishes into the digital ether, leaving you wondering "+
            "if it was ever really there."));

    add_item(({"packet","packets"}),
        BSN("Packets come and go with the fervor of enthusiastic partygoers. The new arrivals are small and eager, "+
            "while the ones leaving are so stuffed with data they seem to waddle."));

    add_item(({"floor"}),
        BSN("The floor is a patchwork of digital debris and packet activity, dominated by a large, rather conspicuous "+
            "opening leading downward."));

    add_item(({"opening"}),
        BSN("The opening in the floor is the gateway to the less glamorous layers below, a yawning maw that swallows "+
            "up packets with the same casual indifference that one might show to a stray confetti." ));

    create_admin(NPC + "web_layer4_http");

    add_exit(NODES + "web_layer3", "down", 0, 0);

    set_mac(({0x00,0x14,0x22,0x03,0x5A,0xB2}));
    set_ip(({198,51,100,15,127}));

    set_hostname("web");
}
