#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parser.h"
#include "lexer.h"


int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Input filename");
		exit(1);
	}

	
	struct Parser *parser = newParser(argv[1]);
	
		

	freeParser(parser);
	return 0;
}	
