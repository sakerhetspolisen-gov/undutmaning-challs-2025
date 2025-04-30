#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/game/master/node";

mapping ports = ([ ]);
/*
    Ports format
        ([
            <port number>: <protocol strng>
                or
            <port number>: ({ ({ <n>,<n>,<n>,<n> }), <remote port> })
        ])
*/
string extra_netmesg;

void init(void)
{
    ::init();
}

public void
create_node()
{

}

void set_extra_msg_netinfo(string str)
{
    extra_netmesg = str;
}

void add_port(int port, mixed arg)
{
    ports += ([ port:arg ]);
}

string query_port_protocol_string(int port)
{
    if(!ports[port])
        return 0;
    if(pointerp(ports[port]))
        return "TCP";
    return ports[port];
}

int query_port_connected(int port)
{
    if(!ports[port])
        return 0;
    if(pointerp(ports[port]))
        return 1;
    return 0;
}

int *query_port_connected_ip(int port)
{
    if(pointerp(ports[port]))
        return (int*)ports[port][0];
    return ({ 0,0,0,0 });
}

int query_port_connected_port(int port)
{
    if(pointerp(ports[port]))
        return ports[port][1];
    return 0;
}

int down_check()
{
    if(TP->always_ok_to_leave())
        return 0;

    /* Lets just ignore missing headers. You can get them elsewere

    object hdr = TP->get_layer_header(3);
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

int block_me()
{
    write(C(get_admin_name()) + " blocks your way upward.\n");
    say(C(get_admin_name()) + " stops " + TP->QN + " from going upward.\n");
    return 1;
}

int up_check(int port)
{
    if(!query_verb())
        return 0;

    if(TP->always_ok_to_leave())
        return 0;

    int port = atoi(query_verb());

    write(C(get_admin_name()) + " examines you carefully.\n");
    say(C(get_admin_name()) + " examines " + TP->QN + " carefully.\n");

    object hdr = TP->get_layer_header(3);
    object ip_hdr = TP->get_layer_header(2);

    string proto = query_port_protocol_string(port);

    if(!hdr)
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you lack the proper identification!\n");
        return block_me();
    }

    if(hdr->query_dst_port() != port || (proto && proto != hdr->query_protocol()))
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, you are not allowed up there!\n");
        return block_me();
    }

    // Make sure the IP header has the correct dst address (loopback ok, but not broadcast)
    if(proto == "TCP" && (!ip_hdr || ip_hdr->query_protocol() != "IP" || 
       (!ip_hdr->check_dst_addr(query_ip()) && !IS_LOOPBACK(ip_hdr->get_field_value(9)))))
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, but you should not be here!\n");
        return block_me();
    }

    if(query_port_connected(port))
    {
        // Established connection. Verify sender ip and port!

        if(!ip_hdr || !ip_hdr->check_src_addr(query_port_connected_ip(port)) || hdr->query_src_port() != query_port_connected_port(port))
        {
            tell_room(TO,C(get_admin_name()) + " says: Sorry, but your information don't seem to match up!\n");
            return block_me();
        }
    }

    if(!hdr->verify_checksum())
    {
        tell_room(TO,C(get_admin_name()) + " says: Sorry, your identification seems to be corrupted somehow!\n");
        return block_me();
    }

    write(C(get_admin_name()) + " lets you pass upward.\n");
    say(C(get_admin_name()) + " lets " + TP->QN + " pass upward.\n");
    return 0;
}

string netinfo(void)
{
    string info = read_file(FILES+"/" + query_hostname() + ".info");
    return extra_netmesg + info;
}