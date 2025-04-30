#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/node";

void init(void)
{
    ::init();
}

public void
create_node()
{
}

int block_me()
{
    write(C(get_admin_name()) + " blocks your way upward.\n");
    say(C(get_admin_name()) + " stops " + TP->QN + " from going upward.\n");
    return 1;
}

int up_check()
{
    write(C(get_admin_name()) + " examines you carefully.\n");
    say(C(get_admin_name()) + " examines " + TP->QN + " carefully.\n");

    if(TP->always_ok_to_leave())
    {   
        write(C(get_admin_name()) + " lets you pass upward.\n");
        say(C(get_admin_name()) + " lets " + TP->QN + " pass upward.\n");
        return 0;
    }

    object hdr = TP->get_layer_header(2);

    if(!hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me();
    }

    if(!check_ip(hdr->get_field_value(9)))
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you are not allowed up there!\n");
        return block_me();
    }

    if(!hdr->verify_checksum())
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, your identification does not seems to be in order!\n");
        return block_me();
    }

    write(C(get_admin_name()) + " lets you pass upward.\n");
    say(C(get_admin_name()) + " lets " + TP->QN + " pass upward.\n");
    return 0;
}

int down_check()
{
    if(TP->always_ok_to_leave())
        return 0;
    
    /* Lets just ingore missing headers. You can get them elsewere

    object hdr = TP->get_layer_header(2);
    if(!hdr)
    {
        write(C(get_admin_name()) + " looks you over and stops you from moving downwards.\n");
        say(C(get_admin_name()) + " looks at " + LANG_ADDART(TP->QN) + " and stops it from "+
            "leaving downwards.\n");
        tell_room(TO,BSN(C(get_admin_name()) + " says: Sorry, but I can't let you leave without "+
                  "carrying the right identification. You'll need the right headers out there!"));
        return 1;
    }
    */
    
    return 0;
}