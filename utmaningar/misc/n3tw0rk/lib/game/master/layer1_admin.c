#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/admin";

void init_living(void)
{
    ::init_living();
    add_action("do_request","request");
    add_action("do_ask","ask");
}

public void
create_admin()
{
    set_name("stressed technician");
    add_name("technician");
    set_short("A stressed technician");

    set_long(BSN("A swirling bundle of data that takes on the form of a harried technician, visibly frazzled "+
        "by the demands of its role. Draped in a somewhat loose-fitting overall and a tool belt crammed with "+
        "an assortment of screwdrivers, pliers, and wrenches, this figure exudes a palpable sense of urgency. "+
        "A battered notebook is clutched tightly in one hand, while a tiny pencil stub is precariously perched "+
        "behind one ear. Every now and then, it mutters to itself and scribbles furiously in the notebook. Despite "+
        "its obvious stress, the technician's expertise is evident. If you need practical advice or technical "+
        "assistance, this is the one you should request it from — just be prepared for a bit of a whirlwind.")); 

    add_item(({"notebook"}),BSN("A well-worn, tarnished notebook. The technician consults it frequently, making "+
        "hasty notes with the tiny pencil stub."));

    set_chat_time(10);

    add_chat("Where did I put that spanner? Oh, right, it's in my... oh no, it's vanished into the cache again.");
    add_chat("This place is held together with duct tape and sheer determination. Mostly the latter, if I'm honest.");
    add_chat("If you're not here to help, at least don't get in the way! I've got enough problems as it is.");
    add_chat("Great. Another misrouted packet. I swear these things have the navigational instincts of a drunk pigeon.");
    add_chat("I can't believe I'm still here. They promised me a promotion to the Transport Layer years ago!");
    add_chat("Don't just stand there! If you need assistance you must request it from me!");

    set_act_time(10);

    add_act("emote rummages through its tool belt, pulling out a tiny screwdriver and muttering.");
    add_act("emote scribbles furiously in its notebook, pauses, then erases with an exasperated sigh, "+
            "leaving behind the faint shadow of frustrated calculations.");
    add_act("emote slaps a malfunctioning component, then steps back as if daring it to defy the laws of "+
            "probability and start working.");
    add_act("emote glances at the ceiling and mutters something about sending a strongly worded complaint "+
            "to someone upstairs.");
    add_act("emote kneels down to examine a stray wire, only to recoil as it sparks.");
}

int create_header(string prot)
{
    object ob = TP->get_layer_header(1);

    if(ob)
    {
        write(BSN(C(QN) + " tells you: You must get rid of your "+ob->QN+" first!"));
        return 1;
    }   

    write(C(QN) + " tells you: Ok, here you go!\n");


    ob = clone_object(HEADERS + prot);
    ob->move(TP,1);

    tell_room(ENV(TO),C(QN) + " takes a " + ob->QN + " out of thin air.\n");

    write(C(QN) + " gives you " + LANG_ADDART(ob->QN) + ".\n");
    say(BSN(C(QN) + " gives " + LANG_ADDART(ob->QN) + " to "+TP->QN+"."));

    return 1;
}


int do_ask(string str)
{
    if(!str)
    {
        write("Ask who about what?\n");
        return 1;
    }

    if(TO->id(str))
    {
        write("Ask "+str+" about what? Perhaps \"help\" might be a good start?\n");
        return 1;
    }

    string who, what;

    if(sscanf(str,"%s about %s",who,what) != 2)
    {
        write("Ask who about what?\n");
        return 1;
    }

    if(!TO->id(who))
    {
        write("You find no "+who+" here to ask about that.\n");
        return 1;
    }

    write("You ask "+lower_case(short(TP))+" about "+what+".\n");

    switch(what)
    {
        case "help":

            write(BSN("The "+QRN+" sighs in exasperation.")+
                BSN(QN+" tells you: Help? You want help? Of course, you do. Everyone wants help, and naturally, I'm "+
                    "the one who's expected to provide it! Never mind the fact that I'm holding this whole operation "+
                    "together with chewing gum, half a roll of duct tape, and sheer bloody-mindedness! Alright, "+
                    "if you want help you must request it from me! Preferably before the next packet storm hits — "+
                    "or worse, before something else decides to spontaneously combust."));    

            break;

        default:

            write(BSN("The "+QRN+" manages to look confused and slightly nauseous at the same time.")+
                BSN(QN+" tells you: Ah, yes, I see. You want me to... what, precisely? Wave my magical spanner "+
                    "and make everything better? Well, you see, that's not exactly how things work down here. "+
                    "This is a finely tuned disaster in progress, and if you're not specific, the whole lot could "+
                    "unravel like a badly knitted sock. If you want my assistance, request it!"));

            break;
    }

    return 1;
}

int do_request(string str)
{
    string arg;
    string who;

    if(!str)
        return notify_fail("Request what from the " + QN + "?\n");

    if(sscanf(str,"%s from %s",arg,who) == 2)
    {
        if(!id(who))
            return notify_fail("Request from who? No " + who + " here.\n");

        arg = lower_case(str);
    }
    else
        arg = lower_case(str);

    switch(arg)
    {
        case "info":
        case "information":
        case "more info":
        case "more information":
        case "help":
        case "practical advice":
        case "advice":
        case "technical assistance":
        case "assistance":

            write(BSN(C(QN) + " tells you: I can help you with varoius things. "+
                  "Just request them from me. I can provide you with a list of "+
                  "headers I can create, a header of your choice, a correct source address or "+
                  "recalculation any checksums that I am familiar with."));

            return 1;

        case "header":

            write(BSN(C(QN) + " tells you: Which header are you requesting? "+
                "Request a list of the ones I am familiar with if you are uncertain."));

            return 1;

        case "headers":
        case "list":
        case "list of headers":

            write(BSN(C(QN) + " tells you: I can create the following headers: "+
                "Ethernet"));

            return 1;

        case "source address":
        case "correct address":
        case "correct source":
        case "correct source address":
            {
                object hdr = TP->get_layer_header(1);

                if(!hdr)
                {
                    write(BSN(C(QN) + " tells you: I'm sorry, but you do not have any header I am familiar with."));
                    return 1;
                }

                int *mac = ENV(TO)->query_mac();

                if(!mac)
                {
                    write(BSN(C(QN) + " tells you: Sorry, but I cant remember the correct address."));
                    return 1;
                }

                hdr->signal_change();
                hdr->set_src_address(mac);
                write(BSN(C(QN) + " tells you: Ok, there you go."));
            }
            return 1;

        case "checksum":
        case "recalculation":
        case "recalculate":
        case "recalculate checksum":
        case "checksum recalculation":
        case "checksum calculation":  
            {
                object hdr = TP->get_layer_header(1);

                if(!hdr)
                {
                    write(BSN(C(QN) + " tells you: I'm sorry, but you do not have any header I am familiar with."));
                    return 1;
                }

                if(!ENV(TO)->check_mac(hdr->get_field_value(2)))
                {
                    write(BSN(C(QN) + " tells you: Sorry, but that header does not seem to be from here! I won't change it."));
                    return 1;
                }

                if(!hdr->update_checksum())
                {
                    write(BSN(C(QN) + " tells you: I'm sorry, but I was unable to update it."));
                    return 1;
                }

                hdr->signal_change();
                write(BSN(C(QN) + " tells you: Ok, there you go."));
            }
            return 1;

        case "ethernet":
        case "ethernet header":
            return create_header("ethernet");

        default:

            write(BSN(C(QN) + " tells you: I don't know how to help you with that."));

            return 1;
    }
    return notify_fail("Request from who? No " + who + " here.\n");
}