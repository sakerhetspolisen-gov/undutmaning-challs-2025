#pragma strict_types

#include "/game/master/defs.h"

inherit HEADER;

void create_header(void)
{
    set_protocol(UDP);
    set_layer(3);

    add_field("src", 16, 0x0000, "Destination port number.");
    add_field("dst", 16, 0x0000, "Source port number.");
    add_field("len", 16, 0x0000, "Length of packet (header and data).");
    add_field("chks", 16, 0x0000, "Checksum of header and data.");
}

string format_data(void)
{
    string desc = "";

    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|    0x%04X   |    0x%04X   |    0x%04X   |    0x%04X   |\n",
        get_field_value(0),get_field_value(1),get_field_value(2),get_field_value(3));
    desc += "+-------------------------------------------------------+";
    
    return desc;
}

int query_dst_port(void)
{
    return (int)get_field_value_by_name("dst");
}

int query_src_port(void)
{
    return (int)get_field_value_by_name("src");
}

int calculate_checksum() 
{
    int *binary_header = ({ });
    int *pseudo_header = ({ });
    int udp_length = 0;

    object ip_hdr = ENV(TO)->get_layer_header(2);
    int *data = ENV(TO)->serialize_data(4);

    if(!ip_hdr || ip_hdr->query_protocol() != IP)
        return -1;

    // Construct the pseudo-header
    pseudo_header += ip_hdr->get_field_value_by_name("src"); // Source IP (4 bytes)
    pseudo_header += ip_hdr->get_field_value_by_name("dst"); // Destination IP (4 bytes)
    pseudo_header += ({ 0x00 });                       // Zero byte (1 byte)
    pseudo_header += ({ 0x11 });                       // Protocol (UDP = 17) (1 byte)

    // Calculate the UDP length (header + data)
    for (int i = 0 ; i < get_num_fields() ; i++) 
    {
        if(intp(get_field_type(i)))
            udp_length += get_field_type(i) / 8;     // Sum the size of each field in bytes
    }
    udp_length += sizeof(data);                        // Add data length

    pseudo_header += ({ (udp_length >> 8) & 0xFF, udp_length & 0xFF });  // UDP Length (2 bytes)

    // Convert the UDP header fields to binary representation
    for (int i = 0 ; i < get_num_fields() ; i++) 
    {
        string field_name = get_field_name(i);
        mixed field_size_or_type = get_field_type(i);
        mixed field_value = get_field_value(i);

        // Convert the field to binary
        if (intp(field_size_or_type)) 
        {
            int field_size = field_size_or_type;
            
            if (field_name == "chks") 
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
    }

    // Calculate the full checksum (pseudo-header + UDP header + data)
    return hlpr_calculate_checksum(pseudo_header + binary_header + data);
}

int update_checksum(void)
{
    int chks = calculate_checksum();
    // Set the checksum field in the original header
    if(chks < 0)
        return 0;

    if(chks == 0)
        set_field_value(3, 0xFFFF); // If checksum is 0 it should be set to 0xFFFF instead
    else
        set_field_value(3, chks);
    return 1;
}

int verify_checksum(void)
{
    int curr_chks = get_field_value(3);
    
    // UDP checksum is optional. If it is 0, it is not used.
    if(curr_chks == 0)
        return 1;

    int chks = calculate_checksum();
    
    // If checksum is 0 match it agains 0xFFFF instead
    if(curr_chks == 0xFFFF)
        return (chks == 0);

    return (get_field_value(3) == chks);
}
