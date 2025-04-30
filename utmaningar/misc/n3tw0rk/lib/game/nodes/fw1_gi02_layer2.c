#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER2;

public void
create_node()
{
    ::create_node();
    set_short("In the network layer, Gi0/2 interface");
    set_long(BSN("You find yourself on a platform that juts out from the side of a towering wall of flames. "+
        "Strangely enough, despite the roaring fire just a few feet away, this place exudes a sense of calm. "+
        "Perhaps it's the slightly warmer air or the distant hum of activity that suggests you're on the more "+
        "relaxed side of things. The platform itself seems almost tranquil, with a wide staircase leading down "+
        "and a narrower one winding upwards. Two openings in the wall of flames catch your eye, though one appears "+
        "to be firmly sealed off, as if to say, 'No entry, not today, not ever.'"));

    add_item(({"platform","room","area"}),
        BSN("This platform seems like a peaceful corner of the network, neither bustling nor deserted, but rather "+
            "a place where packets pass through on their way to somewhere important. It's quieter than the other "+
            "sides of the firewall, and there's a certain orderliness to the comings and goings here."));

    add_item(({"side","fire","wall","wall of fire","flames","wall of flames","flame wall"}),
        BSN("The wall of fire, though still imposing, feels somewhat less menacing from this side. "+
            "It stretches as far as you can see, but there's a sense that it's more for show — or a "+
            "reminder — than for burning anyone who dares to approach."));

    add_item(({"staircase","staircases"}),
        BSN("A wide staircase leads downwards, inviting a steady flow of packets, while a narrower staircase heads up "+
            "to quieter, less trafficked areas."));

    add_item(({"wide staircase"}),
        BSN("The wide staircase seems to be the main thoroughfare, used by most of the packets passing through. "+
            "It has the well-worn look of something that's seen a lot of use, but it's sturdy and reliable."));

    add_item(({"narrow staircase"}),
        BSN("The narrow staircase, by contrast, looks like it's for the more adventurous types, or perhaps those with "+
            "specific business higher up. It's there if you need it, but most packets seem content to take the broader path."));

    add_item(({"packet","packets"}),
        BSN("Packets move through here in a steady, orderly fashion. They're focused, busy, and generally going about their "+
            "business without too much fuss. It's the sort of place where things get done efficiently, without unnecessary "+
            "drama."));

    add_item(({"opening","openings"}),
        BSN("Two openings lead through the wall of flames. One is open, inviting passage, while the other has been "+
            "securely blocked off, as if to say that whatever lies beyond is no longer an option."));

    add_item(({"blocked opening","blocked"}),
        BSN("The blocked opening has been welded shut with a thick sheet of metal. Clearly, someone decided "+
            "that going through there wasn't in the cards, at least not anymore."));

    add_item(({"open","open opening","other opening"}),
        BSN("The open opening leads through the wall of flames to the other side. A sign above it offers a "+
            "friendly reminder to mind your step and keep your wits about you."));

    add_item(({"sign"}),
        ".---------------------------------------------------------------.\n"+
        "| Entrance to Gi0/1 - Mixed zone. Take care and be vigilant!    |\n"+
        "'---------------------------------------------------------------'\n");

    add_exit(NODES + "fw1_gi02_layer3", "up", "@@up_check", 0);
    add_exit(NODES + "fw1_gi02_layer1", "down", "@@down_check", 0);
    // To the other network (DMZ)
    add_exit(NODES + "fw1_gi01_layer2", "gi0/1", "@@gi01_check", 0);

    create_admin(NPC + "fw1_gi02_layer2");
    
    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x23}));
    set_ip(({198,51,100,129,255}));

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
    write(C(get_admin_name()) + " examines you carefully.\n");
    say(C(get_admin_name()) + " examines " + TP->QN + " carefully.\n");

    // Ok destinations
    //------------------
    // 1. All IP:s - All destinations on DMZ, nothing else
    // 2. Admin can connect anywhere

    object iphdr = TP->get_layer_header(2);
    object layer3_hdr = TP->get_layer_header(3);

    if(!iphdr || !layer3_hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me_fw();
    }

    // 1. 

    if(iphdr->check_dst_addr(({198,51,100,0}),({255,255,255,128})))
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    // 2.

    if(iphdr->check_src_addr(({198,51,100,194})))
    {
        tell_room(TO,C(get_admin_name()) + " says: Your identification seems to be in order. Welcome!\n");
        allow_me_fw();
        iphdr->decrease_ttl();
        return 0;
    }

    tell_room(TO,C(get_admin_name()) + " says: Sorry, you are not allowed through there!\n");
    return block_me_fw();
}
