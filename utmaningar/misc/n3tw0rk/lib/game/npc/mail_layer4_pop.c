#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

int alert = 1;

void init_living(void)
{
    ::init_living();
}

void toggle_alert(void)
{
    alert = !alert;

    if(!alert)
        tell_room(ENV(TO),"The intern leans over the desk, focusing on its crossword puzzle.\n");
    else
        tell_room(ENV(TO),"The intern looks up from its crossword puzzle.\n");

    set_alarm((!alert ? 30.0 : 10.0) + rnd() * 20.0,0.0,toggle_alert);
}

void create_monster()
{
    ::create_monster();
    
    set_name("intern");
    add_name("bored intern");

    set_short("A bored intern");
    set_long("@@long_fun");

    add_item(({"tag"}),
        "The tag on the interns chest says \"PRAO\".\n");
    add_item(({"newspaper","crossword","puzzle","crossword puzzle"}),
        "A folded newspaper with a partly solved crossword puzzle.\n");

    set_alarm(15.0 + rnd() * 5.0,0.0,toggle_alert);
}

string long_fun()
{
    return BSN("A youthful digital entity, wearing a wrinkly uniform with a small tag on the chest. "+
               "It is looking quite bored and it appears to be more interested in the crossword puzzle "+
               "it seesm to be trying to solve than doing it's job, whatever that might entail. "+
               (alert ? "At the moment it seems to be making an effort to focus on its job though." : 
               "At the moment it is totaly engrossed by its crossword puzzle, oblivious to its surroundings."));
}

int block_tp(void)
{
    if(!alert)
        return 0;

    tell_room(ENV(TO),"The intern shouts: Hey, you keep away from there. That's not your mailbox!\n");
    say(TP->QN + ", which was about to look in one of the mailboxes, looks startled and backs away.\n");
    write("You back away from the mailbox. Perhaps you should wait for a more opertune moment...\n");
    return 1;
}