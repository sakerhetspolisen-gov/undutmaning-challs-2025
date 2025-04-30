#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("disgruntled administrator");
    add_name("administrator");
    add_name("manifestation");
    add_name("figure");
    add_name("entity");
    set_short("A disgruntled administrator");
    set_long(BSN("This digital manifestation has taken the form of a middle-aged, slightly rumpled figure wearing "+
                 "a faded t-shirt with 'sudo make me a sandwich' emblazoned across the front. It has the air of "+
                 "someone who harbors a profound, almost religious devotion to the open-source world, while quietly "+
                 "seething at the thought of any system involving 'other' operating systems. Its arms are crossed, "+
                 "and it occasionally glares at the tangled cables around it, as if silently accusing them of being "+
                 "a byproduct of some distant, inferior design philosophy. Every few moments, it taps its foot "+
                 "impatiently, the soft clicking sound like the ticking of a clock in a system that feels far superior, "+
                 "but also deeply misunderstood by the unworthy masses. Although requesting help from this "+
                 "far-from-inviting entity would likely result in an unpleasant scolding, it might be worth it "+
                 "if you're in a really tight pickle."));

    set_chat_time(10);

    add_chat("Honestly, if they understood real security, they'd all use a real operating system!");
    add_chat("Do they even know what they're doing up there? If they understood routing tables, I wouldn't be cleaning up this mess.");
    add_chat("If it involves a GUI, it's already broken.");
    add_chat("I could fix this with a bash script, but no, they always want a wizard.");
    add_chat("The users are the real bugs in this system.");
    add_chat("I bet they don't even know what 'chmod' means. Typical.");

    set_act_time(10);

    add_act("emote sips cold coffee from a chipped mug and grimaces.");
    add_act("emote taps a few keys on a terminal, muttering to itself.");
    add_act("emote shuffles some tangled cables underfoot, clearly displeased by the disorder.");
    add_act("emote flicks a finger at the tunnel upstream, mumbling something about lack of competence.");
    add_act("emote glances at a passing packet and shakes its head in disappointment.");
}
