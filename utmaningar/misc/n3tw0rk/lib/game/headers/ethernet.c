#pragma strict_types

#include "/game/master/defs.h"

inherit HEADER;

void create_header(void)
{
    set_protocol(ETHERNET);
    set_layer(1);

    add_field("sfd", 8, 0xAB, "Indicates the start of the ethernet frame.");
    add_field("dst-address", "mac", ({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }), "Ethernet/MAC address of the device to which this frame is sent.");
    add_field("src-address", "mac", ({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }), "Ethernet/MAC address of the device which sent this frame.");
    add_field("len/type", 16, 0x0001, "Ethernet type, or length, of payload."); // 0x0600 > EtherType, < 1500 length
}

int query_broadcast()
{
    if(get_field_value(1)[0] == 0xFF &&
       get_field_value(1)[1] == 0xFF &&
       get_field_value(1)[3] == 0xFF &&
       get_field_value(1)[4] == 0xFF &&
       get_field_value(1)[5] == 0xFF)
       return 1;
        
    return 0;
}

int verify_header(void)
{
    if(get_field_value(0) != 0xAB)
        return 0;

    if(get_field_value(1)[0] == 0 &&
       get_field_value(1)[1] == 0 &&
       get_field_value(1)[2] == 0 &&
       get_field_value(1)[3] == 0 &&
       get_field_value(1)[4] == 0 &&
       get_field_value(1)[5] == 0)
       return 0;

    if(get_field_value(2)[0] == 0 &&
       get_field_value(2)[1] == 0 &&
       get_field_value(2)[2] == 0 &&
       get_field_value(2)[3] == 0 &&
       get_field_value(2)[4] == 0 &&
       get_field_value(2)[5] == 0)
       return 0;

    return 1;
}

void set_dst_address(int *mac)
{
    get_field_value(1)[0] = mac[0];
    get_field_value(1)[1] = mac[1];
    get_field_value(1)[2] = mac[3];
    get_field_value(1)[3] = mac[2];
    get_field_value(1)[4] = mac[3];
    get_field_value(1)[5] = mac[4];
}

void set_src_address(int *mac)
{
    get_field_value(2)[0] = mac[0];
    get_field_value(2)[1] = mac[1];
    get_field_value(2)[2] = mac[3];
    get_field_value(2)[3] = mac[2];
    get_field_value(2)[4] = mac[3];
    get_field_value(2)[5] = mac[4];
}


public string
format_data()
{
    string desc = "";

    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("| 0x%02X | %02X:%02X:%02X:%02X:%02X:%02X | %02X:%02X:%02X:%02X:%02X:%02X | 0x%04X |\n",
                    get_field_value(0),
                    get_field_value(1)[0],get_field_value(1)[1],get_field_value(1)[2],get_field_value(1)[3],get_field_value(1)[4],get_field_value(1)[5],
                    get_field_value(2)[0],get_field_value(2)[1],get_field_value(2)[2],get_field_value(2)[3],get_field_value(2)[4],get_field_value(2)[5],
                    get_field_value(3));
    desc += "+-------------------------------------------------------+";
    
    return desc;
}
