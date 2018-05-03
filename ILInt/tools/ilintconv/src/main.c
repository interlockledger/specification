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
#include "ilint.h"
#include "options.h"
#include "utils.h"
#include <stdio.h>
#include <stdint.h>

int decode(const options_t * opt) {
	uint8_t bin[OPTIONS_MAX_INPUT];
	uint64_t binSize;
	uint64_t val;
	uint64_t valSize;
	char out[32];
	uint64_t outSize;

	binSize = sizeof(bin);
	if (!hexToBin(opt->input, bin, &binSize)) {
		return ERR_INVALID_VALUE;
	}

	valSize = ilint_decode(bin, binSize, &val);
	if (valSize == 0) {
		return ERR_INVALID_VALUE;
	}
	if (valSize != binSize) {
		return ERR_VALUE_TOO_LONG;
	}

	outSize = sizeof(out);
	if (opt->hex) {
		uint64ToHex(val, out, &outSize);
	} else {
		uint64ToDec(val, out, &outSize);
	}
	printf("%s", out);
	return ERR_SUCCESS;
}

int encode(const options_t * opt) {
	uint64_t val;
	bool ret;
	uint8_t enc[16];
	uint64_t encSize;
	char hex[32];

	if (opt->hex) {
		ret = hexToUint64(opt->input, &val);
	} else {
		ret = decToUint64(opt->input, &val);
	}
	if (!ret) {
		return ERR_INVALID_VALUE;
	}

	encSize = ilint_encode(val, enc, sizeof(enc));
	if (encSize == 0) {
		return ERR_UNABLE_TO_CONVERT;
	}

	if (!binToHex(enc, encSize, hex, sizeof(hex))){
		return ERR_UNABLE_TO_CONVERT;
	}
	printf("%s", hex);
	return ERR_SUCCESS;
}

int main(int argc, char ** argv) {
	options_t opt;

	int retval = options_parse(argc, argv, &opt);
	if (retval == ERR_SUCCESS) {
		if (opt.operation == OP_HELP) {
			options_print_help(argv[0]);
		} else {
			if (opt.readInput) {
				if (options_read_input(stdin, opt.input, sizeof(opt.input))) {
					if (!options_is_input_set(&opt)) {
						retval = ERR_VALUE_MISSING;
					}
				} else {
					retval = ERR_VALUE_TOO_LONG;
				}
			}
			if (retval == ERR_SUCCESS) {
				if (opt.operation == OP_DECODE) {
					retval = decode(&opt);
				} else {
					retval =encode(&opt);
				}
			}
		}
	}
	if (retval != ERR_SUCCESS) {
		fprintf(stderr, "%s\n", errors_getMessage(retval));
	}
	return retval;
}

