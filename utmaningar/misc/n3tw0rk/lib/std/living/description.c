/*
 * /std/living/description.c
 *
 * This is a subpart of /std/living.c
 *
 * All description relevant routines are defined here.
 *
 * NOTE
 * There is some calls of the type: this_object()->function()
 * in a number of places. The reason for this is to allow those
 * functions to be shadowed as internal function calls are not
 * possible to shadow.
 */

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <state_desc.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <state_desc.h>

#ifdef DAY_AND_NIGHT
#include <mudtime.h>
#endif

private static int appearance_offset;
private static int is_linkdead;


/*
 * Function name: query_humanoid
 * Description  : Tells whether we are humanoid or not. By default, all
 *                livings are marked as humanoid and then in /std/creature
 *                we unmark them as such by masking this function.
 * Returns      : int - 1.
 */
public int
query_humanoid()
{
    return 1;
}

/*
 * Function name: query_met
 * Description  : Tells if we know a certain living's name. As NPC's always
 *                know everyone, this function is masked in the player object
 *                for true met/nonmet behaviour for players (if defined).
 * Arguments    : mixed name - the name or objectpointer to the living we
 *                             are supposed to have met.
 * Returns      : int 1 - always as NPC's always know everyone.
 */
public int
query_met(mixed name)
{
    return 1;
}

/*
 * Function name:   notmet_me
 * Description:     Finds out if obj is considered to have met me. Players
 *                  must have been introduced to me. All others don't have to
 *                  be introduced to know me.
 * Arguments:       obj: Object in question, has it met me?
 * Returns:         True if object has not met me.
 */
public int
notmet_me(object obj)
{
    return 0;
}

/*
 * Function name:   query_real_name
 * Description:     Returns the lowercase name of this living.
 *                  E.g.: "fatty".
 * Returns:         The name
 */
public string
query_real_name()
{
    return lower_case(::query_name());
}

/*
 * Function name:   query_name
 * Description:     Returns the capitalized name of this living.
 *                  E.g.: "Fatty".
 * Returns:         The name
 */
public string
query_name()
{
    // return ::query_name();
    return capitalize(::query_name());
}

/*
 * Function name:   query_met_name
 * Description:     Returns the name of this living, or "ghost of name" if
 *                  this living is not quite so living. E.g.: "Fatty".
 * Returns:         The name
 */
public string
query_met_name()
{
    if (this_object()->query_ghost())
    	return "ghost of " + query_name();
    else
	    return query_name();
}

/*
 * Function name:   query_Met_name
 * Description:     Returns the capitalized name of this living, prepended
 *                  with "Ghost of" if the living is not that living at all.
 *                  E.g.: "Ghost of Fatty".
 * Returns:         The capitalized name of the living when met.
 */
public string
query_Met_name()
{
    return capitalize(query_met_name());
}

/*
 * Function name:   query_art_name
 * Description:	    Gives the name with a prefix article when the object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "a big fat gnome wizard".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with article.
 */
public varargs string
query_art_name(object pobj)
{
    string pre, aft;

    pre = ""; aft = "";
    if (!objectp(pobj))
    	pobj = previous_object(-1);
    /*
    if (!CAN_SEE(pobj, this_object()) || !CAN_SEE_IN_ROOM(pobj))
	    return LD_SOMEONE;
    */
    if (query_prop(OBJ_I_INVIS) > 0)
    {
    	pre = "(";
	    aft = ")";
    }
    else if (query_prop(OBJ_I_HIDE) > 0)
    {
    	pre = "[";
	    aft = "]";
    }

	return pre + query_met_name() + aft;
}

/*
 * Function name:   query_Art_name
 * Description:	    Gives the name with a capitalized prefix article when the
 *                  calling object has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "A big fat gnome wizard".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with capitalized article.
 */
public varargs string
query_Art_name(object pobj)
{
    string desc = query_art_name(pobj);

    /* Capitalize the right character if the description starts with ( or [. */
    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}

/*
 * Function name:   query_art_possessive_name
 * Description:	    Gives the possessive form of the name with a prefix
 &                  article when the calling object has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty's",
 *                        when unmet: "a big fat gnome wizard's".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Possessive name prefixed with article.
 */
public varargs string
query_art_possessive_name(object pobj)
{
    return LANG_POSS(query_art_name(pobj));
}

/*
 * Function name:   query_Art_possessive_name
 * Description:	    Gives the possessive form of the name with a capitalized prefix
 &                  article when the  calling object has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty's",
 *                        when unmet: "A big fat gnome wizard's".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Possessive name prefixed with capitalized article.
 */
public varargs string
query_Art_possessive_name(object pobj)
{
    return LANG_POSS(query_Art_name(pobj));
}

/*
 * Function name:   query_the_name
 * Description:	    Gives the name preceded by "the" when the object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "the big fat gnome wizard".
 * Arguments:       pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with "the".
 */
public varargs string
query_the_name(object pobj)
{
    string pre = "", aft = "";

    if (!objectp(pobj))
	pobj = previous_object(-1);

    if (!CAN_SEE(pobj, this_object()) || !CAN_SEE_IN_ROOM(pobj))
	return LD_SOMEONE;
    if (query_prop(OBJ_I_HIDE) > 0)
    {
	pre = "[";
	aft = "]";
    }
    if (query_prop(OBJ_I_INVIS) > 0)
    {
	pre = "(";
	aft = ")";
    }

	return pre + query_met_name() + aft;
}

/*
 * Function name:   query_The_name
 * Description:	    Gives the name preceded by "The" when the calling object
 *                  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty",
 *                        when unmet: "The big fat gnome wizard".
 * Argument:        pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Name prefixed with "The".
 */
public varargs string
query_The_name(object pobj)
{
    string desc = query_the_name(pobj);

    /* Capitalize the right character if the description starts with ( or [. */
    if (wildmatch("[\\[(]*", desc))
        return desc[..0] + capitalize(desc[1..]);

    return capitalize(desc);
}

/*
 * Function name:   query_the_possessive_name
 * Description:	    Gives the possessive form of the name preceded by "the"
 *                  when the calling object  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty's",
 *                        when unmet: "the big fat gnome wizard's".
 * Argument:        pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Possessive name prefixed with "the".
 */
public varargs string
query_the_possessive_name(object pobj)
{
    return LANG_POSS(query_the_name(pobj));
}

/*
 * Function name:   query_The_possessive_name
 * Description:	    Gives the possessive form of the name preceded by "The"
 *                  when the calling object  has not met this living.
 *                  E.g.:
 *                        when met:   "Fatty's",
 *                        when unmet: "The big fat gnome wizard's".
 * Argument:        pobj: The object that wants to know the name.
 *                  If pobj is undefined, it is assumed that the call has
 *                  been done through a protected vbfc
 * Returns:         Possessive name prefixed with "The".
 */
public varargs string
query_The_possessive_name(object pobj)
{
    return LANG_POSS(query_The_name(pobj));
}

/*
 * Function:    query_presentation
 * Description: Gives a presentation of the living in one line. Including
 *              Name, Race, Guild titles, Alignment and Experience level
 *              This should only be displayed to met players.
 *              E.g.: "Fatty the donut-fan, wizard, male gnome (eating)"
 * Returns:     The presentation string
 */
public string
query_presentation()
{
    return "";
}

/*
 * Function name:   short
 * Description:     Returns the short-description of this living, for the
 *                  object given. Handles invisibility and met/nonmet.
 * Returns:         The short string.
 */
public varargs string
short(object for_obj)
{
    return query_short();
//	return query_art_name(for_obj);
}

/*
 * Function name: vbfc_short
 * Description:   Gives short as seen by previous object
 * Returns:	  string holding short()
 */
public string
vbfc_short()
{
    object for_obj;

    for_obj = previous_object(-1);
    if (!this_object()->check_seen(for_obj))
	    return LD_SOMEONE;

    return this_object()->short(for_obj);
}

/*
 * Function name:   num_scar
 * Description:     Get the number of scars a player has
 * Returns:         int holding number of scars
 */
public int
num_scar()
{
    int i, j, n,scar;

    j = 1; n = 0; scar = this_object()->query_scar();

    while (i < F_MAX_SCAR)
    {
    	if (scar & j) n++;
    	j *= 2; i++;
    }
    return n;
}

/*
 * Function name:   desc_scar
 * Description:     Get the composite string holding the scar description
 * Returns:         string holding scar description.
 */
public string
desc_scar()
{
    int i, j, scar;
    string *scar_desc, *my_scars;

    scar_desc = F_SCAR_DESCS;
    scar = this_object()->query_scar();
    j = 1;
    my_scars = 0;
    while(i < F_MAX_SCAR)
    {
	if (scar & j)
	{
	    if (my_scars)
		my_scars = my_scars + ({ scar_desc[i] });
	    else
		my_scars = ({ scar_desc[i] });
	}
	j *= 2;
	i += 1;
    }

    if (!my_scars) return 0;

    return COMPOSITE_WORDS(my_scars);
}

/*
 * Function name:   show_scar
 * Description:     Finds out which scars this living has.
 * Returns:         A string with the scars.
 */
string
show_scar(mixed for_obj)
{
	return "";
}

/*
 * Function name:   long
 * Description:     Returns the long-description of this living, and shows also
 *                  the inventory. Handles invisibility and met/nonmet. Note
 *                  that the function does not do any writes! It only returns
 *                  the correct string.
 * Arguments:       string for_obj: return an item-description
 *                  object for_obj: return the living-description
 * Returns:         The description string
 */
public varargs string
long(mixed for_obj)
{
    string          cap_pronoun, res;
    object 	    eob;

    if (stringp(for_obj))   /* Items */
	    return ::long(for_obj);

    if (!objectp(for_obj))
	    for_obj = this_player();

    if (for_obj == this_object())
	    res = LD_PRESENT_YOU(this_object());
    else
    {
	    res = query_long();
	    if (!stringp(res) && !functionp(res))
	    {
            /*
	        cap_pronoun = capitalize((string)this_object()->query_pronoun());
	        if (!notmet_me(for_obj))
		        res = LD_PRESENT_TO(this_object());
	        else if (!(this_object()->short(for_obj)))
		        return "";
	        else
		        res = cap_pronoun + " is " +
			    LANG_ADDART(this_object()->short(for_obj)) + ".\n";
	            if (this_object()->query_ghost())
	            {
		            return LD_MET_GHOST(this_object());
	            }
            */
            res = LD_PRESENT_TO(this_object());
	    }
        else
            res = check_call(res);
    }

    return res + this_object()->show_sublocs(for_obj);
}

/*
 * Function name: do_glance
 * Description  : This is the routine describing rooms to livings. It will
 *                print the long or short description of the room, the
 *                possible exits, all visible non-living and living objects
 *                in the room (but not this_object() itself) and then it
 *                will print possible attacks going on. Note that this
 *                function performs a write(), so this_player() will get the
 *                descriptions printed to him/her.
 * Arguments    : int brief - if true, write the short-description,
 *                            else write the long-description.
 * Returns      : int 1 - always.
 */
public int
do_glance(int brief)
{
    object env;
    string item;
    string text;

    /* Don't waste the long description on NPC's. */
    if (!interactive(this_object()))
    	return 0;

    env = environment();
    
    text = capitalize(env->short(this_object()) + ".");
    /* Describe the room and its contents. */
	if (brief)
  	{
	    write(text + "\n");
	    write(env->exits_description());
	}
	else
    {
	    write(env->long());
    }

    env->show_visible_contents(this_object());

    return 1;
}

/*
 * Function name: appraise_object
 * Description:   This function is called when someone tries to appraise a
 *		  living object.
 * Arguments:     num - use this number instead of the skill.
 */
public void
appraise_object(int num)
{
    /* Nobody is concerned with volume of livings. Display weight only. */
    write("\n" + this_object()->long(0, this_player()) + "\nYou " +
        APPRAISE_VERB + " " + query_possessive() + " weight is about " +
	appraise_weight(num) + ".\n");
}
 
/*
 * Function name: show_hook
 * Description  : This hook is called whenever an item is 'snown' to this
 *                living. It is shown by this_player().
 * Arguments    : object ob - the object shown.
 */
public void
show_hook(object ob)
{
    return;
}
