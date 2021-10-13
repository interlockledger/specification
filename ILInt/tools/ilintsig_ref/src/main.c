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
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
/*
 * This program generates test vectors for the ILIntSign transformations. Just
 * compile it, run and get the output.
 */

//------------------------------------------------------------------------------
/**
 * Performs the ILIntSignEnc transformation.
 * 
 * @param[in] v The value to be encoded.
 * @return The encoded value.
 */
uint64_t ilintsig_enc(int64_t v)
{
	uint64_t tmp = (uint64_t)v;
	if (tmp & 0x8000000000000000l)
	{
		return ~(tmp << 1);
	}
	else
	{
		return (tmp << 1);
	}
}

//------------------------------------------------------------------------------
/**
 * Performs the ILIntSignDec transformation.
 * 
 * @param[in] v The value to be decoded.
 * @return The decoded value.
 */
int64_t ilintsig_dec(uint64_t v)
{
	if (v & 0x1)
	{
		return (int64_t)(~(v >> 1));
	}
	else
	{
		return (int64_t)(v >> 1);
	}
}

//------------------------------------------------------------------------------
/**
 * Converts an unsigned 64-bits into a bit string.
 * 
 * @param[in] value The value to be converted.
 * @param[out] buff The buffer that will hold the converted value. It must have
 * at least 65 bytes.
 */
void to_bits(uint64_t value, char *buff)
{
	char *p = buff + 64;
	*p = 0;
	do
	{
		p--;
		*p = (value & 0x1) ? '1' : '0';
		value = value >> 1;
	} while (p > buff);
}

//------------------------------------------------------------------------------
/**
 * Converts the 64-bit signed integer into the ILIntSig format and prints the
 * resuts as a TSV line into stdout.
 * 
 * @param[in] v The value to be decoded.
 * @return The decoded value.
 */
void print_line(int64_t value)
{
	char value_bits[65];
	char enc_bits[65];
	// Convert...
	uint64_t enc = ilintsig_enc(value);
	// ...and ensure correctness.
	assert(value == ilintsig_dec(enc));
	to_bits((uint64_t)value, value_bits);
	to_bits(enc, enc_bits);
	printf("%ld\t%016lX\t%s\t%lu\t%016lX\t%s\n", value, value, value_bits,
		   enc, enc, enc_bits);
}

//------------------------------------------------------------------------------
/**
 * Generates a random int64 value with the specified sign.
 * 
 * @param[in] negative The resulting signal.
 * @return The random value.
 */
int64_t randon_int64(bool negative)
{
	// To ensure maximum compatibility, it will extract 16-bits at a time from the
	// rand() function.
	int64_t v = 0;
	for (int i = 0; i < 4; i++)
	{
		v = (v << 16) | rand() & 0xFFFF;
	}
	if (negative)
	{
		return v | 0x8000000000000000ll;
	}
	else
	{
		return v & 0x7FFFFFFFFFFFFFFFll;
	}
}

//------------------------------------------------------------------------------
int main(int argc, char **argv, char **envp)
{

	// Print the header
	printf("Value\tValue (hex)\tValue (bin)\tEncoded\tEncoded (hex)\tEncoded (bin)\n");

	// Trivial
	print_line(0);
	print_line(1);
	print_line(-1);
	print_line(256);
	print_line(-256);
	print_line(-257);
	print_line(4294967295);
	print_line(-4294967296);

	// Limit values
	print_line(9223372036854775807ll);
	print_line(-9223372036854775807ll);

	// Random values - positive
	for (int i = 0; i < 4; i++)
	{
		print_line(randon_int64(false));
	}
	// Negative
	for (int i = 0; i < 4; i++)
	{
		print_line(randon_int64(true));
	}
	return 0;
}
