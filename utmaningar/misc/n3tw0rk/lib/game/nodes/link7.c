#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("You find yourself in a corridor that hums with a serene energy, like a place where "+
        "data and purpose meld into a tranquil dance. The surroundings are a gentle blend of soft hues and faint glows, "+
        "with walls that seem to ripple slightly as if they're in the midst of a pleasant dream. The corridor stretches out "+
        "before you in both directions. One way leads back towards a more tumultuous realm you've recently left, while the other "+
        "opens up to what seems like a welcoming crossroads further downstream. This crossroads might very well be a bustling hub "+
        "of activity, where decisions and directions are made with a bit more flair. Perhaps it's worth a visit?"));

    add_item(({"corridor","space","area","path"}),
        BSN("The corridor is a place of gentle hums and soft glows, where the fabric of reality seems to bend a bit "+
            "to accommodate the ever-flowing stream of data. It's more of a gentle journey than a stern passage."));

    add_item(({"walls","floor","ceiling"}),
        BSN("The walls, floor, and ceiling of this corridor undulate softly, like the ripples on a pond. They emit a faint, "+
            "soothing light that suggests a place of comfort rather than a place of harsh reality."));

    add_item(({"hum","gentle hum"}),
        BSN("The hum is a steady, calming presence, like the comforting sound of distant machinery working in perfect harmony. "+
            "It's less about noise and more about feeling, a vibration that resonates with the smooth flow of data."));

    add_item(({"direction","way"}),
        BSN("To one side, the corridor beckons back towards a place of more intense activity. To the other, it opens up "+
            "into what seems like a crossroads or an intersection further downstream. This juncture might lead to a more vibrant "+
            "hub where the data streams converge and decisions are made with a flourish."));
       
    add_item(({"crossroads", "intersection", "junction"}),
        BSN("The crossroads further downstream seems to pulse with life and purpose. You can almost imagine packets tipping "+
            "their metaphorical hats to each other as they decide which direction to take, a courteous nod here, a brisk "+
            "salute there. It's a place where the flow of data carries a common purpouse, and a touch of personality."));

    add_item(({"glows", "faint glows", "hues"}),
        BSN("The faint glows and soft hues that surround you change ever so slightly as you move along. Blues and greens dominate, "+
            "giving the space a serene quality, while occasional pulses of light ripple through, like tiny flashes of insight passing "+
            "between busy minds in quiet contemplation."));

    add_exit(NODES + "fw1_gi02_layer1", "upstream", 0, 0);
    add_exit(NODES + "switch2", "downstream", 0, 0);
}
