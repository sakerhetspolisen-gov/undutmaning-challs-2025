#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/room";

object admin;
string hostname;
int *mac = ({ 0, 0, 0, 0, 0, 0 });
// 5:th digit is broadcast address
int *ip = ({ 0, 0, 0, 0, 255 });

public void
create_node()
{

}

nomask void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    create_node();
}

void set_hostname(string name)
{
    hostname = name;
}

string query_hostname(void)
{
    return hostname ? hostname : "unknown";
}

void set_admin(object ob)
{
    admin = ob;
}

object get_admin(void)
{
    return admin;
}

void create_admin(string path)
{
    object ob = clone_object(path);
    ob->move(TO,1);
    set_admin(ob);
}

string get_admin_name(void)
{
    if(!objectp(admin))
    {
        return "A stern clerk";
    }
    return LANG_ADDART(admin->QN);
}

void set_mac(int *m)
{
    mac[0] = m[0];
    mac[1] = m[1];
    mac[2] = m[2];
    mac[3] = m[3];
    mac[4] = m[4];
    mac[5] = m[5];
}

int compare_mac(int *m,int *m_ok,int broadcastOK = 1)
{
    if(m[0] == m_ok[0] && 
       m[1] == m_ok[1] && 
       m[2] == m_ok[2] && 
       m[3] == m_ok[3] && 
       m[4] == m_ok[4] && 
       m[5] == m_ok[5]) 
    {
        return 1;
    }

    if(broadcastOK &&
       m[0] == 0xFF && 
       m[1] == 0xFF && 
       m[2] == 0xFF && 
       m[3] == 0xFF && 
       m[4] == 0xFF && 
       m[5] == 0xFF) 
    {
        return 1;
    }

    return 0;
}

int check_mac(int *m,int broadcastOK = 1)
{
    return compare_mac(m, mac, broadcastOK);
}

int *query_mac(void)
{
    return mac;
}

void set_ip(int *addr)
{
    ip[0] = addr[0];
    ip[1] = addr[1];
    ip[2] = addr[2];
    ip[3] = addr[3];
    if(sizeof(addr) > 4) // Broadcast address
    ip[4] = addr[4];
}

int check_ip(int *addr,int broadcastOK = 1)
{
    if(addr[0] == ip[0] && 
       addr[1] == ip[1] && 
       addr[2] == ip[2] && 
       addr[3] == ip[3]) 
    {
        return 1;
    }

    // Also allow broadcast address
    if(broadcastOK &&
       addr[0] == ip[0] && 
       addr[1] == ip[1] && 
       addr[2] == ip[2] && 
       addr[3] == ip[4]) 
    {
        return 1;
    }

    // Also allow loopback address
    if(addr[0] == 127 && 
       addr[1] == 0 && 
       addr[2] == 0 && 
       addr[3] == 1) 
    {
        return 1;
    }

    return 0;
}

int *query_ip(void)
{
    return ip;
}
