#pragma once

  

#include "stdint.h"

  
  

/**

* @struct lora_emergency_packet_t

* @brief Packed representation of a minimal emergency packet for LoRa transmission.

*

* This structure is sent “raw” over LoRa (no implicit header mode) and contains:

* - A 1-byte packet_type to indicate the message semantics (e.g., help request, status update).

* - A 1-byte source ID and 1-byte destination ID for simple addressing.

* - A fixed 10-byte payload that carries exactly:

* • 1 byte emergency code

* • 4 bytes latitude (float, IEEE-754)

* • 4 bytes longitude (float, IEEE-754)

* • 1 spare byte (reserved for future use or padding)

* - A 2-byte CRC for end-to-end integrity checking.

*

* All fields are laid out without padding to minimize on-air size.

*/

typedef struct __attribute__((packed)) {

uint8_t packet_type; /**< Message type code:

* - 0x01 = Emergency packet

* - 0x02 = Route discovery packet

* - ... (future codes)

*/

uint8_t source; /**< Unique ID of the sender node (0–255). */

uint8_t destination; /**< Unique ID of the intended recipient (0–255). */

uint8_t payload[10]; /**< Emergency payload, exactly 10 bytes:

* Byte 0: emergency code (same as packet_type or subcode)

* Bytes 1–4: latitude (float, little-endian)

* Bytes 5–8: longitude (float, little-endian)

* Byte 9: reserved for future use (padding or flags)

*/

uint16_t crc; /**< Simple 16-bit checksum over bytes */

} lora_emergency_packet_t;
