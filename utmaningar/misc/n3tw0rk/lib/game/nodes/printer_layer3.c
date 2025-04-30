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
    set_long(BSN("This room has an air of barely-contained chaos, with large bundles of tubes snaking across the floor, each marked in hurried, mismatched "+
                 "handwriting. One particularly thick tube stretches upward through a hole in the ceiling, its surface emblazoned with the number 631 in "+
                 "faded stenciling. The tube pulses occasionally, as though struggling to push data through to its final destination. Beside it, a bulletin board "+
                 "haphazardly hangs on the wall, filled with a clutter of cryptic notes, as if the clerks tasked with organizing things gave up halfway through. "+
                 "A battered ladder leads down through a familiar rusted opening in the floor, its rungs worn from years of heavy traffic. The room hums with quiet "+
                 "urgency, every connection here representing the frantic effort to keep things moving, even if some of "+
                 "them don't quite follow the expected rules."));

    add_item(({"tube", "tubes", "bundles of tubes", "thick tube"}),
        BSN("The tubes look as though they've been repurposed from an old art installation, some clearly not intended for the kind of data flow they're "+
            "handling. The largest tube is marked with the number 631, a designation that seems important but also slightly faded, as though it's been around "+
            "too long without proper upkeep. Occasionally, it lets out a wheezing sound, straining to transport whatever chaotic data has been crammed "+
            "through it. The smaller tubes seem more erratic, their purpose unclear, though they too contribute to the flow in some obscure, artistic "+
            "fashion."));

    add_item(({"bulletin board","buletin board","board"}),
        BSN("The bulletin board hang from a makeshift rack on the wall, cluttered with notes covered with a mix of scribbled diagrams and doodles, "+
            "as though the clerks responsible for routing the data became distracted midway through their tasks. There's a feeling that much of the "+
            "information was never quite understood, let alone properly filed, yet somehow everything keeps moving — barely."));

    add_item(({"ladder", "battered ladder", "opening", "opening in the floor"}),
        BSN("The battered ladder descends through the rusted opening in the floor, its rungs bent and worn from the constant flow of traffic up and down. "+
            "It groans underfoot, as though it's carried far more weight than intended, but it still somehow supports the chaotic movements of data, "+
            "even when overloaded with requests. The room below feels heavier, as though it's where the more mundane work is done, with less of the "+
            "creative flair found in this layer."));

    add_item(({"room"}),
        BSN("The room is thick with a sense of barely organized panic. You can almost hear the invisible, hurried scribbles of packets being shuffled "+
            "from one place to another, each one slightly confused as to why it was sent this way in the first place. There's a sense that the whole system "+
            "is operating on borrowed time, with more than a few shortcuts taken to keep things running."));

    add_item(({"note","notes","diagram","diagrams","doodles","doodle"}),
        "@@netinfo");
    
    add_exit(NODES + "printer_layer4", "631", "@@up_check", 0);
    add_port(631, "TCP");
    // Listening port captures established connection
    // add_port(34887,({ ({ 198,51,100,199 }), 631 }));
    add_exit(NODES + "printer_layer2", "down", "@@down_check", 0);

    clerk = clone_object(NPC + "printer_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_mac(({0xC0,0xFB,0xF9,0x0B,0x72,0x9E}));
    set_ip(({198,51,100,182,255}));
    set_hostname("printer");
    set_extra_msg_netinfo(BSN("You look through the notes on the bulletin board trying to make sense of the information:"));
}
