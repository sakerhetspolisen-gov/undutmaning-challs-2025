#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

void init_living(void)
{
    ::init_living();
    add_action("do_ask","ask");
}

void create_monster()
{
    ::create_monster();
    
    set_name("supervisor");
    add_name("manager");
    add_name("swirling collection of bytes");

    set_short("The process supervisor");
    set_long(BSN("A vaguely humanoid swirl of jittery bytes, radiating an air of authority and just the "+
        "faintest whiff of exasperation. The other packets and bits of data around you seem to give it a "+
        "wide berth, possibly out of a mix of respect and the fear that they might be assigned extra work. "+
        "It seems to be the one running this operation, or at least keeping the chaos at bay. If you're looking "+
        "for answers (or a good scolding), this might be the one to ask."));

    set_chat_time(10);

    add_chat("Oi! You there! If you've got time to stand around, you've got time to do something useful!");
    add_chat("Alright, bits and bytes, let's keep those commands flowing! Remember, we're on a tight schedule!");
    add_chat("Welcome to the FlagDiscovery process! It's all fun and games until someone drops a packet.");
    add_chat("Less chatter, more data transfer! We've got a flag to find and not much time to do it!");
    add_chat("Watch your steps over there! The operator's got a temper, and I don't want to be on the receiving end of it!");
    add_chat("Move those packets along, folks! We need that response, and we needed it yesterday!");
    add_chat("Honestly, I've seen smoother operations in a bowl of alphabet soup!");
    add_chat("Remember, if you mess this up, you're going straight back to the bit bucket!");
    add_chat("Hey! You there! No loitering!");   
    add_chat("I have never seen such sloppy execution in my life, I'd be better of with an abacus!");

    set_act_time(10);

    add_act("emote waves its arms frantically, trying to shepherd the packets into some semblance of order.");
    add_act("emote sighs and mutters under its breath, something about 'incompetent packets' and 'needing more cycles in the day'.");
    add_act("emote looks around with a sharp, critical eye, as though daring anyone to cause a delay.");
    add_act("emote adjusts its form, bytes shifting nervously, before turning to bark an order at a passing packet.");
    add_act("emote taps an invisible watch, reminding everyone that time is running out.");
    add_act("emote briefly stops, rubbing its byte-formed forehead as if it has the digital equivalent of a headache.");
    add_act("emote jots something down in an invisible notebook, shaking its head as though this was just another error to fix.");
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
        case "info":
        case "information":

            write(BSN("The supervisor peers at you with a mixture of pity and mild irritation.")+
                BSN("The supervisor tells you: Information? You want information? Well, the terminal's over there, "+
                "stuffed full of all the data we've scraped together thus far. If you're hoping for a quick cheat "+
                "sheet on what gets through and what doesn't, you're out of luck. My TCP/IP training in "+
                "Process Supervisor School was two hours long and mostly involved pictures of kittens."));    

            break;

        case "goings on":
        case "whats going on":
        case "what's going on":
        case "operation":
        case "the operation":
        case "operations":
        case "the operations":
        
            write(BSN("The supervisor raises an eyebrow at you, or at least what might be an eyebrow in a "+
                "cloud of jittery bytes.")+
                BSN("The supervisor tells you: You're a sentient flag-hunting packet, fresh off the assembly "+
                "line of the FlagDiscovery process. Your job? To infiltrate the n3tw0rk.ex network, find "+
                "the flag those sneaky so-and-sos have hidden away, and report it back to the authorities. "+
                "Now, if you're done with the questions, how about you get to work? Time's a-wasting!"));


            break;

        case "process":
        case "the process":
        case "flagdiscovery":
        case "flagdiscovery process":

            write(BSN("The supervisor beams with pride, or at least you think it's pride.")+
                BSN("The supervisor tells you: Ah, the FlagDiscovery process! A true marvel of modern program development, "+
                "if I do say so myself. We create sentient, independent packets — like you — to scour the network "+
                "for flags. It's certainly clever, possibly efficient, and just a tad bit dangerous. But hey, that's "+
                "programming for you! Now, back to work!"));

            break;

        default:

            write(BSN("The supervisor squints at you, clearly unimpressed.")+
                BSN("The supervisor tells you: I'm afraid that's beyond my purview, and quite frankly, beyond my patience. "+
                "Now, if you've got nothing else, I suggest you stop loitering and get on with your mission!"));

            break;
    }

    return 1;
}