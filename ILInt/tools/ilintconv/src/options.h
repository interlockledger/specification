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
#ifndef __options_H__
#define __options_H_

#ifdef __cplusplus
extern "C"_ {
#endif // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
	OP_HELP,
	OP_DECODE,
	OP_ENCODE
} options_op_t;

#define OPTIONS_MAX_INPUT 32

typedef struct options_t {
	options_op_t operation;
	bool hex;
	bool readInput;
	char input[OPTIONS_MAX_INPUT];
} options_t;

#define OPTIONS_ERR_SUCCESS 0
#define OPTIONS_ERR_UNKNOWN_OPTION 1
#define OPTIONS_ERR_TOO_MANY_OPTIONS 2
#define OPTIONS_VALUE_TOO_LONG 3
#define OPTIONS_VALUE_MISSING 4

#define options_is_input_set(opt) (opt->input[0] != 0)

/**
 * Reads the input from a file.
 */ 
bool options_read_input(FILE * inp, void * buff, uint64_t buffSize);

/**
 * Prints the help screen.
 */ 
void options_print_help();

/**
 * Parses the command line.
 *
 * @param[in] argc The number of arguments. 
 * @param[in] argv Array of arguments.
 * @param[out] opt The command line options.
 * @return OPTIONS_ERR_SUCCESS on success or other error code on failure.
 */ 
int options_parse(int argc, char ** argv, options_t * opt);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //__options_H__

