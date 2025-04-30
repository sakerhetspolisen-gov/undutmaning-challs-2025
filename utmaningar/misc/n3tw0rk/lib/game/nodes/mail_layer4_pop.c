#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

object intern;

void init(void)
{
    ::init();

    add_action("search_mailbox","look");
    add_action("search_mailbox","investigate");
    add_action("search_mailbox","search");
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the POP3 process");
    set_long(BSN("You've found yourself in a remarkably unadventurous room where the walls are plastered with an "+
        "impressive array of mailbox units. They are arranged in neat rows and columns, creating a seemingly "+
        "endless maze of grey metal. The room is lit with a harsh, unforgiving light that reflects off the shiny "+
        "surfaces, making everything look even more sterile and bureaucratic. The only notable feature in this room "+
        "is a small desk, where an intern, looking as though they'd rather be anywhere else, stands idly by. An "+
        "opening in the floor hints at the way forward from this overly orderly space."));

    add_item(({"room"}),
        BSN("The room is a vision of bureaucratic efficiency, with every wall covered in a sea of mailbox units. "+
            "The lighting is excessively bright, casting a sterile glow over everything. The floor's only feature "+
            "of interest is the opening leading downward."));

    add_item(({"wall","walls"}),
        BSN("The walls are dominated by an unending grid of mailbox units. It's a rather monotonous sight, as if "+
            "the room's purpose was to drown you in paperwork's most mundane aspect."));

    add_item(({"mailbox","mailboxes","mailbox units","units"}),
        BSN("Each mailbox unit is a small, grey metal box with a locked door facing the room. Each door has a tiny "+
            "label, though one seems to be slightly ajar. A closer look reveals that this particular mailbox is labeled \"alex\"."));

    add_item(({"door","ajar door","open door","opened door","open mailbox","ajar mailbox", "alex mailbox"}),
        BSN("The door on the mailbox labeled \"alex\" is slightly ajar. It looks like it might be worth investigating. "+
            "Curiosity might not have killed the cat, but it could certainly lead to an interesting discovery here."));

    add_item(({"rows","row","column","columns"}),
        BSN("The room is a labyrinth of rows and columns of mailbox units, each arranged with meticulous precision."));

    add_item(({"opening"}),
        BSN("The opening in the floor appears to be the only escape route from this cavern of paperwork and bureaucracy."));

    add_item(({"desk"}),
        BSN("A small desk stands near the opening. Behind it, an intern is present, looking like they're engaged in a "+
            "battle with their own boredom. They don't seem to be particularly enthusiastic about their role here."));

    intern = clone_object("/game/npc/mail_layer4_pop");
    intern->move(TO,1);

    add_exit(NODES + "mail_layer3", "down", 0, 0);
    set_hostname("mail");
    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
}


int search_mailbox(string str)
{
    string what;

    if(!str)
        return 0;

    if(query_verb() == "search")
    {
        what = str;
    }
    else if(sscanf(str, "inside %s",what) != 1)
    {
        if(sscanf(str, "in  %s") != 1)
            what = "duh";
    }

    if(what == "mailbox" || what == "mailbox unit" || what == "open mailbox" || what == "alex mailbox")
    {
        if(intern->block_tp())
            return 1;

        write("You open the mailbox door and quickly look through the mail within.\nGood thing your a quick reader!\n"+
              "You read:\n");
        say(TP->QN + " opens up one of the mailboxes and starts to rummages through its content.\n");

        TP->more(FILES+"/mailbox.mbox",1);

        return 1;
    }

    return notify_fail("Investigate inside, or search, what?\n");
}