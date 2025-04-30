#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/node";

public void
create_node()
{
    add_item(({"memory","process"}),
        BSN("You and the bytes around you are a part of the NetworkDiscovery process. "+
            "The process is running on a laptop that is connected to an unknown network, "+
            "and the tubes below you are probably open network connections to this network."));
    add_item(({"data", "bytes"}),
        BSN("The bytes of data floats around in the memory of their processes. Doing "+
            "all sorts of important representing and storing."));
}
