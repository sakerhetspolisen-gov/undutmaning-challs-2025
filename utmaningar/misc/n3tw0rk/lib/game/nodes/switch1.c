#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit NODE;

public void
create_node()
{
    set_short("In a network switch");
   set_long(BSN("You find yourself at a crossroads in the bustling realm of bits and bytes. This is no ordinary "+
        "crossroads, mind you — it's the kind of place where decisions are made, where paths diverge, and where "+
        "packets must choose their destiny, or at least which exit to take. In the center of this grand junction, "+
        "a strange figure stands on a raised circular platform, surveying the scene with an air of someone who knows "+
        "far more than they're letting on. All around the perimeter, gateways beckon, some open and inviting, "+
        "others closed and decidedly less welcoming. Above you, the ceiling looms like a dome made of woven wires "+
        "and circuits, though you can't help but wonder if it's all just an elaborate illusion concocted by your "+
        "overworked imagination."));

    add_item(({"crossroad", "crossroads"}),
        BSN("You are at the heart of a crossroads, where the endless streams of data converge and then split off "+
        "again, like some sort of digital roundabout. Exits are spaced evenly around you, each one identified by "+
        "a sign that probably made perfect sense to whoever put it up. You vaguely remember arriving through one "+
        "of these exits, but which one exactly? Well, that's the mystery, isn't it?"));
    
    add_item(({"entrance", "entrances", "exit", "exits"}),
        BSN("Lining the perimeter of the crossroads, these entrances and exits are your way in or out of this "+
        "data hub. Each is marked by a sign reading \"port\" followed by a number, a system that is probably "+
        "intuitive to someone, somewhere. Through the open gateways, you can see packets bustling about their "+
        "business, either leaving for distant destinations or arriving here with the kind of determination normally "+
        "reserved for people who've just realized they left the kettle on."));
    
    add_item(({"packet", "packets"}),
        BSN("Packets of data, in all shapes and sizes, scuttle in and out of the various exits like ants on a sugar "+
        "high. They're all heading somewhere, or coming from somewhere, or possibly both, though none of them seem "+
        "to have the time to stop and chat about it."));
    
    add_item(({"sign", "signs"}),
        BSN("Signs are posted above each exit, boldly labeled \"port\" followed by a number. They're the sort of "+
        "signs that seem helpful until you realize they're not giving you any more information than you already had, "+
        "but at least they're trying."));
    
    add_item(({"platform", "circular platform"}),
        BSN("A raised circular platform occupies the center of the crossroads. From here, one can survey the comings "+
        "and goings of the packets and get a good view of the general mayhem that defines this place. It's the kind of "+
        "place where decisions are made, probably by the figure standing on it with a somewhat smug expression."));
    
    add_item(({"perimeter"}),
        BSN("The exits and entrances that make up the crossroads are evenly spread around the perimeter, forming "+
        "a neat, if somewhat intimidating, circle of possible pathways."));
    
    add_item(({"ceiling", "wires", "circuits", "wire", "circuit"}),
        BSN("The ceiling above you is an intricate weave of wires and circuits, forming a dome that looms overhead "+
        "like the sky on a particularly technological planet. However, if you stare too long, you might start to "+
        "wonder if it's all just an illusion — a trick of the mind, or perhaps an attempt by the universe to give "+
        "you a headache."));

    add_exit(NODES + "link2", "port0", "@@port0_check", 0);
    add_exit(NODES + "link3", "port1", "@@port1_check", 0);
    add_exit(NODES + "link4", "port2", "@@port2_check", 0);
    add_exit(NODES + "link5", "port3", "@@port3_check", 0);
    add_exit(NODES + "link6", "port4", "@@port4_check", 0);

    object ob = clone_object(NPC + "switch1");
    ob->move(TO,1);
    set_admin(ob);

    set_hostname("switch-1");
}

int block_me()
{
    write(C(get_admin_name()) + " quicky stretches out an arm to block you.\n");
    say(BSN(C(get_admin_name()) + " quickly stretches out an arm and blocks "+TP->QN+" from leaving the crossroads."));
    return 1;
}

int port_check(int *mac)
{
    write(C(get_admin_name()) + " examines you carefully.\n");
    say(C(get_admin_name()) + " examines " + TP->QN + " carefully.\n");

    if(TP->always_ok_to_leave())
    {   
        write(C(get_admin_name()) + " lets you float through the exit.\n");
        say(C(get_admin_name()) + " lets " + TP->QN + " float away.\n");
        return 0;
    }

    object hdr = TP->get_layer_header(1);

    if(!hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: You lack the proper identification!\n");
        return block_me();
    }

    if(!compare_mac(hdr->get_field_value(1),mac))
    {
        tell_room(TO,C(get_admin_name()) + " says: You are not supposed to go that way!\n");
        return block_me();
    }

    write(C(get_admin_name()) + " lets you float through the exit.\n");
    say(C(get_admin_name()) + " lets " + TP->QN + " float away.\n");
    return 0;
}


int port0_check()
{
    // FW1 Gi0/1
    return port_check(({0x00,0x03,0x32,0xF2,0x33,0x22}));   
}

int port1_check()
{
    // Proxy
    return port_check(({0xE4,0x3A,0x6E,0x00,0x32,0x67}));   
}

int port2_check()
{
    // IPS
    return port_check(({0x3C,0x7D,0x1C,0xF3,0x44,0x0C}));   
}

int port3_check()
{
    // Web
    return port_check(({0x00,0x14,0x22,0x03,0x5A,0xB2}));   
}

int port4_check()
{
    // Mail
    return port_check(({0x00,0x14,0x22,0xFE,0x61,0x12}));
}
