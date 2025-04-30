#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("receptionist");
    add_name("efficient receptionist");
    set_short("An efficient receptionist");
    set_long(BSN("An entity wearing what looks like business casual attire. It projects "+
        "a feeing of efficiency, quiet but busy. It is looking quite stern, but has an "+
        "otherwise approachable demeanor. Calm and composed it greets packets as they approach "+
        "its desk. Perhaps it is possible to request some information from it?"));
      
    set_chat_time(10);

    add_chat("Welcome! What's your business with us today?");   
    add_chat("Do you have the correct headers ready? Otherwise, please do not take up my time?");
    add_chat("I hope you will be happy with our service today.");

    set_act_time(10);

    add_act("emote checks something on the small screen.");
    add_act("emote fills out some forms.");    
}
