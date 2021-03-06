/*
 * Copyright (c) 2018, Open Communications Security
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "utils.h"
#include <string.h>

//------------------------------------------------------------------------------
char valueToDigit(int v) {

	if (v < 10) {
		return '0' + v;
	} else if (v < 32) {
		return 'A' + (v - 10);
	} else {
		return '\0';
	}
}

//------------------------------------------------------------------------------
int digitToValue(int c) {

	if ((c >= '0') && (c <= '9')) {
		return c- '0';
	} else if ((c >= 'A') && (c <= 'V')) {
		return c - 'A' + 10;
	} else if ((c >= 'a') && (c <= 'v')) {
		return c - 'a' + 10;
	} else {
		return 32;
	}
}

//------------------------------------------------------------------------------
/**
 * Converts an uint64_t value into a string.
 *
 * @param[in] v The value.
 * @param[in] base The base. Must be a value between 2 and 16.
 * @param[out] s The output buffer, must be large enough to hold the value and
 * the null terminator.
 * @param[in] sSize The size of s.
 * @return true for success or false otherwise.
 */
static bool uint64ToStrCore(uint64_t v, unsigned int base, char * s,
		uint64_t * sSize) {
	char tmp[128];
	uint64_t i;

	i = 0;
	do {
		tmp[i] = valueToDigit((int)(v % base));
		v = v / base;
		i++;
	} while (v);
	if (i < *sSize){
		*sSize = i + 1;
		do {
			i--;
			*s = tmp[i];
			s++;
		} while (i > 0);
		*s = '\0';
		return true;
	} else {
		*sSize = i + 1;
		return false;
	}
}

//------------------------------------------------------------------------------
bool uint64ToHex(uint64_t v, char * s, uint64_t * sSize) {
	return uint64ToStrCore(v, 16, s, sSize);
}

//------------------------------------------------------------------------------
bool uint64ToDec(uint64_t v, char * s, uint64_t * sSize) {
	return uint64ToStrCore(v, 10, s, sSize);
}

//------------------------------------------------------------------------------
bool strToUint64Core(const char * s, unsigned int base, uint64_t * v) {

	if (*s == 0) {
		return false;
	}

	*v = 0;
	while (*s) {
		uint64_t val = digitToValue(*s);
		if (val >= base) {
			return false;
		}
		val = ((*v) * base) + val;
		if (val < (*v)) {
			return false;
		}
		(*v) = val;
		s++;
	}
	return true;
}


//------------------------------------------------------------------------------
bool hexToUint64(const char * s, uint64_t * v) {
	return strToUint64Core(s, 16, v);
}

//------------------------------------------------------------------------------
bool decToUint64(const char * s, uint64_t * v) {
	return strToUint64Core(s, 10, v);
}

//------------------------------------------------------------------------------
bool hexToBin(const char * s, uint8_t * bin, uint64_t * binSize) {
	uint64_t sSize;
	uint64_t decSize;
	unsigned int bitBuff;

	sSize = strlen(s);
	if (sSize & 0x1) {
		(*binSize) = 0;
		return false;
	}
	if ((*binSize) < (sSize / 2)) {
		(*binSize) = (sSize / 2);
		return false;
	}

	*binSize = 0;
	decSize = 0;
	bitBuff = 0;
	while(*s) {
		int v = digitToValue(*s);
		if (v >= 16) {
			return false;
		}
		bitBuff = (bitBuff << 4) + v;
		decSize++;
		s++;
		if ((decSize & 0x1) == 0) {
			*bin = (uint8_t)bitBuff;
			bin++;
		}
	}
	(*binSize) = decSize / 2;
	return true;
}

//------------------------------------------------------------------------------
bool binToHex(const uint8_t * bin, uint64_t binSize, char * s, uint64_t sSize) {
	const uint8_t * binEnd;

	if (sSize < ((binSize * 2) + 1)) {
		return false;
	} else {
		binEnd = bin + binSize;
		for (; bin != binEnd; bin++) {
			*s = valueToDigit(((*bin) >> 4) & 0xF);
			s++;
			*s = valueToDigit((*bin) & 0xF);
			s++;
		}
		*s = 0;
		return true;
	}
}
//------------------------------------------------------------------------------
