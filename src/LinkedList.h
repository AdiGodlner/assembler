/*
 * LinkedList.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include "String.h"

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef enum {

	SET, STRING, ENTRY

} DATA_TYPE;

typedef struct Node {

	void *data;
	DATA_TYPE TYPE;
	struct Node *next;

} Node;

/*
 *
 */
void pushHead(Node *newNode, Node **listHeadPtr);

/*
 *
 */
void pushTail(Node *newNode, Node **listHeadPtr);

/*
 *
 */
Node* createNode(void *data, DATA_TYPE TYPE, Node *next);

/*
 *
 */
void deleteList(Node *head);
/*
 *
 */
void deleteNode(Node *node);

#endif /* LINKEDLIST_H_ */
