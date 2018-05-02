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
#include "UtilsTest.h"
extern "C" {
	#include "utils.h"
} // extern "C"
#include <cstring>

//==============================================================================
// class UtilsTest
//------------------------------------------------------------------------------
#define UtilsTest_uint64ToText_SAMPLES_COUNT 3

static struct{
	std::uint64_t value;
	const char * hex;
	const char * dec;
} UtilsTest_uint64ToText_SAMPLES[UtilsTest_uint64ToText_SAMPLES_COUNT] = {
		{0, "0", "0"},
		{0xFACADAll, "FACADA", "16435930"},
		{0xFFFFFFFFFFFFFFFFll, "FFFFFFFFFFFFFFFF", "18446744073709551615"}
};

//------------------------------------------------------------------------------
UtilsTest::UtilsTest() {
}

//------------------------------------------------------------------------------
UtilsTest::~UtilsTest() {
}

//------------------------------------------------------------------------------
void UtilsTest::SetUp() {
}

//------------------------------------------------------------------------------
void UtilsTest::TearDown() {
}

//------------------------------------------------------------------------------
TEST_F(UtilsTest, valueToDigit) {

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ('0' + i, valueToDigit(i));
	}
	for (int i = 10; i < 32; i++) {
		ASSERT_EQ('A' + (i - 10), valueToDigit(i));
	}
	for (int i = 32; i < 256; i++) {
		ASSERT_EQ('\0', valueToDigit(i));
	}
}

//------------------------------------------------------------------------------
TEST_F(UtilsTest, digitToValue) {

	for (int i = 0; i < 10; i++) {
		ASSERT_EQ(i, digitToValue('0' + i));
	}
	for (int i = 0; i < 22; i++) {
		ASSERT_EQ(i + 10, digitToValue('a' + i));
		ASSERT_EQ(i + 10, digitToValue('A' + i));
	}
	for (int c = 0; c < 256; c++) {
		if ((c >= '0') && (c <= '9')) {
			ASSERT_EQ(c - '0', digitToValue(c));
		} else if ((c >= 'A') && (c <= 'V')) {
			ASSERT_EQ(c - 'A' + 10, digitToValue(c));
		} else if ((c >= 'a') && (c <= 'v')) {
			ASSERT_EQ(c - 'a' + 10, digitToValue(c));
		} else {
			ASSERT_EQ(32, digitToValue(c));
		}
	}
}

//------------------------------------------------------------------------------
TEST_F(UtilsTest, uint64ToHex) {
	char tmp[32];

	for (int i = 0; i < UtilsTest_uint64ToText_SAMPLES_COUNT; i++) {
		const char * s = UtilsTest_uint64ToText_SAMPLES[i].hex;
		std::uint64_t v = UtilsTest_uint64ToText_SAMPLES[i].value;
		std::uint64_t sSize;

		sSize = sizeof(tmp);
		ASSERT_TRUE(uint64ToHex(v, tmp, &sSize));
		ASSERT_STREQ(s, tmp);
		ASSERT_EQ(std::strlen(s) + 1, sSize);

		sSize = std::strlen(s) + 1;
		ASSERT_TRUE(uint64ToHex(v, tmp, &sSize));
		ASSERT_STREQ(s, tmp);
		ASSERT_EQ(std::strlen(s) + 1, sSize);

		sSize = std::strlen(s);
		ASSERT_FALSE(uint64ToHex(v, tmp, &sSize));
		ASSERT_EQ(std::strlen(s) + 1, sSize);
	}
}

//------------------------------------------------------------------------------
TEST_F(UtilsTest, uint64ToDec) {
	char tmp[32];

	for (int i = 0; i < UtilsTest_uint64ToText_SAMPLES_COUNT; i++) {
		const char * s = UtilsTest_uint64ToText_SAMPLES[i].dec;
		std::uint64_t v = UtilsTest_uint64ToText_SAMPLES[i].value;
		std::uint64_t sSize;

		sSize = sizeof(tmp);
		ASSERT_TRUE(uint64ToDec(v, tmp, &sSize));
		ASSERT_STREQ(s, tmp);
		ASSERT_EQ(std::strlen(s) + 1, sSize);

		sSize = std::strlen(s) + 1;
		ASSERT_TRUE(uint64ToDec(v, tmp, &sSize));
		ASSERT_STREQ(s, tmp);
		ASSERT_EQ(std::strlen(s) + 1, sSize);

		sSize = std::strlen(s);
		ASSERT_FALSE(uint64ToDec(v, tmp, &sSize));
		ASSERT_EQ(std::strlen(s) + 1, sSize);
	}
}

//------------------------------------------------------------------------------

