#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/switch_admin";

public void
create_admin()
{
    set_name("traffic supervisor");
    add_name("supervisor");
    add_name("figure");
    add_name("official-looking figure");
    set_short("A traffic supervisor");

    set_long(BSN("Perched on the raised platform is the traffic supervisor, a figure that exudes an air of quiet "+
            "authority mixed with just a hint of kindly fussiness. It stand with a clipboard in one hand and an "+
            "almost magical quill in the other, furiously jotting down notes that seemingly vanish into the ether. "+
            "Its eyes flicker over the ebb and flow of packets, nodding approvingly at those that go about their "+
            "business with proper haste and gently scolding those who dare linger. You sense that if packets ever "+
            "needed to complete paperwork, this supervisor would have every necessary form neatly arranged, labeled, "+
            "and color-coded, all while wearing a satisfied smile."));


    set_chat_time(10);

    add_chat("Come along now! Let's keep this data moving in an orderly fashion, shall we?");
    add_chat("A smooth flow is a happy flow! No dawdling, please!");
    add_chat("You there, at port2! Yes, you, don't look so bewildered. Just keep moving!");
    add_chat("Oh, dear, packets in a hurry always forget their MAC address…");
    add_chat("Right, right, less chit-chat, more moving! We've got a network to keep running!");
    add_chat("Remember: a well-organized packet is a happy packet!");
    add_chat("If you don't have your identification in order, I'm afraid you shall not pass. Policy is policy, you know.");
        
    set_act_time(10);

    add_act("The traffic supervisor taps its clipboard, producing a faint *click* with each tap, as if ticking off some unseen checklist.");
    add_act("The supervisor adjusts its glasses, squinting at a passing packet before nodding approvingly.");
    add_act("With a flick of the quill, the supervisor scribbles something on its clipboard, murmuring to themselves.");
    add_act("The supervisor raises a finger, pauses as if considering a lecture, then shakes its head and waves the packet on.");
}
