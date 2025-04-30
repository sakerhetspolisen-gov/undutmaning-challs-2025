#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER4;

int boxes_tipped = 0;

void init(void)
{
    ::init();
    add_action("do_inspect","inspect");
    add_action("do_inspect","search");
    add_action("do_topple","push");
    add_action("do_topple","nudge");
}

public void
create_node()
{
    ::create_node();
    set_short("Inside the printer process");
    set_long("@@long_fun");

    add_item(({"room", "art studio", "space", "studio"}),
        BSN("The room feels less like a place for serious work and more like a chaotic, avant-garde art studio. Abstract sketches "+
               "are pinned haphazardly to the walls, and floating easels display half-finished 'masterpieces' — none of which seem "+
               "remotely related to printing, but all of which the room's inhabitants regard with intense, almost absurd reverence. "+
               "The floor is littered with various cables and crumpled pages that might once have had some technical importance but "+
               "are now just part of the creative 'decor.' There’s an odd blend of organized disorder here: a process meant for "+
               "efficiency but commandeered by eccentrics who see every data packet and every error message as a potential work of art. "+
               "Somewhere in all this chaos, printing is supposed to happen... eventually."));

    add_item(({"blobs", "blob", "data blobs", "blobs of data", "information","queue"}), 
        BSN("These floating blobs seem to contain some sort of information waiting to be processed by the machine, but here they are treated with reverence, "+
            "as though each one is a piece of art awaiting its moment to shine. Perhaps inspecting them a bit closer, to see what they contain, could "+
            "be interesting."));

    add_item(({"display", "message", "error message", "screen"}), 
        BSN("The screen on the machine flashes an unassuming message — 'PC LOAD LETTER' — which, possibly, explains the hold-up in the system. "+
            "The machine itself seems to consider this message to be important anyway. However, none of the room's inhabitants seem too concerned, "+
            "preferring to focus on their artistic pursuits. The error is just another aspect of the chaotic beauty "+
            "of this process, a stumbling block to be worked around, not fixed."));

    add_item(({"machine", "intricate machine", "large machine", "brass", "wires", "piping", "gears", "lights"}),
        BSN("The machine at the center of the room is an intricate, lumbering behemoth of brass and wires, with odd bits of piping twisting out "+
            "like tentacles searching for purpose. The surface is a patchwork of gears and blinking lights, which seem to blink in no particular "+
            "pattern, as if unsure whether they're part of an artistic statement or an actual error. This machine, for all its apparent purpose, "+
            "appears to exist on the fine line between engineering marvel and abstract installation piece. "+
            "A funnel protrudes from the top, leading data blobs into its depths, where they are processed (eventually), but for now it seems "+
            "more content flashing its error message in protest, ignored by seemingly everyone in the room. The machine hums quietly, "+
            "waiting, just like the blobs, for its moment to make an impact on the grand process of printing... one day."));

    add_item(({"tube", "packets"}), 
        BSN("Packets of data zoom through the tube in the floor, in both directions, their payloads occasionally being intercepted by the 'artists,' "+
            "who treat them as new projects. The packets seem unsure of their final destination, some returning in frustration after a failed delivery."));

    add_item(({"sketches", "abstract sketches", "artworks", "sketch", "artwork", "symbol", "symbols"}), 
        BSN("Pinned to the walls and floating around the room are sketches — not of anything recognizable, but abstract forms, bold lines, and indecipherable "+
            "symbols. These artworks are clearly more important to the room's inhabitants than the actual jobs, and some of them seem to stare at their "+
            "own work with misty-eyed pride, oblivious to the technical chaos around them."));

    add_item(({"tower","stack","possible lawsuit","lawsuit"}),
        "@@tower_desc");

    add_item(({"boxes","box"}),
        "@@boxes_desc");

    add_item(({"heap","jumble","edges","flaps","catastrophe"}),
        "@@heap_desc");

    object ob = clone_object(NPC + "printer_layer4");
    ob->move(TO,1);
    set_admin(ob);

    add_exit(NODES + "printer_layer3", "down", 0, 0);
    set_mac(({0xC0,0xFB,0xF9,0x0B,0x72,0x9E}));
    set_ip(({198,51,100,182,255}));
    set_hostname("printer");
    }

int do_topple(string str)
{
    if(boxes_tipped)
    {
        return notify_fail("You don't see anything like that to "+query_verb()+".\n");
    }

    if(str == "tower" || str == "stack" || str == "boxes" || str == "tower of boxes" || str == "stack of boxes")
    {
        write(BSN("You snicker mischievously as you give the stack of boxes a subtle nudge, feeling a guilty thrill as they sway "+
              "precariously for a heartbeat, as if weighing their options. Then, with a glorious clatter that echoes through the "+
              "room, they surrender to gravity, tumbling into a chaotic heap of crumpled cardboard and toner cartridges, leaving "+
              "behind the delightful aftermath of someone else's problem."));
        say(BSN("You notice "+TP->QN+" suspiciously giving the stack of boxes an innocent nudge, followed by a moment where the "+
            "stack of boxes seems to hover in indecision, swaying dangerously like a drunk on a tightrope. Then, with a loud and "+
            "spectacular crash, the entire wobbling tower give way, collapsing into a disheveled heap of cardboard and toner "+
            "cartridges that crashes to the floor with reckless abandon, while the culprit stands nearby, attempting "+
            "(and failing) to appear blameless amidst the glorious chaos it has unleashed."));
        boxes_tipped = 1;
        set_alarm(0.1,0.0,"manager_reaction");
        return 1;
    }
    return notify_fail(C(query_verb()) + " what?\n");
}

void manager_reaction(void)
{
    get_admin()->fixing_mess_fun(0);
}

void set_mess_fixed(void)
{
    boxes_tipped = 0;      
}

string tower_desc(void)
{
    return (boxes_tipped ? 
    BSN("You don't see that here."):
    BSN("Upon closer inspection, the towering stack of boxes reveal its true character: a motley collection of toner cartridges "+
    "crammed into cardboard crates that looks as if they are auditioning for a role in a comedy about office supplies. Each "+
    "box bears the scars of its precarious existence, with creases and smudges that tell tales of near-misses and impromptu "+
    "adventures, suggesting that a gentle nudge could send the whole wobbly structure crashing down, transforming an ordinary "+
    "day into an exciting, if somewhat regrettable, exercise in restacking. The stack is leaning dangerously already and if you "+
    "ever saw an acident waiting to happen, this is it."));
}

string boxes_desc(void)
{
    return (boxes_tipped ? 
    BSN("You feel like you are surveying the scene of some cardboard catastrophe, with a mixture of bewilderment and mild amusement. "+
    "Before you, a haphazard heap of cardboard boxes of varying sizes, some crumpled and others defiantly upright but precariously balanced, "+
    "their flaps yawning open as if gasping in shock after a sudden descent, create a disheveled tableau that whispers tales "+
    "of the grand mischief that likely has transpired here. Who will clean up this mess?"):
    BSN("Upon closer inspection, the towering stack of boxes reveal its true character: a motley collection of toner cartridges "+
    "crammed into cardboard crates that looks as if they are auditioning for a role in a comedy about office supplies. Each "+
    "box bears the scars of its precarious existence, with creases and smudges that tell tales of near-misses and impromptu "+
    "adventures, suggesting that a gentle nudge could send the whole wobbly structure crashing down, transforming an ordinary "+
    "day into an exciting, if somewhat regrettable, exercise in restacking. The stack is leaning dangerously already and if you "+
    "ever saw an acident waiting to happen, this is it."));
}

string heap_desc(void)
{
    return (boxes_tipped ? 
    BSN("You feel like you are surveying the scene of some cardboard catastrophe, with a mixture of bewilderment and mild amusement. "+
    "Before you, a haphazard heap of cardboard boxes of varying sizes, some crumpled and others defiantly upright but precariously balanced, "+
    "their flaps yawning open as if gasping in shock after a sudden descent, create a disheveled tableau that whispers tales "+
    "of the grand mischief that likely has transpired here. Who will clean up this mess?"):
    BSN("You don't see that here."));
}

string long_fun(void)
{
    return BSN("The room feels more like an avant-garde art studio than a computer process, cluttered with abstract sketches pinned to the walls "+
               "and half-completed 'masterpieces' scattered on floating easels. Various figures, each dressed in dramatically eccentric garb, bustle about, "+
               "deliberating over blobs of data floating in mid-air, forming a queue of sorts. It is a bit unclear what kind of data is contained "+
               "in these blobs, but to the room's inhabitants, they are clearly seen as creative works of the highest order. You can hear "+
               "mutterings of 'true genius takes time' as they shuffle the blobs around. The queue of blobs leads up to a large funnel attached to an "+
               "intricate machine lumbering in the center of the room. However, the queue is not moving, and a display on the machine angrily flashes "+
               "a message, though none of the 'artists' seem to take notice — or perhaps they consider the message part of the creative process. "+
               (boxes_tipped ? 
                    "To one side boxes lay in a disheveled heap, a chaotic jumble of crumpled edges and bent flaps, possibly the tragic aftermath of "+
                    "some recent cardboard catastrophe" : 
                    "To one side stands a dangerously leaning tower of boxes, stacked high, constituting a possible lawsuit waiting to happen")+
               ". A large tube opens up in the floor, with packets of data traveling up and down through it as if part of some grand delivery system.");
}

int do_inspect(string str)
{
    string what;
    
    if(!str)
    {
        return notify_fail(C(query_verb())+" what?\n");        
    }

    if(sscanf(str,"%s closely",what) != 1 && sscanf(str,"%s more closely",what) != 1)
    {
        what = str;
    }

    if(what == "blobs" || what == "blob" || what == "data blobs" || what == "blobs of data" || what == "information" || what == "queue")
    {
        if(get_admin()->block_access())
        {
            write("You move closer to get a better look inside the blobs but the art director stops you.\n");
            say(TP->QN + " starts moving closer to the glowing data blobs, but the art director stops it.\n");
            tell_room(TO,"The art director says: No, no, no! No touching the artwork!\n");
            return 1;
        }

        write(BSN("You seize the opportunity while the art director is busy and move closer to get a better look inside the blobs."));
        say(BSN("Seemingly seizing the opportunity while the art director is busy, "+TP->QN+" moves closer to the glowing data blobs."));
        string flag_txt = read_file(FILES + "flag.txt");
        write(BSN("You study the data blobs and one of them catches your eye. You lean forward and realize you can see "+
            "text inside the blob. It reads:\n"));
        write("POST /printers/myprinter HTTP/1.1\n"+
              "Host: printer.n3tw0rk.ex:631\n"+
              "Content-Type: text/plain\n"+
              "Content-Length: "+strlen(flag_txt)+"\n"+
              "\n"+
              flag_txt+"\n\n");
        say(TP->QN+" studies the data blobs intetively.\n");
        return 1;
    }
    return notify_fail(C(query_verb())+" what?\n");        
}
