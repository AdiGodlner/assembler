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

	SET, STRING

} DATA_TYPE;

typedef struct Node{

	void * data;
	DATA_TYPE TYPE;
	struct Node * next;

} Node;

/*
 *
 */
void pushHead(Node * newNode, Node ** listHeadPtr );

/*
 *
 */
void pushTail(Node * newNode, Node ** listHeadPtr );

/*
 *
 */

Node * createNode(void * data, Node * next);

/*
 *
 */
void deleteList(Node * head,void (*deleteDataFunc)(void*));
/*
 *
 */
void deleteNode(Node * node, void (*deleteDataFunc)(void*));




#endif /* LINKEDLIST_H_ */
