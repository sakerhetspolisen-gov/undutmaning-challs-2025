#pragma strict_types

#include "/game/master/defs.h"

inherit HEADER;

void create_header(void)
{
    set_protocol(ICMP);
    set_layer(3); // Not actually true, but for purpouse of simplicity

    add_field("type", 8, 0x00, "ICMP type code.");
    add_field("code", 8, 0x00, "ICMP subtype code.");
    add_field("chks", 16, 0x0000, "Checksum for error checking.");
    add_field("rest", 32, 0x00000000, "Multi-purpose field, content varies depending on type and code.");
}

public string
format_data()
{
    string desc = "";

    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|    0x%02X    |    0x%02X    |    0x%04X    |  0x%08X  |\n",
        get_field_value(0),get_field_value(1),get_field_value(2),get_field_value(3));
    desc += "+-------------------------------------------------------+";
    
    return desc;
}

int calculate_checksum() 
{
    int *binary_header = ({ });

    // Convert the ICMP header fields to binary representation
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

    // Calculate the checksum
    return hlpr_calculate_checksum(binary_header + ENV(TO)->serialize_data(query_layer() + 1));
}

int update_checksum(void)
{
    int chks = calculate_checksum();
    // Set the checksum field in the original header
    if(chks < 0)
        return 0;

    set_field_value(2, chks);
    return 1;
}

int verify_checksum(void)
{
    int chks = calculate_checksum();
    return (get_field_value(2) == chks);
}
