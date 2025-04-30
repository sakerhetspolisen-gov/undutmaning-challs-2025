#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

void create_monster()
{
    ::create_monster();
    
    set_name("promoter");
    add_name("entity");
    set_short("A wildly enthusiastic promoter");
    set_long(BSN("This entity is decked out in a riotous explosion of colors, wrapped in clothing that seems "+
        "to have been designed by someone who had only a passing acquaintance with the concept of 'cool.' "+
        "It wears dark shades that are far too big for its face and a baseball cap that appears to have been "+
        "blasted from a confetti cannon. It exudes an air of manic energy, zipping around among the packets, "+
        "dispensing high fives and fist bumps with the zeal of someone who believes that the secret to happiness "+
        "lies in relentless enthusiasm, regardless of context or fashion sense."));

    set_chat_time(10);

    add_chat("Welcome, welcome, welcome! It's a party every second, every byte, every bit!");
    add_chat("Who's having fun? You're having fun! Don't let those packets have all the good times!");
    add_chat("Have you seen these clips? Top-notch! Just like my dance moves, which are also top-notch!");
    add_chat("Feel that bass, folks? It's shaking the very code beneath your feet!");
    add_chat("We never close! Not ever! If you thought we did, well, you're wrong, my friend!");
    add_chat("Are you not entertained? I mean, really, how could you not be!?");

    set_act_time(10);

    add_act("emote attempts a dance move that defies several laws of physics and good taste.");
    add_act("emote rubs its hands together with the glee of someone who's just discovered a new way to be annoying.");
    add_act("emote enthusiastically offers you a high five, whether you want it or not.");
}
