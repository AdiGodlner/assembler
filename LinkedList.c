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

void pushHead(Node * newNode, Node ** listHead ){

	newNode->next = *listHead;
	*listHead = newNode;

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

void deleteNodeRecursive(Node * node){


	if (node != NULL && node->next != NULL) {
		deleteNodeRecursive((Node*)node->next);
	}

	deleteNode(node);
}


void deleteNode(Node * node){

	free(node->data);
	free(node);

}
