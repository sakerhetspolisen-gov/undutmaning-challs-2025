#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the SNMP process");
    set_long(BSN("You find yourself in a drab and uninspiring room that seems to have been plucked straight "+
        "from the archives of bureaucratic history. Here, the monotonous hum of bureaucracy is palpable. "+
        "The room is cluttered with heaps of letters, which are intermittently delivered by packets that "+
        "seem to move with a purpose so singular that it borders on the absurd. The letters are shuffled "+
        "around by entities that have perfected the art of appearing busy while accomplishing very little. "+
        "Occasionally, one of these entities will carry off a letter, only for it to reappear through a "+
        "tube-like opening in the floor, presumably on its way to another equally uninspired location.")); 

    add_item(({"room"}),
        BSN("This room embodies the essence of dreariness. It's filled with scattered letters and an "+
            "assortment of half-hearted bureaucratic machinery. The floor's only notable feature is an "+
            "opening that leads to further administrative ennui below.")); 

    add_item(({"entities","entity"}),
        BSN("The entities that shuffle about the room are an exercise in blandness. They are vaguely "+
            "human-shaped, faintly transparent, and carry out their tasks with all the enthusiasm of a "+
            "clerk stuck in an endless paperwork loop. They appear to be more like vague representations "+
            "of bureaucracy rather than actual, tangible beings.")); 

    add_item(({"letters"}),
        BSN("The letters, all haphazardly stacked and sorted, seem to be of little consequence. They're "+
            "the kind of correspondence that gets lost in the mire of administrative tedium, handled with "+
            "all the care of someone marking time until retirement.")); 

    add_item(({"messages"}),
        BSN("These messages, buried within the heaps of letters, are probably important to someone, "+
            "somewhere. However, deciphering their true significance is as thrilling as watching paint dry.")); 

    add_item(({"packet","packets"}),
        BSN("The packets drift about, carrying their bits of information with a hum of electrical "+
            "indifference. They perform their duties with mechanical precision, ferrying data to and fro "+
            "with all the excitement of a monotonous office job.")); 

    add_item(({"opening","tube"}),
        BSN("The tube-like opening in the floor is a gateway to yet more of the same bureaucratic "+
            "tedium. It leads downward, presumably to another equally uninspired section of this vast, "+
            "monotonous machine.")); 

    add_item(({"floor"}),
        BSN("The floor is as uninspired as the rest of the room, with only the tube-like opening "+
            "providing any hint of intrigue — though it's not much of an intrigue. It's simply an exit "+
            "to the next level of paperwork purgatory.")); 

    add_item(({"wall","walls"}),
        BSN("As you take stock of the surroundings, you realize that there are no distinct walls here. "+
            "This 'room' feels more like a conceptual prison, an expanse of endless, shapeless bureaucracy. "+
            "The walls are more a metaphysical construct than physical barriers, and you begin to wonder "+
            "if you're even properly standing here or if this is all just a figment of some twisted "+
            "imagination. Best not to ponder this too deeply — it only serves to make the process seem "+
            "more pointless, or unnerving, than it already is.")); 

    add_exit(NODES + "mail_layer3", "down", 0, 0);
    set_hostname("mail");
    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
}
