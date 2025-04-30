#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER3;

public void
create_node()
{
    ::create_node();
    set_short("In the transport layer, Gi0/1 interface");
    set_long(BSN("You've arrived at an open space precariously near the top of the wall of flames, "+
        "a place that feels as if it's where serious things happen — just not where you can see them. "+
        "Above you looms an immense cloud of swirling data, like a sentient fog, well beyond your reach "+
        "and giving the impression that it's busy doing something terribly important, but not so much as to "+
        "involve you. A switchboard with a flashing display stands nearby, looking rather pleased with itself "+
        "for having something to do. Despite the ominous surroundings, there's an odd sense of order here, "+
        "as if everything is running like clockwork, though perhaps a clockwork in need of some oiling."));

    add_item(({"platform", "space", "open space"}),
        BSN("You find yourself standing on a platform seemingly made of fire itself, jutting out from the "+
        "side of the wall. It's as if someone decided to build a balcony in the middle of an inferno. "+
        "You're near the top of the wall now, but not close enough to see over it. It's quiet up here — "+
        "the kind of quiet that makes you wonder what's lurking in the background."));
    
    add_item(({"wall", "wall of flames", "flames", "light"}),
        BSN("The wall of flames, still as imposing and fiery as ever, dominates your view. "+
        "However, you've been around it long enough now that it's starting to feel almost familiar — "+
        "like a particularly large and moody pet. It remains immense, foreboding, and not something "+
        "you'd want to mess with, but at least it doesn't seem quite as eager to singe your eyebrows off anymore."));
    
    add_item(({"cloud", "swirling cloud", "data", "cloud of data", "cloud of swirling data"}),
        BSN("The cloud above you swirls and shifts with a kind of arcane purpose, as though something "+
        "mysterious and important is happening within it. It's the sort of thing that makes you feel "+
        "like you're missing the big picture. Whatever is going on in there, it's the cloud that seems "+
        "to be directing all the activity below — although how exactly it does that is anybody's guess."));
    
    add_item(({"activity"}),
        BSN("Not much seems to be happening around you at the moment, but you can sense that somewhere "+
        "in this fiery labyrinth, things are bustling along just fine. It's the kind of subdued, distant activity "+
        "that feels reassuring, even if you can't see it directly."));
    
    add_item(({"switchboard"}),
        BSN("The switchboard is crammed with levers and buttons in a way that suggests they're all terribly "+
        "important, though what they actually do is anyone's guess. The flashing display is the real attention-grabber, "+
        "blinking away like it's got something very urgent to tell you."));
    
    add_item(({"buttons", "levers"}),
        BSN("The switchboard wouldn't be much of a switchboard without its assortment of buttons and levers, "+
        "would it? They're scattered across its surface, each one probably controlling something that you'd "+
        "rather not break. Or maybe something you'd love to break, depending on your mood."));
  
    add_item(({"display","flashing display"}),
        "@@netinfo");
    
    add_exit(NODES + "fw1_gi01_layer2", "down", "@@down_check", 0);

    object ob = clone_object(NPC + "fw1_gi01_layer3");
    ob->move(TO,1);
    set_admin(ob);

    set_hostname("fw1");
    set_mac(({0x00,0x03,0x32,0xF2,0x33,0x22}));
    set_ip(({198,51,100,1,127}));
    set_extra_msg_netinfo("You look at the display, noticing the text that it is showing:\n");
}
