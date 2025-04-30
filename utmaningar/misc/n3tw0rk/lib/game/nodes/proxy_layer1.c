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
    set_long(BSN("You stand at the ground floor of a rather unremarkable building, the very epitome "+
        "of functionalism. The space around you is stark and utilitarian, as if someone had taken a vow of "+
        "minimalism and then decided to make it a way of life. Packets dart about with purpose, their efficiency "+
        "seeming almost palpable as they zip up and down the staircase. The environment hums with the whirring "+
        "of unseen gears and the faint crackle of electricity, a subtle reminder that in this realm, speed and "+
        "efficiency are the only measures of worth. The staircase, a sturdy conduit for the relentless stream of "+
        "data, ascends with no pretensions. Next to it, a small desk, manned by a receptionist, stands guard. "+
        "Behind you, an opening leads upstream into a tunnel, while ahead, the staircase beckons with a promise "+
        "of continued efficiency."));

    add_item(({"building"}),
        BSN("This building embodies the very essence of dullness, as if its sole purpose is to blend into the "+
            "background. Boxy and uninspired, it feels more like a functional cog in a larger machine than a "+
            "place with any particular character."));
    add_item(({"packet", "packets"}),
        BSN("Packets of all shapes and sizes whiz past you with the kind of focused efficiency that would make "+
            "a Swiss watchmaker proud. They come and go with such speed that you almost feel like you're in the "+
            "middle of a well-rehearsed dance, where every step is timed to perfection."));
    add_item(({"area","space"}),
        BSN("This ground floor is a monument to practicality. The space is so stripped-down and functional that "+
            "it feels like it was designed by someone who believes that anything beyond the bare essentials is "+
            "frivolous. There's nothing to distract or impede the rapid flow of packets and data."));
    add_item(({"gears"}),
        BSN("The gears are a faint, almost imperceptible hum, their constant spinning a reassuring sign that "+
            "everything is running like a well-oiled machine. You can't see them, but you can certainly hear "+
            "their industrious activity."));
    add_item(({"staircase"}),
        BSN("The staircase is a bustling artery, with packets rushing up and down in a ceaseless flow. Its utilitarian "+
            "design speaks of no-nonsense efficiency, dedicated to maintaining the brisk pace of data transmission."));
    add_item(({"opening", "tunnel"}),
        BSN("An unadorned opening that leads into the depths of a tunnel, flowing seamlessly upstream from here. "+
            "It's an entrance to the next stage of the data's journey, as straightforward and efficient as the rest of "+
            "this place."));
    add_item(({"desk"}),
        BSN("A compact desk, almost an afterthought, with just enough space for a screen and a receptionist. "+
            "It stands as the only piece of furniture in this otherwise stark environment, adding a touch of human "+
            "element to the otherwise mechanistic surroundings."));
    add_item(({"screen"}),
        BSN("A small screen, angled towards the receptionist. It remains a mystery to you, its contents hidden, "+
            "but it no doubt plays a role in the relentless efficiency of the operation here."));

    add_exit(NODES + "proxy_layer2", "up", "@@up_check", 0);
    add_exit(NODES + "link3", "upstream", "@@upstream_check", 0);

    object ob = clone_object(NPC + "proxy_layer1");
    ob->move(TO,1);
    set_admin(ob);

    set_mac(({0xE4,0x3A,0x6E,0x00,0x32,0x67}));
    set_ip(({198,51,100,33,127}));
    set_hostname("proxy");
}
