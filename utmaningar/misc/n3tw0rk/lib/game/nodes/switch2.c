#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit NODE;

public void
create_node()
{
    set_short("In a network switch");
   set_long(BSN("You find yourself in a rather well-organized intersection of the network. Openings in all "+
        "directions beckon like polite doorways, each labeled with the word 'port' and a number. The tunnels beyond "+
        "lead into a mysterious and possibly labyrinthine beyond. Packets bustle about with the air of busy "+
        "office workers — heads down, focused, yet not frazzled. There's no panicked rushing here, just a calm, "+
        "purposeful flow. In the center, on a slightly raised platform, stands an official-looking figure who "+
        "oversees the entire operation with an air of mild authority. Above, the ceiling — if it can be called "+
        "that — glimmers with the occasional flicker of light, hinting at the electrical impulses shooting "+
        "through the network. It's all quite civilized, really."));

    add_item(({"intersection", "network switch", "switch"}),
        BSN("The switch here feels more like a crossroads in a well-organized city than a chaotic junction. It's "+
            "a place where packets gather, exchange nods, and go about their business without any fuss. "+
            "If network nodes had local councils, this one would have neatly trimmed lawns and a committee "+
            "meeting every third Tuesday of the month. And there would be coffee. And biscuits."));
    
    add_item(({"openings", "tunnels", "doorways"}),
        BSN("Each opening is like the entrance to a cozy little tunnel, marked with signs that display the word "+
            "'Port' followed by a number. They have an air of polite efficiency, as though each tunnel is "+
            "inviting you in for a quick chat and a cup of tea before sending you on your way."));
    
    add_item(({"port", "ports", "signs"}),
        BSN("The signs are clear and direct, marked simply as 'port' followed by a number. None of your overly "+
            "complicated, jargon-filled signposts here — just straightforward labels, as if the network itself "+
            "has decided that clarity is next to godliness."));
    
    add_item(({"packets", "packet"}),
        BSN("The packets move around with the businesslike demeanor of clerks in a post office, each with its "+
            "destination already in mind. There's a calm rhythm to their flow, a subtle assurance that "+
            "everything is ticking along just as it should."));
    
    add_item(({"platform", "raised platform"}),
        BSN("In the middle of the room is a slightly raised platform, the sort of thing that an official might "+
            "stand on to make announcements or simply look important. It's not too high — just enough to give "+
            "its occupant a sense of modest authority. A small plaque at the base reads, 'Switch Supervisor: Please "+
            "Do Not Disturb (Unless Necessary).'"));
    
    add_item(({"ceiling", "metaphysical ceiling"}),
        BSN("The ceiling isn't a ceiling in the conventional sense. It flickers gently with occasional flashes "+
            "of light, giving the impression of electrical impulses flitting by overhead. It's as if the network "+
            "is subtly reminding everyone that, yes, important work is being done here."));

    add_exit(NODES + "link7", "port0", "@@port0_check", 0);
    add_exit(NODES + "link8", "port1", "@@port1_check", 0);
    add_exit(NODES + "link9", "port2", "@@port2_check", 0);
    add_exit(NODES + "link10", "port3", "@@port3_check", 0);

    object ob = clone_object(NPC + "switch2");
    ob->move(TO,1);
    set_admin(ob);

    set_hostname("switch-2");
}

int block_me()
{
    write(C(get_admin_name()) + " raises a hand in a gesture that suggests both politeness and absolute refusal.\n");
    say(BSN(C(get_admin_name()) + " raises a hand, stopping " + TP->QN + " with the kind of firm but gentle "+
        "authority you'd expect from a particularly strict librarian."));
    return 1;
}

int port_check(int *mac)
{
    write(C(get_admin_name()) + " gives you a once-over, as if mentally checking a list.\n");
    say(C(get_admin_name()) + " looks at " + TP->QN + " with an expression that suggests a meticulous review is taking place.\n");

    if(TP->always_ok_to_leave())
    {   
        write(C(get_admin_name()) + " nods approvingly, allowing you to continue.\n");
        say(C(get_admin_name()) + " nods at " + TP->QN + ", permitting them to pass with a look of quiet satisfaction.\n");
        return 0;
    }

    object hdr = TP->get_layer_header(1);

    if(!hdr)
    {
        tell_room(TO, C(get_admin_name()) + " says: I'm afraid you lack the proper identification.\n");
        return block_me();
    }

    if(!compare_mac(hdr->get_field_value(1),mac))
    {
        tell_room(TO, C(get_admin_name()) + " says: No, no, that way's not for you, I'm afraid.\n");
        return block_me();
    }

    write(C(get_admin_name()) + " gives a satisfied nod and gestures for you to proceed.\n");
    say(C(get_admin_name()) + " nods approvingly at " + TP->QN + ", allowing it to pass through.\n");
    return 0;
}

int port0_check()
{
    // FW1 Gi0/2
    return port_check(({0x00,0x03,0x32,0xF2,0x33,0x23}));   
}

int port1_check()
{
    // Workstation
    return port_check(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));   
}

int port2_check()
{
    // Admin
    return port_check(({0x00,0x10,0xE3,0x8C,0xEA,0x51}));   
}

int port3_check()
{
    // Printer
    return port_check(({0xC0,0xFB,0xF9,0x0B,0x72,0x9E}));   
}
