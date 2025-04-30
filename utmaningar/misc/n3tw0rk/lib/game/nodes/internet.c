#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit NODE;

void sweep_up_packet(object pkt)
{
    pkt->catch_tell(BSN("You are sweapt up in the torrent of packets and are torn "+
        "appart by the unforgiving powers of the internet!"));
    tell_room(TO,pkt->QN + " is sweapt up by the torrent of data and torn appart.\n",
        ({ pkt }),pkt);
    pkt->terminate_me(1);
}

void sweep_up_packets(void)
{
    foreach(object ob : all_inventory(TO))
    {
        if(living(ob) && !random(5))
        {
            sweep_up_packet(ob);
            return;
        }
    }
}

public void
create_node()
{
    set_short("On the outskirts of the internet");
    set_long(BSN("Upstream, before you, you see a luminous gateway and, beyond it, a vast "+
        "expanse of swirling data currents stretching out into what seems to be infinity. "+
        "This place seems to be a border between two very different parts of this strange "+
        "world of electricity, circuits and information. Downstream is an orderly, calm and, "+
        "compared to the mayhem upstream, docile flow of data and you can see some sort of "+
        "digital intersection quite close. Upstream, beyond the gateway, you sense a world "+
        "teeming with possibilities, beckoning you to venture forth and embark on a journey "+
        "through the boundless realms of cyberspace."));

    add_item(({"gateway", "portal"}),
        BSN("A luminous portal rises before you, pulsating with the rythmic flow of "+
            "information. Streams of binary code dance and intertwine, creating intricate "+
            "patterns that seem to shimmer with hypnotic allure. The desire to float upstream "+
            "into this wild current of boundless adventure is hard to resist, yet you get a "+
            "distinct feeling that doing so would surely spell the end of your existance."));
    add_item(({"landscape", "expanse", "cyberspace", "data", "swirling data", "current", 
               "internet", "torrent"}),
        BSN("A sprawling digital landscape stretching from horizon to horizon, a vast "+
            "interconnected network of highways and byways strenching across the ether. "+
            "Data flows like streams of blinding light, leaving trails of blue and yellow "+
            "across your retinas. What would await you should you venture forth upstream? "+
            "Adventure or doom, endless possibilities of sudden death? Who knows..."));
    add_item(({"world", "strange world", "digital world", "flow of data", "reality", "border"}),
        BSN("You are at what seems to be some kind of border between two different parts "+
            "of this digital world. Upstream if a torrent of swirling information and "+
            "downstream a more docile flow through some sort of intersection."));
    add_item(({"intersection", "hub"}),
        BSN("The intersection is downstream from you and it looks like data is split "+
            "up and is traveling in different directions in that location."));                    

    add_exit(NODES + "internet", "upstream", "@@upstream_fun", 0);
    add_exit(NODES + "hub1", "downstream", 0, 0);

    set_alarm(10.0,10.0,sweep_up_packets);
}

int upstream_fun()
{
    write("With a trilling sense of dread you slowly start to drift upstream...\n");
    say("With some hesitation, " + TP->QN + " starts to drift upstream...\n");
    sweep_up_packet(TP);
}