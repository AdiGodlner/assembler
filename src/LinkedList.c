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
#include "set.h"

#define MEM_ERR "failed to allocate memory"

void pushHead(Node *newNode, Node **listHeadPtr) {

	newNode->next = *listHeadPtr;
	*listHeadPtr = newNode;

}

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

Node* createNode(void *data,DATA_TYPE TYPE, Node *next) {

	Node *node = malloc(sizeof(Node));
	node->data = data;
	node->TYPE = TYPE;
	node->next = next;

	return node;

}

void deleteList(Node *head) {

	Node *nextNode;
	while (head) {

		nextNode = head->next;
		deleteNode(head);
		head = nextNode;

	}

}

void deleteNode(Node *node) {

	if (node->TYPE == SET) {
		deleteSet(node->data);
	}else if(node->TYPE == STRING) {
		deleteString(node->data);
	}

	free(node);

}
