#ifndef crc16dnp_h
#define crc16dnp_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stddef.h>


uint16_t crc16_dnp(const uint8_t *data, size_t len);


#ifdef __cplusplus
}
#endif

#endif