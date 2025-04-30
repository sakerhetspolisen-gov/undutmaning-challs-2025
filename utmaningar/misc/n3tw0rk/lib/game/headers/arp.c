#pragma strict_types

#include "/game/master/defs.h"

inherit HEADER;

void create_header(void)
{
    set_protocol(ARP);
    set_layer(2);

    add_field("hw-type", 16, 0x0001, "Hardware address type.");
    add_field("proto-type", 16, 0x0800, "Type of the protocol address to be mapped.");
    add_field("hw-addr-len", 8, 0x06, "Length, in bytes, of the hardware address.");
    add_field("proto-addr-len", 8, 0x04, "Length, in bytes, of the protocol address.");
    add_field("op-type", 16, 0x0001, "Operation code, which describes the type of message.");
    add_field("src-mac", "mac", ({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }), "Hardware address of the device sending the message.");
    add_field("src-ip", "ip", ({ 0x00, 0x00, 0x00, 0x00 }), "Protocol address of the device sending the message.");
    add_field("dst-mac", "mac", ({ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }), "Hardware address of the device to which the message is being sent.");
    add_field("dst-ip", "ip", ({ 0x00, 0x00, 0x00, 0x00 }), "Protocol address of the device to which the message is being sent.");
}

string
format_data()
{
    string desc = "";
    
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|  0x%04X  |  0x%04X  |   0x%02X   |   0x%02X   |   0x%04X  |\n",
        get_field_value(0),get_field_value(1),get_field_value(2),get_field_value(3),get_field_value(4));
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|       %02X:%02X:%02X:%02X:%02X:%02X       |   %18|s  |\n",
        get_field_value(5)[0],get_field_value(5)[1],get_field_value(5)[2],get_field_value(5)[3],get_field_value(5)[4],get_field_value(5)[5],
        sprintf("%d.%d.%d.%d",get_field_value(6)[0],get_field_value(6)[1],get_field_value(6)[2],get_field_value(6)[3]));
    desc += "+-------------------------------------------------------+\n";
    desc += sprintf("|       %02X:%02X:%02X:%02X:%02X:%02X       |   %18|s  |\n",
        get_field_value(7)[0],get_field_value(7)[1],get_field_value(7)[2],get_field_value(7)[3],get_field_value(7)[4],get_field_value(7)[5],
        sprintf("%d.%d.%d.%d",get_field_value(8)[0],get_field_value(8)[1],get_field_value(8)[2],get_field_value(8)[3]));
    desc += "+-------------------------------------------------------+";

    return desc;
}