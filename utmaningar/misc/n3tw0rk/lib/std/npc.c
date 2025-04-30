/*
  /std/npc.c

  This is the base for all NPC creatures that need to use combat tools.

*/
#pragma save_binary
#pragma strict_types

inherit "/std/creature";

#include <files.h>
#include <money.h>
#include <stdproperties.h>

void
create_npc()
{
    ::create_creature();
}

nomask void
create_creature() 
{
    if (query_prop(LIVE_I_UNDEAD))
    {
	create_npc();
        MONEY_CONDENSE(this_object());
	return;
    }
    create_npc(); 
    MONEY_CONDENSE(this_object());
}

void
reset_npc()
{
    ::reset_creature();
}

nomask void
reset_creature()
{
    reset_npc();
}

/*
 * Description:  Use the combat file for generic tools
 */
public string 
query_combat_file() 
{
    return "/std/combat/ctool"; 
}

/*
 * Function name:  default_config_npc
 * Description:    Sets all neccessary values for this npc to function
 */
varargs public void
default_config_npc(int lvl)
{
    default_config_creature(lvl);
}
