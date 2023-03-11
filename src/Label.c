/*
 * Label.c
 *
 *  Created on: 5 Mar 2023
 *      Author: Adi
 */

#include "Label.h"
#include "String.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>

Label * createLabel(char* name){

 Label * label = malloc(sizeof (Label));
 label->name = createNewString(name);
 label->size = 0;

 return label;

}

String* labelToString(void * label){

	String * str = createNewString(((Label*) label)->name->value);
	return str;
}

void deleteLabel(Label *label){

	deleteString(label->name);
	free(label);

}
