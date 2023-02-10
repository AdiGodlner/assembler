/*
 * LinkedList.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include "String.h"

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


typedef struct Node{

	void * data;
	struct Node * next;

} Node;

/*
 *
 */
void pushHead(Node * newNode, Node ** listHead );

/*
 *
 */

Node * createNode(void * data, Node * next);
/*
 *
 */
void deleteNodeRecursive(Node * node);

/*
 *
 */
void deleteNode(Node * node);




#endif /* LINKEDLIST_H_ */
