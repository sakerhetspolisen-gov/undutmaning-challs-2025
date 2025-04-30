#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

void init(void)
{
    ::init();
    add_action("do_write","write");
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the SSH process");
   set_long(BSN("You find yourself in what can only be described as the bureaucratic heart of secure data "+
        "transmission, a place where packets are shuffled with all the gravity of a civil servant filing tax returns. "+
        "The process itself is a minimalist affair, floating serenely in the vast expanse of memory, which seems to "+
        "stretch on for miles in every direction — or possibly just a few kilobytes, depending on your perspective. "+
        "Around the edges of this floating isle of purpose, several large, ominous black squares hover, like silent "+
        "judges at a particularly dreary trial. Only one of these squares is currently active, emitting a faint glow "+
        "as if it's deep in thought, or perhaps just napping with one eye open."));

    add_item(({"process", "area", "room", "slice", "reality"}),
        BSN("This area is as neat and orderly as a librarian's desk, with everything in its place and a place "+
            "for everything. The various equipment scattered about looks capable of all sorts of complex activities, "+
            "though at the moment, only one of the black squares is actually doing anything, and even that seems to "+
            "be done with a kind of resigned efficiency, as if it would much rather be on holiday."));

    add_item(({"memory"}),
        BSN("You take a moment to ponder the mysteries of the surrounding memory. Bits and bytes swirl "+
            "around like thoughts in a wizard's head — chaotic, incomprehensible, and somehow all interconnected. "+
            "You can't help but wonder how it all stays in place, or indeed, how it ever makes any sense at all."));

    add_item(({"packet", "packets"}),
        BSN("The packets here move with a sense of duty, as if they're on an errand for someone very important, "+
            "but not particularly exciting. They shuffle in through the opening in the floor, make a brief detour "+
            "to the active black square, and then, having completed whatever cryptic task was required of them, "+
            "shuffle back out again."));

    add_item(({"opening", "floor"}),
        BSN("The opening in the floor yawns below you, leading downwards with all the appeal of a government form. "+
            "It's not particularly inviting, but it is certainly there, just waiting for someone to fill it in — or fall into it."));

    add_item(({"square", "black square", "used square"}),
        BSN("The black square that is currently active seems to be a terminal of some sort, its screen flickering "+
            "with lines of text that look important, though you're not entirely sure what they mean. The square "+
            "gives off an aura of smug satisfaction, as if it knows something you don't, and is in no hurry to tell you."));

    add_item(({"squares", "black squares"}),
        BSN("There are several of these black squares floating around, like idle philosophers lost in thought. "+
            "Most of them are currently dormant, but you get the distinct impression that they could spring into "+
            "action at any moment — though they'd probably complain about it."));

    add_item(({"text", "terminal"}),
        "@@terminal_fun");

    add_exit(NODES + "web_layer3", "down", 0, 0);

    set_mac(({0x00,0x14,0x22,0x03,0x5A,0xB2}));
    set_ip(({198,51,100,15,127}));

    set_hostname("web");
}

string terminal_fun(void)
{
    return ".------------------------------------------------------------------------------.\n"+
           "| "+sprintf("%77-s","admin@"+query_hostname()+": $ sudo apt update")+"|\n"+
           "| [sudo] password for admin:                                                   |\n"+
           "| Hit:1 http://deb.debian.org/debian stable InRelease                          |\n"+
           "| Hit:2 https://deb.nodesource.com/node_14.x buster InRelease                  |\n"+
           "| Hit:3 http://security.debian.org/debian-security stable/updates InRelease    |\n"+
           "| Reading package lists... Done                                                |\n"+
           "| "+sprintf("%77-s","admin@"+query_hostname()+": $ sudo apt install --only-upgrade nodejs")+"|\n"+
           "| Reading package lists... Done                                                |\n"+
           "| Building dependency tree                                                     |\n"+      
           "| Reading state information... Done                                            |\n"+
           "| nodejs is already the newest version (14.18.2-1nodesource1).                 |\n"+
           "| 0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.               |\n"+
           "| "+sprintf("%77-s","admin@"+query_hostname()+": $ ")+"|\n"+
           "'------------------------------------------------------------------------------'\n";
}

int do_write(string str)
{
    write("Ah, yes. That have would been interesting, now wouldn't it!?\n");
    return 1;
}