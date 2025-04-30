#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("frantic overseer");
    add_name("overseer");
    add_name("network administrator");
    add_name("manifestation");
    set_short("A frantic overseer");
    set_long(BSN("The digital entity before you has taken the form of a perpetually stressed overseer, hunched over with a "+
                 "slightly disheveled appearance, as if it has been awake for days chasing elusive packets. Its hair, "+
                 "or what remains of it, stands up at odd angles, defying any attempts at order, much like the endless streams "+
                 "of data it tries to control. Its hands flutter nervously over invisible consoles, typing commands into "+
                 "non-existent terminals, only to undo them moments later in a state of digital anxiety. There's an air of "+
                 "someone who's constantly in crisis mode, even if everything is running smoothly. Every few seconds, it glances "+
                 "at the flowcharts on the walls, as if expecting them to change into some new, incomprehensible configuration "+
                 "of protocols, just to torment it further. Its eyes are ringed with the dark circles of one who's seen far "+
                 "too many crashes and late-night patches. You would feel a bit bad about requesting any help or information "+
                 "from it, as it seems to be on the verge of a mental, or complete, breakdown, but necessity knows no law."));

    set_chat_time(10);

    add_chat("Protocols, always more protocols! Why can't they just follow the rules?");
    add_chat("No, no, no! That packet's going the wrong way again!");
    add_chat("Flowcharts... if they make one more change, I swear I'll... well, I'll manage. Like always.");
    add_chat("I knew it. I told them we needed more bandwidth, but do they ever listen?");
    add_chat("Network congestion is a nightmare. They're all clogging it up with streaming, aren't they?");
    add_chat("I'll just tweak the firewall... No! Wait! Maybe that wasn't the right rule.");

    set_act_time(10);

    add_act("emote furrows its brow and mutters about 'packet prioritization' under its breath.");
    add_act("emote taps furiously at an invisible console, then sighs as if realizing it's a futile effort.");
    add_act("emote checks a flowchart on the wall, groans, and scribbles a non-existent correction.");
    add_act("emote glances at the ladder and staircase, contemplating whether to escape or stay and fight the data stream.");
    add_act("emote brushes a hand through its hair, only to find it standing more on end than before.");
}

