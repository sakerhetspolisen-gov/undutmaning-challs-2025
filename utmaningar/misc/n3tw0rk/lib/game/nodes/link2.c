#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LINK;

public void
create_node()
{
    ::create_node();
    set_short("In a network cable");
    set_long(BSN("You are drifting through what appears to be a tunnel, though calling it that "+
        "might be a bit generous. The walls, floor, and ceiling are all of the circular variety, or they would be "+
        "if they were solid, which they most certainly are not. Everything here seems a bit ethereal, like something "+
        "out of a half-forgotten dream. Around you, flashes of light zip by, clumping together into little bundles "+
        "of data, scurrying along with the sort of urgency usually reserved for people who realize they've left the "+
        "oven on. It's abundantly clear that this is not a place where data stop for a cup of tea and a chat, but "+
        "rather a thoroughfare, whisking them away to far more interesting destinations."));

    add_item(({"tunnel", "thoroughfare"}),
        BSN("This isn't your typical, run-of-the-mill tunnel. No, this is more of a metaphysical "+
            "passageway, a thoroughfare for data bustling both upstream and downstream with "+
            "a purpose known only to them. Where they're headed is anyone's guess — possibly somewhere "+
            "important, possibly just out for a stroll."));
    
    add_item(({"wall", "walls", "floor", "ceiling"}),
        BSN("None of these elements seem to be quite real, more like your mind's attempt to "+
            "make sense of something that exists in a reality that's having a bit of an identity crisis. "+
            "They're the kind of walls, floor, and ceiling that might show up in a dream, where you don't "+
            "question them until you wake up and think, ‘Hang on a minute...'"));
    
    add_item(({"data", "bundles", "light","flashes","flash"}),
        BSN("Data streak past you like lightning, trailing streaks of blueish light in their wake. "+
            "It's a light show that makes you feel like you've wandered into a cosmic disco, minus the "+
            "questionable fashion choices. It's almost hypnotic, and you find yourself wondering if you could "+
            "just... stay here, watching the lights, forever..."));
    
    add_item(({"blueish light", "streak","streaks"}),
        BSN("Flashes of light beam through the tunnel, leaving behind streaks of blue that "+
            "linger on your retina like the ghost of a particularly vivid memory. These beams of light "+
            "aren't just pretty — they're busy forming intricate structures, carrying information of "+
            "the utmost importance. Or at least, it seems that way. Perhaps they're just delivering the "+
            "latest gossip from one end of the network to the other."));
    
    add_item(({"packet", "packets", "structure", "structures"}),
        BSN("Packets of data, in all shapes and sizes, zip past you with the kind of determination "+
            "you only see in people who've just realized they're late for something important. "+
            "Where are they going? What are they carrying? And most importantly, did you remember to turn "+
            "the oven off before you left?"));

    add_exit(NODES + "fw1_gi01_layer1", "upstream", 0, 0);
    add_exit(NODES + "switch1", "downstream", 0, 0);

    object ob = clone_object(NPC + "ips_packet_link2");
    ob->move(TO,1);
}
