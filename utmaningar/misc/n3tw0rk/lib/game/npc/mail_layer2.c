#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("dispassionate administrator");
    add_name("administrator");
    add_name("entity");
    set_short("A dispassionate administrator");
    set_long(BSN("This official-looking entity has an aura of indiffirence and nonchalance. "+
        "You deduce that it has some kind of responsibility here as the other enteties floating "+
        "around here seems to refer to it. It looks around the room with an uninterested gaze. "+
        "You wonder if it would have any luch requestring information from it."));
}

