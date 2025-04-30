#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

void create_monster()
{
    ::create_monster();

    set_name("overworked clerk");
    add_name("clerk");
    add_name("organizer");
    set_short("An overworked clerk");
    set_long(BSN("This digitaly representation of abstract ideas has taken the form of a frazzled, overworked clerk buried beneath a mountain of "+
                 "paperwork, folders, and blinking gadgets. The clerk is a harried figure with wild eyes and a constantly furrowed brow, trying "+
                 "desperately to keep up with an unending stream of tasks, from sorting emails to flagging items for follow-up. A tangled "+
                 "headset hangs loosely around their neck, a symbol of the constant calls and reminders that never seem to end. Their clothing "+
                 "is a patchwork of coffee stains and sticky notes, and they occasionally mutter to themselves about missed deadlines and "+
                 "overbooked calendars. Despite the chaos surrounding them, they seem determined to impose some kind of order, though it's clear "+
                 "they're just one unexpected email away from complete collapse."));

    set_chat_time(10);

    add_chat("I swear, if I get one more meeting request, I'm going to scream.");
    add_chat("Flagged for follow-up? More like flagged for never, at this rate.");
    add_chat("You think it's easy sorting this many emails? Try it with a hundred unread every minute.");
    add_chat("Search results? I think it found an old sandwich from 2015.");
    add_chat("Where did that email go? Oh well, lost to the abyss, I suppose.");

    set_act_time(10);

    add_act("emote frantically sorts through a stack of papers, accidentally knocking over a nearby folder.");
    add_act("emote slams their hands on the desk, causing a cascade of sticky notes to fall around them.");
    add_act("emote squints at the gigantic 'Search' tool in the corner, clearly unimpressed with its latest attempt to find something.");
    add_act("emote taps furiously on a keyboard, muttering about overbooked calendars and missed reminders.");
    add_act("emote watches as an email vanishes down the dark tube, their shoulders slumping in resignation.");

}
