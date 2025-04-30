#pragma strict_types

#include "/game/master/defs.h"
#include <std.h>

inherit HEADER;

void create_header(void)
{
    set_protocol(IP);
    set_layer(2);

    add_field("version", 2, 0x4, "Version of the IP protocol.");
    add_field("tot-len", 16, 0x0004, "Total length of header and data.");
    add_field("id", 16, 0x0004, "Identification for fragmented datagrams.");
    add_field("flags", 3, 0x2, "Flags used to identify or control fragments.");
    add_field("offs", 13, 0x0000, "Fragment offset relative to beginning of first fragment.");
    add_field("ttl", 8, 0xFF, "Number of hops left before expiering.");
    add_field("protocol", 8, 0x04, "Protocol used in the data portion of the IP datagram.");
    add_field("checksum", 16, 0x0000, "Checksum to verify header.");
    add_field("src", "ip", ({ 0, 0, 0, 0 }), "Address of the device that sent this packet.");
    add_field("dst", "ip", ({ 0, 0, 0, 0 }), "Address of the decive to which the packet is being sent.");
}

void decrease_ttl(void)
{
    signal_change();
    fields[5][2] = fields[5][2] - 1;
    if(fields[5][2] == 0)
    {
        ENV(TO)->catch_tell("Your time to live is all used up!\n");
        ENV(TO)->terminate_me();
        return;
    }
    update_checksum();
}

int check_dst_addr(int *ip,int *mask = ({255,255,255,255}))
{
    if((get_field_value(9)[0] & mask[0]) == (ip[0] & mask[0]) &&
       (get_field_value(9)[1] & mask[1]) == (ip[1] & mask[1]) &&
       (get_field_value(9)[2] & mask[2]) == (ip[2] & mask[2]) &&
       (get_field_value(9)[3] & mask[3]) == (ip[3] & mask[3]))
       return 1;
    return 0;
}

int check_src_addr(int *ip,int *mask = ({255,255,255,255}))
{
    if((get_field_value(8)[0] & mask[0]) == (ip[0] & mask[0]) &&
       (get_field_value(8)[1] & mask[1]) == (ip[1] & mask[1]) &&
       (get_field_value(8)[2] & mask[2]) == (ip[2] & mask[2]) &&
       (get_field_value(8)[3] & mask[3]) == (ip[3] & mask[3]))
       return 1;
    return 0;
}

void set_dst_addr(int *ip)
{
    get_field_value(9)[0] = ip[0];
    get_field_value(9)[1] = ip[1];
    get_field_value(9)[2] = ip[2];
    get_field_value(9)[3] = ip[3];
}

void set_src_addr(int *ip)
{
    get_field_value(8)[0] = ip[0];
    get_field_value(8)[1] = ip[1];
    get_field_value(8)[2] = ip[2];
    get_field_value(8)[3] = ip[3];
}

public string
format_data()
{
    string desc = "";

    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|  0x%1X  | 0x%04X | 0x%04X |  0x%1X  |  0x%04X  |   0x%02X   |\n",
        get_field_value(0),get_field_value(1),get_field_value(2),get_field_value(3),get_field_value(4),get_field_value(5));
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|  0x%02X  | 0x%04X | %16|s | %16|s |\n",
        get_field_value(6),get_field_value(7),
        sprintf("%d.%d.%d.%d",get_field_value(8)[0],get_field_value(8)[1],get_field_value(8)[2],get_field_value(8)[3]),
        sprintf("%d.%d.%d.%d",get_field_value(9)[0],get_field_value(9)[1],get_field_value(9)[2],get_field_value(9)[3]));
    desc += "+-------------------------------------------------------+";
    
    return desc;
}

int calculate_checksum(void)
{
    int *binary_header = ({ });

    // Construct the binary representation of the header
    for(int i = 0 ; i < get_num_fields() ; i++) 
    {
        string field_name = get_field_name(i);
        mixed field_size_or_type = get_field_type(i);
        mixed field_value = get_field_value(i);

        // Convert the field to binary
        if (intp(field_size_or_type)) 
        {
            int field_size = field_size_or_type;
            
            if (field_name == "checksum") 
            {
                binary_header += ({ 0x00, 0x00 });  // Set checksum to zero for calculation
            } 
            else if (field_size > 8) 
            {
                // Handle splitting values larger than 8 bits
                for (int j = field_size - 8; j >= 0; j -= 8) 
                {
                    binary_header += ({ (field_value >> j) & 0xFF });            
                }
            } 
            else 
            {
                // Handle fields 8 bits or smaller
                binary_header += ({ field_value & 0xFF });
            }
        }
        else if (stringp(field_size_or_type) && field_size_or_type == "ip") 
        {
            binary_header += field_value;
        }
    }
    
    // Calculate the checksum
    return hlpr_calculate_checksum(binary_header);
}

int update_checksum(void)
{
    int chks = calculate_checksum();

    if(chks < 0)
        return 0;

    // Set the checksum field in the original header
    set_field_value(7, chks);
    return 1;
}

int verify_checksum(void)
{
    int chks = calculate_checksum();
    return (get_field_value(7) == chks);
}