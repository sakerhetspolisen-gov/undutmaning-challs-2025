#ifndef GAME_DEFINES_H
#define GAME_DEFINES_H

#include <std.h>
#include <macros.h>

#define HEADER "/game/master/header.c"

#define OBJ "/game/obj/"
#define NPC "/game/npc/"
#define NODES "/game/nodes/"
#define HEADERS "/game/headers/"
#define FILES "/game/files/"

#define NODE "/game/master/node"
#define LINK "/game/master/link"
#define LAYER1 "/game/master/layer1"
#define LAYER2 "/game/master/layer2"
#define LAYER3 "/game/master/layer3"
#define LAYER4 "/game/master/layer4"

#define ETHERNET "Ethernet"
#define ARP "ARP"
#define ICMP "ICMP"
#define DATA "DATA"
#define IP "IP"
#define TCP "TCP"
#define UDP "UDP"

#define IS_LOOPBACK(x) ((x[0] == 127 && x[1] == 0 && x[2] == 0 && x[3] == 1) ? 1 : 0)

#endif GAME_DEFINES_H