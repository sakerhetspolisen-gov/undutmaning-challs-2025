#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

object clerk;

int do_use_switchboard(string str);

void init(void)
{
    ::init();
    add_action(do_use_switchboard,"pull");
    add_action(do_use_switchboard,"push");
}

public void
create_node()
{
    ::create_node();
    set_short("In the transportation layer");

    set_long(BSN("You find yourself drifting in what can only be described as the bustling, and "+
        "somewhat chaotic, transportation layer of a rather shady computer's network stack. "+
        "Packets of various shapes and sizes whizz past you in every direction, some with purpose, "+
        "others with an air of aimlessness as if they've lost their way — or perhaps they're just "+
        "pretending to. Above you, a tube labeled '31337' leads upwards, while a gaping opening "+
        "below beckons ominously. A rather imposing switchboard looms nearby, blinking and beeping "+
        "with a sense of self-importance, and off to one side, a large blackboard hangs in the air, "+
        "scribbled with all sorts of cryptic information."));

    add_item(({"stack", "network stack"}),
        BSN("You quickly realize that this is the network stack of the computer you're currently "+
            "inhabiting. The stack is a towering construct of sophisticated, and possibly dubious, "+
            "code designed to facilitate the computer's communications with other machines on the "+
            "network — no doubt in a manner that skirts the edges of legality."));
    
    add_item(({"packet", "packets"}),
        BSN("Packets of data flash by at breakneck speeds, darting up and down the layers with an "+
            "urgency that suggests they're carrying important, if not entirely above-board, information."));
    
    add_item(({"computer"}),
        BSN("You're nestled within the memory of a computer that gives off a distinct impression of "+
            "being up to no good. From where you're positioned, you can't see much of its nefarious "+
            "activities, but you can certainly sense them."));
    
    add_item(({"tube"}),
        BSN("A tube that ascends upwards, ominously marked with the number '31337' — a number that "+
            "might indicate something elite, or perhaps just a cleverly disguised gateway to mischief."));
    
    add_item(({"switchboard","switch board","switch-board"}),
        BSN("The switchboard bristles with levers, buttons, and tags, all of which seem designed to "+
            "manage the flow of data through this murky layer. It blinks and beeps as if it knows it's "+
            "controlling something significant — or possibly something a bit shady."));
    
    add_item(({"lever","levers","button","buttons"}),
        BSN("The levers and buttons on the switchboard seem integral to controlling the network's "+
            "flow of information, though it's unclear whether they're guiding it along a straight "+
            "path or leading it astray."));
    
    add_item(({"tag","tags"}),
        BSN("The tags attached to the various controls on the switchboard offer a glimpse into its "+
            "operations, bearing labels like OPEN, CLOSE, ACCEPT, and DENY — simple commands, yet "+
            "capable of wielding considerable power over the data coursing through this layer."));
    
    add_item(({"opening"}),
        BSN("A wide, slightly foreboding opening below you leads down to the lower layers of the "+
            "network stack, where who knows what awaits."));
    
    add_item(({"blackboard","large blackboard","text"}),
        "@@netinfo");
        

    add_exit(NODES + "start_node", "31337", "@@up_check", 0);
    add_exit(NODES + "evil_layer2", "down", "@@down_check", 0);

    clerk = clone_object("/game/npc/evil_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_hostname("evil");
    set_mac(({0xE0,0x2C,0xB2,0x01,0xC0,0xA2}));
    set_ip(({128,32,137,251,255}));
    set_extra_msg_netinfo("You look at the blackboard, reading the text you see on it:\n");
}

int do_use_switchboard(string str)
{
    if(str == "button" || str == "buttons" || str == "lever" || str == "levers")
    {
        write(C(get_admin_name()) + " stops you.\n");
        say(C(get_admin_name()) + " stops " + TP->QN + " from interacting with the switchboard.\n");
        tell_room(TO,C(get_admin_name()) + " says: You leave that alone!\n");
        return 1;
    }

    return notify_fail(C(query_verb()) + " what?\n");
}