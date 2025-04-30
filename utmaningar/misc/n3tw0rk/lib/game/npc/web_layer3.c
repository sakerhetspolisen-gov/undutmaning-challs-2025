#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer3_admin";

public void
create_admin()
{
    set_name("usher");
    add_name("casual usher");
    add_name("entity");
    set_short("A laid-back usher");
    set_long(BSN("The usher, leaning casually against the glowing switchboard, wears a jacket that looks like it once "+
                 "aspired to be formal, but has since given up. Beneath it, a rumpled white polo shirt and a pair of "+
                 "well-worn jeans suggest a distinct lack of interest in formality, as if it were told to wear a uniform "+
                 "and thought, 'close enough.' Its job appears to involve making sure packets don't get too lost or "+
                 "confused, but there's a relaxed, almost laissez-faire attitude about it, like someone who's long ago "+
                 "learned that most problems tend to solve themselves if given enough time. Still, if a packet looks "+
                 "particularly lost or nervous, the usher is quick to offer a friendly nod and point them in the right "+
                 "direction with a wink and a grin — or the requested information."));

    add_item(({"jacket", "polo shirt", "jeans"}),
        BSN("The usher's jacket once had pretensions of grandeur, but now it hangs open over a white polo shirt and a "+
            "pair of jeans that have seen better days. It's a curious mix of 'trying' and 'barely trying at all.'")); 

    set_chat_time(10);

    add_chat("All right, everyone, move along. Nothing to see here, just business as usual.");
    add_chat("Confused? It happens to us all sometimes. Just request some help or information.");
    add_chat("You'll be fine, don't worry. Just follow the lights. They'll take you where you need to go.");
    add_chat("Tube 80 or 443? Ah, yes, the popular destinations. Always busy this time of day.");
    add_chat("No rush, no rush. Plenty of time to make it to your destination.");
    add_chat("Lost? Not a problem. I've got you covered. Just head up the tube and you'll be back on track.");

    set_act_time(15);

    add_act("emote adjusts its jacket absentmindedly, as if trying to make it look more formal, but quickly gives up.");
    add_act("emote glances at the tubes with a casual nod, keeping an eye on the flow of packets.");
    add_act("emote flips through a digital clipboard, though it seems more for show than necessity.");
}
