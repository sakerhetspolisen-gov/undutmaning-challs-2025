#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("security dispatcher");
    add_name("dispatcher");
    set_short("Focused security dispatcher");
    set_long(BSN("A human-like figure draped in protective gear, looking every bit like someone who's seen "+
        "one too many close calls. With a hard hat perched precariously on its head and heavy gloves gripping "+
        "a clipboard, it stands on the platform with a posture that's more about pretending to be calm than "+
        "actually feeling it. Its eyes keep darting nervously to the swirling cloud overhead, as if expecting "+
        "it to unleash some untold chaos at any moment. You get the sense it would much rather be somewhere "+
        "else, but duty keeps it rooted to the spot."));

    set_chat_time(10);

    add_chat("You might want to rethink hanging around here — safety's not exactly guaranteed!");   
    add_chat("If you're here by mistake, you'd better move along quickly. This place is hardly for the faint-hearted.");   
    add_chat("You are probably no supposed to be here. No one really is.");   

    set_act_time(15);

    add_act("@@display_lightning");
}

void officer_leaves(void)
{
    tell_room(ENV(TO),"The official looking figure leaves down the ladder.\n");
}

void spawn_officer(void)
{
    tell_room(ENV(TO),BSN("As the cloud of dust dissipates you can see a figure in a uniform standing where the lightning struck.\n"));
    set_alarm(0.2,0.0,"officer_leaves");
}

string display_lightning(void)
{
    string *msgs = ({ "say That was a bit too close for comfort!", 
                      "emote wipes a nervous bead of sweat from under its hard hat.",
                      "say That was a close one!",
                      "emote wipes some sweat of its brow." });

    tell_room(ENV(TO), BSN("A blinding flash of lightning suddenly strikes the platform, accompanied by a deafening "+
                           "crack and the lingering tang of ozone. For a moment, the whole place seems to shudder under the impact.\n"));
    set_alarm(0.4,0.0,"spawn_officer");
    return (msgs[random(sizeof(msgs) - 1)]);
}