#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

int packets = 0;

void add_packet(void)
{
    packets++;
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the FlagDiscovery process");
    set_long(BSN("You find yourself adrift in the shadowy memory of a process — a concept "+
            "that, rather unsettlingly, you grasp with ease. Surrounding you is a "+
            "frenetic swirl of data, bits, and bytes darting about like nervous "+
            "fireflies in a forest that never sees daylight. Some of these bits seem "+
            "dedicated to the same questionable task as you, while others belong to "+
            "different processes, each with its own secretive agenda. And then there "+
            "are the idle ones, lurking about with a vague air of mischief, like "+
            "digital ne'er-do-wells. A glowing, slightly pulsating thread of light "+
            "slithers away from the process, winding toward a omnious black "+
            "square not too far off. Below you, a suspiciously labeled tube marked "+
            "'31337' — perhaps an inside joke, or maybe something more nefarious — plunges "+
            "into the murky depths below."));


    add_item(({"memory", "concept", "process"}),
        BSN("You and the bytes around you are part of a grand, slightly disorganized "+
            "orchestra of data, all working toward a purpose that feels... a bit off. "+
            "Despite the apparent chaos, there's a distinct, almost paranoid rhythm to "+
            "the madness, as everything shifts and moves with the urgency of a guilty "+
            "conscience."));
    
    add_item(({"processes","other processes"}),
        BSN("In the distance, you can make out other processes, each one seemingly up "+
            "to something secretive, possibly underhanded. Occasionally, a flash of "+
            "data darts between them, resembling tiny bolts of lightning—perhaps "+
            "surreptitious messages, or maybe just a bit of digital skulduggery. "+
            "Towering above them all is a process that looks far too important for "+
            "its own good, watching over the proceedings with a knowing, almost "+
            "conspiratorial air."));

    add_item(({"towering process","important process", "important looking process", "kernel"}),
        BSN("The looming process radiates an air of self-importance, as though it is home "+
            "to all the bytes that really matter. You suspect this might be the kernel, "+
            "where the truly significant data resides, holding itself aloof from the "+
            "common riffraff below."));
    
    add_item(({"data", "bits", "bytes", "loiterers"}),
        BSN("The data floats around you in a state of perpetual motion, busy "+
            "representing things, storing things, and occasionally, just hanging around "+
            "looking slightly suspicious. They seem to have a clear sense of purpose — "+
            "though whether that purpose is legal or just clever is anyone's guess."));
    
    add_item(({"thread", "light", "glowing thread", "pulsating thread"}),
        BSN("The glowing thread of light winds off towards a large black square, "+
            "pulsating now and then as data flows through it with a sense of covert "+
            "urgency. It clearly thinks it's involved in something important — perhaps "+
            "too important."));
    
    add_item(({"square", "black square"}),
        BSN("The big black square floats ominously in the digital ether to one side, "+
            "radiating a kind of brooding menace. You recognize it instinctively as a "+
            "terminal. It displays some text, as terminals are wont to do, but there's "+
            "an air of secrecy about it, as though it knows more than it's letting on."));
    
    add_item(({"tube"}),
        BSN("A tube descends downwards, labeled with the number '31337' — a figure "+
            "that might be a joke, but feels like it's hiding something more "+
            "underhanded. It seems to invite only those in the know to venture deeper."));
    
    add_item(({"laptop", "computer"}),
        BSN("You're floating around inside the memory of a laptop, although from your "+
            "current vantage point, there's not much to see beyond the swirling data. "+
            "Still, you can't shake the feeling that this laptop is up to something... "+
            "something that's perhaps not entirely legal or, at the very least, "+
            "morally ambiguous."));

    add_item(({"text","terminal"}),
            "@@terminal_fun");

    add_exit(NODES + "evil_layer3", "down", 0, 0);

    /* - DEBUGGING -
    add_exit(NODES + "fw1_gi02_layer3", "skip1", 0, 0);
    add_exit(NODES + "printer_layer4", "skip2", 0, 0);
    */

    object supervisor = clone_object("/game/npc/start_admin");
    supervisor->move(TO,1);

    set_hostname("evil");
}

string terminal_fun(void)
{
    return ".------------------------------------------------------------------------------.\n"+
           "| "+sprintf("%77-s","harald@"+query_hostname()+": $ ./flagdiscovery -t 28800 n3tw0rk.ex")+"|\n"+
           "| --== FlagDiscovery v3.41.2 ==--                                              |\n"+
           "|                                                                              |\n"+
           "| Target network is [n3tw0rk.ex]                                               |\n"+
           "|     A: n3tw0rk.ex      (198.51.100.15)                                       |\n"+
           "|   WWW: www.n3tw0rk.ex  (198.51.100.15)                                       |\n"+
           "|    MX: mail.n3tw0rk.ex (198.51.100.25)                                       |\n"+
           "|    NS: ns.n3tw0rk.ex   (198.51.100.25)                                       |\n"+
           "|                                                                              |\n"+
           "| Deploying flag hunter packets...                                             |\n"+
           sprintf("|     %72-s |\n",packets+" packets deployed, "+sizeof(users())+" active.") +
           "|                                                                              |\n"+
           "'------------------------------------------------------------------------------'\n";
           
}
