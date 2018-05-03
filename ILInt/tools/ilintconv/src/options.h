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
extern "C" {
#endif // __cplusplus

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "errors.h"

/**
 * Type used to identify the program operation.
 */
typedef enum {
	/**
	 * Show help.
	 */
	OP_HELP,
	/**
	* Decode the input.
	*/
	OP_DECODE,
	/**
	* Encode the input.
	*/
	OP_ENCODE
} options_op_t;

/**
 * Maximum size of the input value.
 */
#define OPTIONS_MAX_INPUT 32

/**
 * Type used to hold the options passed to the program.
 */
typedef struct options_t {
	/**
	 * Current operation.
	 */
	options_op_t operation;
	/**
	 * Flag that indicates if the input is decimal or hexadecimal
	 * when encoding.
	 */
	bool hex;
	/**
	 * Flag that determines if the input should be read from stdin.
	 */
	bool readInput;
	/**
	 * The value of the input.
	 */
	char input[OPTIONS_MAX_INPUT];
} options_t;

/**
 * Verifies if the input is set or not.
 *
 * @param[in] opt A pointer to a options_t.
 * @return true if the input is set or false otherwise.
 */
#define options_is_input_set(opt) ((opt)->input[0] != 0)

/**
 * Reads the input from a file. This function will fail if the buffer
 * is not large enough to hold all the input available in the stream.
 * 
 * @param[in] inp The input stream.
 * @param[out] buff The output buffer.
 * @param[in] buffSize The size of buff in bytes.
 * @return true for success or false otherwise.
 */ 
bool options_read_input(FILE * inp, void * buff, uint64_t buffSize);

/**
 * Prints the help screen.
 *
 * @param[in] progName The name of the program.
 */ 
void options_print_help(const char * progName);

/**
 * Parses the command line.
 *
 * @param[in] argc The number of arguments. 
 * @param[in] argv Array of arguments.
 * @param[out] opt The command line options.
 * @return ERR_SUCCESS on success or other error code on failure.
 */ 
int options_parse(int argc, char ** argv, options_t * opt);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif //__options_H__

