#include <stdio.h>
#include "eunjung_packets.h"
#include "distant_vector_routing.h"
#include "esp_log.h"
#include "esp_mac.h"


/*
    TODO:
    
    - crate node leaving/joinig broadcast algorithm
    - write test for dv routing
    - start to implement tcp server

*/


static const char *TAG = "DV-Routing";

static dv_routing_table_t routing_table;
static client_addr_table_t client_addr_table;
static dv_timeout_table_t timeout_table;



/*
    static function definitions
*/

static int insert_hop(dv_element_t);


/*
    end of static function definitions
*/


void init_dv_routing(uint8_t network_addr)
{
    routing_table.network_addr = network_addr;
    routing_table.index = 0;
    routing_table.table[routing_table.index].destination_network = network_addr;
    routing_table.table[routing_table.index].next_hop = 0;
    routing_table.table[routing_table.index].hop_count= 0;

    client_addr_table.index = 0;
    client_addr_table.size = CLIENT_ADDR_TABLE_SIZE;

    timeout_table.size = TIMEOUT_TABLE_SIZE;
}


void on_client_join(uint8_t client_ip, int sock_fd) 
{
    if (client_addr_table.index >= client_addr_table.size)
    {
        ESP_LOGW(TAG, "client table is full");
    }
    client_addr_t new_client = {.ip_addr=client_ip, .socket=sock_fd};
    client_addr_table.table[client_addr_table.index++] = new_client;
    

    ESP_LOGI(TAG, "new client connected with ip: %d", client_ip);

}

dv_routing_table_t get_dv_routing_table(void)
{
    return routing_table;
}


void handle_dv_update(const dv_update_packet_t *dv_update_packet)
{
    
    for(uint8_t j=0; j<dv_update_packet->table_size; j++)
    {
        if (dv_update_packet->table[j].destination_network == routing_table.network_addr)
        {
            continue;
        }

        int8_t index = -1;
        for (size_t i = 0; i <= routing_table.index; i++)
        {
            if (routing_table.table[i].destination_network == dv_update_packet->table[j].destination_network)
            {
                index = i;
                break;
            }
        }

        if (index > -1)
        {
            dv_element_t dv_element = dv_update_packet->table[index];
            dv_element.hop_count +=1;
            if (routing_table.table[index].hop_count > dv_element.hop_count)
            {
                ESP_LOGI(TAG, "better way found, old hop: %d, old count: %d, new hop: %d, new count: %d", 
                routing_table.table[index].next_hop, routing_table.table[index].hop_count, dv_element.next_hop, dv_element.hop_count);

                routing_table.table[index].next_hop = dv_update_packet->source_addr;
                routing_table.table[index].hop_count = dv_element.hop_count;
                
            }
        }

        else
        {
            dv_element_t new_element;
            new_element.destination_network = dv_update_packet->table[j].destination_network;
            //new_element.destination_device = dv_update_packet->table[j].destination_device;
            new_element.hop_count = dv_update_packet->table[j].hop_count + 1;
            new_element.next_hop = dv_update_packet->source_addr;
            if (insert_hop(new_element) > 0)
            {
                ESP_LOGI(TAG, "new hop added to routing table, destination_network: %d, hop count: %d, next hop: %d", 
                 new_element.destination_network, new_element.hop_count, new_element.next_hop);
            }else {
                ESP_LOGW(TAG, "new hop cant be be added to routing table, table is full");
            }
        }
    }
}


uint8_t lookup_route(uint8_t destination_network)
{

    if (destination_network == routing_table.network_addr)
    {
        return 0;
    }

    for (size_t i = 0; i < routing_table.index; i++)
    {
        if (routing_table.table[i].destination_network == destination_network)
        {
            return routing_table.table[i].next_hop;
        }
    }
    return -1;
}


void handle_alive_request(dv_alive_packet_t alive_packet)
{

    for (size_t i = 0; i < timeout_table.size; i++)
    {
        if (alive_packet.source_addr == timeout_table.table[i].network_addr)
        {
            ESP_LOGI(TAG, "%d network is alive", alive_packet.source_addr);
            timeout_table.table[i].timeout--;
            return;
        }
    }

    ESP_LOGW(TAG, "%d network not in timeout table!!", alive_packet.source_addr);
}


int increase_timeout_table(void)
{
    for (size_t i = 0; i < timeout_table.size; i++)
    {
        timeout_table.table[i].timeout++;
    }
}



static int insert_hop(dv_element_t new_element)
{
    if (routing_table.index >= MAX_HOP)
    {
        return -1;
    }
    routing_table.table[routing_table.index++] = new_element;
    return 1;
}





