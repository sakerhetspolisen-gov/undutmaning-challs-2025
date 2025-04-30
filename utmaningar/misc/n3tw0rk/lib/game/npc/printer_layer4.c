#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

int fixing_mess = 0;

void create_monster()
{
    ::create_monster();

    set_name("eccentric art director");
    add_name("art director");
    add_name("director");
    set_short("An eccentric art director");
    set_long(BSN("This digital manifestation takes the form of an eccentric figure draped in elaborate, paint-splattered robes, with a beret "+
                 "perched precariously on its head. The art director flits between blobs of data as though each is a personal masterpiece, "+
                 "occasionally gesturing with a dramatic flourish. Its hands are perpetually ink-stained, and it carries a quill that seems "+
                 "to do nothing except add exaggerated strokes of approval to the floating data queues. However, despite the flair, there is "+
                 "an undercurrent of frustration — the art director keeps eyeing the lumbering machine in the center of the room with an air of "+
                 "indignant impatience, as if the true genius of its work is being hindered by mere mechanics. Occasionally, it mutters about "+
                 "'deadlines' and 'inferior paper quality' as though these concepts are beneath it."));

    set_chat_time(10);

    add_chat("Ah, perfection cannot be rushed!");
    add_chat("They do not understand... every print is a masterpiece in its own right.");
    add_chat("These blobs... mere novices compared to my vision!");
    add_chat("Perhaps if they gave me better paper, my genius would truly shine!");

    set_act_time(10);

    add_act("emote flicks ink-stained fingers at the queue of data blobs with a dramatic sigh.");
    add_act("emote glares at the large machine in the center, muttering about 'flawed machinery stifling true art.'");
    add_act("emote examines a floating blob of data, raising an eyebrow, as though deciding if it meets 'artistic standards.'");
    add_act("emote adjusts its beret and takes a sweeping bow to no one in particular.");
}

int block_access(void)
{
    return !fixing_mess;
}

void fixing_mess_fun(int step)
{
    string msg;
    fixing_mess = 1;
    switch(step)
    {
        case 0:
            msg = "With a distinctive tone of despair the art director cries: Oh, no! Not again!";
            break;
        case 1:
            msg = "The art director stares at the cardboard carnage with a mixture of irritation and quiet defeat, clearly weighing "+
                    "the injustice of the situation before giving in to the inevitable task ahead. It sighs deeply, muttering something "+
                    "under its breath, and bends down to gather the scattered toner cartridges, one by one, with the resigned air of "+
                    "someone who's done this far too many times.";
            break;
        case 2:
            msg = "Cardboard flaps crinkles and squeakes as the art director wrestles each box back into shape, straightening bent "+
                    "corners with a mix of frustration and determination. Every now and then, a box stubbornly resist, forcing a sigh or "+
                    "an exasperated grunt before it is beaten back into submission.";
            break;
        case 3:
            msg = "There is a rhythmic thud as the art director stacks the boxes back into a teetering column, each one landing with "+
                    "a dull thump, the whole structure wobbling slightly with every addition. The occasional soft curse is heard under its "+
                    "breath as the tower sways, but holds together.";
            break;
        case 4:    
            msg = "Finally, after stepping back to assess its work, the art director gives a wary look at the tower, as if daring it "+
                    "to collapse again, before it walks off with a tired shake of the head and an air of a person who knows they'll "+
                    "probably be back to do this again sooner than later.";
            break;
        default:
            tell_room(ENV(TO),BSN("The art director mutters: I really should get an intern to do that!")); 
            fixing_mess = 0;           
            ENV(TO)->set_mess_fixed();
            return;
    }

    tell_room(ENV(TO),BSN(msg));
    set_alarm(1.5 + rnd(),0.0,&fixing_mess_fun(step + 1));
}