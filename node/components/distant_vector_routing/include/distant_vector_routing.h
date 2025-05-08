#pragma once

#include "stdint.h"

#define MAX_HOP 10
#define CLIENT_ADDR_TABLE_SIZE 15
#define TIMEOUT_TABLE_SIZE 50


typedef struct __attribute__((packed))
{
    uint8_t ip_addr;
    int socket;

} client_addr_t;

typedef struct __attribute__((packed))
{
    uint8_t index;
    uint8_t size;
    client_addr_t table[CLIENT_ADDR_TABLE_SIZE];
} client_addr_table_t;

typedef struct __attribute__((packed))
{
    uint8_t destination_network;
    uint8_t next_hop;
    uint8_t hop_count;

} dv_element_t;

typedef struct __attribute__((packed)) 
{
    uint8_t index;
    uint8_t network_addr;
    
    dv_element_t table[MAX_HOP];

} dv_routing_table_t;

typedef struct __attribute__ ((packed))
{
    uint8_t packet_type;
    uint8_t source_addr;
    uint8_t table_size;
    dv_element_t table[MAX_HOP]; //this payload covers routing table

} dv_update_packet_t;


typedef struct __attribute__((packed))
{

    uint8_t packet_type;
    uint8_t source_addr;

} dv_alive_packet_t;

typedef struct __attribute__ ((packed))
{
    uint8_t network_addr;
    uint8_t timeout;

}dv_timeout_table_element_t;


typedef struct __attribute__((packed))
{

    uint8_t size;
    dv_timeout_table_element_t table[TIMEOUT_TABLE_SIZE];

} dv_timeout_table_t;


/*
* Initialize client addres table
* @param length of the table
* @return returns allocated client_addr_t pointer
*/

/*
* Initialize routing table
* @param length of the table
* @return returns allocated dv_element_t pointer
*/



//
// 1. When a Wi-Fi client joins your ESP32 AP, learn a “zero‐cost” route to it
//
void on_client_join(uint8_t client_ip, int sock_fd);

//
// 2. Periodically flood your Distance-Vector table out over LoRa
//
dv_routing_table_t get_dv_routing_table(void);

//
// 3. When a DV packet arrives over LoRa, merge it into your local routing table
//
void handle_dv_update(const dv_update_packet_t*);

//
// 4. Look up the next-hop for a given destination IP
//
uint8_t lookup_route(uint8_t destination_network);


void handle_alive_request(dv_alive_packet_t);

int increase_timeout_table(void);

void init_dv_routing(uint8_t network_addr);

