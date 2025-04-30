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
    set_name("stern engineer");
    add_name("engineer");
    set_short("A stern engineer");
    set_long(BSN("A swirling mass of data taking on the form of a no-nonsense engineer, perpetually immersed in its work. "+
        "This figure moves with a purposeful efficiency, its virtual eyes constantly scanning the environment for any "+
        "irregularities. It clutches a clipboard, furiously jotting down notes with an air of practiced precision. Despite its "+
        "stern demeanor, it's quite knowledgeable. If you're in need of technical guidance or information, this is the one "+
        "to approach to request it — provided you don't mind its brusque manner.")); 

    add_item(({"clipboard"}),BSN("A meticulously maintained clipboard, bearing the marks of constant use. The engineer treats it with "+
        "great importance, frequently updating it with critical information."));

    set_chat_time(10);

    add_chat("This isn't chaos, thank you very much. It's a *system*. A messy, temperamental system, but a system nonetheless.");
    add_chat("If the routing tables don't match, heads will roll. Or at least packets will drop.");
    add_chat("Do I look like I have time for small talk? Unless it's a traceroute, I'm not interested.");
    add_chat("That was a perfectly good request, until someone decided to compress it into nonsense!");
    add_chat("Keep it moving, people! This isn't the Application Layer - we don't have time for idle pleasantries.");
    add_chat("Don't just stand there! If you need assistance you must request it from me!");

    set_act_time(10);

    add_act("emote adjusts its clipboard with a crisp snap, scribbles something down, and mutters.");
    add_act("emote glares at a rogue packet, its metaphorical eyes narrowing into twin beams of disapproval, "+
            "until the packet nervously adjusts course.");
    add_act("emote taps the side of a nearby tube, causing the data within to speed up as if out of fear of "+
            "further reprimand.");
    add_act("emote pauses to survey the room, its gaze sharp and analytical, before nodding with grim satisfaction.");

}

int create_header(string prot)
{
    if(prot == lower_case(ICMP))
    {
        // Special handling since ICMP is really layer 2 but layered on top of IP
        object ob = TP->get_layer_header(2);

        if(!ob || ob->query_protocol() != IP)
        {
            write(BSN(C(QN) + " tells you: You must have an IP header to go with your ICMP one!"));
            return 1;
        }   

        ob = TP->get_layer_header(3);

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

        write(BSN(C(QN) + " tells you: If you need another IP header to go with your ICMP one, just request yet another IP header!"));

        return 1;
    }

    object ob = TP->get_layer_header(2);

    if(ob)
    {
        if(prot == lower_case(IP))
        {
            object ob2 = TP->get_layer_header(3);
            if(ob->query_protocol() == IP && ob2->query_protocol() == ICMP)
            {
                if(TP->get_layer_header(5))
                {
                    write(BSN(C(QN) + " tells you: You must get rid of your "+ob->QN+" first!"));
                    return 1;
                }

                write(BSN(C(QN) + " tells you: Since you already have an IP and an ICMP header "+
                        "I'll just assume you want an IP header to go with your ICMP packet."));

                ob = clone_object(HEADERS + "ip_data");
                ob->move(TP,1);

                tell_room(ENV(TO),C(QN) + " takes a " + ob->QN + " out of thin air.\n");

                write(C(QN) + " gives you " + LANG_ADDART(ob->QN) + ".\n");
                say(BSN(C(QN) + " gives " + LANG_ADDART(ob->QN) + " to "+TP->QN+"."));
                return 1;
            }
        }

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

             write(BSN("The "+QRN+" pauses mid-note, its clipboard momentarily forgotten.")+
                BSN(QN+" tells you: Help? Of course, I can help. I've been doing nothing but helping since "+
                    "this process booted up. What is it this time? Lost packets? Misconfigured routes? Someone "+
                    "plugged a toaster into the network again? Request what you need from me, but quickly. "+ 
                    "I've got protocols to debug and a deadline that's always yesterday!."));    

            break;

        default:

            write(BSN("The "+QRN+" narrows its eyes, tilting its head slightly as though the query had manifested as "+
                      "an unparseable string floating in the air.")+
                BSN(QN+" tells you: What? No, seriously, what? If that was meant to be a question, it's got more "+
                    "loose ends than a spaghetti junction with a vendetta against logic. Clarify, or we'll both "+
                    "be stuck here pondering the mysteries of your syntax until the universe garbage-collects us. "+
                    "If you want my assistance you must request it!"));

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
        case "guidance":
        case "assistance":

            write(BSN(C(QN) + " tells you: I can help you with varoius things. "+
                  "Just request them from me. I can provide you with a list of "+
                  "headers I can create, a header of your choice, a correct source address or "+
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
                "IP, ICMP and ARP"));

            return 1;

        case "source address":
        case "correct address":
        case "correct source":
        case "correct source address":
            {
                object hdr = TP->get_layer_header(2);

                if(!hdr)
                {
                    write(BSN(C(QN) + " tells you: I'm sorry, but you do not have any header I am familiar with."));
                    return 1;
                }

                int *ip = ENV(TO)->query_ip();

                if(!ip)
                {
                    write(BSN(C(QN) + " tells you: Sorry, but I cant remember the correct address."));
                    return 1;
                }

                hdr->signal_change();
                hdr->set_src_addr(ip);
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
                object hdr = TP->get_layer_header(2);

                if(!hdr)
                {
                    write(BSN(C(QN) + " tells you: I'm sorry, but you do not have any header I am familiar with."));
                    return 1;
                }

                if(!ENV(TO)->check_ip(hdr->get_field_value(8)))
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

                object hdr2 = TP->get_layer_header(3);

                if(hdr2 && hdr2->query_protocol() == ICMP)
                {
                    write(BSN(C(QN) + " tells you: I'll change your ICMP header while I'm at it too."));
                    hdr2->update_checksum();
                    hdr2->signal_change();
                }

                write(BSN(C(QN) + " tells you: Ok, there you go."));
            }
            return 1;

        case "ip":
        case "ip header":
            return create_header("ip");

        case "arp":
        case "arp header":
            return create_header("arp");

        case "icmp":
        case "icmp header":
            return create_header("icmp");


        default:

            write(BSN(C(QN) + " tells you: I don't know how to help you with that."));

            return 1;
    }
    return notify_fail("Request from who? No " + who + " here.\n");
}