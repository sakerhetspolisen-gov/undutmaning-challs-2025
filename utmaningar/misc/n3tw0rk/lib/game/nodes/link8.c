#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("In this crisscrossing labyrinth of data flows, you've stumbled into yet another uninspiring "+
                 "round tunnel, where you and your digital brethren zip along, propelled by both duty and the current. "+
                 "There isn't much sense of urgency here, just a steady trudging along, as if everyone is trying to get "+
                 "things done while keeping one eye on the clock, hoping to make it home in time for dinner. Further "+
                 "downstream, the tunnel terminates at what appears to be a cozy suburban townhouse, while upstream lies "+
                 "an intersection that could lead to adventure, or just another dead end."));

    add_item(({"tunnel", "round tunnel", "labyrinth"}),
        BSN("The tunnel stretches endlessly, a round passage where the walls pulse gently with the ebb and flow of data. "+
            "It's not quite claustrophobic, but it does have that peculiar feeling of being inside a very large, very lazy "+
            "sausage — all packed in but not really in a hurry to go anywhere."));

    add_item(({"data flows", "data", "currents"}),
        BSN("The data flows through here like a lazy river, with bits and bytes drifting along, occasionally bumping into one another, "+
            "grumbling about delays and wondering when their next stop will be. It's a rather uneventful journey, but it feels oddly comforting."));

    add_item(({"suburban townhouse", "townhouse"}),
        BSN("At the end of this tunnel, a suburban townhouse looms, looking like a perfectly normal place where packets might rest "+
            "before their next big adventure. It seems out of place in this digital realm, but perhaps that's part of its charm."));

    add_item(({"intersection", "upstream intersection"}),
        BSN("Upstream lies an intersection, a crossroads where paths diverge, leading to the potential for both opportunity and chaos. "+
            "It's a bustling hub of sorts, where packets might pause to discuss their next move, weighing the risks and rewards of their journey."));

    add_exit(NODES + "workstation_layer1", "downstream", 0, 0);
    add_exit(NODES + "switch2", "upstream", 0, 0);
}
