/*
 * /std/std.h
 *
 * This file holds all global constants and macros relevant to game security.
 */

#ifndef SECURE_DEFINED
#define SECURE_DEFINED

#ifndef SHORT_QUERIES_DEFINED
#define SHORT_QUERIES_DEFINED
#define TO this_object()
#define TP this_player()
#define QN query_name()
#define QRN query_real_name()
#define QPR query_pronomen()
#define INV(x) inventory(x)
#define ENV(x) environment(x)
#define C(x) capitalize(x)
#endif SHORT_QUERIES_DEFINED

#ifndef FILES_DEFINED
#include "/sys/files.h"
#endif  FILES_DEFINED

/*
 * MUDLIB_VERSION
 *
 * This is the name of the version of the mudlib.
 */
#define MUDLIB_VERSION ("CD.01.01")

/*
 * CALLED_BY_SECURITY
 *
 * SECURITY holds all functions that have to do with levels, rights etcetera.
 * Use CALLED_BY_SECURITY to see whether a function is called from this
 * master module.
 */
#define CALLED_BY_SECURITY (previous_object() == find_object(SECURITY))

/*
 * ROOT_UID
 * BACKBONE_UID
 *
 * These are the default defined userids.
 */
#define ROOT_UID	"root"
#define BACKBONE_UID	"backbone"

#ifndef CONFIG_DEFINED
#include "/sys/config.h"
#endif  CONFIG_DEFINED

/*
 * CRYPT_METHOD
 *
 * The method used to encrypt long passwords. See 'man crypt'.
 */
#define CRYPT_METHOD        ("$2b$06$")
#define CRYPT_SALT_LENGTH   22

/* No definitions beyond this line. */
#endif SECURE_DEFINED
