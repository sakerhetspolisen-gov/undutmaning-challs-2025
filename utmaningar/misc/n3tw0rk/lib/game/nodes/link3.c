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
    set_long(BSN("Happily you zipp along what appears to be the inside of a tunnel, but "+
        "something gives you pause — a certain unreality to your surroundings, as if the walls, floor, and "+
        "ceiling are only half-present, existing more in the realm of ideas than in solid reality. "+
        "It's like traveling through a pipe that can't quite decide if it's real or not. Upstream, you "+
        "glimpse the vague outline of some sort of structure, while downstream, an intersection looms in "+
        "the distance, bustling with activity."));

    add_item(({"surroundings", "structure", "tubelike structure", "tunnel", "pipe"}),
        BSN("The tunnel stretches both upstream and downstream, its rounded walls pressing in on you and "+
            "the other packets as you travel through it. It looks like the inside of a pipe, but there's "+
            "something not entirely convincing about that. It's more of a suggestion of a pipe, really."));
    
    add_item(({"floor", "wall", "walls", "ceiling"}),
        BSN("The walls, ceiling, and floor curve around you like the inside of a pipe, but their very "+
            "existence seems a bit tenuous, as if they're only here because you expect them to be. They "+
            "confine your path to either upstream or downstream, which seems reasonable enough."));
    
    add_item(({"existance","plane", "plane of existence"}),
        BSN("That's not really something you can look at directly. Perhaps it's more of a philosophical "+
            "question than a physical one. Maybe you should try meditating on it, or not."));
    
    add_item(({"structure"}),
        BSN("The structure lies upstream, but from here it's just a distant shape, barely discernible. "+
            "You can't quite make it out, but you have a feeling it's important, or at least thinks it is."));
    
    add_item(({"intersection"}),
        BSN("Downstream, you can just make out an intersection. It seems to be a hub of activity, with "+
            "packets bustling back and forth in a way that suggests there's a lot going on over there. "+
            "You'd almost call it busy, if packets weren't so silent about their business."));

    add_item(({"packet", "packets"}),
        BSN("Packets zip past you in a seemingly endless procession, each one whizzing by with a sense of purpose "+
            "that suggests they're on important errands or perhaps just a bit impatient. They dart and weave through "+
            "the tunnel like busy bees in a hive, each packet with its own little mission. Some are large and bulky, "+
            "while others are small and sprightly, but all seem to be moving with a hurry that makes you wonder if "+
            "there's a grand plan at work or if they're just very disorganized."));

    add_exit(NODES + "switch1", "upstream", 0, 0);
    add_exit(NODES + "proxy_layer1", "downstream", 0, 0);

    object ob = clone_object(NPC + "ips_packet_link3");
    ob->move(TO,1);
}
