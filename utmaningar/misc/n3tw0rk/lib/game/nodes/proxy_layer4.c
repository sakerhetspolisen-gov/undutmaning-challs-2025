#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the PROXY process");
    set_long(BSN("You've stumbled into a chamber that resembles a highly efficient customs office, "+
        "only without the dubious pastries. The room is neatly divided into two distinct territories "+
        "by a colossal desk that appears to be the nerve center of this operation. On one side, packets "+
        "arrive in a flurry, like eager pigeons at a bread-throwing contest. They are swiftly sorted, "+
        "torn apart, and scrutinized with an intensity usually reserved for top-secret documents. Once "+
        "dissected, their contents are scrutinized, repackaged with a fresh layer of secrecy, and then "+
        "dispatched through a gaping chasm in the floor."));

    add_item(({"room","area","areas","chamber"}),
        BSN("This room is a grand assembly line of data, split in two by an enormous desk that's more "+
        "like a grand battleground for packets. The purpose of each side is a mystery wrapped in an "+
        "enigma, but clearly, packets entering one side are destined to exit the other. Efficiency "+
        "reigns supreme here, with everything in its place and a place for everything."));
    add_item(({"desk"}),
        BSN("The desk, a monumental structure dividing the room, is where the magic — or rather, the "+
        "meticulous sorting — happens. It's a hub of activity where packets are inspected and their fates "+
        "decided with a swiftness that would make a courier envious."));
    add_item(({"sorting"}),
        BSN("In this realm of relentless efficiency, packets are subjected to a rigorous sorting process. "+
        "Thrown into bins, and retreived from bins. Rules of order known only to the almighty algorithms "+
        "dictate their path through a labyrinth of bins and bureaucratic precision."));
    add_item(({"bin","bins"}),
        BSN("Bins of various sizes are scattered about, like receptacles of destiny. Packets are "+
        "temporarily housed here before undergoing the intense scrutiny they need. Additional bins "+
        "stand by, ever-ready to take on the next data deluge."));
    add_item(({"packet","packets"}),
        BSN("Packets here are like busy little workers on a never-ending assembly line. They arrive, "+
        "get torn apart, sorted with military precision, and then exit, reborn with a fresh identity. "+
        "It's a sight to behold, if you're into that sort of thing."));
    add_item(({"content"}),
        BSN("As packets are dismantled, their inner secrets are briefly exposed. It's like watching a "+
        "magician reveal their tricks, only the tricks are data, and the audience might want to avoid "+
        "making any sudden movements."));
    add_item(({"opening","chasm"}),
        BSN("The gaping chasm in the floor, a conduit to wherever this relentless process leads, "+
        "beckons with a certain finality. It's a one-way ticket to the next stage of the grand data "+
        "adventure, wherever that may be."));

    add_exit(NODES + "proxy_layer3", "down", 0, 0);

    object ob = clone_object("/game/npc/proxy_layer4");
    ob->move(TO,1);
    set_admin(ob);

    set_hostname("proxy");
    set_mac(({0xE4,0x3A,0x6E,0x00,0x32,0x67}));
    set_ip(({198,51,100,33,127}));
}
