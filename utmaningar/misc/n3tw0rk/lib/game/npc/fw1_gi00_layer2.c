#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("stern security guard");
    add_name("guard");
    add_name("stern guard");
    add_name("security guard");
    set_short("A stern security guard");
    set_long(BSN("A formidable presence of data, shaped into the likeness of a very stern and no-nonsense "+
        "security guard. Its gaze, sharp as a freshly honed algorithm, scrutinizes every passing packet with "+
        "the intensity of someone who's seen it all and trusts nothing. When its eyes lock onto you, a shiver "+
        "creeps down your metaphysical spine, making you wonder if your headers are in order. Despite its "+
        "unyielding demeanor, you might still dare to request help or information from it. The wire in its ear, "+
        "tethered to something unseen, hints at a connection to higher powers."));

    add_item(({"wire","ear","earpiece"}),
        BSN("A thin, unobtrusive wire, likely linked to some sort of communications device, keeping the guard "+
             "in constant contact with its superiors."));

    set_chat_time(10);

    add_chat("Move along, packets! If you're idling, you're a problem waiting to happen!");   
    add_chat("Get in line, stay in line, and wait your turn. No exceptions, no excuses!");
    add_chat("Anything out of the ordinary? Report it at once, or it's on your head!");
    add_chat("Baggage left unattended will be confiscated and thoroughly inspected!");
    add_chat("Identification out and ready! Let's keep things efficient, no dilly-dallying!");
    add_chat("Remember, a well-organized packet is a happy packet. Stay in order!");
    add_chat("No dawdling! Time waits for no packet, and neither do I!");
    add_chat("I've got my eye on you. Don't even think about causing trouble!");

    set_act_time(10);

    add_act("stern");
    add_act("emote puts one of its index fingers to its ear, listening intently for a moment, as if receiving orders from above.");
    add_act("emote scans the area with a practiced eye, ever watchful for the slightest hint of trouble.");
    add_act("emote straightens its posture, a reminder to everyone present that it brooks no nonsense.");
    add_act("emote adjusts its cap with a brisk motion, ensuring it's sitting just right.");
    add_act("emote crosses its arms and taps its foot, clearly waiting for something — or someone — to step out of line.");
    add_act("emote checks an invisible watch, a subtle hint that time is of the essence here.");
}
