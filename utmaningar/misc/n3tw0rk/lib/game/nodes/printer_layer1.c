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
    set_long(BSN("You stand in a dim, dusty basement. This isn't where magic happens; it's where all the forgotten groundwork and "+
                 "mechanical underpinnings reside — out of sight and out of mind. The floor is cluttered with discarded cables and "+
                 "stacks of old paper that never quite made it through what ever process is going on higher up, now crumpled and "+
                 "covered in ink stains. The walls are lined with shelves holding mismatched spools of ink ribbons and outdated parts, "+
                 "each one a relic of some long-lost attempt at modernizing the system. A tunnel is leading away upstream and a "+
                 "ladder is leading upwards, through a circular opening in the ceiling. There's an unmistakable hum of old wiring "+
                 "struggling to keep up, and the occasional flicker of light suggests that this place is just one short-circuit away "+
                 "from a complete breakdown."));

    add_item(({"cables", "wires", "discarded cables"}),
        BSN("Cables snake across the floor in tangled piles, some fraying at the ends, others simply abandoned mid-task. They look "+
            "like they've been plugged in and unplugged countless times, forgotten relics of projects that never finished or "+
            "connections that were only ever temporary."));

    add_item(({"paper", "old paper", "crumpled paper"}),
        BSN("Stacks of paper — some crumpled, others half-printed — litter the floor like discarded sketches. Ink blots and smudges "+
            "are splattered across them, evidence of countless failed attempts to get things working correctly. It's clear this is the "+
            "place where jobs that didn't quite make it were discarded, forgotten in favor of newer, equally chaotic requests."));

    add_item(({"shelves", "spools", "ink ribbons", "parts"}),
        BSN("The shelves are packed with old spools of ink ribbons and mismatched parts. Many of them are covered in dust, as if "+
            "they've been sitting there for years, waiting to be useful again. There are ink cartridges, rollers, and trays of "+
            "paper sizes that haven't been used in decades. Every piece looks like it could either fix a problem or make things "+
            "worse, depending on how it's reassembled."));

    add_item(({"lights", "wiring", "flickering lights"}),
        BSN("The hum of old wiring fills the air, a constant reminder that this place is barely holding together. The lights above "+
            "flicker intermittently, casting shadows across the floor that seem to dance in time with the sputtering fans inside the "+
            "building. It’s clear that this basement-like layer is one bad connection away from plunging the whole system into chaos."));

    add_item(({"room", "basement"}),
        BSN("The air is thick with the smell of old, dried ink and burnt circuitry, giving the space the feel of a forgotten basement "+
            "workshop. You can almost taste the dust in the air as it clogs up the ancient machinery, struggling to push data "+
            "through decades-old connections. Every now and then, you hear the faint clatter of a paper jam somewhere in the distance, "+
            "as if the processes above is waging a never-ending battle with its own inner workings."));

    add_exit(NODES + "printer_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link10", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "printer_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0xC0,0xFB,0xF9,0x0B,0x72,0x9E}));
    set_ip(({198,51,100,182,255}));
    set_hostname("printer");
}

