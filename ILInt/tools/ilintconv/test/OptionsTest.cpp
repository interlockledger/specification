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
#include "OptionsTest.h"
#include "options.h"
#include <cstring>
#include <cstdarg>
#include <string>
#include <vector>
#include <memory>

//==============================================================================
// class OptionsTest
//------------------------------------------------------------------------------
OptionsTest::OptionsTest() {
}

//------------------------------------------------------------------------------
OptionsTest::~OptionsTest() {
}

//------------------------------------------------------------------------------
void OptionsTest::SetUp() {
}

//------------------------------------------------------------------------------
void OptionsTest::TearDown() {
}

//==============================================================================
// class ArgumentList
//------------------------------------------------------------------------------
class ArgumentList {
public:
	enum {MAX_ENTRIES = 16};
private:
	char * _args[MAX_ENTRIES];
	int _count;
public:
	ArgumentList(): _count(0) {
		std::memset(this->_args, 0, sizeof(ArgumentList::_args));
	}

	~ArgumentList() {
		this->reset();
	}

	void reset(){
		for (int i = 0; i < this->count(); i++) {
			delete [] this->_args[i];
		}
		this->_count = 0;
	}

	int count() const {
		return this->_count;
	}

	void add(const char * value) {
		if (this->count() < ArgumentList::MAX_ENTRIES) {
			char * v;
			int size = std::strlen(value) + 1;
			v = new char[size];
			std::memcpy(v, value, size);
			this->_args[this->_count] = v;
			this->_count++;
		}
	}

	void addAll(const char * v1, ...) {
		va_list args;

		if (v1) {
			this->add(v1);
			va_start(args, v1);
			for (const char * s = va_arg(args, const char *); s != NULL; s = va_arg(args, const char *)) {
				this->add(s);
			}
			va_end(args);
		}
	}

	char ** args() {
		return this->_args;
	}
};

//------------------------------------------------------------------------------
#define OptionsTest_options_read_input_SAMPLE "0123456789ABCDEF"

TEST_F(OptionsTest, options_read_input) {
	FILE * tmpFile;
	char buff[32];

	// Create the temporary file
	tmpFile = tmpfile();
	ASSERT_TRUE(tmpFile != NULL);
	ASSERT_EQ(16, fwrite(OptionsTest_options_read_input_SAMPLE, 1, 16, tmpFile));

	// Read the full file
	ASSERT_EQ(0, fseek(tmpFile, SEEK_SET, 0));
	ASSERT_TRUE(options_read_input(tmpFile, buff, sizeof(buff)));
	ASSERT_STREQ(OptionsTest_options_read_input_SAMPLE, buff);

	// Read exact
	ASSERT_EQ(0, fseek(tmpFile, SEEK_SET, 0));
	ASSERT_TRUE(options_read_input(tmpFile, buff, 17));
	ASSERT_STREQ(OptionsTest_options_read_input_SAMPLE, buff);

	// Fail because the buffer is too small
	ASSERT_EQ(0, fseek(tmpFile, SEEK_SET, 0));
	ASSERT_FALSE(options_read_input(tmpFile, buff, 16));

	fclose(tmpFile);
}

//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_is_input_set) {
	options_t opt;

	std::memset(&opt, 0, sizeof(opt));

	ASSERT_FALSE(options_is_input_set(&opt));
	opt.input[0] = 1;
	ASSERT_TRUE(options_is_input_set(&opt));
}


//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_parse_no_args) {
	options_t opt;
	ArgumentList args;
	int retval;

	args.addAll("prog", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);
}

//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_parse_help) {
	options_t opt;
	ArgumentList args;
	int retval;

	args.addAll("prog", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);

	args.reset();
	args.addAll("prog", "-h", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);

	args.reset();
	args.addAll("prog", "-h", "-c", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);

	args.reset();
	args.addAll("prog", "-h", "-x", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);

	args.reset();
	args.addAll("prog", "-h", "-d", "3131323", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_HELP, opt.operation);
}

//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_parse_encode) {
	options_t opt;
	ArgumentList args;
	int retval;

	args.reset();
	args.addAll("prog", "123456", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_ENCODE, opt.operation);
	ASSERT_FALSE(opt.hex);
	ASSERT_FALSE(opt.readInput);
	ASSERT_STREQ("123456", opt.input);

	args.reset();
	args.addAll("prog", "-x", "123456", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_ENCODE, opt.operation);
	ASSERT_TRUE(opt.hex);
	ASSERT_FALSE(opt.readInput);
	ASSERT_STREQ("123456", opt.input);

	args.reset();
	args.addAll("prog", "-c", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_ENCODE, opt.operation);
	ASSERT_FALSE(opt.hex);
	ASSERT_TRUE(opt.readInput);
	ASSERT_STREQ("", opt.input);

	args.reset();
	args.addAll("prog", "-c", "-x", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_ENCODE, opt.operation);
	ASSERT_TRUE(opt.hex);
	ASSERT_TRUE(opt.readInput);
	ASSERT_STREQ("", opt.input);
}

//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_parse_decode) {
	options_t opt;
	ArgumentList args;
	int retval;

	args.reset();
	args.addAll("prog", "-d", "123456", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_DECODE, opt.operation);
	ASSERT_FALSE(opt.hex);
	ASSERT_FALSE(opt.readInput);
	ASSERT_STREQ("123456", opt.input);

	args.reset();
	args.addAll("prog", "-d", "-x", "123456", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_DECODE, opt.operation);
	ASSERT_TRUE(opt.hex);
	ASSERT_FALSE(opt.readInput);
	ASSERT_STREQ("123456", opt.input);

	args.reset();
	args.addAll("prog", "-d", "-c", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_DECODE, opt.operation);
	ASSERT_FALSE(opt.hex);
	ASSERT_TRUE(opt.readInput);
	ASSERT_STREQ("", opt.input);

	args.reset();
	args.addAll("prog", "-d", "-c", "-x", NULL);
	ASSERT_EQ(ERR_SUCCESS, options_parse(args.count(), args.args(), &opt));
	ASSERT_EQ(OP_DECODE, opt.operation);
	ASSERT_TRUE(opt.hex);
	ASSERT_TRUE(opt.readInput);
	ASSERT_STREQ("", opt.input);
}

//------------------------------------------------------------------------------
TEST_F(OptionsTest, options_parse_error) {
	options_t opt;
	ArgumentList args;
	int retval;

	args.reset();
	args.addAll("prog", "-x", NULL);
	ASSERT_EQ(ERR_VALUE_MISSING, options_parse(args.count(), args.args(), &opt));

	args.reset();
	args.addAll("prog", "-d", NULL);
	ASSERT_EQ(ERR_VALUE_MISSING, options_parse(args.count(), args.args(), &opt));

	args.reset();
	args.addAll("prog", "-x", "-d", NULL);
	ASSERT_EQ(ERR_VALUE_MISSING, options_parse(args.count(), args.args(), &opt));

	args.reset();
	args.addAll("prog", "0123456789ABCDEF0123456789ABCDEF", NULL);
	ASSERT_EQ(ERR_VALUE_TOO_LONG, options_parse(args.count(), args.args(), &opt));

	args.reset();
	args.addAll("prog", "-c", "0123456789ABCDEF", NULL);
	ASSERT_EQ(ERR_TOO_MANY_OPTIONS, options_parse(args.count(), args.args(), &opt));
}

//------------------------------------------------------------------------------

