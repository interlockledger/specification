/*
 * Copyright (c) 2017-2021, Open Communications Security
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
#ifndef __ILINT_H__
#define __ILINT_H__

#include <stdint.h>

/**
 * LInt base value. All values larger then or equal to will use more
 * than 1 byte to be encoded.
 */
#define ILINT_BASE 0xF8

/**
 * Returns the size of the given value encoded as an ILInt.
 *
 * @return The size in bytes.
 */
int ilint_size(uint64_t v);

/**
 * Encodes the given value using the ILInt format.
 *
 * @param[in] v The value to be encoded.
 * @param[out] out The output buffer. It must have at least ilint_size(v) bytes.
 * @param[in] outSize The size of out in bytes.
 * @return The size in bytes or zero in case of error.
 */
int ilint_encode(uint64_t v, void *out, int outSize);

/**
 * Decodes the given value encoded as an ILInt.
 *
 * @param[in] inp The input buffer.
 * @param[in] inpSize The size of inp in bytes.
 * @param[out] v The decoded value.
 * @return The number of bytes used or zero in case of error.
 */
int ilint_decode(const void *inp, int inpSize, uint64_t *v);

/**
 * Performs the ILIntSignEnc transformation.
 * 
 * @param[in] v The value to be encoded.
 * @return The encoded value.
 */
uint64_t ilintsig_enc(int64_t v);

/**
 * Performs the ILIntSignDec transformation.
 * 
 * @param[in] v The value to be decoded.
 * @return The decoded value.
 */
int64_t ilintsig_dec(uint64_t v);

#endif //__ILINT_H__
