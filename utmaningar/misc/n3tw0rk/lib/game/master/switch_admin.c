#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/admin";

void init_living(void)
{
    ::init_living();
}

public void
create_admin()
{
    set_name("traffic officer");
    add_name("officer");
    set_short("A traffic officer");
    set_long(BSN("A figure of swirling electricity projecting a feeling of distinct order and "+
        "efficiency. It is moving so fast it's hard to make out any clear features. Its arms limbs "+
        "seems to be able to stretch out to reach any part of the surrounding area and then contract "+
        "in an instant. It is wearing a cap that says \"Traffic Officer\" in golden letters."));
    add_item(({"features"}),
        BSN("The figure is moving to fast for you to make out any clear features."));
    add_item(({"limb","limbs"}),
        BSN("The traffic officers lims seems to be both imensly flexible and imensly fast."));    
    add_item(({"cap","letters"}),
        BSN("The cap seems to mark the figure as an official and the letters on the cap "+
            "says \"Traffic Officer\"."));    
}

