#include <stdlib.h>
#include <stdio.h>

#include "linkedlist.h"

struct LinkedList *newLinkedList() {
	struct LinkedList *p = malloc(sizeof(struct LinkedList)); 
	p->head = NULL;
	p->tail = NULL;
	p->length = 0;

	return p;
}

void addListNode(struct LinkedList *linkedList,  void *node) {
	struct LinkedListNode *p = malloc(sizeof(struct LinkedListNode));
	p->body = node;
	p->next = NULL;
	if (linkedList->head == NULL) {
		linkedList->head = p;
		linkedList->tail = p;
		linkedList->length = 1;
		return;
	}
	linkedList->tail->next = p;
	linkedList->tail = p;
	linkedList->length++;
	return;
}

void freeLinkedList(struct LinkedList *linkedlist) {
	struct LinkedListNode *node = linkedlist->head;
	struct LinkedListNode *next;
	while(node != NULL) {
		printf("cleaning: %p\n", node);
		next = node->next;
		free(node->body);
		free(node);
		node = next;
	}
	free(linkedlist);
}

