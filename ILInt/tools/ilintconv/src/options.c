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
#include "options.h"
#include <string.h>

//------------------------------------------------------------------------------
void options_default(options_t * opt) {
	opt->operation = OP_ENCODE;
	opt->hex = false;
	opt->readInput = false;
	memset(opt->input, 0, OPTIONS_MAX_INPUT);
}

//------------------------------------------------------------------------------
bool options_read_input(FILE * inp, void * buff, uint64_t buffSize) {
	char tmp[4];

	if (!fgets(buff, buffSize, inp)) {
		return false;
	}
	return (fgets(tmp, sizeof(tmp), inp) == NULL);
}

//------------------------------------------------------------------------------
void options_print_help(const char * progName) {

	printf("Usage: %s [-c] [-d] [-h] [-x] [<value>]\n", progName);
	printf("Options:\n");
	printf("\t-c: Read input from the standard input\n");
	printf("\t-d: Decodes the ILInt value\n");
	printf("\t-h: Prints this help screen\n");
	printf("\t-x: Use hexadecimal constants instead of decimal\n");
	printf("\n");
	printf("<value>: the value to be encoded or decoded.\n");
}

//------------------------------------------------------------------------------
int options_parse(int argc, char ** argv, options_t * opt) {
	int i;

	options_default(opt);
	if (argc == 1) {
		opt->operation = OP_HELP;
	} else {
		for (i = 1; i < argc; i++) {
			const char * val = argv[i];
			if (strcmp("-c", val) == 0) {
				opt->readInput = true;
			} else if (strcmp("-d", val) == 0) {
				opt->operation = (opt->operation == OP_HELP)?
					OP_HELP : OP_DECODE;
			} else if (strcmp("-h", val) == 0) {
				opt->operation = OP_HELP;
			} else if (strcmp("-x", val) == 0) {
				opt->hex = true;
			} else {
				if (opt->input[0]) {
					return ERR_TOO_MANY_OPTIONS;
				}
				if (strlen(val) < OPTIONS_MAX_INPUT) {
					strcpy(opt->input, val);
				} else {
					return ERR_VALUE_TOO_LONG;
				}
			}
		}
		
		// Check the input
		if (opt->operation != OP_HELP) {
			if (opt->readInput) {
				if (options_is_input_set(opt)) {
					return ERR_TOO_MANY_OPTIONS;
				}
			} else {
				if (!options_is_input_set(opt)) {
					return ERR_VALUE_MISSING;
				}
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------

