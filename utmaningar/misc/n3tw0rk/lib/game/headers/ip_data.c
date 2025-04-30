#pragma strict_types

#include "/game/master/defs.h"
#include <std.h>

inherit HEADER;

void create_header(void)
{
    set_protocol(IP,1);
    set_layer(5);

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
    add_field("data", "data", ({ 0,0,0,0,0,0,0,0 }), "First 8 bytes of the original IP packet.");
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
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|       0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X         |\n",
        get_field_value(10)[0],get_field_value(10)[1],get_field_value(10)[2],get_field_value(10)[3],
        get_field_value(10)[4],get_field_value(10)[5],get_field_value(10)[6],get_field_value(10)[7]);
    desc += "+-------------------------------------------------------+";
    
    return desc;
}
