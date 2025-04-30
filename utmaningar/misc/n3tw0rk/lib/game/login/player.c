#pragma strict_types
#pragma save_binary

inherit "/std/player";

#include <std.h>
#include <macros.h>
#include "/sys/const.h"
#include "/game/login/login.h"

mixed data;

object get_layer_header(int layer);

int is_player_object(void)
{
    return 1;
}

string format_data(void)
{
    if(get_layer_header(5))
    {
        // If we carry data as an object. Do not show it here...
        return "";
    }

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
        string desc = "+------------+\n";
        desc += sprintf("| %10|s |\n",sprintf("0x%02X",data));
        desc += "+------------+";
        return desc;
    }
    return "";
}

mixed query_data(void)
{
    object ob = get_layer_header(5);

    return (ob ? ob : data);
}

// Returns all data from the given layer and "up" as an array of bytes
// If no layer is given we only return the actual data
int *serialize_data(int layer = 0)
{
    int *binary_data = ({ });
    if(layer)
    {
        for (int i = layer ; i <= 4 ; i++)
        {
            object hdr = get_layer_header(i);
            if(hdr)
                binary_data += hdr->serialize_header();
        }
    }

    mixed tmp = query_data();

    if(tmp)
    {
        if(stringp(tmp))
        {
            for (int i = 0 ; i < strlen(tmp); i++) 
            {
                binary_data += ({ atoi(tmp[i]) & 0xFF });
            }
        }
        if(objectp(tmp))
        {
            binary_data += tmp->serialize_header();
        }
        if(intp(tmp))
        {   
            binary_data += ({ tmp });
        }
    }

    return binary_data;
}

void set_data(mixed d)
{
    if(objectp(data))
        data->destroy();
    data = d;
}

void terminate_me(int silent)
{
    if(!silent && environment(this_object()))
    {
        TO->catch_tell("You fizzle out of existance. Better luck next time!\n");
        tell_room(environment(),TO->QN + " fizzles out of existance!\n", ({ TO }), TO);
    }
    if(objectp(data))
        data->destroy();
    destruct();
}

public nomask void
enter_new_player(int d)
{
    if(!interactive(this_object()))
    {
        write("None interactive player, destroying!\n");
        remove_object();
        return;
    }

    set_login_from();
    set_default_start_location(DEFAULT_START_LOCATION);

    DEFAULT_START_LOCATION->add_packet();

    TO->save_vars_init();
    TO->save_vars_sec_init();

    data = d; 
    enter_game("byte of data");
}

object get_layer_header(int layer)
{
    foreach(object ob: all_inventory())
    {
        if(ob->query_layer() == layer)
            return ob;
    }
    return 0;
}

int sort_headers(object h1, object h2)
{
    if(h1->query_layer() < h2->query_layer()) return -1;
    if(h1->query_layer() > h2->query_layer()) return 1;
    return 0;
}

string show_subloc_data(object on, object for_obj)
{
    // Format the data contained
    string res = "";
    object *headers = sort_array(all_inventory(),sort_headers); 

    foreach(object ob: headers)
    {
        string header;
        if((header = ob->format_data()) != 0)
            res += header + "\n";
    }

    string str = format_data();
    res += (strlen(str) ? str + "\n" : "");

    return res;
}

string query_protocol(void)
{
    object *headers = sort_array(all_inventory(),sort_headers); 

    if(!sizeof(headers))
        return 0;
    
    int i = sizeof(headers) - 1;
    while(headers[i]->query_layer() > 4)
    {
        i--;
        if(i < 0)
            return 0;
    }

    return headers[i]->query_protocol();  
}

mixed query_long()
{
    string p = query_protocol(); 

    if(!p)
        return "A measly byte of data, roaming the network.\n";

    return C(LANG_ADDART(p)) + " packet, roaming the network.\n";  
}

string query_name()
{
    string p = query_protocol(); 

    if(!p)
        return "Byte of data";

    return C(p) + " packet";  
}

string short(void)
{
    return query_name() + " roaming the network";
}

int get_header_layer(object ob)
{
    return ob->query_layer();
}

int prevent_enter(object ob)
{
    if(!ob->query_layer())
        return 0;

    int *layers = map(all_inventory(),get_header_layer);

    if(!sizeof(layers) || member_array(ob->query_layer(),layers) < 0)
        return 0;
    
    write("You already carry a header of the same layer.\n");
    return 1;
}

public void start_player()
{
    add_name("packet");
    add_name("byte");
    add_name("data");
    set_gender(G_NEUTER);
    TO->add_cmdsoul("/cmd/live/info");
    TO->add_cmdsoul("/cmd/live/social");
    // TO->add_cmdsoul("/cmd/live/speech"); // - No talking! 
    TO->add_cmdsoul("/cmd/live/state");
    TO->add_cmdsoul("/cmd/live/things");
    ::start_player();
}
