#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

public void
create_admin()
{

}

void
create_monster()
{
    ::create_monster();
    add_name("administrator");
    add_name("admin");
    create_admin();
}