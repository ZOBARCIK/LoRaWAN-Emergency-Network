#pragma once

  

#include "stdint.h"

#define EMERGENCY_PACKET 1
#define DV_UPDATE_PACKET 2
#define DV_ALIVE_PACKET 3

  
  

/**

* @struct lora_emergency_packet_t

* @brief Packed representation of a minimal emergency packet for LoRa transmission.

*/

typedef struct __attribute__((packed)) {

uint8_t packet_type; /**< Message type code */

uint8_t source; /**< Unique ID of the sender node (0–255). */

uint8_t destination_network; /**< Unique ID of the intended recipient (0–255). */

uint8_t destination_device;

uint8_t payload[10]; // emergency code, latitude, longitude

uint16_t crc; /**< Simple 16-bit checksum over bytes */

} lora_emergency_packet_t;



