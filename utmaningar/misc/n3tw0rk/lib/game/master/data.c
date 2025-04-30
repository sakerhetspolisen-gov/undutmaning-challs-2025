/* 
 * This is a standard header object to inherit for other headers.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include "/game/master/defs.h"
#include <std.h>
#include <language.h>
#include <stdproperties.h>

/*
 * Global variable. 
 */
static mixed data;

void set_data(mixed d)
{
    data = d;
}

string format_data(void)
{
    if(!data)
        return "";
    if(stringp(data))
        return data;
    if(objectp(data))
    {
        string str = data->format_data();
        return (strlen(str) ? str : "");
    }
    if(intp(data))
    {
        string desc = "+------------+\n"
        desc += sprintf("| %10|s |\n",sprintf("0x%02X",data));
        desc += "+------------+"
        return desc;
    }
    return "";
}

void init(void)
{
    ::init();
    add_action("do_manipulate","manipulate");
    add_action("do_copy","copy");
    add_action("do_delete","delete");
}

int do_manipulate(string str)
{
    return 0;
}

int do_copy(string str)
{
    return 0;
}

int do_delete(string str)
{
    return 0;
}

void destruct_data(void)
{
    destruct();
    return;
}

void
create_object()
{
    set_name("data");
    set_pname("data");
    set_short("some data");
    set_long("A blob of data.");

    add_prop(OBJ_M_NO_GIVE,1);
}

public string
long()
{
    string str = format_data();
    return ::long() + "\n" + (strlen(str) ? str +  "\n" : "");
}

