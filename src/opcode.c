/*
 * opcode.c
 *
 *  Created on: 9 Feb 2023
 *      Author: Adi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "opcode.h"
#include "HashTable.h"

#define OPCODE_LENGTH 4
#define MAX_ADDRESSING_LENGTH 4
#define OPCODE_START_INDEX 6

Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr) {

	Opcode *opcode;
	Set *srcAddressing = NULL, *destAddressing = NULL;
	Set **srcAddressingPtr = &srcAddressing;
	Set **destAddressingPtr = &destAddressing;

	opcode = malloc(sizeof(Opcode));

	populateAddressingSet(srcAddressingPtr, srcAddressingStr);
	populateAddressingSet(destAddressingPtr, destAddressingStr);

	opcode->name = createNewString(name);
	opcode->code = code; /* is the code variable really usefull? */
	opcode->numOfParameters = numOfParameters;
	opcode->srcAddressing = srcAddressing;
	opcode->destAddressing = destAddressing;

	return opcode;

}

/*TODO #define macros / numbers */

void writeAREToBinaryWord(Set *binaryWord, int are){

	writeToBinaryWord(binaryWord, are, 0, 2);

}
void writeDestToBinaryWord(Set *binaryWord, int dest){

	writeToBinaryWord(binaryWord, dest, 2, 2);

}
void writeSrcToBinaryWord(Set *binaryWord, int src){

	writeToBinaryWord(binaryWord, src, 4, 2);

}
void writeCodeToBinaryWord(Set *binaryWord, int code){

	writeToBinaryWord(binaryWord, code, OPCODE_START_INDEX, OPCODE_LENGTH);

}
void writeSecondOperandToBinaryWord(Set *binaryWord, int operand){

	writeToBinaryWord(binaryWord, operand, 10, 2);

}
void writeFirstOperandToBinaryWord(Set *binaryWord, int operand){

	writeToBinaryWord(binaryWord, operand, 12, 2);

}
void writeSrcRegiserToBinaryWord(Set *binaryWord, int reg){
	writeToBinaryWord(binaryWord, reg, 2, 6);

}
void writeDestRegiserToBinaryWord(Set *binaryWord, int reg){
	writeToBinaryWord(binaryWord, reg, 8, 6);

}

void writeToBinaryWord(Set *binaryWord, int decimal, int offset, int length){

	int i = 0;
	int temp;
	int opcodeBinary[length];

	for (i = 0; i < length; ++i) {

		temp = (decimal % 2);
		opcodeBinary[i] = temp ? (offset + i) : -1;
		decimal /= 2;

	}

	read_set(&binaryWord, opcodeBinary, length);

}


void populateAddressingSet(Set ** addressingPtr, char *addressingStr) {

	char *tok;
	int addressingArr[MAX_ADDRESSING_LENGTH ], i = 0;


	String * addressingStrCopy = createNewString(addressingStr);
	tok = strtok(addressingStrCopy->value, " ,");

	while (tok != NULL) {

		addressingArr[i] = atoi(tok);
		tok = strtok(NULL, " ,");
		i++;

	}

	read_set(addressingPtr, addressingArr, i);
	deleteString(addressingStrCopy);

}

/*TODO is this even needed */
Set * charToBinaryWord(char c){

	return intToBinaryWord(c);

}

Set* intToBinaryWord(int num){
	return intToBinaryWordWithOffset(num, 0);
}

Set* intToBinaryWordWithOffset(int num, int offset){

	int i =0;
	Set * set = createNewSet();
	/*TODO define 14 as a macro */
	for (i= 0; i < 14; ++i) {
		if (num & (1<<i)) {
			insertToSet(set, i +offset);
		}
	}

	return set;
}


void initOpcode(HashTable *table) {

	char *addres013 = "0,1,3";
	char *addres123 = "1,2,3";
	char *addres13 = "1,3";
	char *addres1 = "1";
	char *empty = "";

	Opcode *moveOpCode = createOpcode("mov", 0, 2, addres013, addres13);
	Opcode *cmpOpCode = createOpcode("cmp", 1, 2, addres013, addres013);
	Opcode *addOpCode = createOpcode("add", 2, 2, addres013, addres13);
	Opcode *subOpCode = createOpcode("sub", 3, 2, addres013, addres13);
	Opcode *notOpCode = createOpcode("not", 4, 1, empty, addres13);
	Opcode *clrOpCode = createOpcode("clr", 5, 1, empty, addres13);
	Opcode *leaOpCode = createOpcode("lea", 6, 2, addres1, addres13);
	Opcode *incOpCode = createOpcode("inc", 7, 1, empty, addres13);
	Opcode *decOpCode = createOpcode("dec", 8, 1, empty, addres13);
	Opcode *jmpOpCode = createOpcode("jmp", 9, 1, empty, addres123);
	Opcode *bneOpCode = createOpcode("bne", 10, 1, empty, addres123);
	Opcode *redOpCode = createOpcode("red", 11, 1, empty, addres13);
	Opcode *prnOpCode = createOpcode("prn", 12, 1, empty, addres013);
	Opcode *jsrOpCode = createOpcode("jsr", 13, 1, empty, addres123);
	Opcode *rtsOpCode = createOpcode("rts", 14, 0, empty, empty);
	Opcode *stopOpCode = createOpcode("stop", 15, 0, empty, empty);

	insertToTable(table, "mov", moveOpCode);
	insertToTable(table, "cmp", cmpOpCode);
	insertToTable(table, "add", addOpCode);
	insertToTable(table, "sub", subOpCode);
	insertToTable(table, "not", notOpCode);
	insertToTable(table, "clr", clrOpCode);
	insertToTable(table, "lea", leaOpCode);
	insertToTable(table, "inc", incOpCode);
	insertToTable(table, "dec", decOpCode);
	insertToTable(table, "jmp", jmpOpCode);
	insertToTable(table, "bne", bneOpCode);
	insertToTable(table, "red", redOpCode);
	insertToTable(table, "prn", prnOpCode);
	insertToTable(table, "jsr", jsrOpCode);
	insertToTable(table, "rts", rtsOpCode);
	insertToTable(table, "stop", stopOpCode);

}
