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
	opcode->code = code; // is the code variable really usefull?
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

//TODO is this even needed
Set * charToBinaryWord(char c){

	return intToBinaryWord(c);

}

Set* intToBinaryWord(int num){

	int i =0;
	Set * set = createNewSet();
	//TODO define 14 as a macro
	for (i= 0; i < 14; ++i) {
		if (num & (1<<i)) {
			insertToSet(set, i);
		}
	}

	return set;
}


String * opcodeToString(Opcode * opcode){

	//TODO maybe change the String it returns to better represent opcode not really important
	//TODO or maybe change the String it returns the end output required by the secound pass

	return setToBinaryString(opcode->binaryWord);


}

