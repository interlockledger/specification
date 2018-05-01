/*
 * Copyright (c) 2017-2018, Open Communications Security
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
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace InterlockRecord.Common
{
    public static class TagHelpers
    {
        public const int ILINT_BASE = 0xF8;

        public static ulong ILIntDecode(this byte[] buffer) => ILIntDecode(new MemoryStream(buffer, 0, buffer.Length));

        public static ulong ILIntDecode(this byte[] buffer, int index, int count) => ILIntDecode(new MemoryStream(buffer, index, count));

        public static ulong ILIntDecode(this Stream stream)
        {
            ulong value = 0;
            var nextByte = stream.ReadSingleByte();
            if (nextByte < ILINT_BASE)
                return nextByte;
            int size = nextByte - ILINT_BASE + 1;
            while (size-- > 0)
                value = (value << 8) + stream.ReadSingleByte();
            if (value > 0xFFFFFFFFFFFFFFFFL - ILINT_BASE)
                return 0;
            return value + ILINT_BASE;
        }

        public static byte[] ILIntEncode(this ulong value, byte[] buffer, int offset, int count)
        {
            ILIntEncode(value, b =>
            {
                if (--count < 0)
                    throw new TooFewBytesException();
                buffer[offset++] = b;
            });
            return buffer;
        }

        public static Stream ILIntEncode(this Stream stream, ulong value)
        {
            value.ILIntEncode(stream.WriteByte);
            return stream;
        }

        public static byte[] ILIntEncode(this ulong value)
        {
            int size = ILIntSize(value);
            return value.ILIntEncode(new byte[size], 0, size);
        }

        public static int ILIntSize(this ulong value)
        {
            if (value < ILINT_BASE)
                return 1;
            if (value <= (0xFF + ILINT_BASE))
                return 2;
            if (value <= (0xFFFF + ILINT_BASE))
                return 3;
            if (value <= (0xFFFFFF + ILINT_BASE))
                return 4;
            if (value <= (0xFFFFFFFFL + ILINT_BASE))
                return 5;
            if (value <= (0xFFFFFFFFFF + ILINT_BASE))
                return 6;
            if (value <= (0xFFFFFFFFFFFFL + ILINT_BASE))
                return 7;
            if (value <= ((ulong)0xFFFFFFFFFFFFFFL + ILINT_BASE))
                return 8;
            return 9;
        }

        private static void ILIntEncode(this ulong value, Action<byte> writeByte)
        {
            int size = ILIntSize(value);
            if (size == 1) {
                writeByte((byte)(value & 0xFF));
            } else {
                writeByte((byte)(ILINT_BASE + (size - 2)));
                value = value - ILINT_BASE;
                for (int i = ((size - 2) * 8); i >= 0; i -= 8) {
                    writeByte((byte)((value >> i) & 0xFF));
                }
            }
        }
    }
}
