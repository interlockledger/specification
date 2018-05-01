
#include "options.h"
#include <string.h>
#include <stdio.h>

//------------------------------------------------------------------------------
void options_default(options_t * opt) {
	opt->operation = OP_ENCODE;
	opt->hex = false;
	opt->readInput = false;
	memset(opt->input, 0, OPTIONS_MAX_INPUT);
}

//------------------------------------------------------------------------------
int options_read_input(options_t * opt) {

	if (opt->input[0]) {
		return OPTIONS_ERR_TOO_MANY_OPTIONS;
	} else {
		fgets(opt->input, OPTIONS_MAX_INPUT, stdin);
		return 0;
	}
}

//------------------------------------------------------------------------------
int options_parse(options_t * opt, int argc, char ** argv) {
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
					return OPTIONS_ERR_TOO_MANY_OPTIONS;
				}
				if (strlen(val) < OPTIONS_MAX_INPUT) {
					strcpy(opt->input, val);
				} else {
					return OPTIONS_VALUE_TOO_LONG;
				}
			}
		}
		
		// Check the input
		if (opt->readInput) {
			return options_read_input(opt);
		} else {
			if (opt->input[0] == 0) {
				return OPTIONS_VALUE_MISSING;
			}
		}
	}
	return 0;
}

//------------------------------------------------------------------------------

