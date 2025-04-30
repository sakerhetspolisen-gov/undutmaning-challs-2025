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
    set_long(BSN("You enter a room that feels oddly compressed, like it's been tucked away inside a fortress where security is "+
                 "more than a suggestion, it's an obsession. The walls are lined with glowing, arcane-looking symbols — encryption "+
                 "standards, protocols, and key exchanges — all in a dizzying dance of mathematical rigor. In the center stands a "+
                 "towering terminal, flickering with life. The room hums with quiet tension, every action logged, every breath "+
                 "monitored. Around you, shadows of other processes flicker in and out, each focused on its own task but wary "+
                 "of what might try to slip through. To one side, there's an opening in the floor, a narrow tube is leading down "+
                 "into the lower levels of the network, and you can feel the pull of packets rushing up and down, frantically "+
                 "delivering their bits and bytes.")); 

    add_item(({"room", "process"}), 
        BSN("The room is compact and feels like a secure vault, isolated yet essential. Every corner is steeped in security measures, "+
            "with a sense of constant surveillance. Despite its utilitarian purpose, the room has an air of importance — as though "+
            "the very act of passing through it requires respect. The figures in the shadows and the encrypted walls give the place "+
            "a feeling of guarded elegance, where every packet that enters must prove its worth to move onward."));

    add_item(({"walls", "symbols", "encryption standards", "protocols", "keys"}), 
        BSN("The walls glow with a constant shifting pattern of encryption algorithms — RSA, AES, and some arcane scribbles that "+
            "might be a hashing function — all working together to ensure that whatever passes through here does so securely. "+
            "The symbols hum with an intensity that suggests they take their job seriously, warding off anything less than fully authorized."));

    add_item(({"terminal", "flickering terminal"}), 
        "@@terminal_fun");

    add_item(({"figures", "security figures", "guardians"}), 
        BSN("The figures in the shadows move with quiet precision, their forms barely distinguishable, but their presence is undeniable. "+
            "They are the silent guardians of the process, each one tasked with ensuring that no unauthorized packets slip through. "+
            "Their movements are swift and calculated, watching every connection with an unwavering vigilance. They give off the impression "+
            "that they've seen it all, and they are not impressed by flashy encryption tricks or clever disguises — only pure, proven security "+
            "gets their nod of approval."));

    add_item(({"shadows", "processes", "running processes"}), 
        BSN("Just on the edge of your vision, other processes lurk, flitting between tasks. They seem to exist in that liminal "+
            "space where administrative duties are never done, but always one step away from total system collapse. They monitor, "+
            "log, and move swiftly, always prepared for the next security challenge."));

    add_item(({"tube", "opening", "floor"}), 
        BSN("A narrow tube is leading down through an opening in the floor, vanishing into the lower, murkier parts of the network stack. "+
            "Packets of data zip up and down the tube like messengers, delivering vital information to other parts of the machine or "+
            "other parts of the network. It's clear that whatever happens down there is crucial to keeping the connection alive, but "+
            "down is where the real mysteries lie."));

    add_item(({"text", "terminal"}),
        "@@terminal_fun");

    add_exit(NODES + "admin_layer3", "down", 0, 0);

    set_mac(({0x00,0x10,0xE3,0x8C,0xEA,0x51}));
    set_ip(({198,51,100,194,255}));
    set_hostname("admin");
}

string terminal_fun(void)
{
    return ".------------------------------------------------------------------------------.\n"+
           "| admin@web: $ sudo apt update                                                 |\n"+
           "| [sudo] password for admin:                                                   |\n"+
           "| Hit:1 http://deb.debian.org/debian stable InRelease                          |\n"+
           "| Hit:2 https://deb.nodesource.com/node_14.x buster InRelease                  |\n"+
           "| Hit:3 http://security.debian.org/debian-security stable/updates InRelease    |\n"+
           "| Reading package lists... Done                                                |\n"+
           "| admin@web: $ sudo apt install --only-upgrade nodejs                          |\n"+
           "| Reading package lists... Done                                                |\n"+
           "| Building dependency tree                                                     |\n"+      
           "| Reading state information... Done                                            |\n"+
           "| nodejs is already the newest version (14.18.2-1nodesource1).                 |\n"+
           "| 0 upgraded, 0 newly installed, 0 to remove and 0 not upgraded.               |\n"+
           "| admin@web: $ █                                                               |\n"+
           "'------------------------------------------------------------------------------'\n";
}

int do_write(string str)
{
    write("Ah, yes. That have would been interesting, now wouldn't it!?\n");
    return 1;
}