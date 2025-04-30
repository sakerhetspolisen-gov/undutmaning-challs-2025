#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer2_admin";

public void
create_admin()
{
    set_name("erratic curator");
    add_name("curator");
    set_short("An erratic curator");
    set_long(BSN("This digital manifestation has taken the form of an eccentric curator, dressed in patchwork robes of mismatched "+
                 "colours, each possibly representing a different network protocol or data stream. The curator moves with a frenetic energy, "+
                 "as though managing an unpredictable gallery of abstract digital 'art' in the form of packets. The curator eyes passing "+
                 "packets warily, occasionally dashing over to adjust one, rearranging it as if to improve its 'aesthetic balance'. There's "+
                 "a frantic determination in its movements, as if trying to impose order on the network chaos, but also a resigned acceptance "+
                 "that it's all part of the 'creative process'. You feel uncertain wether a request for help or information will be welcomed "+
                 "or met with a sneer."));

    set_chat_time(10);

    add_chat("A masterpiece in progress, or just another dropped connection?");
    add_chat("True art lies in understanding the network's chaos — or at least pretending to.");
    add_chat("This packet... it could be something. Or maybe not. Let's just see.");
    add_chat("Why rush? The queue will move eventually... or break. Either works.");
    
    set_act_time(10);

    add_act("emote gestures grandly at a floating blob of data, muttering something about 'unappreciated genius'.");
    add_act("emote dashes between two packets, adjusting their positions like a chaotic conductor at an art gallery.");
    add_act("emote glares at a data blob, as if willing it to transmit faster.");
    add_act("emote tilts its head, considering a particularly stubborn blob of data, before rearranging it like a misplaced sculpture.");
}
