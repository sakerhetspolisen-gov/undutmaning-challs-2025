/*
 * /std/room/description.c
 *
 * This is a sub-part of /std/room.c
 *
 * In this module you will find the things relevant to the description of the
 * room.
 */

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <living_desc.h>
#include <ss_types.h>
#include <login.h>

static  mixed   room_descs;        /* Extra longs added to the rooms own */
static  int     searched;          /* Times this room has been searched */
static  string *herbs;             /* WHat herbs grows in this room? */
/* Buffer this as it's a rather costly call. */
static  string  gmcp_room_id = MASTER_HASH(this_object());

/*
 * Function name: add_my_desc
 * Description:   Add a description printed after the normal long description.
 * Arguments:     str: Description as a string
 *                cobj: Object responsible for the description
 *                      Default: previous_object()
 */
varargs public void
add_my_desc(string str, object cobj)
{
    if (query_prop(ROOM_I_NO_EXTRA_DESC))
        return;

    if (!cobj)
        cobj = previous_object();

    if (!str)
        return;

    if (!room_descs)
        room_descs = ({ cobj, str });
    else
        room_descs = room_descs + ({ cobj, str });
}

/*
 * Function name:       change_my_desc
 * Description:         Change a description printed after the normal
 *                      longdescription. NOTE: if an object has more than
 *                      one extra description only one will change.
 * Arguments:           str: New description as a string
 *                      cobj: Object responsible for the description
 *                            Default: previous_object()
 */
varargs public void
change_my_desc(string str, object cobj)
{
    int i;
    mixed tmp_descs;

    if (query_prop(ROOM_I_NO_EXTRA_DESC))
        return;

    if (!cobj)
        cobj = previous_object();

    if (!str || !cobj)
        return;

    i = member_array(cobj, room_descs);

    if (i < 0)
        add_my_desc(str, cobj);
    else
        room_descs[i + 1] = str;
}

/*
 * Function name:       remove_my_desc
 * Description:         Removes an earlier added  description printed after
 *                      the normal longdescription.
 * Arguments:           cobj: Object responsible for the description
 *                            Default: previous_object()
 */
varargs public void
remove_my_desc(object cobj)
{
    int i, sf;

    if (query_prop(ROOM_I_NO_EXTRA_DESC))
        return;

    if (!cobj)
        cobj = previous_object();

    sf = objectp(cobj);

    i = member_array(cobj, room_descs);
    while (i >= 0)
    {
        if (sf)
            room_descs = exclude_array(room_descs, i, i + 1);
        else
            room_descs = exclude_array(room_descs, i - 1, i);
        i = member_array(cobj, room_descs);
    }
}

/*
 * Function name:    query_desc
 * Description:      Gives a list of all added descriptions to this room
 * Returns:          Array on the form:
 *                     desc1, obj1, desc2, obj2, ..... descN, objN
 */
public mixed
query_desc()
{
    return slice_array(room_descs, 0, sizeof(room_descs));
}

/*
 * Function name: exits_description
 * Description  : This function will return the exits described in a nice way.
 * Returns      : string - the description.
 */
public string
exits_description()
{
    string *exits;
    int size;
    string text;

    if (query_noshow_obvious())
    {
        exits = ({ });
    }
    else
    {
        exits = query_obvious_exits();
    }

    switch(size = sizeof(exits))
    {
    case 0:
        text = "";
        break;

    case 1:
        text =  "There is one obvious exit: " + exits[0] + ".\n";
        break;

    default:
        text = "There are " + LANG_WNUM(size) +
            " obvious exits: " + COMPOSITE_WORDS(exits) + ".\n";
    }

    if (this_player()->query_wiz_level())
    {
        exits = query_exit_cmds() - exits;
        switch(size  = sizeof(exits))
        {
        case 0:
            break;

        case 1:
            text += "There is one non-obvious exit: " + exits[0] + ".\n";
            break;

        default:
            text += "There are " + LANG_WNUM(size) +
               " non-obvious exits: " + COMPOSITE_WORDS(exits) + ".\n";
        }
    }

    return text;
}

/*
 * Function name: long
 * Description  : Describe the room and possibly the exits
 * Arguments    : string item: name of item or 0
 * Returns      : string - A string holding the long description of the room.
 */
varargs public string
long(string item)
{
    int index;
    int size;
    string desc = ::long(item);

    /* When querying for an item, just return the underlying desc. */
    if (stringp(item))
    {
        return desc;
    }

    /* Initialize in case there isn't a long description (bad long). */
    if (!stringp(desc))
    {
        desc = "";
    }

    /* This check is to remove extra descriptions that have been added by
     * an object that is now destructed.
     */
    while ((index = member_array(0, room_descs)) >= 0)
    {
        room_descs = exclude_array(room_descs, index, index + 1);
    }

    if (pointerp(room_descs))
    {
        index = -1;
        size = sizeof(room_descs);
        while((index += 2) < size)
        {
            desc += check_call(room_descs[index]);
        }
    }

    return desc + exits_description();
}

/*
 * Function name: describe_contents
 * Description:   Give a description of items in this room
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    object *lv, *dd;
    string item;

    for_obj->catch_tell(show_sublocs(for_obj));

    obarr -= ({ for_obj });

    lv = FILTER_LIVE(obarr);
    dd = obarr - lv;

    item = COMPOSITE_FILE->desc_dead(dd, 1);
    if (stringp(item))
    {
        for_obj->catch_tell(capitalize(item) + ".\n");
    }

    item = COMPOSITE_FILE->desc_live(lv, 1, for_obj, 1);
    if (stringp(item))
    {
        for_obj->catch_tell(capitalize(item) + ".\n");
    }
}

/*
 * Function name: calc_pros
 * Description:   Finding formula, positive side effects
 * Arguments:     player - The herbalist
 * Returns:       A number
 */
int
calc_pros(object player)
{
    int p = player->query_skill(SS_HERBALISM);

    /* Penalty will be given if no skill. */
    /* To add a certain element of luck  - wise players might get lucky. */
    return p + random(player->query_stat(SS_WIS) / 3);
}

/*
 * Function name: calc_cons
 * Description:   Finding formula, negative side effects
 * Arguments:     player - The herbalist
 * Returns:       A number ;-)
 */
int
calc_cons(object player)
{
    int p;

    /* If no herbalism skill, players will really have problems. */
    if (!player->query_skill(SS_HERBALISM))
        p += 15;

    /* Extra penalty if the player cannot see in the room or is blind */
    if (!CAN_SEE_IN_ROOM(player) || !CAN_SEE(player, this_object()))
        p += 45;

    /* Penalty increases for each time the room has been searched.
     * This will of course be sad for those who comes to the room after
     * a non-skilled searcher has tried to search some times, but this
     * could indicate that the first person trampled the herbs underfoot :-)
     */
    p += searched * searched * 5;

    /* If we have good luck, we can also have bad luck....
     * ....and stupid players with low intelligence have more bad luck ;-)
     */
    p += random((100 - player->query_stat(SS_INT)) / 3);

    return p;
}

/*
 * Function name: no_find
 * Description:   Called when the herbalist didn't find any herbs
 * Returns:       string to write
 */
string
no_find()
{
    return "You search everywhere, but find no herbs.\n";
}

/*
 * Function name: search_for_herb
 * Description:   The herbalist has searched the room, now let's see if and
 *                what he has found.
 * Arguments:     herbalist - The player searching for herbs
 *                herb_file - the file of the herb the player is looking for
 *                            (optional)
 * Returns:       The message to write
 */
varargs string
search_for_herbs(object herbalist, string herb_file = 0)
{
    object herb;
    int difficulty;
    int specific;

    seteuid(getuid(this_object()));

    if (!herbs || !sizeof(herbs))
        return no_find();

    /* If we don't want a specific herb, select a random one. */
    if (!(specific = strlen(herb_file)))
        herb_file = one_of_list(herbs);

    /* Before accessing the herb file, make sure it loads ... */
    if (!herb_file || LOAD_ERR(herb_file))
        return no_find();

    /* If we look for a specific herb, we must be able to identify it. */
    if (specific && !herb_file->do_id_check(herbalist))
        return no_find();

    difficulty = herb_file->query_find_diff();
    if ((calc_pros(herbalist) - calc_cons(herbalist) -
            (difficulty * 10 - 50)) <= 0)
    {
        searched += 1;
        return no_find();
    }

    herb = clone_object(herb_file);
    tell_room(environment(herbalist), QCTNAME(herbalist) +
        " finds some herbs.\n", herbalist);
    searched += 2;

    /* Reward the player for finding the herb. */
    herbalist->add_exp_general(F_EXP_HERBSEARCH(difficulty));

    if (herb->move(herbalist))
    {
        herb->move(this_object(), 1);
        herb->start_decay();
        return "You find " + LANG_ASHORT(herb) + ", but are unable "+
               "to carry it with you!\n";
    }
    return "You find " + LANG_ASHORT(herb) + "!\n";
}

/*
 * Function name: add_herb_file
 * Description:   Add a herb file to our array
 * Arguments:     file - The filename to our herb
 * Returns:       1 if added
 */
int
add_herb_file(string file)
{
    if (!file)
        return 0;

    if (!herbs)
        herbs = ({ file });
    else
        herbs += ({ file });
    return 1;
}

/*
 * Function name: remove_herb_file
 * Description:   Remove a herb file from our array
 * Arguments:     file - The filename to our herb
 * Returns:       1 if removed
 */
int
remove_herb_file(string file)
{
    if (!file)
        return 0;

    if (!herbs)
        herbs = ({ });
    else
        herbs = filter(herbs, &operator(!=)(, file));

    return 1;
}

/*
 * Function name: query_herb_files
 * Description:   Query the herb files
 * Returns:       The herb array or 0.
 */
mixed
query_herb_files()
{
    return herbs;
}

/*
 * Function name: set_searched
 * Description:   Set the searched times number, perhaps there grow some new
 *                herbs at reset?
 * Arguments:     i - The new search number
 */
void set_searched(int i)
{
    searched = i;
}

/*
 * Function name: query_searched
 * Description:   Query for the search number
 * Returns:       The search number
 */
int query_searched()
{
    return searched;
}
