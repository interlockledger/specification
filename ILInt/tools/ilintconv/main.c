
#include "ilint.h"
#include "options.h"
#include <stdio.h>
#include <stdint.h>


void printHelp(const char * progName) {
	
	printf("Usage: %s [-c] [-d] [<value>]", progName);
}

int main(int argc, char ** argv) {
	options_t opt;

	int retval = options_parse(&opt, argc, argv);
	printf("%d %s\n", retval, opt.input);

	printHelp(argv[0]);
	return 0;
}

