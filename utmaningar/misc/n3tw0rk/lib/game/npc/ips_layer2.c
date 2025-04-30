#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("grumpy inspector");
    add_name("inspector");
    add_name("entity");
    set_short("A grumpy inspector");
    set_long(BSN("A swirling vortex of data takes the vaguely intimidating form of a surly inspector, its "+
        "displeasure radiating like a dark cloud. Draped in a drab, dark uniform with \"IPS\" emblazoned "+
        "in stark white letters across the back, it wields a tablet with the air of someone who's just waiting "+
        "for you to make a mistake. The screen occasionally flickers with what looks like a map, but you're not "+
        "about to ask for a closer look. This is not the sort of entity you want to cross, but if you're desperate, "+
        "you might have no choice but to request help from it."));

    add_item(({"tablet"}),
        BSN("The inspector clutches the tablet with a grim determination, periodically glancing at the screen. "+
            "You catch glimpses of a map, but it's clear that you're not meant to understand what it shows."));
    add_item(({"screen","map"}),
        BSN("The screen displays a map, though the inspector's grip and glare suggest you'd better not linger too "+
            "long trying to figure it out."));

    set_chat_time(10);

    add_chat("You've got no business here! Clear off before I call in backup.");   
    add_chat("You most likely should not be here! Scram, before I send for a security officer.");   
    add_chat("You don't belong here! Move along before I decide to make an issue of it.");
    add_chat("What's your excuse for loitering? Don't think I won't notice.");
    add_chat("One more step out of line, and you'll regret it, packet!");

    set_act_time(10);

    add_act("emote taps something furiously on its tablet, as if taking notes on your every move.");
    add_act("emote narrows its eyes at you, clearly contemplating the fastest way to get rid of you.");
    add_act("emote emits a low growl, the sound of barely suppressed frustration.");
    add_act("emote checks its tablet again, as if searching for a reason to reprimand you.");
    add_act("grumble angr");
}

