#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("You find yourself yet again zipping along one of those oh-so-common rounded tunnels, where you "+
                 "and a multitude of other packets, each with their own peculiar shapes and sizes, dart towards your "+
                 "individual destinations. The ghostly walls shimmer with the reflected sparks of electricity coursing "+
                 "through the tunnel, a sort of digital lifeblood that pushes you and your fellow packets onward, "+
                 "like the veins of a body but decidedly less icky. Upstream, you can see a crossroads in the distance, "+
                 "a place where decisions might be made (or at least debated over a cup of something caffeinated). "+
                 "A bit further downstream lies what, from this distance, looks linke some sort tangled heap of cables."));

    add_item(({"cable", "tunnel", "rounded tunnel"}),
        BSN("The tunnel is round and smooth, not unlike a really boring piece of spaghetti, but it serves its purpose "+
            "with a quiet dignity. It has an air of familiarity, as if many packets have traversed this path, sharing tales "+
            "of their digital escapades along the way."));

    add_item(({"walls", "ghostly walls"}),
        BSN("The walls of this tunnel shimmer and flicker, as if they have their own private conversations with the electric "+
            "sparks dancing along them. They're neither solid nor entirely insubstantial, a bit like a daydream that's yet to "+
            "decide what it wants to be when it grows up."));

    add_item(({"electricity", "sparks"}),
        BSN("The electricity courses through the tunnel, producing tiny sparks that illuminate the path ahead. It's a bit like "+
            "the digital equivalent of starlight, guiding packets along their journey and reminding them that they're not alone, "+
            "even if they are just bits of data."));

    add_item(({"crossroads", "crossroad"}),
        BSN("Upstream, the crossroads beckons, a place where paths diverge and decisions await. It's a gathering spot for packets "+
            "to stop, chat, and perhaps ponder the meaning of life, or at least the meaning of their next hop in the network."));

    add_item(({"cables", "tangled heap", "tangled heap of cables", "heap"}),
        BSN("A cluttered, tangled monstrosity of wires, cables, and stray bits of hardware, as if someone attempted to create "+
            "a functional piece of technology using the principles of abstract art. The cables spill out in every direction, "+
            "like the tentacles of a particularly disgruntled octopus."));

    add_exit(NODES + "admin_layer1", "downstream", 0, 0);
    add_exit(NODES + "switch2", "upstream", 0, 0);
}
