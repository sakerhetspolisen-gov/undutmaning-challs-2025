/*
  /std/creature.c

  This is the base for all nonhumanoid livings.

*/
#pragma save_binary
#pragma strict_types

inherit "/std/mobile";

void
create_creature() { ::create_mobile(); }

nomask void
create_mobile()
{
    create_creature(); 
}

void
reset_creature() {  ::reset_mobile(); }

nomask void
reset_mobile() { reset_creature(); }

/*
 * Function name:  default_config_npc
 * Description:    Sets some necessary values for this creature to function
 *                 This is basically stats and skill defaults.
 */
varargs public void
default_config_creature(int lvl)
{
    default_config_mobile(lvl);
}

/*
 * Function name: query_humanoid
 * Description  : Since this is not a humanoid, we mask this function so
 *                that it returns 0.
 * Returns      : int - 0.
 */
public int
query_humanoid()
{
    return 0;
}

