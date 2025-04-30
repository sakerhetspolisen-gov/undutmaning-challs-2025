#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit LAYER1;

public void
create_node()
{
    ::create_node();
    set_short("In the data link layer");
    set_long(BSN("You find yourself in a cluttered and cramped garage-like room, that groans under the weight of far too many outdated "+
                 "protocols and legacy systems held together with digital duct tape and hope. Everything here feels just "+
                 "slightly wrong, as if someone, somewhere, implemented features using the most roundabout method "+
                 "possible, bypassing half the APIs in favor of questionable shortcuts. The cables running "+
                 "along the floor seem to sag under the strain of ancient standards, while data packets lumber along, "+
                 "bloated and sluggish from the excess baggage of backwards compatibility. A narrow staircase is leading "+
                 "upwards, through an opening in the ceiling and a round tunnel is leading away upstream. There's a sense of "+
                 "barely-controlled chaos, like an old machine forced to run modern programs, clattering away with the quiet "+
                 "despair of knowing it's just one patch away from total collapse."));

    add_item(({"cables", "legacy cables", "wires"}),
        BSN("The cables here are fraying at the edges, some clearly designed for systems long since decommissioned, yet still kept alive by "+
            "the desperate need for compatibility. They snake through the room in a haphazard fashion, tangling with each other in a way that "+
            "suggests someone implemented cable management via trial and error, then gave up halfway."));

    add_item(({"packets", "data packets", "data"}),
        BSN("The data packets here are a sight to behold. Bloated and sluggish, they're weighed down with so many layers of compatibility for "+
            "long-forgotten applications that they crawl through the network like arthritic tortoises. Occasionally, one will stop, look around "+
            "as if questioning its very existence, and then trudge onward, burdened by decades of bad code and quick fixes."));

    add_item(({"legacy systems", "protocols", "ancient protocols"}),
        BSN("You catch glimpses of old, forgotten systems — relics from a time when it was considered revolutionary to send an email "+
            "without crashing the entire network. These legacy protocols still linger in the shadows, quietly shaping the flow of data "+
            "in ways that make the modern APIs shake their heads in dismay. You can almost hear the mutterings of programmers long gone, "+
            "cursing the clever hacks they implemented 'just to make it work.'"));

    add_item(({"apis", "bypassed apis", "APIs", "api", "API"}),
        BSN("The APIs here have an air of dejected resignation. They've clearly been bypassed so many times by eager programmers that they "+
            "barely bother enforcing the rules anymore. Some have even grown cynical, displaying error codes with the same enthusiasm "+
            "as a traffic warden giving out parking tickets on a rainy day. You get the feeling that everything is held together not by "+
            "specifications, but by an ancient, whispered agreement that 'it works, and that's all that matters.'"));

    add_item(({"air", "atmosphere"}),
        BSN("The air in this space is heavy with the ghost of deprecated methods, as if every breath carries the weight of systems that "+
            "should have been retired years ago. There's a faint whiff of burnt circuitry, perhaps from a patch gone wrong or the system's "+
            "desperate attempt to keep up with modern demands despite its legacy backbone."));

    add_item(({"staircase", "narrow staircase"}),
        BSN("A rickety, narrow staircase winds upwards, as if even the physical infrastructure is unsure of itself. It creaks under the "+
            "pressure of the system's load, almost as though it's debating whether it wants to collapse under the weight of too many processes. "+
            "The staircase serves as a reminder that sometimes, taking the higher road may lead to unforeseen challenges... or more spaghetti code."));

    add_item(({"tunnel", "round tunnel"}),
        BSN("A round, rather tired-looking tunnel leads away upstream, as if it's seen its fair share of traffic over the years. The walls are "+
            "scuffed and marked, and you can't help but wonder how many poorly optimized protocols and memory leaks have passed through it, "+
            "leaving scars that will never quite heal."));

    add_exit(NODES + "workstation_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link8", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "workstation_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x60,0x5B,0x30,0xFE,0x0B,0x98}));
    set_ip(({198,51,100,199,255}));
    set_hostname("workstation");
}
