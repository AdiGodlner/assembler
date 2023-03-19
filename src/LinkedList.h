/*
 * LinkedList.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include "String.h"

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*Node definition*/
typedef enum {

	SET, STRING, ENTRY

} DATA_TYPE;

typedef struct Node {

	void *data;
	DATA_TYPE TYPE;
	struct Node *next;

} Node;

/*
 * This method insert from head the new node.
 * @param newNode - the node that needs to be added to the list.
 * @param listHeadPtr - the head pointer, pointes where the next node goes.
 */
void pushHead(Node *newNode, Node **listHeadPtr);

/*
 * This method insert from tail the new node.
 * @param newNode - the node that needs to be added to the list.
 * @param listHeadPtr - the tail pointer, pointes where the next node goes.
 */
void pushTail(Node *newNode, Node **listHeadPtr);

/*
 * This method create a node with dynamicly memory allocation.
 * @param data -
 * @param TYPE - the type of the node.
 * @param next - pointes to the next node in list.
 * @return - returns new node.
 */
Node* createNode(void *data, DATA_TYPE TYPE, Node *next);

/*
 * This method delete the head node from the list.
 * @param head - the head pointer, it's set to point to the next node.
 */
void deleteList(Node *head);
/*
 * This method free the dynamicly allocated memory from heap.
 * @param node - the node that need to be freed.
 */
void deleteNode(Node *node);

#endif /* LINKEDLIST_H_ */
