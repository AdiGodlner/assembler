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
#define OPCODE_START_INDEX 5

Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr) {

	int opcodeBinary[OPCODE_LENGTH];
	int i = 0, temp;
	Opcode *opcode;
	Set *binaryWord = NULL, *srcAddressing = NULL, *destAddressing = NULL;
	Set **binaryWordPtr = &binaryWord;
	Set **srcAddressingPtr = &srcAddressing;
	Set **destAddressingPtr = &destAddressing;

	opcode = malloc(sizeof(Opcode));

	if (opcode == NULL) {
		printf("memm prob create opcode TODO fix later");
	}

	for (i = 0; i < OPCODE_LENGTH; ++i) {
		temp = (code % 2);
		opcodeBinary[i] = temp ? (OPCODE_START_INDEX + i) : -1;
		code /= 2;

	}

	read_set(binaryWordPtr, opcodeBinary, OPCODE_LENGTH);

	populateAddressingSet(srcAddressingPtr, srcAddressingStr);
	populateAddressingSet(destAddressingPtr, destAddressingStr);

	opcode->name = createNewString(name);
	opcode->code = code; /* is the code variable really usefull? */
	opcode->numOfParameters = numOfParameters;
	opcode->binaryWord = binaryWord;
	opcode->srcAddressing = srcAddressing;
	opcode->destAddressing = destAddressing;

	return opcode;

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

	int i =0;
	Set * set = createNewSet();
	/*TODO define 14 as a macro */
	for (i= 0; i < 14; ++i) {
		if (num & (1<<i)) {
			insertToSet(set, i);
		}
	}

	return set;
}


String * opcodeToString(Opcode * opcode){

	/*TODO maybe change the String it returns to better represent opcode not really important*/
	/*TODO or maybe change the String it returns the end output required by the secound pass */

	return setToBinaryString(opcode->binaryWord);


}


void initOpcode(HashTable *table) {

	char *addres013 = "0,1,3";
	char *addres123 = "1,2,3";
	char *addres13 = "1,3";
	char *addres1 = "1";
	char *empty = "";

	Opcode *moveOpCode = createOpcode("move", 0, 2, addres013, addres13);
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

	insertToTable(table, "move", moveOpCode);
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
