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
#include "ilint.h"

//------------------------------------------------------------------------------
int ilint_size(uint64_t v)
{

	if (v < ILINT_BASE)
	{
		return 1;
	}
	else if (v <= (0xFF + ILINT_BASE))
	{
		return 2;
	}
	else if (v <= (0xFFFF + ILINT_BASE))
	{
		return 3;
	}
	else if (v <= (0xFFFFFFl + ILINT_BASE))
	{
		return 4;
	}
	else if (v <= (0xFFFFFFFFll + ILINT_BASE))
	{
		return 5;
	}
	else if (v <= (0xFFFFFFFFFFll + ILINT_BASE))
	{
		return 6;
	}
	else if (v <= (0xFFFFFFFFFFFFll + ILINT_BASE))
	{
		return 7;
	}
	else if (v <= (0xFFFFFFFFFFFFFFll + ILINT_BASE))
	{
		return 8;
	}
	else
	{
		return 9;
	}
}

//------------------------------------------------------------------------------
int ilint_encode(uint64_t v, void *out, int outSize)
{
	int size;
	uint8_t *p;
	int i;

	size = ilint_size(v);
	if (outSize < size)
	{
		return 0;
	}
	p = (uint8_t *)out;
	if (size == 1)
	{
		*p = (uint8_t)(v & 0xFF);
	}
	else
	{
		*p = ILINT_BASE + (size - 2);
		p++;
		v = v - ILINT_BASE;
		for (i = ((size - 2) * 8); i >= 0; i -= 8, p++)
		{
			*p = (uint8_t)((v >> i) & 0xFF);
		}
	}
	return size;
}

//------------------------------------------------------------------------------
int ilint_decode(const void *inp, int inpSize, uint64_t *v)
{
	const uint8_t *p;
	const uint8_t *pEnd;
	int size;

	if (inpSize <= 0)
	{
		return 0;
	}
	p = (const uint8_t *)inp;
	size = *p;
	if (size < ILINT_BASE)
	{
		*v = size;
		return 1;
	}
	else
	{
		p++;
		size = size - ILINT_BASE + 1;
		if (inpSize <= size)
		{
			return 0;
		}
		pEnd = p + size;
		*v = 0;
		for (; p < pEnd; p++)
		{
			*v = ((*v) << 8) | ((*p) & 0xFF);
		}
		if (*v > (0xFFFFFFFFFFFFFFFFll - ILINT_BASE))
		{
			return 0;
		}
		*v += ILINT_BASE;
		size++;
		return size;
	}
}

//------------------------------------------------------------------------------
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
