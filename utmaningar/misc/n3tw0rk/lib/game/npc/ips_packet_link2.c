#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/ips_packet";

void create_ips_packet(void)
{
    ::create_ips_packet();

    set_ok_exits(({"upstream","downstream","port0"}));
    set_network(({198,51,100,0}),({255,255,255,192}));
}
