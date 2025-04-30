#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

void create_monster()
{
    ::create_monster();
    
    set_name("manager");
    add_name("logistics manager");
    set_short("A logistics supervisor");
    set_long(BSN("A mass of bits and bytes forming the likeness of a logistics supervisor. "+
        "It seems organized and structured in a way that is so orderly is is slightly worrying. "+
        "It is wearing slacks, a shirt and what looks like a lab coat. It seems very much in "+
        "control of the situation as it oversees the packing and unpacking of data. It is holding "+
        "a clipboard."));

    add_item(({"cliboard"}),
        BSN("The logistics mannagers clipboard seems to be full of lists of important shipments."));

    set_chat_time(10);

    add_chat("Keep packing those packes! There are customers waiting for them!");   
    add_chat("Do not lose any data. All dataloss will be investigated!");
    add_chat("Get those packets moving!");

    set_act_time(10);

    add_act("tap");
    add_act("narrow thou");
    add_act("emote quickly counts the packets that are being processed and checks its list.");
}
