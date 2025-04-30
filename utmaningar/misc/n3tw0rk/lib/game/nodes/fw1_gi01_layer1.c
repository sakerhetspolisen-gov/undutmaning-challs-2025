#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer, Gi0/1 interface");
    set_long(BSN("You are drifting lazily at the foot of a towering wall of flames that "+
        "stretches upwards like the sort of thing that would have any sensible fire safety inspector "+
        "fainting dead away. The wall climbs far beyond what you can see, though your view is promptly "+
        "cut short by a platform hanging somewhere above, like a ceiling that's had enough of being "+
        "up and has decided to see what the ground looks like. A staircase clings to the side of the "+
        "wall, winding its way up to that very platform. To your left, the wall abruptly turns at a sharp "+
        "right angle, forming a corner that seems to exist solely to make the wall look more impressive. "+
        "Off to one side, a gateway yawns open, leading into a corridor that feels suspiciously like it's "+
        "going downstream, though where it flows is anyone's guess."));

    add_item(({"wall","flames","wall of flames","light"}),
        BSN("The wall stretches endlessly both to your right and straight up into the distance, "+
            "efficiently obscuring whatever lies beyond. It's the sort of wall that takes pride in "+
            "being in the way. On your left, it suddenly decides it's had enough of going straight and "+
            "makes a sharp right turn, forming a corner that looks like it's never been useful for anything, "+
            "ever. A staircase climbs upward along the side of the wall, leading to the platform above."));
    
    add_item(({"packet", "packets","queue"}),
        BSN("Packets of data mill about, looking slightly more organized than your average mob, "+
            "with some queuing obediently at the foot of the stairs, while others seem to be readying "+
            "themselves for a journey downstream, wherever that may take them."));
    
    add_item(({"gateway","archway"}),
        BSN("A large archway, yawning open like a tunnel that's just remembered it's supposed to be "+
            "leading somewhere. The corridor beyond it seems to beckon you forward in a distinctly "+
            "downstream direction."));
    
    add_item(({"stair","stairs","staircase",}),
        BSN("A narrow staircase clings desperately to the side of the flame wall, leading upward "+
            "toward the platform above. A small but determined queue of packets has formed at its base, "+
            "waiting patiently for their turn to ascend."));
    
    add_item(({"corner","sharp corner"}),
        BSN("Ah, the corner. It's sharp, it's right-angled, and it's about as useful as a chocolate "+
            "teapot. A lonely, unremarkable bit of geometry, tucked away where no one's likely to bother with it."));

    add_item(({"platform"}),
        BSN("The platform above juts out from the wall of flames like a rebellious bit of architecture "+
            "that's decided to defy gravity. It hangs there with an air of nonchalance, as if to say, "+
            "'Yes, I'm a platform. I'll be staying here, thank you very much.' It's just far enough up to "+
            "cut off your view of the wall's higher reaches, and it seems to be the destination for those "+
            "ascending the staircase."));

    add_item(({"tunnel", "corridor"}),
        BSN("The tunnel stretches out ahead of you like a long, narrow throat that's suddenly "+
            "decided to lead somewhere, though where that might be is anyone's guess. It's the kind of "+
            "corridor that looks like it's seen better days, but is still doing its job, albeit with the "+
            "enthusiasm of someone working on a Friday afternoon. The walls seem to hum faintly, perhaps "+
            "with the distant rush of data flowing downstream, or maybe it's just the tunnel grumbling "+
            "about how underappreciated it is."));

    add_exit(NODES + "fw1_gi01_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link2", "downstream", "@@downstream_check", 0);

    object ob = clone_object(NPC + "fw1_gi01_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x22}));
    set_ip(({198,51,100,1,127}));
    set_hostname("fw1");
}
