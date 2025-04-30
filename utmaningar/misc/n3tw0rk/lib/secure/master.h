/*
 * /secure/master.h
 *
 * This file includes the prototypes for the master. Since the master has
 * been split in several files, some prototypes are necessary to allow
 * the functions to access functions in other parts that are included after
 * the calling module.
 */

/*
 * /secure/master.c
 */
static void reset_master();
varargs mixed do_debug(string icmd, mixed a1, mixed a2, mixed a3);
public void check_memory(int dodecay);
int valid_read(string file, mixed reader, string func);
int valid_write(string file, mixed writer, string func);
public int query_start_time();
