#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("artistic courier");
    add_name("courier");
    add_name("entity");
    set_short("An artistic courier");
    set_long(BSN("This manifestation takes the form of a slightly disheveled courier, draped in a patchwork uniform adorned with colorful "+
                 "splashes of ink and faded labels. With a clipboard overflowing with delivery slips and scribbled sketches, it seems to "+
                 "embody both the chaos of the delivery process and the whimsical spirit of creativity. The courier moves with a nervous "+
                 "energy, glancing at the pulsing tubes and muttering about 'inspired ideas lost in transit' and 'the abstract nature of "+
                 "delivery routes.' Its eyes dart between the large tube marked '631' and the cluttered bulletin board, where half-finished "+
                 "art pieces mingle with frantic notes, as if the chaos itself is part of the artistic process. You get the sense that "+
                 "while this courier is determined to keep things moving, it might just get swept up in a torrent of creative mayhem at any moment. "+
                 "It seems focused enough to answering any requests for help tough, should they present themselves."));
    
    set_chat_time(10);
    
    add_chat("Why is it that creativity and chaos always seem to go hand in hand? I swear, these tubes are like art installations!");
    add_chat("Lost in transit? Perhaps it just found a new muse instead.");
    add_chat("The tube's clogged again! It's like trying to channel inspiration through a block of concrete.");
    add_chat("Do they even realize how heavy some of these data blobs are? It's like carrying an abstract sculpture in a postman's sack.");
    
    set_act_time(10);
    
    add_act("emote flourishes a delivery slip as if it were a piece of art, only for it to get blown away by an errant draft.");
    add_act("emote inspects a blob of data, nodding thoughtfully as if critiquing a painting.");
    add_act("emote peers up at the thick tube marked '631', wondering aloud if it could be transformed into a modern art piece.");
    add_act("emote fumbles with a data blob that slipped off the end of a tube, juggling it like a performer before sheepishly placing it back into the system.");
}
