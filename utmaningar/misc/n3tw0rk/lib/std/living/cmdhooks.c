/*
 * /std/living/cmdhooks.c
 *
 * This is a subpart of /std/living.c
 *
 * All command hooks are handled here, wiz, soul, tool and spell commands.
 */

#include <cmdparse.h>
#include <login.h>
#include <macros.h>
#include <std.h>
#include <options.h>

/*
 * Variables, These are only accessed from routines in this module.
 */
static private mapping com_sounds;
static string   *wiz_souls,             /* The wizard soul names */
                *soul_souls,            /* The ordinary soul names */
                *tool_souls,            /* The tool soul names */
                say_string;             /* The last message said */

/*
 * Prototypes
 */
public void update_hooks();
public varargs int communicate(string str = "");
public varargs int acommunicate(string str = "");
public varargs int wcommunicate(string str = "");
static int my_commands(string str);

/*
 * Function name: cmdhooks_reset
 * Description  : Start the command parsing. The last added action is
 *                evaluated first, so speech is checked first.
 */
static void
cmdhooks_reset()
{
    update_hooks();

    add_action(my_commands, "", 1);
    add_action(communicate, "'", 2);
    add_action(acommunicate, "a'", 2);
    add_action(wcommunicate, "w'", 2);

    com_sounds = ([ ]);
}

/*
 * Function name: communicate
 * Description  : This function is called whenever the player wants to say
 *                something using the single quote ' as alias for say.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public varargs int
communicate(string str)
{
    return CMD_LIVE_SPEECH->say_text(str);
}

/*
 * Function name: acommunicate
 * Description  : This function is called whenever the player wants to say
 *                something using the shortcut a' as alias for asay.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public varargs int
acommunicate(string str)
{
    return CMD_LIVE_SPEECH->asay(str);
}

/*
 * Function name: wcommunicate
 * Description  : This function is called whenever the player wants to
 *                whisper something using the shortcut w'.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
public varargs int
wcommunicate(string str)
{
    return CMD_LIVE_SPEECH->whisper(str);
}

/*
 * Function name: query_say_string
 * Description  : This function returns the text the player last spoke using
 *                the say command. This can only be queried with this person
 *                being the interactive party for security reasons.
 * Returns      : string - the last string the player said.
 */
public nomask string
query_say_string()
{
    if (this_interactive() != this_object())
    {
        return "";
    }

    return say_string;
}

/*
 * Function name: set_say_string
 * Description  : We store the text the player says to allow guilds to modify
 *                the verb based on the text. In order not to allow people to
 *                put words in your mouth, this function may only be called
 *                from the speech soul itself.
 * Arguments    : string str - the text to say.
 */
public nomask void
set_say_string(string str)
{
    if (file_name(previous_object()) == CMD_LIVE_SPEECH)
    {
        say_string = str;
    }
}

/*
 * Function name: race_sound
 * Description  : This function returns the VBFC value for the sound a
 *                particular living hears when this player speaks. It
 *                operates on previous_object(-1). Notice that we use
 *                query_race rather than query_race_name since the first
 *                will always return a true and valid race name. The
 *                person speaking is this_player().
 * Returns      : string - the race sound the receiver hears.
 */
public string
race_sound()
{
    string raceto = previous_object(-1)->query_race();

    if (!com_sounds[raceto])
    {
        return "says";
    }

    return com_sounds[raceto];
}

/*
 * Function name: actor_race_sound
 * Description  : This function returns the sound this_player() makes when
 *                he or she speaks. By default this is 'say'.
 * Returns      : string - the race sound the receiver hears.
 */
public string
actor_race_sound()
{
    return "say";
}

/*
 * Function name: query_com_sounds
 * Description  : Returns the mapping with the sounds the way people
 *                understand the speech of this player.
 * Returns      : mapping - the mapping.
 */
public mapping
query_com_sounds()
{
    return secure_var(com_sounds);
}

/*
 * Function name:   start_souls
 * Description:     Tell the souls that we are using them, this is used to
 *                  add sublocations for the living object. Also call
 *                  'replace_soul' so that an obsolete soul can rederict
 *                  the usage to another newer soul/souls.
 * Arguments:       souls: an array with all souls that should be started
 */
nomask public string *
start_souls(string *souls)
{
    int il, rflag;
    mixed ob;
    string *replace_souls, *used_souls, *tmp;
    mapping replaced;

    used_souls = ({});
    replaced = ([]);

    do
    {
        rflag = 0;
        for (replace_souls = ({}), il = 0; il < sizeof(souls); il++)
        {
            ob = souls[il];

            if (!stringp(ob))
                continue;

            catch(ob->teleledningsanka());
            ob = find_object(ob);
            if (ob)
            {
                if (replaced[ob]) /* Dont replace twice */
                    continue;
                else
                {
                    tmp = ob->replace_soul();
                    replaced[ob] = 1;
                }

                if (stringp(tmp))
                {
                    replace_souls += ({ tmp });
                    rflag = 1;
                }
                else if (pointerp(tmp))
                {
                    replace_souls += tmp;
                    rflag = 1;
                    if (member_array(souls[il], tmp) >= 0)
                        tmp = 0;
                }

                if ((tmp == 0) && (member_array(souls[il], used_souls) < 0))
                {
                    ob->using_soul(this_object());
                    used_souls += ({ souls[il] });
                }
            }
            else
                used_souls += ({ souls[il] });
        }
        if (rflag)
            souls = replace_souls + ({});
    } while (rflag);

    return used_souls;
}

/*
 * Function name: load_command_souls
 * Description  : Load the command souls into the player.
 * Returns      : int 1/0 - success/failure.
 */
nomask public int
load_command_souls()
{
    soul_souls = query_cmdsoul_list();
    if (!sizeof(soul_souls))
    {
        soul_souls = NPC_SOULS;
    }

    soul_souls = start_souls(soul_souls);
    update_cmdsoul_list(soul_souls);
    return 1;
}

/*
 * Function name:   my_commands
 * Description:     Try to find and perform a command.
 * Arguments:       str - the argument string.
 * Returns:         True if the command was found.
 */
static int
my_commands(string str)
{
    int    i, rv;
    object ob;
    string verb = query_verb();
    int    size;

    size = sizeof(soul_souls);
    i = -1;
    while(++i < size)
    {
        ob = find_object(soul_souls[i]);
        if (!ob)
        {
            if (catch(soul_souls[i]->teleledningsanka()))
                tell_object(this_object(),
                    "Yikes, baaad soul: " + soul_souls[i] + "\n");
            ob = find_object(soul_souls[i]);
            if (!ob)
                continue;
        }
        if (ob->exist_command(verb))
        {
            if (ob->do_command(verb, str))
                return 1;
        }
    }

    return 0;
}

/*
 * Function name: update_hooks
 * Description  : This function loads and initializes all wizards souls,
 *                tool souls and command souls the player can have.
 */
nomask public void
update_hooks()
{
    load_command_souls();
}

/*
 * Function name:   cmdhooks_break_spell
 * Description:     Break the preparation for a spell. Note that the caster
 *                  still suffers the attack delay.
 * Returns:         True if a spell was being prepared
 */
varargs public int
cmdhooks_break_spell(string msg)
{
    /* Functionality moved into spells.c */
    return this_object()->break_spell(msg);
}
