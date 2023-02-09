#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <sys/types.h>
struct LinkedList {
	struct LinkedListNode *head;
	struct LinkedListNode *tail;
	uint length;

};

struct LinkedListNode {
	void *body;
	struct LinkedListNode *next;
};


struct LinkedList *newLinkedList(); 
void addListNode(struct LinkedList *linkedList,  void *node);
void freeLinkedList(struct LinkedList *linkedlist);



#endif
