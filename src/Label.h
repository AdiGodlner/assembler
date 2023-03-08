/*
 * symbol.h
 *
 *  Created on: 4 Mar 2023
 *      Author: Adi
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "LinkedList.h"
#include "Set.h"

typedef enum {

	DATA, INSTRUCTION,EXTERNAL

}LABEL_TYPE;

typedef struct {

	String * name;//TODO remove if not used
	LABEL_TYPE type;
	int address;
	int size;//TODO remove if not used

} Label;


/*
 *
 */
void deleteLabel(Label *label);
/*
 *
 */
Label * createLabel(char* name);
/*
 *
 */
void insertBinaryWord(Label *label, Set * binaryWord);


#endif /* LABEL_H_ */