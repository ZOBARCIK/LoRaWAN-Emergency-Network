#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#define CRC16_DNP_POLY 0x3D65



    static uint8_t reflect8bits(uint8_t input) {                            //reflect input (process byte by byte)        
        input = (input & 0xF0) >> 4 | (input & 0x0F) << 4; // Swap 4-bit halves
        input = (input & 0xCC) >> 2 | (input & 0x33) << 2; // Swap 2-bit groups
        input = (input & 0xAA) >> 1 | (input & 0x55) << 1; // Swap individual bits
        return input;
    }

    static uint16_t reflect16bits(uint16_t output) {                         //reflect output
        output = (output & 0xFF00) >> 8 | (output & 0x00FF) << 8; // Swap bytes
        output = (output & 0xF0F0) >> 4 | (output & 0x0F0F) << 4; // Swap 4-bit halves
        output = (output & 0xCCCC) >> 2 | (output & 0x3333) << 2; // Swap 2-bit groups
        output = (output & 0xAAAA) >> 1 | (output & 0x5555) << 1; // Swap individual bits
        return output;
    }

    uint16_t crc16_dnp(const uint8_t *data, size_t len) {
            uint16_t crc = 0x0000; //current crc value
        for (size_t i = 0; i < len; i++) {
            uint8_t buffer = reflect8bits(data[i]); //byte buffer to hold each byte of the data[i]
            crc ^= (uint16_t)buffer << 8; // cast to 16 and xor with crc
            for (int j = 0; j < 8; j++) {
                if (crc & 0x8000) //if MSB is =1
                    crc = (crc << 1) ^ CRC16_DNP_POLY;
                else
                    crc <<= 1;
            }
        }

        crc = reflect16bits(crc);
        return crc ^ 0xFFFF;  // Final XOR

    }







