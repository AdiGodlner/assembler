/*
 * symbol.h
 *
 *  Created on: 4 Mar 2023
 *      Author: Adi
 */

#ifndef LABEL_H_
#define LABEL_H_

#include "LinkedList.h"
#include "set.h"

/*Definition of Label and of Label Type*/
typedef enum {

	DATA, INSTRUCTION,EXTERNAL

}LABEL_TYPE;

typedef struct {

	String * name;/*TODO remove if not used */
	LABEL_TYPE type;
	int address;
	int size;/*TODO remove if not used*/

} Label;


/*
 *
 */
String* labelToString(void * label);

/*
 * This method frees the allocated memory fro heap
 * @param label - the given label that need to be freed.
 */
void deleteLabel(void *label);
/*
 * This method allocates dynamic memory from heap to create a lable.
 * @param name - the label given name.
 * @return  - returns new Label.
 */
Label * createLabel(char* name);
/*
 *TODO ?? DO WE USE THIS FUNC
 */
void insertBinaryWord(Label *label, Set * binaryWord);



#endif /* LABEL_H_ */
