#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("nervous networker");
    add_name("networker");
    add_name("manifestation");
    add_name("figure");
    set_short("A nervous networker");
    set_long(BSN("This digital manifestation appears as a thin, frazzled individual, constantly glancing from side to side as if "+
                 "expecting something to go wrong at any moment. It wears a slightly rumpled jacket adorned with various networking "+
                 "badges — some shiny and new, others rusted with age. The networker seems perpetually on edge, juggling the flow "+
                 "of data between this machine and the endless void of the outside network. Despite its best efforts, the wear of "+
                 "legacy systems and hastily applied patches weigh heavily on its shoulders, giving it a twitchy, almost paranoid "+
                 "demeanor. Every packet that flows through is met with a nervous glance, and the networker frequently mutters about "+
                 "'bottlenecks', 'outdated protocols,' and 'someone else's quick hacks.' It's clear that while it's doing its job, "+
                 "it's always bracing for the next disaster, hoping the entire network stack doesn't come crashing down around it. "+
                 "Requesting help from it would be adding insult to injury, but that's the service sector in a nutshell isn't it?"));

    set_chat_time(10);

    add_chat("If only they'd update these protocols, I wouldn't be constantly babysitting packet flow.");
    add_chat("Another reroute? Great. Because shortcuts never cause problems... right?");
    add_chat("We could really use a patch here, but no one ever listens to me.");
    add_chat("Do they even realize what happens when packets get stuck in a loop?");
    add_chat("This would be so much easier if they stopped using ancient tech. But no, let's keep patching over patches.");
    
    set_act_time(10);

    add_act("emote nervously taps its fingers on a terminal as it watches packets trickle through.");
    add_act("emote checks the packet logs for bottlenecks, frowning.");
    add_act("emote mutters to itself about outdated protocols and quick hacks.");
    add_act("emote glances anxiously towards the spiral staircase, half-expecting trouble.");
    add_act("emote sighs deeply as a particularly bloated packet struggles through.");
}
