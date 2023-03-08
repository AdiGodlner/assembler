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



void pushHead(Node * newNode, Node ** listHeadPtr ){

	newNode->next = *listHeadPtr;
	*listHeadPtr = newNode;

}

void pushTail(Node * newNode, Node ** listHeadPtr ){

	if (*listHeadPtr == NULL) {
		*listHeadPtr = newNode;
			return;
	}

	while((*listHeadPtr)->next !=NULL){
		*listHeadPtr = (*listHeadPtr)->next;
	}

	(*listHeadPtr)->next = newNode;

}
Node * createNode(void * data,  Node * next){

	Node * node = malloc(sizeof(Node));

	if (node == NULL) {
		printf(MEM_ERR);
		return NULL;
	}

	node->data = data;
	node->next = next;

	return node;

}
//TODO if recursively is to much we can do this in a for loop
void deleteNodeRecursive(Node * node, void (*deleteDataFunc)(void*)){


	if (node != NULL && node->next != NULL) {
		deleteNodeRecursive((Node*)node->next,deleteDataFunc);
	}

	deleteNode(node,deleteDataFunc);
}


void deleteNode(Node * node, void (*deleteDataFunc)(void*)){

	deleteDataFunc(node->data);
	free(node);

}
