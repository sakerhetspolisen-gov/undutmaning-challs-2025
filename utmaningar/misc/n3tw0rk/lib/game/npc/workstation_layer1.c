#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("jaded technician");
    add_name("technician");
    add_name("manifestation");
    add_name("figure");
    set_short("A jaded technician");
    set_long(BSN("This digital entity appears as a jaded, slightly hunched-over technician, with the permanent scowl of "+
                 "someone who's spent far too long wrangling outdated systems and patching together kludges. It wears a faded, "+
                 "oil-stained jumpsuit, adorned with an odd assortment of badges, each representing some half-forgotten "+
                 "protocol or legacy system. Its eyes have the dull, glassy look of someone who's seen too many patch cycles, "+
                 "and its fingers twitch as if forever entering obscure command-line arguments. Despite its disheveled state, "+
                 "the technician seems oddly efficient, patching up broken connections and mumbling about backwards compatibility "+
                 "as it works. There's an air of quiet resignation about it, as though it knows that no matter how hard it tries, "+
                 "the systems it oversees are always one step from complete collapse. Still, it continues, because someone has to "+
                 "keep this antiquated machine running, even if it's just delaying the inevitable. Should you request some "+
                 "help or information from it, it would probably grumble and mutter, but help you none the less."));

    set_chat_time(10);

    add_chat("Legacy systems… they always want more without cleaning up the old mess.");
    add_chat("This would've worked better with a modern API, but nooo, let's stick with the 90s.");
    add_chat("You'd think they'd upgrade the hardware, but no, here I am duct-taping packets together.");
    add_chat("Why use a simple fix when you can spend hours cobbling together something that'll break next week?");
    add_chat("If these cables could talk, they'd be begging for retirement.");
    
    set_act_time(10);

    add_act("emote fiddles with a tangled mess of cables, shaking its head.");
    add_act("emote pulls out a roll of digital duct tape and patches up a sagging connection.");
    add_act("emote sighs deeply as a bloated data packet lumbers past.");
    add_act("emote mumbles about 'ancient protocols' and 'overly bloated standards' while glancing at the ceiling.");
    add_act("emote pokes at a sagging cable with a wrench, muttering under its breath.");
}
