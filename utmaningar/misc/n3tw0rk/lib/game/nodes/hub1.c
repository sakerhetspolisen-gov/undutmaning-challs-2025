#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit NODE;

public void
create_node()
{
    set_short("In a network hub");
    set_long(BSN("Ah, you've arrived at a rather makeshift intersection in the grand parade of data flow. "+
                 "This hub seems to have been thrown together in a fit of temporary enthusiasm, with no one "+
                 "bothering to keep things tidy or under control. You're floating amid a tangled mess of data traffic, "+
                 "where three gateways splay out like the arms of a very confused octopus. Two of these exits are bustling "+
                 "with packets zooming around like caffeinated squirrels, while the third languishes in relative solitude, "+
                 "its purpose as obscure as a cryptic riddle written in binary."));

    add_item(({"intersection", "hub"}),
        BSN("Here you are, at the bustling crossroads of the data flow, a hub of sorts where packets congregate. "+
            "Three distinct paths diverge from this central point, yet there's no way to ascertain their destinations. "+
            "Beyond these exits, you see tunnels stretching off into the digital void, full of potential and mystery."));

    add_item(({"opening", "openings", "gateway", "gateways", "exit", "exits", "entrance", "entrances"}),
        BSN("Three rather uninspired openings lead away from this intersection, each marked with cryptic labels. "+
            "The signs read 'port0', 'port1', and 'port2' — a minimalist's approach to signage that leaves much to "+
            "the imagination. Beyond these openings, tunnels stretch into the great unknown, promising adventures "+
            "of varying degrees of probability and plausibility."));

    add_item(({"tunnel", "tunnels"}),
        BSN("The tunnels beyond the openings are like the alleyways of a sprawling digital city, leading off into regions "+
            "that might as well be on another planet. They beckon with a sense of mystery and mischief, their destinations "+
            "as elusive as a good cup of coffee in a bureaucratic office.")); 

    add_exit(NODES + "internet", "port0", 0, 0);
    add_exit(NODES + "link0", "port1", 0, 0);
    add_exit(NODES + "link1", "port2", 0, 0);
}
