#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

object clerk;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("In the transportation layer");
    set_long(BSN("You find yourself in what feels like a bustling, chaotic post office. Small, clerk-like entities shuffle around with clipboards, "+
                 "trying their best to keep track of which data stream goes where. A large, dusty blackboard hangs on one side of the room, filled with "+
                 "scribbles and cryptic numbers, while the clerks fuss around it with a mixture of anxiety and resignation. The scent of "+
                 "legacy workarounds hangs in the air like the faint whiff of old varnish. Everything here technically functions, but it's clear that "+
                 "it's being held together by tradition, guesswork, and the occasional bypassed API. Five large tubes snake along the floor, leading "+
                 "upwards to destinations unknown, each of them carrying strange markings that likely have some forgotten significance. A rickety "+
                 "spiral staircase winds down through a hole in the floor, leading deeper into the system."));

    add_item(({"clerks", "enteties", "clerk-like entities"}),
        BSN("The clerks are harried, overworked figures, clutching clipboards that seem far too full of checkboxes and instructions. They dart from "+
            "one tube to another, muttering under their breath about protocols, ports, and data streams. Every now and then, one drops a clipboard "+
            "with a weary sigh, as though questioning all of life's decisions that led them to this moment. They seem to operate on the edge of barely "+
            "controlled chaos, keeping things running through sheer force of habit rather than any well-implemented system."));

    add_item(({"clipboards"}),
        BSN("The clipboards carried by the clerks are overflowing with checklists, forms, and instructions. Each sheet seems to reflect another layer "+
            "of unnecessary complexity added over the years. Some sections are marked with urgent red notes, while others are scrawled with cryptic "+
            "warnings like 'Do not touch!' and 'Handle with extreme caution.' One clipboard has a handwritten note in the margin: 'API? Never met her.'"));

    add_item(({"tubes", "three tubes", "markings", "strange markings"}),
        BSN("The five large tubes loom on the floor like silent sentinels, connecting this layer to the unknown regions above. They are marked "+
            "with the numbers \"135\", \"445\", \"34887\", \"43891\" and \"55643\" respectively. Perhaps it is some form of cryptic graffiti?"));

    add_item(({"blackboard", "large blackboard", "board"}),
        BSN("The blackboard is a chaotic mess of random strings and numbers. Some sections have been crossed out and rewritten "+
            "so many times that the chalk is starting to wear through the surface. It's clear that this board is meant to keep track of "+
            "something, but its contents have become so convoluted that even the clerks seem confused by it."));

    add_item(({"room", "office", "post office"}),
        BSN("The air here is thick with the weight of old, unresolved decisions. There's a faint scent of burnt circuitry, perhaps from long-forgotten "+
            "hardware. Every breath carries a hint of desperation, as if the room itself knows that its continued existence relies on a precarious "+
            "balancing act between outdated standards and modern needs."));

    add_item(({"staircase", "spiral staircase", "stairs leading down","hole"}),
        BSN("The spiral staircase descends steeply through a hole in the floor. The metal is worn, and some parts seem to have been reinforced "+
            "hastily, perhaps after a near-collapse."));

    add_item(({"text", "strings", "numbers", "random strings", "random numbers", 
               "random strings and numbers", "writings on the blackboard","mess",
               "scribbles", "cryptic numbers", "chalk"}),
        "@@netinfo");
    
    add_exit(NODES + "nowhere", "135", "@@fw_block_fun", 0);
    add_exit(NODES + "nowhere", "445", "@@fw_block_fun", 0);
    add_exit(NODES + "workstation_layer4_mail", "34887", "@@up_check", 0);
    add_port(34887,({ ({ 198,51,100,25 }), 110 }));
    add_exit(NODES + "workstation_layer4_web", "43891", "@@up_check", 0);
    add_port(43891,({ ({ 198,51,100,33 }), 1080 })); 
    add_exit(NODES + "workstation_layer4_spoolsv", "55643", "@@up_check", 0);
    add_port(55643,({ ({ 198,51,100,182 }), 631 })); 
    
    add_exit(NODES + "workstation_layer2", "down", "@@down_check", 0);

    clerk = clone_object(NPC + "workstation_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
    set_extra_msg_netinfo(BSN("You read the text that is written on the blackboard:"));
}

void delayed_mutter(void)
{
    tell_room(TO,C(get_admin_name()) + " mutters: Beats me why they're always there in the first place, really...\n");
}

int fw_block_fun(void)
{
    write(C(get_admin_name()) + " stops you from entering the tube marked "+query_verb()+".\n");
    say(C(get_admin_name()) + " blocks " + TP->QN + " from entering a tube marked "+query_verb()+".\n");
    tell_room(TO,C(get_admin_name()) + " says: Sorry, apparently no one is allowed to go through there!\n");
    set_alarm(0.2,0.0,"delayed_mutter");
    return 1;
}