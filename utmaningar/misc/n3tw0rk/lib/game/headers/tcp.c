#pragma strict_types

#include "/game/master/defs.h"

inherit HEADER;

void create_header(void)
{
    set_protocol(TCP);
    set_layer(3);

    add_field("src", 16, 0x0000, "Source port number.");
    add_field("dst", 16, 0x0000, "Destination port number.");
    add_field("seq", 32, 0x00000000, "Sequence number.");
    add_field("ack", 32, 0x00000000, "Acknowledge number.");
    add_field("hdr-len", 4, 0x5, "Length of the TCP header, in 32-bit words.");
    add_field("flag", 12, 0x00000, "Various flags.");
    add_field("win", 16, 0x0000, "Size of the receive window.");
    add_field("chks", 16, 0x0000, "Checksum of the packet (IP header, TCP header and data).");
    add_field("urg", 16, 0x0000, "Urgent data offset from sequence number. Valid if the urgent flag is set.");
}

public string
format_data()
{
    string desc = "";

    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|   0x%04X   |   0x%04X   |  0x%08X  |  0x%08X  |\n",
        get_field_value(0),get_field_value(1),get_field_value(2),get_field_value(3));
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|   0x%1X  |   0x%03X  |   0x%04X  |   0x%04X  |   0x%04X  |\n",
        get_field_value(4),get_field_value(5),get_field_value(6),get_field_value(7),get_field_value(8));
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

int calculate_checksum(void) 
{
    int *binary_header = ({ });
    int *pseudo_header = ({ });
    int tcp_length = 0;

    object ip_hdr = ENV(TO)->get_layer_header(2);
    int *data = ENV(TO)->serialize_data(4);

    if(!ip_hdr || ip_hdr->query_protocol() != IP)
        return -1;

    // Construct the pseudo-header
    pseudo_header += ip_hdr->get_field_value_by_name("src"); // Source IP (4 bytes)
    pseudo_header += ip_hdr->get_field_value_by_name("dst"); // Destination IP (4 bytes)
    pseudo_header += ({ 0x00 });                       // Zero byte (1 byte)
    pseudo_header += ({ 0x06 });                       // Protocol (TCP = 6) (1 byte)

    // Calculate the TCP length (header + data)
    for(int i = 0 ; i < get_num_fields() ; i++) 
    {
        if(intp(get_field_type(i)))
            tcp_length += get_field_type(i) / 8;     // Sum the size of each field in bytes
    }
    tcp_length += sizeof(data);                        // Add data length

    pseudo_header += ({ (tcp_length >> 8) & 0xFF, tcp_length & 0xFF });  // TCP Length (2 bytes)

    // Convert the TCP header fields to binary representation
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

    // Calculate the full checksum (pseudo-header + TCP header + data)
    return hlpr_calculate_checksum(pseudo_header + binary_header + data);
}

int update_checksum(void)
{
    int chks = calculate_checksum();
    // Set the checksum field in the original header
    if(chks < 0)
        return 0;

    set_field_value(7, chks);
    return 1;
}

int verify_checksum(void)
{
    int chks = calculate_checksum();
    return (get_field_value(7) == chks);
}
