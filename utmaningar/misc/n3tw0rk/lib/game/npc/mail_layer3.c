#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("grumpy administrator");
    set_short("A grumpy administrator");
    add_name("administrator");
    set_long(BSN("This digital entity has taken the metaphysical form of a quite noticeable grumpy "+
        "administrator. It is strictly attired in a dark suit and red tie, the suit is however heavily "+
        "wrinkled and there is a large stain on the tie. Its cold gaze sweaps over its surroundings "+
        "as it directs its small team of overseers in an effort to make sure everyone is going where "+
        "they are supposed to. It checks and rechecks its cipboard constantly. Eventhough it does not "+
        "appear to be very approchable you can probably request some information from it."));
}
