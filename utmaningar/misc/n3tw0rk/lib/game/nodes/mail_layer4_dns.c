#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
    add_action("do_read","read");
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the DNS process");
    set_long(BSN("You find yourself floating in what can only be described as a bureaucratic "+
        "data vortex. It's as if a cosmic filing cabinet exploded, and all its contents decided "+
        "to drift around in a sort of well-ordered chaos. The centerpiece of this room is an "+
        "imposing list, suspended in mid-air with an air of utter importance, as though it's the "+
        "very essence of order itself. Packets drift upwards from below, only to be intercepted by "+
        "various entities who handle them with a meticulousness that borders on the obsessive. After "+
        "interacting with the list, these packets, now transformed, make their way back downwards, "+
        "bearing the fruits of their bureaucratic labor."));

    add_item(({"data"}),
        BSN("A flurry of data whirls around like busy bureaucrats on coffee breaks. Each piece of data "+
            "seems to be engaged in some critical task or another, as if their very existence hinges on "+
            "the efficiency of their performance."));

    add_item(({"container","data vortex","vortex"}),
        BSN("A swirling mass of data that confines you and the data within its invisible bounds, much like an officious "+
            "envelope stuffed with paperwork that no one dares throw away. The edges are shrouded in an opaque "+
            "barrier, hinting at a world outside that is better left to the imagination. Your only exit is through "+
            "the downward opening, which is as close to a door as one can get in this realm of floating bureaucracy."));

    add_item(({"activity"}),
        BSN("The scene is one of frenetic yet organized activity. Packets come and go with an almost rhythmic precision, "+
            "data is consulted with great seriousness, and everything seems to be working with the kind of accuracy "+
            "that would make a Swiss watch jealous. The whole process has a palpable air of bureaucratic efficiency."));

    add_item(({"list"}),
        BSN("The list, floating as though it has been magically imbued with significance, is the focal point of this "+
            "bureaucratic ballet. It appears to be the key to all the activity, holding the secrets and perhaps the "+
            "infinite wisdom of the data universe. It's worth a look if you can decipher its arcane contents, mayhap "+
            "by trying to read it?"));

    add_item(({"packet","packets"}),
        BSN("Packets move through the room like obedient couriers on a very strict timetable. They ascend and descend "+
            "with purpose, as if each packet's journey is a vital part of a grand, unseen plan."));

    add_item(({"entity","entities","blob","blobs","clerks"}),
        BSN("These entities are like the diligent clerks of this data-driven realm. They float about, seemingly "+
            "following ancient and unchangeable instructions, ensuring that every packet is handled with bureaucratic "+
            "finesse. They seem to have an intuitive grasp of their roles, almost as if they were programmed by the "+
            "most meticulous of administrators."));

    add_exit(NODES + "mail_layer3", "down", 0, 0);

    set_hostname("mail");
    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
}

int do_read(string arg)
{
    if(arg != "list")
        return notify_fail("Read what?\n");

    write("You drift close and try to read from the list. It says:\n"+
        read_file("/game/files/ns.conf") + "\n");
    say(TP->QN+" drifts closer to the list and studies it closely.\n");
    return 1;
}