#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("Yet again you find yourself confined by rounded walls, ceiling and floor. The tunnel looks much like all the others you've "+
        "experienced while zipping around the pathways of the network. There isn't much traffic through here though and not feeling "+
        "cramped and pushed by other packets is a bit of a novelty. The tunnel opens up at a colourfull building a bit further downstream "+
        "and upstream you can see some kind of intersection."));

    set_long(BSN("Once more, you find yourself squeezed into a rounded tunnel, where the walls, ceiling, and floor seem to blend into one "+
                 "curiously uniform entity. It resembles the countless other tunnels you've traversed, yet here, a delightful lack of traffic "+
                 "allows you to stretch your metaphorical legs. The absence of impatient packets is almost a relief, a tranquil interlude in "+
                 "the otherwise bustling network. Upstream, you glimpse an intersection that promises further adventures, while downstream, a "+
                 "vibrant building awaits, likely teeming with the excitement and, apparently, bright colours."));

    add_item(({"tunnel", "rounded tunnel"}),
        BSN("The tunnel curves gracefully, reminiscent of a well-used but cherished path in a park. It's comfortable and familiar, a place "+
            "where packets can glide along without the usual hustle and bustle."));

    add_item(({"walls", "ceiling", "floor"}),
        BSN("The walls, ceiling, and floor all merge into a seamless expanse, their surfaces occasionally shimmering as if sharing private "+
            "jokes with the electricity zipping by. They seem to hum a gentle tune, a sort of lullaby for weary packets."));

    add_item(({"packet", "packets", "traffic", "lack of traffic"}),
        BSN("The lack of traffic here is almost deafening in its quietness. It's a rare oasis in the frantic landscape of data, offering a "+
            "moment of peace amidst the chaos of the network."));

    add_item(({"intersection", "upstream intersection"}),
        BSN("Upstream lies an intersection, a junction buzzing with potential and perhaps a little confusion. It's where paths converge, "+
            "and decisions are made — who knows what packets might be found there, arguing over directions like lost tourists?"));

    add_item(({"building", "vibrant building", "colourful building"}),
        BSN("Downstream, a colourful building comes into view, possibly the realm of some famous painter. It exudes an air of creativity, "+
            "with bright banners proclaiming its purpose. Inside, one can imagine the whirring and chugging of mechanical artists at work, turning "+
            "digital dreams into tangible reality, one sheet of paper at a time."));

    add_exit(NODES + "printer_layer1", "downstream", 0, 0);
    add_exit(NODES + "switch2", "upstream", 0, 0);
}
