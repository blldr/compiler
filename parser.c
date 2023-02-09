#include <stdio.h>	
#include <stdlib.h>

#include "linkedlist.h"
#include "parser.h"
#include "lexer.h"


struct Parser *newParser(char *filename) {
	struct Parser *p = malloc(sizeof(struct Parser));
	struct Lexer *l = newLexer(filename);
	struct LinkedList *freeList = newLinkedList();
	p->lexer = l;
	p->freeList = freeList;
	p->head = newCompoundS(p);

	return p;
}

void freeParser(struct Parser *parser) {
	free(parser->lexer);
	freeLinkedList(parser->freeList);
	free(parser);
}



int parse() {
	return 1;	

}

struct AstNode *newCompoundS(struct Parser *parser) {
	struct AstNode *p = malloc(sizeof(struct AstNode));
	addListNode(parser->freeList, p);
	printf("length: %d, tail: %p, node: %p\n", parser->freeList->length, parser->freeList->tail->body, p);
	p->flag = S_compound;
	return p;
}

struct AstNode *newSelectionS(struct Parser *parser) {
	struct AstNode *p = malloc(sizeof(struct AstNode));
	addListNode(parser->freeList, p);
	p->flag = S_selection;
	return p;
}

struct AstNode *newIterationS(struct Parser *parser) {
	struct AstNode *p = malloc(sizeof(struct AstNode));
	addListNode(parser->freeList, p);
	p->flag = S_iteration;
	return p;
}

struct AstNode *newJumpS(struct Parser *parser, enum S_jumptype type) {
	struct AstNode *p = malloc(sizeof(struct AstNode));
	addListNode(parser->freeList, p);
	p->flag = S_jump;
	p->body.S_jump = type;
	return p;
}








