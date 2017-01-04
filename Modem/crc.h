#ifndef CRC_H
#define CRC_H

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdint.h>

uint16_t crc16_ccitt(uint16_t crc_start, uint8_t *buf, int len);

#ifdef __cplusplus
}
#endif

#endif // CRC_H
