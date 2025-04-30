#pragma strict_types

#include <std.h>
#include <macros.h>
#include "/game/master/defs.h"

inherit "/std/monster";

string *ok_exits = ({ });

int react_alarm = 0;

int num_inspected_packets = 0;
object *inspected_packets = ({ });

int *network_address   = ({ 0,0,0,0 });
int *network_mask      = ({ 0,0,0,0 });
int *network_broadcast = ({ 0,0,0,0 });

void calculate_broadcast_address(void)
{
    for(int i = 0 ; i < 4 ; i++)
    {
        network_broadcast[i] = network_address[i] | (~network_mask[i] & 255);
    }
}

void set_network(int *ip,int *mask)
{
    network_address[0] = ip[0];
    network_address[1] = ip[1];
    network_address[2] = ip[2];
    network_address[3] = ip[3];

    network_mask[0] = mask[0];
    network_mask[1] = mask[1];
    network_mask[2] = mask[2];
    network_mask[3] = mask[3];

    calculate_broadcast_address();
}

int verify_valid_packet(object who)
{
    // All addresses should be valid
    // Broadcast addressess should add up
    // All ports should be valid
    // All checksums should be correct

    int mac_is_BC = 0;

    object hdr = who->get_layer_header(1);

    if(!hdr->verify_header())
        return 0;

    switch(hdr->query_protocol())
    {
        case ETHERNET:
            mac_is_BC = hdr->query_broadcast();

            break;
        default:
            return 0;
    }

    hdr = who->get_layer_header(2);

    if(!hdr->verify_header())
        return 0;

    switch(hdr->query_protocol())
    {
        case IP:
            // Either dst or src IP should be on the correct network
            if(!hdr->check_src_addr(network_address,network_mask) && !hdr->check_dst_addr(network_address,network_mask))
                return 0;

            // If MAC is broadcast so should dst IP be broadcast too (can be valid in other cases too really, but nah!)
            if(mac_is_BC && !hdr->check_dst_addr(network_broadcast))
                return 0;

            break;

        default:
            return 0;
    }

    hdr = who->get_layer_header(3);

    if(!hdr->verify_header())
        return 0;

    switch(hdr->query_protocol())
    {
        case TCP:
            break;

        case UDP:
            break;

        default:
            return 0;
    }


    return 1;
}


int check_uninspected(object who)
{
    if(member_array(who,inspected_packets) < 0)
        return 1;
    return 0;
}

void add_inspected(object who)
{
    if(num_inspected_packets > 8)
    {
        num_inspected_packets--;
        inspected_packets -= ({ inspected_packets[0] });
    }

    inspected_packets += ({ who });
    num_inspected_packets++;
}

void prune_inspected_packets(void)
{
    if(num_inspected_packets > 0)
    {
        num_inspected_packets--;
        inspected_packets -= ({ inspected_packets[0] });
    }
}

string *filter_exits(string *exits)
{
    if(!exits || !sizeof(exits))
        return ({ });

    string *res_exits = ({ });
    for (int i = 0; i < sizeof(exits); i += 3)
    {
        if(sizeof(ok_exits) && member_array(exits[i + 1],ok_exits) < 0)
        {
            continue;
        }
        else
        {
            res_exits += ({ exits[i + 1] });
        }
    }
    return res_exits;
}

string get_walk_exit()
{
    mixed *exits;

    if (!ENV(TO))
        return 0;

    exits = filter_exits(ENV(TO)->query_exit());

    if (!sizeof(exits))
    {
        return 0;
    }

    return exits[random(sizeof(exits))];
}

void set_ok_exits(string *exits)
{
    ok_exits = exits;
}

int always_ok_to_leave()
{
    return 1;
}

int is_player(object ob)
{
    return ob->is_player_object();
}

string inspect_and_move(void)
{
    if(random(4))
    {
        // Inspect a packet
        object *present_players = filter(all_inventory(ENV(TO)),is_player);
        present_players = filter(present_players,check_uninspected);

        if(!sizeof(present_players))
            return get_walk_exit(); // No unchecked players, move to different room

        object target = present_players[random(sizeof(present_players))];

        if(!react_alarm)
        {
            tell_room(ENV(TO),"The security officer studies "+target->QN+" very carefully.\n",target);
            target->catch_msg("The security officer studies you very carefully.\n");

            react_alarm = set_alarm(0.1 + rnd(), 0.0, "inspect_player",target);

            return "narrow though";
        }
        else
        {
            return "confused";
        }
    }
    else
        return get_walk_exit();
}

void inspect_player(object target)
{
    remove_alarm(react_alarm);
    react_alarm = 0;

    if(!present(target,ENV(TO)))
    {
        tell_room(ENV(TO),"The security officers says: Now where did that suspicios packet run of to!?\n");
        return;
    }

    add_inspected(target);

    if(verify_valid_packet(target))
    {
        tell_room(ENV(TO),"The security officers says: Everything seems to be in order. Carry on!\n");
        return;       
    }

    tell_room(ENV(TO),"The security officers snarls: You carry invalid information, packet!\nYou are obviously tresspassing!\n");
    tell_room(ENV(TO),"The security officers zaps " + target->QN + "!\n",target);
    target->catch_tell("The security officers zaps you!\n");
    target->terminate_me(0);
}

void create_ips_packet(void)
{
    set_name("security officer");
    add_name("IPS packet");
    add_name("packet");
    add_name("officer");
    set_short("A security officer on the prowl");
    set_long(BSN("A formidable figure clad in a uniform of dark authority, with the emblem \"IPS\" emblazoned across its chest. "+
        "Its piercing, unblinking eyes scan every packet with an air of cold scrutiny. The inspector's posture is rigid, and "+
        "its stance seems to radiate a sense of unease to any packet that crosses its path. There's a palpable tension in the air, "+
        "as if the very presence of this inspector sets the stage for a rigorous examination, with every packet bracing for the "+
        "potential wrath of a meticulous and unforgiving judgment."));

    set_chat_time(5);

    add_chat("Have you seen any suspicious packets in the area?");   
    add_chat("Any packet that's not up to snuff better watch out.");  
    add_chat("If you're not compliant, you might just find yourself in trouble.");  
    add_chat("It's a tough job, but someone's got to ensure the rules are followed.");
    add_chat("I'm here to keep things in line — no funny business!");   
    add_chat("If your headers aren't up to code, expect a stern review.");  
    add_chat("Every detail counts in this inspection — I won't let anything slip by.");  
    add_chat("Stand by and keep your headers in order. A keen eye is watching!");

    set_chat_time(5);

    set_act_time(2);
    add_act("@@inspect_and_move");
}

void create_monster()
{
    ::create_monster();
    create_ips_packet();    
}

