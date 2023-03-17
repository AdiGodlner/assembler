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
	int numOfParameters;
	Set *srcAddressing;
	Set *destAddressing;

} Opcode;

/*
 *
 */
Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr);

void writeAREToBinaryWord(Set *binaryWord, int are);
void writeDestToBinaryWord(Set *binaryWord, int dest);
void writeSrcToBinaryWord(Set *binaryWord, int src);
void writeCodeToBinaryWord(Set *binaryWord, int code);
void writeSecondOperandToBinaryWord(Set *binaryWord, int operand);
void writeFirstOperandToBinaryWord(Set *binaryWord, int operand);
void writeSrcRegiserToBinaryWord(Set *binaryWord, int reg);
void writeDestRegiserToBinaryWord(Set *binaryWord, int reg);

/*
 *
 */
void writeToBinaryWord(Set *binaryWord, int decimal, int offset, int length);
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
Set* intToBinaryWordWithOffset(int num, int offset);

/*
 *
 */
void initOpcode(HashTable *table);


#endif /* OPCODE_H_ */
