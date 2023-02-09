#ifndef PARSER_H
#define PARSER_H

#include "linkedlist.h"
#define STRINGLIT_WIDTH 64
#define IDENTIFIER_WIDTH 32
#define ARGUMENTS_WIDTH 16

struct Parser {
	struct Lexer *lexer;
	struct AstNode *head;
	struct LinkedList *freeList;
};

enum S_jumptype { S_break, S_continue, S_return };

struct AstNode {
	/*
	* Enum prefix types:
	*	S -> Statement
	*	E -> Expression
	*	B -> Binarydiv
	*	O -> Operator
	*/
	enum {
		S_compound, S_selection, S_iteration, S_jump,
		E_stringlit, E_numeric, E_call, EB_assignment, EB_arithmetic, EB_relational, EB_logical
	} flag;
	union {
		// Statements
		struct { struct AstNode *node; struct AstNode *next; } S_compound;
		struct { struct AstNode *condition; struct AstNode *first; struct AstNode *second; } S_selection;
		struct { struct AstNode *condition; struct AstNode *body; } S_iteration;
		enum S_jumptype  S_jump;
		
		// Expressions
		char E_stringlit[STRINGLIT_WIDTH];
		// struct {  } E_numeric;
		struct { char idfname[IDENTIFIER_WIDTH]; struct AstNode *args[ARGUMENTS_WIDTH]; } E_call;
		struct { char idfname[IDENTIFIER_WIDTH]; struct AstNode *value; } EB_assignment;
		struct { enum { O_add, O_sub, O_multpl, O_div } op; struct AstNode *op1; struct AstNode *op2; } EB_arithmetic;
		struct { enum { O_eq, O_noteq, O_less, O_grt, O_lesseqq, O_grteqq } op; struct AstNode *op1; struct AstNode *op2; } EB_relational;
		struct { enum { O_And, O_Or } op; struct AstNode *op1; struct AstNode *op2; } EB_logical;
	} body;
};

struct Parser *newParser(char *filename);
void freeParser(struct Parser *parser);

struct AstNode *newCompoundS(struct Parser *parser); 
struct AstNode *newSelectionS(struct Parser *parser);
struct AstNode *newIterationS(struct Parser *parser);
struct AstNode *newJumpS(struct Parser *parser, enum S_jumptype type);
struct AstNode *newStringlitE(struct Parser *parser, char *buffer); 






#endif

