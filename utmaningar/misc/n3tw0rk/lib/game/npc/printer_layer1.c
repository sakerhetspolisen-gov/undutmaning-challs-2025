#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("grumbling mechanic");
    add_name("mechanic");
    set_short("A grumbling mechanic");
    set_long(BSN("This digital manifestation takes the form of a tired, hunched-over mechanic dressed in oil-stained overalls, "+
                 "clutching a worn-out wrench that looks like it's been in service for far longer than anyone should reasonably expect. "+
                 "The mechanic shuffles about the dim, dusty basement with an air of perpetual exasperation, muttering curses under "+
                 "its breath as it kicks piles of discarded cables and stacks of crumpled, ink-stained paper that seem to multiply with "+
                 "every step. Its eyes are ringed with exhaustion, and every flicker of light or misbehaving wire earns a frustrated "+
                 "grumble. This is the figure responsible for keeping the ancient, creaking physical infrastructure running, and it does "+
                 "so reluctantly — more out of obligation than passion, muttering about how things used to be 'built to last.' It seems "+
                 "to know its way around here though so should you need to request any information, it could probably help, grudgingly."));

    set_chat_time(10);

    add_chat("Bloody wires... always flickering. Used to be they'd last a century.");
    add_chat("Ink ribbons? Pah! Haven't seen a decent one in years.");
    add_chat("These cables are ancient, no wonder nothing works like it should.");
    add_chat("If I had a penny for every paper jam, I'd buy a new wrench.");

    set_act_time(10);

    add_act("emote kicks a crumpled stack of paper with a sigh.");
    add_act("emote tightens a bolt on a sagging shelf, grumbling about 'modern parts.'");
    add_act("emote wipes ink stains from its hands onto its already-stained overalls.");
    add_act("emote glares at the old wiring, muttering about 'impending disaster.'");
}
