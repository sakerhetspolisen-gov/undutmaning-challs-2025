#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("frazzled dispatcher");
    add_name("dispatcher");
    add_name("clerk");
    set_short("A frazzled dispatcher");
    set_long(BSN("This digital entity has manifested as a weary, overworked clerk in a faded, ill-fitting uniform. With disheveled hair "+
                 "and ink-stained fingers clutching a worn clipboard, the dispatcher flits about the room in a state of constant motion. "+
                 "Their face is locked in a permanent frown of concentration, occasionally twitching in frustration as they try to organize "+
                 "and route the seemingly endless stream of data packets. Despite their best efforts, the dispatcher seems eternally one step "+
                 "behind the chaos, frequently muttering about forgotten protocols, outdated standards, and misrouted streams. Their worn shoes "+
                 "click along the floor as they rush between tubes, trying to keep the flow moving, all while eyeing the rickety spiral staircase "+
                 "with the kind of dread reserved for something that frequently goes wrong. The entire scene has the air of a postal office that's "+
                 "been running for far too long without an upgrade, held together by habit and a prayer. However, it is here to work and "+
                 "should you request help or information, it will most surely provide you with it, along with copious amounts of internal grumbling."));

    set_chat_time(10);

    add_chat("These streams never stop, do they? If only we had an actual system for this.");
    add_chat("Which tube was it again? Oh right, the one with the faded markings... as always.");
    add_chat("Legacy workarounds, they said. It'll be fine, they said.");
    add_chat("We really need to stop bypassing APIs, but here we are...");
    add_chat("If I have to sort one more misrouted packet, I swear...");

    set_act_time(10);

    add_act("emote scurries over to one of the large tubes, inspecting the markings with a puzzled expression.");
    add_act("emote fumbles with a clipboard, scribbling something down while shaking their head.");
    add_act("emote sighs deeply as another misrouted packet is brought to their attention.");
    add_act("emote glances nervously at the dusty blackboard, as if half-expecting it to explode with more cryptic numbers.");
    add_act("emote pauses briefly to straighten their disheveled uniform, then hurries off to inspect another data stream.");
}
