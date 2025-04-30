/*
  /local.h

  This file contains all world specific information. To configure your
  own world and set up your own mud, make changes to this file.

  This file is configured for NetMud.

*/
#ifndef CONFIG_DEFINED
#define CONFIG_DEFINED

#define DEBUG_MODE_ENABLED 1
/*
 *
 * MUD_NAME
 *
 * The name of the mud. This will be defined in all files compiled.
 * It is either a single string or a mapping of one names for each
 * port it might be running on. '0' in the mapping means default name.
 *
 */
#define MUD_NAME ([ 0: "NetMud" ])

#define BASE_DOMAIN "game"

/*
 * OPEN_LOG_DIR
 *
 * This is the location of the open logs.
 */
#define OPEN_LOG_DIR "/game/log"

/*
 * DISCARD_DOMAIN_DIR
 *
 * This is the name of the directory where all the removed domains are
 * put awaiting further developments.
 */
#define DISCARD_DOMAIN_DIR "/discarded"

/*
 * DEFAULT_START
 *
 * This is the default starting location if nothing else is defined
 */
#define DEFAULT_START "/game/nodes/start_node"

#define DEFAULT_START_LOCATION "/game/nodes/start_node"
#define DEF_STARTING_PLACE DEFAULT_START_LOCATION
#define TEMP_STARTING_PLACE DEFAULT_START_LOCATION

/*
 * LOGIN_NEW_PLAYER
 *
 * This is the player object that manages all entering of new players.
 */
#define LOGIN_NEW_PLAYER  "/game/login/player"

/*
 * LOGIN_FILE_WELCOME  - general welcome before password.
 * LOGIN_FILE_NEWS     - special news message after password.
 * LOGIN_FILE_RUNLEVEL - message about using a runlevel.
 * LOGIN_FILE_NEWCHAR  - message to new characters before confirmation.
 *
 * This is the names of the files that are written to user logging in.
 */
#define LOGIN_FILE_WELCOME  "/doc/login/WELCOME"
#define LOGIN_FILE_RUNLEVEL "/doc/login/RUNLEVEL"

#define LOCAL_HELP_PATH "/doc/help/local/"

/*
 * DEFAULT_DEATH tells what object should be loaded when a player dies
 */

#define DEFAULT_DEATH "/game/nodes/death/death_mark"

/*
 * DOMAIN_LINK
 *
 * Filenames trailing /d/Domain_name/ to preload on startup
 */
#define DOMAIN_LINK "domain_link"

/*
 * GAMEINFO_LOGIN
 * GAMEINFO_INFO
 *
 * Information about the game in login procedure.
 */
#define GAMEINFO_INFO	"/game/doc/login/GAMEINFO_INFO"

/*
 * NO_GUEST_LOGIN
 *
 * Define this if you do not want a shared "guest" character to log in
 * without using a password. Undefine this and "guest" will be able to
 * log in.
 */
#define NO_GUEST_LOGIN

/*
 * MAX_PLAY
 *
 * This is the maximum amount of players that may be logged on at
 * one time.
 */
#define MAX_PLAY        (2048)

/*
 * SMALL_MEMORY_LIMIT
 * LARGE_MEMORY_LIMIT
 *
 * This is the maximum memory allowed by the master object before itself
 * starts Armageddon. The memory consumption is fetched from the
 * debug("malloc") efun as the number before (a). The use of SMALL/LARGE
 * is determined by external calls to the gamedriver.
 * No need for us to monitor this any more, I'm setting this to a very
 * high value, in effect disabling the monitoring functionality. /Mrpr
 * 1.0 GB = 1073741824
 */
#define SMALL_MEMORY_LIMIT (2147483648)
#define LARGE_MEMORY_LIMIT (2147483648)

/*
 * SWAP_MEM_MIN
 * SWAP_MEM_MAX
 * SWAP_TIME_MIN
 * SWAP_TIME_MAX
 *
 * These are swapping control parameters and control when we do swapping.
 * The swapping will start when we have used SWAP_MEM_MIN bytes of memory,
 * when we reach SWAP_MEM_MAX we will swap as much as possible. We will
 * not swap objects unless it is SWAP_TIME_MIN seconds old and we will
 * swap all objects older than SWAP_TIME_MAX seconds.
 */
#define SWAP_MEM_MIN    350000000
#define SWAP_MEM_MAX    450000000
#define SWAP_TIME_MIN   180
#define SWAP_TIME_MAX   900

/*
 * ARMAGEDDON
 *
 * This is the object to call "slow_shut" in when the GD tells master
 * that the memory is getting low.
 */
// #define ARMAGEDDON "/game/obj/armageddon"

/*
 * NPC_SOULS
 *
 * The array of sould that all mobiles should have
 */
// #define NPC_SOULS ({ "/cmd/std/soul_cmd", "/game/cmd/misc" })
#define NPC_SOULS ({ "/cmd/std/soul_cmd", "/cmd/live/speech", "/cmd/live/things" })

/*
 * MAX_IDLE_TIME
 *
 * The maximum time you are guaranteed to be able to stay idle before
 * being logged out. The amount is counted in seconds.
 */
#define MAX_IDLE_TIME 3600

/*
 * FOB_KEEP_CHANGE_TIME
 *
 * Define this when you also want to keep track in the KEEPERSAVE of the time
 * the domain or rank/level of the wizard was changed. When undefined, this
 * infromation will not be kept. Naturally the LEVEL log will still contain
 * that information, should that be defined.
 */
#undef FOB_KEEP_CHANGE_TIME

/*
 * BLOCK_DOUBLE_LOGIN
 *
 * Define this to block double logins from listed seconds.
 */
#define BLOCK_DOUBLE_LOGIN

/*
 * DAY_AND_NIGHT
 *
 * If DAY_AND_NIGHT is active there will be a day night cyclus from 10 pm
 * to 5 am.
 */
#undef DAY_AND_NIGHT

/*
 * REGULAR_REBOOT
 *
 * If defined, the hour during which the game will be rebooted.
 */
#undef REGULAR_REBOOT 9

/*
 * REGULAR_UPTIME
 * UPTIME_VARIATION
 *
 * Define this to specify the amount of hours uptime after which a reboot
 * shall follow. The variation is the total time window in hours on this
 * maximum uptime. I.e. an uptime of 10 hours and var of 2 means 9 - 11.
 * This shouldn't be a whole number of days, so it cycles through the day.
 */
#define REGULAR_UPTIME 332
#define UPTIME_VARIATION 2

/*
 * NO_ALIGN_TITLE
 *
 * Defined if alignment title is not used
 */
#define NO_ALIGN_TITLE

#undef NO_SKILL_DECAY

/*
 * LANG_PRETITLES
 *
 * We use badname instead of the pretitle check.
 */
#undef LANG_PRETITLES

/*
 * CYCLIC_LOG_SIZE
 *
 * This is a mapping containing the maximum file size for logs for a given
 * euid. Normally the maximum file size for a log is given with the euid '0',
 * however, if the name of the euid appears in this mapping, the owner of the
 * euid has the option of allowing the size grow to the given value before
 * cycling is done.
 * If the size is less than 0, the log will be allowed to grow indefinately.
 */
#define CYCLIC_LOG_SIZE ([ 0 : 20000, "root" : -1, "NetMud" : 100000 ])

/*
 * PRELOAD_FIRST
 *
 * Information on what files are to be preloaded before anything else.
 * This can either be a string and is then a filename holding all
 * files to be preloaded.
 *
 * It can also be an array holding the files to preload.
 */
#define PRELOAD_FIRST "/secure/preload_list"

#endif

