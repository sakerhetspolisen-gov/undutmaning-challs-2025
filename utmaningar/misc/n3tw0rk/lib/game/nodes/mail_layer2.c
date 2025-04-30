#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER2;

public void
create_node()
{
    ::create_node();
    set_short("In the network layer");
    set_long(BSN("You find yourself perched at the summit of an ancient and somewhat creaky staircase. "+
        "It leads either up to this realms of yet undiscovered marvels or down into the depths of "+ 
        "bureaucratic tedium, depending on your viewpoint. Surrounding you is a cavernous warehouse "+
        "that might have been state-of-the-art in the early days of the digital age. Packets dart about "+
        "with a sense of purpose, if not urgency, as they are directed by various official-looking entities "+
        "floating around with an air of importance. Another staircase, circular and imposing, spirals "+
        "upwards while packets continue their steady procession up and down its length."));

    add_item(({"old-fashioned staircase","old staircase"}),
        BSN("You are at the top of a rather old-fashioned staircase that leads down into the lower "+
        "reaches of this establishment. From here, it seems like a journey back into the heart "+
        "of bureaucratic drudgery awaits."));

    add_item(({"warehouse","room"}),
        BSN("The room you're in resembles a warehouse from a bygone era, spacious and a touch forlorn. "+
            "It has an air of being both underused and over-extended, designed for a time when packing "+
            "and sorting was a grand affair."));

    add_item(({"packet","packets"}),
        BSN("Packets zip around with a mechanical regularity, their path directed by the ever-watchful entities. "+
            "They move either up the staircase or down with a sense of purpose that belies the overall "+
            "drabness of their surroundings."));

    add_item(({"entity","entities"}),
        BSN("These official-looking entities float around with an air of bureaucratic gravitas. "+
            "They direct the packets with an efficiency that seems almost ancient, as if they were "+
            "part of a grand but outdated system."));

    add_item(({"circular staircase"}),
        BSN("The grand circular staircase leads upwards, its steps worn from years of packet traffic. "+
            "The constant flow of packets moving up and down creates a steady, rhythmic motion, as if "+
            "the staircase were alive with purpose."));

    add_item(({"staircase"}),
        BSN("There are two of them, blessing this room with thier stairiness. A circular one leading up "+
        "and a rather old-fashioned leading down."));

    add_exit(NODES + "mail_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "mail_layer1", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "mail_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
    set_hostname("mail");
}


