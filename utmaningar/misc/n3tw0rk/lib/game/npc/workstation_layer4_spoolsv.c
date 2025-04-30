#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

void
create_monster()
{
    ::create_monster();

    set_name("spool manager");
    add_name("manager");
    add_name("overseer");
    set_short("The spool manager");
    set_long(BSN("Before you stands the Spool Manager, an officious-looking figure with a tall, quill-like plume sticking out "+
                 "from the top of its head, looking for all the world like a bureaucrat who has been in this room for far too long. "+
                 "Its posture is stiff, shoulders square, and its clothing — a slightly frayed lab coat — billows around it as it moves, "+
                 "though there's an air of constant irritation clinging to it, as though the very act of managing print jobs has worn it "+
                 "down over the years. A large brass monocle rests on its nose, and it peers at you with a sharp, scrutinizing gaze. "+
                 "One hand clutches a crumpled sheet of paper, which it occasionally holds up to the light, frowning at whatever is written "+
                 "on it as if it's perpetually stuck reviewing a job that’s never quite right. Every few minutes, it glances towards the "+
                 "irate tube in the corner with a sigh, muttering something about 'the cursed queue.' The Spool Manager seems to live for "+
                 "the organization of print jobs, but it's clear that the most recent one has pushed its patience to the limit."));

    set_chat_time(10);

    add_chat("The printer says it's queued again? How many times must I tell them — just print it!");
    add_chat("I've had it up to here with misaligned margins. It's not that hard!");
    add_chat("If I get one more 'printer not responding,' someone is getting unspooled.");

    set_act_time(10);

    add_act("emote glares at the ledger on the desk, jabbing a finger at an entry marked 'queued.'");
    add_act("emote holds up a crumpled print request, squinting at it, before sighing heavily.");
    add_act("emote adjusts its monocle and mutters something about 'jobs never getting done right these days.'");
}
