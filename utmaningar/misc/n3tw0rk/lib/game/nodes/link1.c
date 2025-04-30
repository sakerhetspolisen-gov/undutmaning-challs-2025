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
   set_long(BSN("You find yourself in a data stream expressway, where packets of various sizes are "+
                 "whizzing past you with the urgency of a last-minute shopper on Christmas Eve. "+
                 "The sensation here is like being inside a continuously running laser light show, "+
                 "with data darting about in every conceivable direction. If you squint upstream, you'll "+
                 "spot the cable leading to an intersection that looks like it was put together on a Friday "+
                 "afternoon with whatever parts were left over. However, downstream is where things get truly "+
                 "dramatic — a massive wall of blazing flames stretches out in an endless, fiery expanse, as if "+
                 "daring you to get any closer. It's both impressive and a little nerve-wracking, like looking "+
                 "at a dragon's mouth from a safe distance.")); 

    add_item(({"wall", "fire", "firewall", "flames", "inferno", "expanse"}),
        BSN("The towering inferno that blocks your way further downstream is a sight to behold. It looks like someone "+
            "decided to use a dragon's breath as a security measure. The flames flicker and ripple, creating a "+
            "fiery display that would give any pyromaniac a thrill. Getting closer might reveal more details, but for "+
            "now, it's a sight that makes even the bravest packets think twice about their journey.")); 

    add_item(({"shadow", "shadows", "light", "wave", "waves", "display"}),
        BSN("The occasional waves of heat and flame produce a light show of flickering shadows that dance "+
            "around like mischievous sprites. It's as if the very wall is playing a game of 'catch me if you can' "+
            "with your eyes.")); 

    add_item(({"data", "packets", "show", "lasershow", "light", "laser light show"}),
        BSN("The cable is alive with the hustle and bustle of data zipping about like streaks of lightning. "+
            "It's a mesmerizing display, with blueish trails of light left in their wake. It's so captivating, "+
            "you might find it hard to look away — like trying to ignore a particularly hypnotic disco ball.")); 

    add_item(({"cable"}),
        BSN("The walls of the cable are snugly pressing against you and your fellow packets, creating a cozy, if "+
            "somewhat cramped, atmosphere. Despite the tight squeeze, there's a surprisingly upbeat vibe here, with "+
            "data flowing along in what can only be described as a perfectly orderly chaos.")); 

    add_item(({"intersection"}),
        BSN("The intersection lies upstream, looking like a hastily assembled patchwork of network components. "+
            "It's functional but far from inspiring — more of a temporary stopgap than a grand design. You'll need "+
            "to travel there for a closer inspection, but don't expect any architectural marvels.")); 

    add_exit(NODES + "fw1_gi00_layer1", "downstream", 0, 0);
    add_exit(NODES + "hub1", "upstream", 0, 0);
}
