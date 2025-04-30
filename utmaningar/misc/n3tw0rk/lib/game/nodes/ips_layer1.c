#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer");
    set_long(BSN("You find yourself at the base of a towering, menacing structure, a twisted "+
        "conglomeration of steel beams arranged in a way that suggests the architect had a grudge "+
        "against right angles — and possibly humanity itself. The entire edifice seems to glare down "+
        "at you with silent hostility, daring you to approach. Barbed wire coils around the sharp edges, "+
        "and you can almost hear it whispering unpleasant things about what it might do if you get too close. "+
        "A narrow staircase clings precariously to the outside of the tower, spiraling upwards to a "+
        "platform shrouded in shadow. It's the sort of place that doesn't need signs to say \"Keep Out\" — the "+
        "very air feels thick with warnings, and a distinct sense that whatever lives here does not "+
        "appreciate visitors."));

    add_item(({"tower","building"}),
        BSN("The tower is a brutal construct, all harsh angles and sharp lines, as if the steel beams "+
            "themselves are straining to stab anyone foolish enough to come too close. Barbed wire is "+
            "strung haphazardly around the structure, serving as both a deterrent and a reminder that "+
            "this is not a place meant for comfort — or survival, for that matter. Floodlights, dark for "+
            "now, are mounted like sentinels, ready to flood the area with blinding light the moment something "+
            "unwelcome dares to approach."));

    add_item(({"metal","steel","beams"}),
        BSN("The beams look less like metal and more like an artist's harsh rendition of the concept "+
            "of ‘metal.' They're strong, unyielding, and carry the sort of presence that suggests they "+
            "weren't made to support anything so much as to crush whatever lies beneath them."));

    add_item(({"angles"}),
        BSN("The angles are sharp — too sharp. Even the ones that should be ninety degrees seem to "+
            "threaten with a barely contained violence, as if they might snap closed like a trap at "+
            "any moment. The whole structure seems to be daring you to come closer and test your luck."));

    add_item(({"barbed wire","wire"}),
        BSN("Barbed wire wraps around the tower like a venomous snake, each barb a pointed reminder "+
            "that you are not welcome here. It's the architectural equivalent of a snarl, promising pain "+
            "to anyone foolish enough to press on."));

    add_item(({"staircase","stairs"}),
        BSN("The staircase spirals upwards, clinging to the outside of the tower as if it's not entirely "+
            "sure it wants to be there. Each step creaks ominously, and the path upwards feels more like "+
            "a gauntlet than a route to safety."));

    add_item(({"platform"}),
        BSN("The platform looms above, partially obscured in shadow. You can't see much from down here, "+
            "but what little you can make out suggests that it's not a place for casual visits. If the "+
            "staircase is a gauntlet, the platform is the arena at the end — where something dangerous waits."));

    add_item(({"lights","floodlights","light","floodlight"}),
        BSN("The floodlights are dormant for now, but you can tell they're waiting — waiting to blaze "+
            "to life at the slightest provocation, ready to spotlight whatever poor soul dares to disturb "+
            "this place. They're not here to illuminate; they're here to hunt."));

    add_exit(NODES + "ips_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link4", "upstream", "@@upstream_check", 0);

    create_admin(NPC + "ips_layer1");
    
    set_mac(({0x3C,0x7D,0x1C,0xF3,0x44,0x0C}));
    set_ip(({198,51,100,5,127}));
    set_hostname("ips");
}
