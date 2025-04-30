#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/layer1_admin";

public void
create_admin()
{
    set_name("attendant");
    add_name("bored attendant");
    set_short("A bored attendant");
    set_long(BSN("A mass of bits and bytes that somehow manages to look extremely bored, eventhough "+
        "it doesn't really have a facial expression, or indeed a face. It seems to be wearing some sort "+
        "of uniform and it is casualy leaning aganist the desk in front of it. Eventhough it looks to be "+
        "a quite unattentive attendant you could probably request some information from it."));
      
    set_chat_time(30);

    add_chat("So, what's your bussiness here today then?");   

    set_act_time(20);

    add_act("blank");
    add_act("sigh");    
    add_act("grumble");    
}
