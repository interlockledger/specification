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
#ifndef __utils_H__
#define  __utils_H__

#include <stdint.h>
#include <stdbool.h>

/**
 * Returns the digit for the value v.
 *
 * @param[in] v The value. Must be a value
 * between 0 and 32.
 * @return The digit for the given value.
 */
char valueToDigit(int v);

/**
 * Returns the value for the digit.
 *
 * @param[in] c The character.
 * @return The value of the character between 0 and 31 or 32 if the
 * character is not valid.
 */
int digitToValue(int c);

/**
 * Converts an uint64_t value into an hexadecimal string.
 *
 * @param[in] v The value.
 * @param[out] s The output buffer, must be large enough to hold the value and
 * the null terminator.
 * @param[in,out] sSize On input, it is the size of s in characters.
 * On output, it is the actual size of s in characters, including the terminator.
 * @return true for success or false otherwise.
 */
bool uint64ToHex(uint64_t v, char * s, uint64_t * sSize);

/**
 * Converts an uint64_t value into a decimal string.
 *
 * @param[in] v The value.
 * @param[out] s The output buffer, must be large enough to hold the value and
 * the null terminator.
 * @param[in,out] sSize On input, it is the size of s in characters.
 * On output, it is the actual size of s in characters, including the terminator.
 * @return true for success or false otherwise.
 */
bool uint64ToDec(uint64_t v, char * s, uint64_t * sSize);

bool hexToUint64(const char * s, uint64_t * v);

bool hexToBin(const char * s, uint8_t * bin, uint64_t * binSize);

bool binToHex(const uint8_t * bin, uint64_t * binSize, char * s, uint64_t sSize);

#endif // __utils_H__

