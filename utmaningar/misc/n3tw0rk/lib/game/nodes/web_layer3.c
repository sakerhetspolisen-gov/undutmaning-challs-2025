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
    set_long(BSN("Welcome to the bustling antechamber of the digital nightclub! This place feels like the bustling foyer "+
        "of an exclusive venue, with an air of anticipation that crackles more intensely than a New Year's Eve crowd. "+
        "Above, you can barely discern the weight of revelry pressing down on this space, as if the entire edifice "+
        "extends upwards into infinity, or perhaps into the realm of gigabytes. "+
        "Three grand tubes dominate the room, each leading up to where the party is clearly in full swing. Two of these tubes "+
        "are larger and prominently marked with the numbers '80' and '443', from which a vibrant cascade of sounds and lights "+
        "descends in a thrilling, chaotic display. The third tube, marked '22', is smaller and less flamboyant but equally "+
        "important. The packets, like eager club-goers, bustle about, entering and exiting these tubes with an energetic fervor. "+
        "A switchboard with a softly glowing display sits to one side, its screens flashing with cryptic data. Below, a circular "+
        "staircase descends to the more mundane layers of the network.")); 

    add_item(({"room","antechamber","chamber","foyer"}),
        BSN("This isn't just any room; it's the vestibule to the grand event above. The design is dominated by the three tubes "+
            "that stretch upwards, each one a conduit to the extravagant festivities. The sounds and lights from the tubes create "+
            "an aura of anticipation and excitement.")); 

    add_item(({"tubes","tube","small tube","large tube","other tube"}),
        BSN("Three tubes climb upwards from this chamber. The one marked '22' is smaller, while the ones marked '80' and '443' "+
            "are larger and significantly more vibrant. The latter two seem to be the main conduits for the incoming torrents of "+
            "sound and light.")); 

    add_item(({"sound","sounds"}),
        BSN("The sounds you hear are like the distant thrum of a nightclub's bassline. You can almost feel the rhythm, even if "+
            "it's just a faint echo from the party above.")); 

    add_item(({"light","lights","flashing lights"}),
        BSN("Flashing lights in a dazzling array of colors cascade from the tubes above, adding to the sensation that you're "+
            "on the verge of joining a grand celebration.")); 

    add_item(({"packets","packet"}),
        BSN("Packets dart in and out of the tubes, like party-goers shuffling between different rooms and events. Each one carries "+
            "a touch of data, making its way through the bustling network.")); 

    add_item(({"switchboard"}),
        BSN("The switchboard with its softly glowing display is like a bouncer at the entrance, keeping an eye on the flow of data "+
            "with an inscrutable calm.")); 

    add_item(({"staircase","circular staircase"}),
        BSN("The circular staircase spirals downwards, a less glamorous but equally important route to the more mundane layers "+
            "of the network. It's a bit more utilitarian compared to the vibrant spectacle above but offers a smooth transition "+
            "from the lively atmosphere of the antechamber to the quieter, more functional realms below. As you peer down, you "+
            "can almost sense the subdued hum of operations and the faint glow of distant, more utilitarian lights."));

    add_item(({"display"}),
        "@@netinfo");       

    add_exit(NODES + "web_layer4_http", "80", "@@up_check", 0);
    add_port(80,"TCP");
    add_exit(NODES + "web_layer4_http", "443", "@@up_check", 0);
    add_port(443,"TCP");
    add_exit(NODES + "web_layer4_ssh", "22", "@@up_check", 0);
    add_port(22,"TCP"); // Also catches the established connection

    add_exit(NODES + "web_layer2", "down", "@@down_check", 0);

    create_admin(NPC + "web_layer3");

    set_mac(({0x00,0x14,0x22,0x03,0x5A,0xB2}));
    set_ip(({198,51,100,15,127}));
    set_hostname("web");
    set_extra_msg_netinfo("You take a look at what the display on the switchboard is showing:\n");
}

string netinfo(void)
{
    string info = ::netinfo();
    for(int i = 0 ; i < 1 + random(5) ; i++)
    {
        string rand_ip = sprintf("%d.%d.%d.%d",1 + random(255),1 + random(255),1 + random(255),1 + random(255));
        string lport = (!random(4) ? "80 " : "443");
        for(int j = 0 ; j < 1 + random(5) ; j++)
        {
            info += " tcp       198.51.100.15:" + lport + "       " + 
              sprintf("%-23s",rand_ip + ":" +  (10000 + random(55535))) + " " +
              (!random(5) ? (random(3) ? "CLOSING" : "CLOSED") : "TIME-WAIT") + "\n";
        }
    }
    return info;
}