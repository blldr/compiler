#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "lexer.h"


struct Lexer *newLexer(char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		perror("");
		exit(1);
	}

	struct Lexer *p = malloc(sizeof(struct Lexer));

	p->file = file;
	p->putback = 0;
	p->col = 1;
	p-> row = 1;
	return p;
}

static int getChar(struct Lexer *lexer) {
	int c;
	if (lexer->putback != 0) {
		c = lexer->putback;
		lexer->putback = 0;
		return c;
	}
	c = fgetc(lexer->file);
	lexer->col += 1;
	return c;
}

static void setPutback(struct Lexer *lexer, int c) {
	lexer->putback = c;
}

static void readStringLiteral(struct Lexer *lexer) {
	int quote_type = getChar(lexer);
	int c = getChar(lexer);
	for(int i = 0; c != quote_type && i < TOKENBUFFER_SIZE -1 && c != EOF && c != '\n'; i++) {
		lexer->tokenBuffer[i] = c;
		c = getChar(lexer);
	}
	if (c == EOF || c == '\n') {
		fprintf(stderr, "Invalid string literal at %d:%d\n", lexer->row, lexer->col);
		exit(1);
	}
	if (c != quote_type) {
		fprintf(stderr, "String literal too long at %d:%d\n", lexer->row, lexer->col);
		exit(1);
	}
	lexer->token.type = T_StringLiteral;
}

static void readNumericLiteral(struct Lexer *lexer) {
	int c = getChar(lexer);
	int i = 0;	
	for (; i < TOKENBUFFER_SIZE - 1 && (48 <= c && c <= 57); i++) {
		lexer->tokenBuffer[i] = c;
		c = getChar(lexer);
	}
	if (c == '.' ) {
		lexer->tokenBuffer[i] = '.';
		i += 1;
		c = getChar(lexer);
		for (; i < TOKENBUFFER_SIZE - 1 && (48 <= c && c <= 57); i++) {
			lexer->tokenBuffer[i] = c;
			c = getChar(lexer);
		}
		if (lexer->tokenBuffer[i] == '.' || c == '.') {
			fprintf(stdout, "Invalid numeric literal at %d:%d\n", lexer->row, lexer->col);
			exit(1);
		}
	}

	if (48 <= c && c <= 57) {
		fprintf(stdout, "Numeric literal too long at %d:%d\n", lexer->row, lexer->col);
		exit(1);
	} 
	setPutback(lexer, c);
	lexer->token.type = T_NumericLiteral;
	return;
	
}

static void readIdentifier(struct Lexer *lexer) {
	int c = getChar(lexer);
	for (int i = 0; i < TOKENBUFFER_SIZE - 1 && ( c == '_' || (c >= 97 && c<= 122) || (c >= 65 && c <= 90)); i++) {
		lexer->tokenBuffer[i] = c;
		c = getChar(lexer);
	}
	if (c == '_' || (c >= 97 && c<= 122) || (c >= 65 && c <= 90)) {
		fprintf(stdout, "Identifier too long at %d:%d\n", lexer->row, lexer->col);
		exit(1); 
	}
	setPutback(lexer, c);
	lexer->token.type = T_Identifier;
	return;
}

static void readSpecialSymbol(struct Lexer *lexer) {
	lexer->token.type = T_SpecialSymbol;
	lexer->tokenBuffer[0] = getChar(lexer);
}


void readToken(struct Lexer *lexer) {
	memset(lexer->tokenBuffer, '\0', TOKENBUFFER_SIZE);
	
	int c = getChar(lexer);
	switch(c) {
		case EOF:
			lexer->token.type = T_EOF;
			return;
		
		case '\n':
			lexer->row += 1;
			lexer->col = 0;
			readToken(lexer);
			return;

		case ' ':
			readToken(lexer);
			return;

		case '"':
		case '\'':
			setPutback(lexer, c);
			readStringLiteral(lexer);
			return;

		case 48 ... 57:
			setPutback(lexer, c);
			readNumericLiteral(lexer);
			return;

		case 97 ... 122:
		case 65 ... 90:
		case '_':
			setPutback(lexer, c);
			readIdentifier(lexer);
			return;

		case 37 ... 38:
		case 40 ... 47:
		case 58 ... 62:
		case 91 ... 93:
		case 123 ... 125:
			setPutback(lexer, c);
			readSpecialSymbol(lexer);
			return;
	}
	fprintf(stderr, "Unexpected symbol at %d:%d\n", lexer->row, lexer->col);
	exit(1);
}

