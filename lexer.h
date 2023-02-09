#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

#define TOKENBUFFER_SIZE 64

struct Token{
	enum {
		T_Identifier, T_NumericLiteral, T_StringLiteral, T_SpecialSymbol, T_EOF
	} type;
} ;


struct Lexer {
	FILE *file;
	struct Token token;
	char tokenBuffer[TOKENBUFFER_SIZE];
	int putback;
	int col;
	int row;
};

// Function prototypes
void readToken(struct Lexer *lexer);
struct Lexer *newLexer(char *filename);
 
#endif
