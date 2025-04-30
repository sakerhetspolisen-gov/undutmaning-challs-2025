#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void
create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("You find yourself in yet another one of those claustrophobic, pipelike corridors that "+
        "seem to snake their way across the network, carrying out their mysterious and undoubtedly "+
        "important duties. Important, yes, but certainly not glamorous. The decor here leaves much "+
        "to be desired — two stars on Google Maps would be optimistic, especially given the eerie "+
        "silence and the occasional flicker of something moving just out of sight. The tunnel stretches "+
        "upstream towards a bustling interchange and downstream towards a building that exudes a distinct, "+
        "unwelcome aura. The kind of aura that makes you wish you were anywhere but here, preferably "+
        "with a hot cup of tea and a very thick firewall between you and whatever lies ahead."));

    add_item(({"corridor","tunnel","pipelike tunnel","pipe","pipelike corridor"}),
        BSN("The tunnel is long, dark, and uncomfortably confined. The walls seem to close in around "+
            "you, as if they'd rather you weren't here. It's a bit like being inside a very sullen "+
            "sausage, with no clear idea of how you got in or how you're supposed to get out."));

    add_item(({"wall","walls","floor","ceiling"}),
        BSN("The walls are solid, yet somehow ghostly, as though they exist in that curious state of "+
            "being both real and not real. They're sturdy enough to keep you trapped, yet insubstantial "+
            "enough to make you wonder what might slip through from the other side. If they had any "+
            "color at all, it's long since been drained away, leaving only a dull, oppressive grey."));

    add_item(({"network"}),
        BSN("The network, much like an elaborate conspiracy, is vast and mostly unseen. From here, "+
            "you can only glimpse a tiny part of it — a part that suggests you might want to start "+
            "drawing a map, or at least leave a trail of breadcrumbs behind you."));

    add_item(({"interchange"}),
        BSN("Upstream lies the interchange, a frenetic hub of activity where packets whizz by with "+
            "the urgency of someone late for a very important date. It's busy, it's chaotic, and it's "+
            "probably best to avoid getting too close. Who knows what might hitch a ride?"));

    add_item(({"building"}),
        BSN("Downstream, the tunnel ends at a building that practically radiates hostility. Just "+
            "looking at it sends a cold shiver down your bit sequence. It's spiky, it's unpleasant, "+
            "and it's very clear that whatever is inside does not want visitors. You can't help but "+
            "feel that this is a place where data goes in... and never comes out the same."));

    add_exit(NODES + "switch1", "upstream", 0, 0);
    add_exit(NODES + "ips_layer1", "downstream", 0, 0);

    object ob = clone_object(NPC + "ips_packet_link4");
    ob->move(TO,1);

}
