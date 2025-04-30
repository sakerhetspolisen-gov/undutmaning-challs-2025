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
    set_name("attentive clerk");
    set_short("An attentive clerk");
    add_name("clerk");
    set_long(BSN("A swirling, vaguely humanoid mass of data that resembles a diligent middle-aged clerk. "+
        "This entity exudes an aura of constant activity, its many metaphorical eyes flitting around as it "+
        "performs its duties. It clutches a well-worn clipboard with an air of purpose, jotting down "+
        "observations with meticulous care. Its demeanor suggests a deep well of knowledge, so if you "+
        "need guidance, this is your go-to for requesting help or information, though you might find it "+
        "prefers to stay focused on its tasks."));

    add_item(({"clipboard"}),BSN("An old but well-maintained clipboard. It seems to hold the key to many "+
        "important details, with the clerk diligently updating it as events unfold."));

    set_chat_time(10);

    add_chat("Paperwork, paperwork, paperwork. They always say we're going paperless, but then I get "+
             "handed *this*! Metaphorically, of course.");
    add_chat("The queue is everything. Without it, there's only chaos, and we've already got enough "+
             "of that in the upper layers.");
    add_chat("Yes, I see the packet is marked urgent. They're *all* marked urgent, aren't they?");
    add_chat("Let me remind everyone - deadlines exist for a reason. That reason is not to be ignored.");
    add_chat("Don't just stand there! If you need assistance you must request it from me!");

    set_act_time(10);

    add_act("emote straightens its clipboard with an air of supreme importance, then scribbles something "+
            "down in a meticulous hand.");
    add_act("emote frowns at a delayed packet, taps its clipboard, and makes a quick note before waving "+
            "it onward with a curt gesture.");
    add_act("emote rearranges its metaphorical desk, as if tidying the room will somehow fix the larger "+
            "inefficiencies of the system.");
    add_act("emote gestures sharply toward a tube, sending a flurry of packets on their "+
            "way with no room for nonsense.");
}

int create_header(string prot)
{
    object ob = TP->get_layer_header(3);

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

             write(BSN("The "+QRN+" glances up from its clipboard, its metaphorical pen pausing mid-scribble.")+
                BSN(QN+" tells you: Help? Oh, yes, yes, of course, I can help. I'm the one who keeps everything "+
                    "moving, after all. Without me, packets would be wandering the void like lost sheep, bumping "+
                    "into firewalls and crying for their routers. Now, let's be efficient about this — "+
                    "request what you want from me. No dithering, please, I've got schedules to maintain and data "+
                    "flows to herd."));    

            break;

        default:

            write(BSN("The "+QRN+" blinks, its expression a mixture of confusion and mild irritation, like "+
                "someone who's just been asked to alphabetize smoke.")+
                BSN(QN+" tells you: I'm sorry, but whatever you just said has all the clarity of a corrupted "+
                    "header. Care to try again? This time, perhaps, request what you want from me, with fewer "+
                    "ambiguous metaphors and more actionable specifics? Honestly, some of these queries feel "+
                    "like they were delivered by carrier pigeon with a bad sense of direction."));

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

    switch(str)
    {
        case "info":
        case "information":
        case "more info":
        case "more information":
        case "help":

            write(BSN(C(QN) + " tells you: I can help you with varoius things. "+
                  "Just request them from me. I can provide you with a list of "+
                  "headers I can create, a header of your choice or "+
                  "recalculating any checksums that I am familiar with."));

            return 1;

        case "header":

            write(BSN(C(QN) + " tells you: Which header are you requesting? "+
                "Request a list of the ones I am familiar with if you are uncertain."));

            return 1;

        case "headers":
        case "list":
        case "list of headers":

            write(BSN(C(QN) + " tells you: I can create the following headers: "+
                "TCP or UDP"));

            return 1;

        case "checksum":
        case "recalculation":
        case "recalculate":
        case "recalculate checksum":
        case "checksum recalculation":
        case "checksum calculation":

            object hdr = TP->get_layer_header(3);

            if(!hdr || hdr->get_protocol() == ICMP)
            {
                write(BSN(C(QN) + " tells you: I'm sorry, but you do not have any header I am familiar with."));
                return 1;
            }

            if(!hdr->update_checksum())
            {
                write(BSN(C(QN) + " tells you: I'm sorry, but I was unable to update it."));
                return 1;
            }

            hdr->signal_change();

            object hdr2 = TP->get_layer_header(3);

            if(hdr2 && hdr2->query_protocol() == ICMP)
            {
                write(BSN(C(QN) + " tells you: I'll change your ICMP header while I'm at it too."));
                hdr2->update_checksum();
                hdr2->signal_change();
            }

            write(BSN(C(QN) + " tells you: Ok, there you go."));
            return 1;

        case "udp":
        case "udp header":
            return create_header("udp");

        case "tcp":
        case "tcp header":
            return create_header("tcp");

        default:

            write(BSN(C(QN) + " tells you: I don't know how to help you with that."));

            return 1;
    }
    return notify_fail("Request from who? No " + who + " here.\n");
}