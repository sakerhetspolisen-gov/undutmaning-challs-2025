#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/switch_admin";

public void
create_admin()
{
    set_name("traffic officer");
    add_name("officer");
    add_name("figure");
    set_short("A traffic officer");
    set_long(BSN("Before you hovers a figure that seems to be made entirely of fizzing, crackling energy, "+
        "like a thunderstorm trapped in a well-tailored uniform. The air around it hums with a sense of brisk "+
        "efficiency, the kind that suggests this being has seen it all and will not be tolerating any nonsense. "+
        "Its limbs, if they can be called that, stretch and retract with a speed that defies belief, almost as if time itself "+
        "is a suggestion rather than a rule. Perched on its head is a slightly askew cap emblazoned with the words "+
        "\"Traffic Officer\" in gleaming, golden letters, lending a touch of bureaucratic authority to its otherwise "+
        "chaotic appearance."));
    
    add_item(({"features"}),
        BSN("The figure moves with such speed and energy that any distinct features blur into a frenzied whirlwind of "+
            "motion. Perhaps that's for the best — you get the sense that this is not someone you want to study too closely."));
    
    add_item(({"limb","limbs"}),
        BSN("The limbs of the traffic officer are astonishingly agile, stretching out to cover vast distances in an instant, "+
            "before snapping back like an elastic band, ready to dart out again at a moment's notice."));
    
    add_item(({"cap","letters"}),
        BSN("The cap, slightly askew on the figure's head, bears the proud inscription \"Traffic Officer\" in shiny, golden letters. "+
            "It seems almost absurdly official, given the chaotic energy of its wearer, but there it is — a badge of order amidst the storm."));


    set_chat_time(10);

    add_chat("Come on now, packets! No loitering, keep the data flowing!");   
    add_chat("Chop chop! Find your exits with haste, there's no time to dawdle!");
    add_chat("Keep it moving, keep it moving! We've got a network to run!");
    add_chat("I'm not here for my health, you know. Let's keep things brisk!");
    add_chat("Keep those bits and bytes marching, no time for a tea break!");
    add_chat("Mind the gaps and mind your manners, move along smartly now!");
    add_chat("No dawdling, we've got packets to deliver and a network to maintain!");
    add_chat("Remember, swift and steady wins the race. Onward you go!");
}
