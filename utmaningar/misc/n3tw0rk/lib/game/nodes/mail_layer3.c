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
    set_long(BSN("You've stumbled into a room that looks like it was designed by someone who thought "+
        "bureaucracy and ancient technology made an excellent pairing. This place is dominated by three grandiose "+
        "tubes, their metal surfaces adorned with the patina of time and the occasional suspicious stain. Each tube "+
        "boasts a sign with a number, like a peculiar old-fashioned lottery where everyone's a winner, provided they "+
        "don't mind the rust. The staircase leading downwards is sturdier than it has any right to be, groaning under "+
        "the weight of its own history. In one corner, a blackboard stands stoically, as though it has resigned itself "+
        "to being the repository of outdated information and forgotten deadlines."));

    add_item(({"tubes","tube"}),
        BSN("Three imposing tubes, each festooned with a sign bearing cryptic numbers: \"25\", \"53\", and \"110\". They seem to "+
            "be engaged in a never-ending battle with gravity, while their polished surfaces hint at an age when such things were "+
            "considered modern."));

    add_item(({"sign","signs"}),
        BSN("The signs above the tubes, marked \"25\", \"53\", and \"110\", are relics of a bygone age. They look like they've been "+
            "there so long that their purpose has become as obscure as the handwriting on a pub's last call chalkboard."));

    add_item(({"room","design","interior design", "décor"}),
        BSN("The room itself seems to be trapped in a time warp where outdated technology and a lack of imagination reign supreme. "+
            "The décor — if one could call it that — is a study in bland efficiency, with the tubes standing as the room's only nod to "+
            "excited innovation. Everything else is a monument to stubborn practicality and faded charm."));

    add_item(({"staircase","stairs"}),
        BSN("The staircase spirals downwards in a fashion that suggests it has been around since the days when stairs were a novel "+
            "invention. Its steps are worn smooth, and it creaks with a dignified air, as though it is fully aware of its role in "+
            "this monument to antiquity."));

    add_item(({"packet","packets"}),
        BSN("Packets drift through the room with a languid grace, moving at a pace that suggests they are in no particular rush. "+
            "Some head up the tubes with a sense of purpose, while others meander down the staircase, perhaps contemplating the "+
            "meaning of their journey — or lack thereof."));

    add_item(({"blackboard","board"}),
        BSN("The blackboard stands in a corner, looking more like an ancient artifact than a useful tool. Its chalky surface is "+
            "covered in the faded remains of information that may have once been important. The only thing more reliable than its "+
            "obsolescence is its stubborn refusal to be updated or replaced. Only the last few lines appear to have been changed "+
            "by anyone currently still alive."));

    add_item(({"last lines","lines","last few lines"}),
        BSN("The last few lines on the blackboard are smudged and almost illegible, as if someone scribbled hurriedly before "+
            "deciding that such things were better left forgotten. The writing has been erased and rewritten so many times that "+
            "the faded chalk has taken on a ghostly quality, like the echoes of a forgotten memo."));

    add_item(({"writing","information","letters","chalk letters"}),
        "@@netinfo");

    add_exit(NODES + "mail_layer4_dns", "53", "@@up_check", 0);
    add_port(53,"UDP"); // Port 53 is only UDP
    add_exit(NODES + "mail_layer4_snmp", "25", "@@up_check", 0);
    add_port(25,"TCP"); // Port 25 is only TCP
    add_exit(NODES + "mail_layer4_pop", "110", "@@up_check", 0);
    add_port(110,"TCP"); // Port 110 is only TCP
    // The established connection to port 110 is captured by the listening port above
    // add_port(110,({ ({ 198,51,100,199 }), 34887 }));

    add_exit(NODES + "mail_layer2", "down", "@@down_check", 0);

    clerk = clone_object("/game/npc/mail_layer3");
    clerk->move(TO,1);
    set_admin(clerk);

    set_hostname("mail");
    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
    set_extra_msg_netinfo("You read the writing on the blackboard:\n");
}
