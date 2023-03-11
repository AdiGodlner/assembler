/*
 * opcode.h
 *
 *  Created on: 9 Feb 2023
 *      Author: Adi
 */
#ifndef OPCODE_H_
#define OPCODE_H_

#include "set.h"
#include "HashTable.h"

typedef struct {

	String *name;
	int code;
	Set *binaryWord;
	int numOfParameters;
	Set *srcAddressing;
	Set *destAddressing;

} Opcode;

/*
 *
 */
Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr);
/*
 *
 */
void populateAddressingSet(Set **addressingPtr, char *addressingStr);

/*
 *
 */
Set* intToBinaryWord(int num);
/*
 *
 */
String* opcodeToString(Opcode *opcode);

/*
 *
 */
void initOpcode(HashTable *table);


#endif /* OPCODE_H_ */
