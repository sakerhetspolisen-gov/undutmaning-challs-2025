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
    set_long(BSN("You've stumbled into the ground floor of what can only be described as an "+
        "architectural relic. The building's grey, boxy exterior could easily be mistaken for "+
        "an oversized filing cabinet, and everything within seems to be stuck in a perpetual "+
        "state of obsolescence. The exposed wiring trails along the walls like neglected vines, "+
        "and the cables look as if they might short-circuit if someone merely glanced at them "+
        "too sharply. The fluorescent lights above cast a cold, unfeeling glow that makes even "+
        "the most vibrant hues seem to retreat into the drab monotony of yesteryear. An old, "+
        "battered desk, as worn as a centenarian's slippers, sprawls along one wall, behind "+
        "which an attendant stands, embodying the spirit of ennui. The staircase leading up to "+
        "the higher floors seems as tired as the rest of the place, and a tunnel leads away "+
        "upstream, presumably to somewhere that isn't suffering from the same dreary fate."));

    add_item(({"floor","ground floor","building","relic","boxy structure","boxy buildning"}),
        BSN("The ground floor of this architectural curiosity is the very definition of drab. "+
        "The building itself is a grey, boxy structure that seems to have given up on trying to "+
        "be anything other than functional — like a beige cardigan for a particularly dreary day."));

    add_item(({"wiring","wires"}),
        BSN("The exposed wiring is a testament to the building's age. It's as if someone decided "+
        "that keeping the technological arteries visible was a good way to remind everyone of the "+
        "passage of time — or perhaps to provide a live-action exhibit of entropy."));

    add_item(({"lighting","lights","light","fluorescent light","fluorescent lightning"}),
        BSN("The fluorescent lights cast a pallid, lifeless glare that drains all vibrancy from "+
        "the room. They seem to be working hard to ensure that no matter how interesting things "+
        "might be, they will always look as dull as dishwater."));

    add_item(({"packet","packets"}),
        BSN("Despite the drab surroundings, packets continue to arrive and depart with a relentless "+
        "regularity. They zip around in their usual fashion, apparently unfazed by the atmosphere "+
        "of bureaucratic inertia."));

    add_item(({"desk"}),
        BSN("The desk is a relic in its own right — old, worn, and more of a resting place for the "+
        "attendant than a functional workspace. It has seen better days and has possibly been the "+
        "unwilling recipient of a fair amount of leaning and sighing."));

    add_item(({"stairs","stair","staircase"}),
        BSN("The staircase leading up to the higher floors seems to be functioning but carries an "+
        "air of weariness, as though it has seen more than its fair share of trudging feet."));

    add_item(({"tunnel"}),
        BSN("The tunnel leading away from this floor is a dark, uninviting passage that seems to "+
        "promise nothing but more of the same drab and dreary existence further upstream."));
     
    add_exit(NODES + "mail_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link6", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "mail_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0x00,0x14,0x22,0xFE,0x61,0x12}));
    set_ip(({198,51,100,25,127}));
    set_hostname("mail");
}
