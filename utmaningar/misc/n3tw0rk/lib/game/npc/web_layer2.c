#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("network concierge");
    add_name("concierge");
    add_name("supervisor");
    set_short("A busy network concierge");
    set_long(BSN("The network concierge, an affable digital entity, greets you with the kind of polished professionalism "+
                 "you might expect from the host of an exclusive gala. With a practiced smile and a subtle nod, it manages "+
                 "the endless stream of packets as though they were high-profile guests at a grand event, each one being "+
                 "handled with care and precision. Despite the swirling chaos of the nightclub-like environment, this concierge "+
                 "radiates calm, its movements fluid and practiced. Whether packets are ascending or descending, the concierge "+
                 "makes sure everything runs as smoothly as the finest clockwork, offering just the right nudge of encouragement "+
                 "to keep things on track. It would most certainly provide you with help or information if you request it."));

    add_item(({"clipboard", "notes"}),
        BSN("The concierge keeps a sleek, digital clipboard in hand, though it seems more for show than necessity. It occasionally "+
             "glances at it, ticking off tasks with a flourish, more for the satisfaction of appearing busy than from any real need.")); 

    set_chat_time(10);

    add_chat("Welcome, welcome! Let's keep things moving along, shall we? The network never sleeps.");
    add_chat("Everything in order? Splendid! Off you go, to the next destination!");
    add_chat("Up, down, sideways — it matters not, as long as everyone gets to where they need to be.");
    add_chat("No need to rush, but do try not to dawdle. We like to keep the packets flowing smoothly here.");
    
    set_act_time(15);

    add_act("emote adjusts its immaculate digital uniform with a flourish, offering a reassuring nod to a passing packet.");
    add_act("emote flicks through its clipboard, ticking off tasks that seem to complete themselves.");
    add_act("emote gives a friendly wave to a newly-arrived packet, sending it on its way with a smile.");
}

