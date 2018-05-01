

#ifndef __options_H__
#define __options_H__

#include <stdbool.h>

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

int options_parse(options_t * opt, int argc, char ** argv);

#endif //__options_H__

