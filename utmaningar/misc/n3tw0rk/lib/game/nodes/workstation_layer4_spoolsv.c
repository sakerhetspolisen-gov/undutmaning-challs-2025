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
    set_short("Inside the Spoolsv process");
    set_long(BSN("You find yourself in a room that buzzes with a quiet but determined sense of purpose. The space is neat, almost too neat, "+
                 "as if it's constantly preparing for the next big task. Shelves line the walls, each filled with rolled-up requests, neatly stacked "+
                 "and labeled with tiny tags that flutter in an unseen breeze. A large, polished desk stands in the middle of the room, with an ink-stained "+
                 "ledger resting atop it. The air hums with the tension of a process awaiting the next job. In one corner, a particularly irate-looking "+
                 "tube opens up in the floor, leading downward to what ever lies below. The tube pulses occasionally, as though trying to nudge the "+
                 "process into moving things along faster. There's a clock on the wall, but it seems to tick irregularly, as if unsure whether "+
                 "it should measure time or just add to the general air of bureaucratic delay. A small placard on the desk reads: 'We Take Our "+
                 "Jobs Very Seriously, Until We Don't.'"));

    add_item(({"room", "process", "spoolsv room"}),
        BSN("The room hums with the kind of bureaucratic energy that only a system process with an endless backlog of work can muster. "+
            "The walls are lined with shelves cluttered with forgotten print requests, most of which are marked with labels like 'URGENT' "+
            "or 'RETRY,' though clearly they've been neither urgent nor retried in quite some time. The air smells faintly of ink and "+
            "desperation, as though the room itself is resigned to its thankless task of forever queuing, retrying, and managing jobs "+
            "that rarely seem to leave the queue at all."));

    add_item(({"shelves", "rolled-up requests", "requests"}),
        BSN("The shelves are meticulously organized, each holding a series of rolled-up print requests. Some are fresh and crisp, awaiting their time, "+
            "while others are dog-eared and dusty, their jobs long forgotten. You notice one particular roll at the top of the pile, marked with an ominous "+
            "red tag, awaiting attention but clearly in limbo."));
    
    add_item(({"desk", "polished desk"}),
        BSN("The polished desk dominates the room, its surface gleaming with the kind of sheen that suggests many things are moved about here, but little "+
            "ever leaves. An open ledger sits atop it, filled with columns of neat handwriting cataloging jobs."));
    
    add_item(({"ledger", "open ledger", "book"}),
        BSN("The ledger is an ancient-looking tome, its pages yellowed and dog-eared from what seems like decades of use. "+
            "Each page is filled with scribbled print requests, some of which are marked 'completed' in neat, smug handwriting, "+
            "while others are aggressively underlined and annotated with phrases like 'QUEUED!' or 'PRINTER NOT RESPONDING.' "+
            "The last entry catches your eye — it's a simple request to print an email, but scrawled beside it in increasingly "+
            "illegible handwriting are comments like 'Still waiting!' and 'Queue AGAIN? Really?!'. The whole thing has an aura of "+
            "quiet desperation, as though the ledger itself is tired of dealing with the same printer-related mishaps, day in and day out."));

    add_item(({"tube", "irate tube", "opening", "floor"}),
        BSN("The tube in the corner is a large, almost ominous hole that opens up in the floor. It pulses with a frustrated energy, as though "+
            "it wants to move packets of data through, but something — likely a miscommunication with the printer — has stopped it in its tracks. "+
            "Occasionally, a soft 'thunk' can be heard, as if something's trying to escape but keeps getting stuck."));
    
    add_item(({"clock", "irregular clock"}),
        BSN("The clock on the wall seems to tick with a mind of its own. It's not entirely clear whether it's measuring actual time or merely "+
            "adding to the room's sense of mild frustration. Every so often, it skips a beat, as though deciding that time itself is irrelevant "+
            "to the tasks at hand."));

    object ob = clone_object(NPC + "workstation_layer4_spoolsv");
    ob->move(TO,1);
    set_admin(ob);

    add_exit(NODES + "workstation_layer3", "down", 0, 0);
    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
}
