/*
 * /sys/living_desc.h
 *
 * Holds all textual descriptions used in /std/living
 *
 * Note that local changes to these are done in
 * /config/sys/living_desc2.h
 */

#ifndef LD_DEFINED
#define LD_DEFINED

#define LD_SAYS 		" says: "
#define LD_UNDERSTANDS(str)     (str)
#define LD_WIZARD 		"wizard"
#define LD_GHOST 		"ghost"
#define LD_SOMEONE		"someone"
#define LD_THE			"the"
#define LD_DARK_LONG		"A dark room.\n"
#define LD_CANT_SEE		"You are lost, you can't see a thing.\n"
#define LD_DARK_ROOM(o)		(o->query_prop(ROOM_I_INSIDE) ? \
    				"A dark room.\n" : "A dark area.\n")

/* Day / Night things */
#define LD_IS_NIGHT(o)		"It's Night.\n" + o->short() + ".\n"

/* longdesc */
#define LD_PRESENT_YOU(o)	"You are " + LANG_ADDART(o->QN) + ", roaming the network in search of information.\n"

#define LD_PRESENT_TO(o)	C(TO->QPR) + " is " + LANG_ADDART(o->QN) + ", roaming the network.\n"

#define LD_MET_GHOST(o)		"It is the " + o->query_name() + "\n"

/* drink_eat.c */
#define LD_NOTICE_HEADACHE	"You notice that you have a terrible headache.\n"

#define LD_SUDDEN_HEADACHE	"You suddenly get a headache, making you feel rather miserable.\n"

#define LD_GONE_HEADACHE	"Your headache seems to be gone.\n"

/* gender.c */
#define LD_GENDER_MAP		([ G_MALE : "male", G_FEMALE : "female",\
				   G_NEUTER : "neuter" ])
#define LD_GENDER_REVERSE_MAP	([ "male" : G_MALE, "female" : G_FEMALE,\
				   "neuter" : G_NEUTER ])

#define LD_PRONOUN_MAP		([ G_MALE:"he",G_FEMALE:"she",G_NEUTER:"it"])
#define LD_POSSESSIVE_MAP	([ G_MALE:"his",G_FEMALE:"her",G_NEUTER:"its"])
#define LD_OBJECTIVE_MAP	([ G_MALE:"him",G_FEMALE:"her",G_NEUTER:"it"])


/* move.c */
#define LD_ALIVE_MSGIN		F_ALIVE_MSGIN
#define LD_ALIVE_MSGOUT		F_ALIVE_MSGOUT
#define LD_ALIVE_TELEIN		F_ALIVE_TELEIN
#define LD_ALIVE_TELEOUT	F_ALIVE_TELEOUT

/*
 * LD_ATTRIB_CATEGORIES  - an array of the player attribute categories.
 * LD_ATTRIBS_BY_CAT(c)  - an array of the attributes with in a category.
 * LD_IS_ATTRIBUTE(a)    - find out if an attribute is a valid attribute.
 * LS_ATTRIB_CATEGORY(a) - find out the category an attribute belongs to.
 */
#ifndef ADVERBS_FILE
#define ADVERBS_FILE "/sys/global/adverbs.c"
#endif

#define LD_ATTRIB_CATEGORIES  ((string *)ADVERBS_FILE->query_attribute_categories())
#define LD_ATTRIBS_BY_CAT(c)  ((string *)ADVERBS_FILE->query_attributes(c))
#define LD_IS_ATTRIBUTE(a)    ((int)ADVERBS_FILE->query_is_attribute(a))
#define LD_ATTRIB_CATEGORY(a) ((string)ADVERBS_FILE->query_attribute_category(a))

/* In login, filter for these prefixes and suffices to issue a warning. */
#ifndef LD_UNWANTED_PREFIX
#define LD_UNWANTED_PREFIX	({ "king*" })
#endif  LD_UNWANTED_PREFIX

/* No definitions beyond this line. */
#endif LD_DEFINED
