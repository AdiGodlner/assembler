/*
 * LinkedList.c
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "String.h"

#define MEM_ERR "failed to allocate memory"

void pushHead(Node *newNode, Node **listHeadPtr) {

	newNode->next = *listHeadPtr;
	*listHeadPtr = newNode;

}

//TODO fix this ??
//void pushTailOLD(Node *newNode, Node **listHeadPtr) {
//
//	if (*listHeadPtr == NULL) {
//		*listHeadPtr = newNode;
//		return;
//	}
//
//	while ((*listHeadPtr)->next != NULL) {
//		*listHeadPtr = (*listHeadPtr)->next;
//	}
//
//	(*listHeadPtr)->next = newNode;
//
//}

void pushTail(Node *newNode, Node **headPtr ) {

	Node *last = *headPtr;

	if (*headPtr == NULL) {
		*headPtr = newNode;
		return;
	}

	while (last->next != NULL) {
		last = last->next;
	}

	last->next = newNode;

	return;
}

Node* createNode(void *data, Node *next) {

	Node *node = malloc(sizeof(Node));

	if (node == NULL) {
		printf(MEM_ERR);
		return NULL;
	}

	node->data = data;
	node->next = next;

	return node;

}

void deleteList(Node *head, void (*deleteDataFunc)(void*)) {

	Node *nextNode;
	while (head) {

		nextNode = head->next;
		deleteNode(head, deleteDataFunc);
		head = nextNode;

	}

}

void deleteNode(Node *node, void (*deleteDataFunc)(void*)) {

	deleteDataFunc(node->data);
	free(node);

}
