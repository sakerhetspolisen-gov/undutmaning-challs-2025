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
   set_long(BSN("You've found yourself adrift in a cylindrical corridor of sorts, an expanse that "+
        "could be the tunnel of a colossal mechanical beast or just a remarkably large straw. "+
        "Pulses of light flicker along the walls, casting an ever-changing spectacle as packets "+
        "zip by in a ceaseless ballet of binary brilliance. Upstream, the tunnel opens into a "+
        "bustling expanse resembling a chaotic carnival of data. Downstream, however, is a more "+
        "subdued affair — a drab, uninspired structure that could be the very essence of bureaucratic "+
        "dullness or a shoebox pretending to be an office building."));

    add_item(({"tunnel","cable","pipe","corridor","straw"}),
        BSN("You are floating through a cylindrical conduit, its rounded walls, floor, and ceiling "+
        "reminiscent of a pipe in a cosmic plumbing system. It's probably just as well you're "+
        "floating rather than walking; standing on the curve might just induce a sense of vertigo, "+
        "or worse, an existential crisis."));
    add_item(({"wall","walls","floor","ceiling","surface","surfaces"}),
        BSN("The tunnel's walls, floor, and ceiling are all part of the same curvaceous pipe, "+
        "creating a snug, if slightly claustrophobic, embrace as you float through."));
    add_item(({"packet","packets"}),
        BSN("Packets zip past you, glowing with pulses of light that dance and shimmer off the "+
        "tunnel's surfaces. It's like a never-ending light show, with a soundtrack provided by the "+
        "whirring and clicking of digital activity."));
    add_item(({"pulses","light","reflections","lights","show"}),
        BSN("The light from the packets creates a dazzling, if somewhat dizzying, light show as it "+
        "bounces off the tunnel's inner surfaces. It's an impromptu laser display, brought to you by "+
        "the wonderful world of data transmission."));
    add_item(({"expanse","bustling expanse","carnival","intersection","marketplace"}),
        BSN("The expanse upstream looks like a bustling data intersection, where packets mingle and "+
        "move with the frenetic energy of a marketplace at high noon."));
    add_item(({"building","shoebox","office building"}),
        BSN("Downstream, you see a building so unremarkable and grey that it might well be a shoebox "+
        "masquerading as a serious piece of architecture. It's the sort of place where excitement goes "+
        "to have a nap and inspiration is in permanent vacation mode."));

    add_exit(NODES + "switch1", "upstream", 0, 0);
    add_exit(NODES + "mail_layer1", "downstream", 0, 0);

    object ob = clone_object(NPC + "ips_packet_link6");
    ob->move(TO,1);
}
