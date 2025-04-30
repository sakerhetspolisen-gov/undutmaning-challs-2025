#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER2;

public void
create_node()
{
    ::create_node();
    set_short("In the network layer, Gi0/0 interface");
    set_long(BSN("You find yourself on a precarious platform high up the side of a blazing firewall. The heat is "+
            "intense, and the light is so bright it feels like your metaphorical retinas are being seared. "+
            "The platform, wide enough to avoid falling off (if you're careful), seems to be made of the same "+
            "flames as the wall itself. Fortunately, as a sentient packet, you're spared the inconvenience of being set alight. "+
            "A large staircase leads both up and down, while two gateways beckon you into the fiery "+
            "depths of the wall. One of these, however, has been resolutely sealed with a stern-looking sheet of metal. "+
            "Clearly, not all packets are welcome here."));

    add_item(({"platform"}),
        BSN("The platform you're on juts out from the fiery wall, made entirely of flames. It's a good thing you're "+
        "not made of anything flammable. The platform is wide enough to avoid plummeting into the abyss, but there's "+
        "no safety rail to stop an overenthusiastic packet from teetering off the edge. Various packets bustle about, "+
        "each looking more important than the last, although whether they actually are is up for debate."));
    
    add_item(({"packet", "packets"}),
        BSN("Packets of data move about purposefully, each waiting to ascend, descend, or vanish through the gateway "+
        "in the wall. Queues have formed at the staircase and the open gateway, while stern security entities hover nearby, "+
        "ensuring no one tries any funny business."));
    
    add_item(({"gateways"}),
        BSN("Two gateways are set into the wall of flames, promising passage to who knows where. One is welded shut with "+
        "a solid sheet of metal — clearly, someone doesn't want just anyone wandering through."));
    
    add_item(({"gateway"}),
        BSN("Ah, you mean the gateway? Well, one's open, one's closed. It's a bit like choosing between "+
        "the lesser of two evils, except one evil is currently unavailable due to being welded shut."));
    
    add_item(({"open gateway", "opened gateway"}),
        BSN("This gateway leads deeper into the wall of flames. Above it, a rather stern-looking sign makes it "+
        "clear that unauthorized packets need not apply."));
    
    add_item(({"sign"}),
        ".----------------------------------------------------------------.\n"+
        "|  Entrance to Gi0/1 - Only authorized packets beyond this point |\n"+
        "'----------------------------------------------------------------'\n");

    add_item(({"staircase", "stairs"}),
        BSN("The staircase is steep and treacherous, leading both upwards and downwards along the side of the flaming wall. "+
            "It seems to stretch on endlessly, with each step glowing faintly from the intense heat. Climbing these stairs would "+
            "be a harrowing journey for any corporeal being, but as a packet, you merely need to worry about missing your step "+
            "and getting caught in the eternal data loop."));            

    add_exit(NODES + "fw1_gi00_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "fw1_gi00_layer1", "down", "@@down_check", 0);
    // To the other network (DMZ)
    add_exit(NODES + "fw1_gi01_layer2", "gi0/1", "@@gi01_check", 0);

    object ob = clone_object(NPC + "fw1_gi00_layer2");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x21}));
    set_ip(({128,32,137,12,255}));
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


int gi01_check()
{
    write(C(get_admin_name()) + " eyes you with a practiced and suspicious gaze.\n");
    say(C(get_admin_name()) + " scrutinizes " + TP->QN + " carefully.\n");

    // Ok destinations
    //------------------
    // 1. Mailserver: TCP any src and dst 198.51.100.25 - dst port 25 
    // 2. Webserver: TCP any src and dst 198.51.100.15 - dst port 80 and 443
    // 3. DNS queries: UDP nay src and dst 198.51.100.25 - dst port 53
    // 4. Established connection: TCP: 23.253.58.227:443 -> 198.51.100.33:22493 

    object iphdr = TP->get_layer_header(2);
    object layer3_hdr = TP->get_layer_header(3);

    if(!iphdr || !layer3_hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me_fw();
    }


    // 1. 

    if(iphdr->check_dst_addr(({198,51,100,25})) && 
       layer3_hdr->query_protocol() == "TCP" && 
       layer3_hdr->query_dst_port() == 25)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 2.

    if(iphdr->check_dst_addr(({198,51,100,15})) && 
       layer3_hdr->query_protocol() == "TCP" && 
       (layer3_hdr->query_dst_port() == 80 || layer3_hdr->query_dst_port() == 443))
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 3.

    if(iphdr->check_dst_addr(({198,51,100,25})) && 
       layer3_hdr->query_protocol() == "UDP" && 
       layer3_hdr->query_dst_port() == 53)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 4. 

    if(iphdr->check_src_addr(({23,253,58,227})) && iphdr->check_dst_addr(({198,51,100,33})) &&
       layer3_hdr->query_protocol() == "TCP" && 
       layer3_hdr->query_src_port() == 443 && layer3_hdr->query_dst_port() == 22493)
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    tell_room(TO,C(get_admin_name()) + " says: Sorry, you are not allowed through there!\n");
    return block_me_fw();
}