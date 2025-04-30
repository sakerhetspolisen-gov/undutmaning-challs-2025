#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    ::create_admin();
    set_long(BSN("A swirling collection of data that manifests as a slightly harried but "+
        "intensely focused technician. Clad in a rugged, slightly oversized overall and equipped "+
        "with a tool belt bursting with an eclectic mix of screwdrivers, pliers, and wrenches, "+
        "this figure seems ever-ready for the unexpected. A laminated, fireproof notebook is "+
        "firmly grasped in one hand, while a well-chewed pencil juts out from behind one ear. "+
        "Every so often, it hums a distracted tune and jots down notes with rapid, practiced "+
        "strokes. Despite the evident stress, the technician's eyes remain sharp and attentive, "+
        "reflecting a deep commitment to the task at hand. If you need practical advice or technical "+
        "assistance, this is the one you should request it from."));
}
