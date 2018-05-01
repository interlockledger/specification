

#ifndef __utils_H__
#define  __utils_H__

#include <stdint.h>
#include <stdbool.h>

bool uint64ToHex(uint64_t v, char * s, uint64_t sSize);

bool uint64ToDec(uint64_t v, char * s, uint64_t sSize);

bool hexToUint64(const char * s, uint64_t * v);

bool hexToBin(const char * s, uint8_t * bin, uint64_t * binSize);

bool binToHex(const uint8_t * bin, uint64_t * binSize, char * s, uint64_t sSize);

#endif // __utils_H__

