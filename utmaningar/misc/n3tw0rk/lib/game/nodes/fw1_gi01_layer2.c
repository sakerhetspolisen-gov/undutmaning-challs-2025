#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER2;

public void
create_node()
{
    ::create_node();
    set_short("In the network layer, Gi0/1 interface");
    set_long(BSN("You stand on a platform precariously wedged between two towering walls of fire, "+
        "which meet at a perfect right angle as if they were on unusually good terms. Unfortunately, the fire doesn't "+
        "continue in the other two directions, leaving nothing but a yawning void. Openings in the fiery walls beckon "+
        "you towards the unknown beyond, while staircases, resembling particularly fiery snakes, curl both upwards and "+
        "downwards from the platform. The whole scene gives the impression that the laws of physics are taking a very "+
        "long tea break."));

    add_item(({"platform"}),
        BSN("The platform is suspiciously suspended between the two walls of fire, defying both logic and gravity. "+
        "What it's made of is anyone's guess — perhaps the collective sighs of exasperated engineers, or the last shreds "+
        "of common sense. Either way, it's holding up for now, so best not to think too hard about it."));
    
    add_item(({"packet", "packets"}),
        BSN("Packets of various shapes and sizes bustle about the platform, some queuing up for the journey upward, "+
        "others bracing themselves for the descent. They seem to have a better idea of where they're going than you do."));
    
    add_item(({"opening", "openings", "gateways"}),
        BSN("Two gateways pierce the flaming walls, leading to who knows where. One is under the watchful eye of "+
        "administration, guarded as though the fate of the world depended on it. The other, by contrast, seems much more "+
        "casually monitored, as if even the administrators couldn't muster up the energy to be overly concerned."));
    
    add_item(({"gateway", "opening"}),
        BSN("Are you talking about the one that's closely guarded, or the one that could really use a bit more attention?"));

    add_item(({"guarded gateway", "closely guarded gateway", "guarded opening", "closely guarded opening"}),
        BSN("This gateway is diligently guarded as if it's the entrance to a particularly exclusive club. A small sign "+
        "hangs above it, adding a touch of officialdom to the whole affair."));
    
    add_item(({"sign"}),
        BSN("Ah, which one do you mean? The large one or the small one?"));

    add_item(({"small sign"}),
        ".----------------------------------------------------------------.\n"+
        "| Entrance to Gi0/2 - Only authorized packets beyond this point. |\n"+
        "'----------------------------------------------------------------'\n");
    
    add_item(({"relaxed gateway", "more relaxed gateway", "relaxed opening", "more relaxed opening",
               "loosely watched gateway", "loosely watched opening","unattended opening",
               "opening that needs attention","opening that could use a bit more attention",
               "opening that could use more attention"}),
        BSN("This gateway, unlike its strict neighbor, seems to be on a permanent coffee break. "+
        "A large sign hangs above it, filled with dire warnings and vague threats that make you wonder if "+
        "you're really in the right place. Or maybe that's the point."));
    
    add_item(({"large sign"}),
        ".---------------------------------------------------------------------------.\n"+
        "| Entrance to Gi0/0 - Take care! Here be monsters!                          |\n"+
        "|                     Hazardous conditions exist. Travel at your own risk!  |\n"+
        "'---------------------------------------------------------------------------'\n");

    add_exit(NODES + "fw1_gi01_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "fw1_gi01_layer1", "down", "@@down_check", 0);
    // To the other network (Internet)
    add_exit(NODES + "fw1_gi00_layer2", "gi0/0", "@@gi00_check", 0);
    // To the other network (Office)
    add_exit(NODES + "fw1_gi02_layer2", "gi0/2", "@@gi02_check", 0);

    object ob = clone_object(NPC + "fw1_gi01_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x22}));
    set_ip(({198,51,100,1,127}));
    set_hostname("fw1");
}

int block_me_fw()
{
    write(C(get_admin_name()) + " forcefully stops you from passing through.\n");
    say(C(get_admin_name()) + " forcefully stops " + TP->QN + " from going through the entrance.\n");
    return 1;
}

int allow_me_fw()
{
    write(C(get_admin_name()) + " steps aside and lets you through.\n");
    say(C(get_admin_name()) + " steps aside and lets " + TP->QN + " pass through the entrance.\n");
    return 0;
}


int gi02_check()
{
    write(C(get_admin_name()) + " examines you carefully.\n");
    say(C(get_admin_name()) + " examines " + TP->QN + " carefully.\n");

    // Ok destinations
    //------------------
    // 1. Established connection TCP: 198.51.100.194:21456 (admin) -> 198.51.100.15:22 (webserver)
    // 2. Established connection TCP: 198.51.100.199:43891 (workstation) -> 198.51.100.33:1080 (proxy)
    // 3. Established connection TCP: 198.51.100.199:34887 (workstation) -> 198.51.100.25:110 (mail)

    object iphdr = TP->get_layer_header(2);
    object layer3_hdr = TP->get_layer_header(3);

    if(!iphdr || !layer3_hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me_fw();
    }

    // 1. 

    if(iphdr->check_src_addr(({198,51,100,15})) && iphdr->check_dst_addr(({198,51,100,194})) &&
       layer3_hdr->query_protocol() == "TCP" && 
       layer3_hdr->query_src_port() == 22 && layer3_hdr->query_dst_port() == 21456)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 2.

    if(iphdr->check_src_addr(({198,51,100,33})) && iphdr->check_dst_addr(({198,51,100,199})) && 
       layer3_hdr->query_protocol() == "TCP" && 
       layer3_hdr->query_src_port() == 1080 && layer3_hdr->query_dst_port() == 43891)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 3.

    if(iphdr->check_src_addr(({198,51,100,25})) && iphdr->check_dst_addr(({198,51,100,199})) && 
       layer3_hdr->query_protocol() == "TCP" && 
       layer3_hdr->query_src_port() == 110 && layer3_hdr->query_dst_port() == 34887)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }


    tell_room(TO,C(get_admin_name()) + " says: Sorry, you are not allowed through there!\n");
    return block_me_fw();
}

int gi00_check()
{
    write(C(get_admin_name()) + " looks you over in an unintrested manner.\n");
    say(C(get_admin_name()) + " gazes at " + TP->QN + ", looking marginaly interested.\n");

    // Ok destinations
    //------------------
    // 1. Everywhere that has an internet address 

    object iphdr = TP->get_layer_header(2);

    if(!iphdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me_fw();
    }


    if(iphdr->check_dst_addr(({198,51,100,0}),({255,255,255,0})))
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, but you are not supposed to go that way!\n");
        return block_me_fw();
    }

    tell_room(TO,C(get_admin_name()) + " says: Take care out there! It can be a rough place...\n");
    allow_me_fw();
    iphdr->decrease_ttl();
    return 0;
}   