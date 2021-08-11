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
#include <stdio.h>
#include <string.h>
#include "ilint.h"

//------------------------------------------------------------------------------
void printBin(const void *v, size_t vSize)
{
	const uint8_t *p;
	const uint8_t *pEnd;

	p = (const uint8_t *)v;
	pEnd = p + vSize;
	for (; p != pEnd; p++)
	{
		printf("%02X", *p);
	}
}

//------------------------------------------------------------------------------
void printILIntSize(uint64_t v)
{
	printf("\tSize of %lu (0x%lX): %d\n", v, v, ilint_size(v));
}

//------------------------------------------------------------------------------
void printSignedTransform(int64_t v)
{

	uint64_t e = ilintsig_enc(v);
	int64_t d = ilintsig_dec(e);
	printf("\tValue %ld (0x%lX), Encoded: 0x%lX; Decoded: %ld;\n", v, v, e, d);
}

//------------------------------------------------------------------------------
int main(int argc, char argv)
{
	uint8_t buff[16];

	// Print size
	printf("ilint_size():\n");
	printILIntSize(0);
	printILIntSize(0xF7ll);
	printILIntSize(0xF8ll);
	printILIntSize(0xF8ll + 0xFFll);
	printILIntSize(0xF8ll + 0xFFll + 1);
	printILIntSize(0xF8ll + 0xFFFFll);
	printILIntSize(0xF8ll + 0xFFFFll + 1);
	printILIntSize(0xF8ll + 0xFFFFFFll);
	printILIntSize(0xF8ll + 0xFFFFFFll + 1);
	printILIntSize(0xFFFFFFFFFFFFFFFFll);

	printf("printSignedTransfer():\n");
	printSignedTransform(0);
	printSignedTransform(1);
	printSignedTransform(0x7FFFFFFFFFFFFFFFl);
	printSignedTransform(-1);
	printSignedTransform(-2);
	printSignedTransform((int64_t)0x8000000000000000l);
	return 0;
}
//------------------------------------------------------------------------------
