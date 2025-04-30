#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("sullen manager");
    set_short("A sullen manager");
    add_name("manager");
    set_long(BSN("This digital entity has taken the metaphysical form of a sullen manager, its presence radiating an "+
                 "aura of both authority and disdain as well as a smug self-satisfaction. It hovers restlessly among "+
                 "the chaos, arms crossed and brow furrowed, as if constantly in a state of mild annoyance at the very "+
                 "existence of anything that might disrupt its precious work. Its eyes, sharp and "+
                 "glowing like LED indicators, dart about, scanning for errant packets or rogue connections. "+
                 "You get the feeling that it will not be happy about it, but its programming will probably compell "+
                 "it to aid you should you request it."));
    
    set_chat_time(10);

    add_chat("If only users understood the joy of a well-structured subnet...");
    add_chat("Safety regulations? Just a suggestion.");
    add_chat("If it ain't broken, I must have fixed it.");
    add_chat("I can do this faster in the terminal.");
    add_chat("Why do users always insist on complicating things?");
    add_chat("I could route circles around this mess if I had proper resources.");
    add_chat("Ah yes, another day of managing chaos.");
    add_chat("Do they really think these safety protocols mean anything down here?");

    set_act_time(10);

    add_act("grumble angr");
    add_act("emote sighs and mutters something under its breath.");
    add_act("emote glances at the blackboard and shakes its head.");
    add_act("emote sighs deeply, as though burdened by the weight of the entire transport layer.");
    add_act("emote fiddles with a stray cable, its expression one of vague disgust.");
    add_act("emote glares at the rickety staircase, as if it personally offends its sense of efficiency.");
    
}
