/*
 * /secure/master/player.c
 *
 * This file is a sub-part of SECURITY related to player matters, most notably
 * registration of seconds and characters marked for deletion due to
 * inappropriate names.
 */

#include "/sys/log.h"

#define PREDEATH_CLEANUP 31536000 /* one year */
#define BAD_NAME_CLEANUP  1209600 /* two weeks */
#define NEW_CHAR_CLEANUP  1209600 /* two weeks */
#define NEW_CHAR_MINAGE      3600 /* two hours in heartbeats */

/* Indices to the m_seconds mapping. */
#define SNDS_REPORTER 0
#define SNDS_TIME     1

