#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("irritable overseer");
    add_name("overseer");
    set_short("An irritable overseer");
    set_long(BSN("A seething mass of data, pulsing with barely contained irritation. Its form shifts "+
        "and crackles as it glares suspiciously at everything that moves, clearly itching for an excuse "+
        "to unleash its pent-up frustration on some unfortunate packet. It grudgingly allows a few packets "+
        "to ascend the stairs, though with the distinct impression that it would rather detain them for a "+
        "good, long chat involving sharp data spikes. Requesting information or help from it might very well "+
        "result in a verbal lashing — or worse, if it's having a particularly bad day, but might still be usefull "+
        "or necessary."));

    set_chat_time(10);

    add_chat("You there! What mischief are you plotting!?");   
    add_chat("Step out of line, and I'll personally make sure you regret it!");   
    add_chat("I'm watching you! Don't think you can sneak by unnoticed!");   
    add_chat("You better have a good reason for being here, or things will get unpleasant!");
    add_chat("You're not up to something are you!?");   
    add_chat("What are you doing here!? I'm quite sure you shouldn't be here!");   

    set_act_time(10);

    add_act("emote narrows its eyes at you, as if calculating the precise level of trouble you're about to cause.");
    add_act("emote crackles ominously, its frustration practically radiating off of it.");
    add_act("emote grumbles under its breath, clearly looking for an excuse to lash out.");
    add_act("emote taps a metaphorical foot, waiting for someone to step out of line.");
    add_act("emote glares angrily at you.");
    add_act("grumble angr");
}
