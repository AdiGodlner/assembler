/*
 * Label.c
 *
 *  Created on: 5 Mar 2023
 *      Author: Adi
 */

#include "Label.h"
#include "String.h"
#include "Set.h"
#include <stdio.h>
#include <stdlib.h>

Label * createLabel(char* name){

 Label * label = malloc(sizeof (Label));
 label->name = createNewString(name);
// label->binaryWordList = NULL;
 label->size = 0;

 return label;

}

//void insertBinaryWord(Label *label, Set * binaryWord){
//
//	Node * newNode = createNode(binaryWord, NULL);
//	pushHead(newNode, &(label->binaryWordList));
//
//}

void deleteLabel(Label *label){

	deleteString(label->name);
	//TODO delete linked list binaryWordList
	free(label);

}
