/*
 * assembly.c
 *
 *  Created on: 3 Mar 2023
 *      Author: Adi
 */

#include "HashTable.h"
#include "opcode.h"
#include "assembly.h"
#include "macro.h"
#include "Result.h"
#include "Label.h"
#include "Utils.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*TODO find all repeating macros and put them in one file with extern?*/
#define MAX_LINE_LEN 82/*adding two to max length, for new line and null charecter*/
#define MAX_LABEL_LENGTH 30/*TODO 30 or 31 adding one to max length, for null charecter*/

/*TODO change char *srcFile to char **srcFiles*/
void assemble(char *srcFile) {

	/*src file is .am file*/

	RESULT_TYPE resType;
	HashTable *symbolTable = createDefualtHashTable();
	Node *instructionBinarysList = NULL;
	Node *dataBinarysList = NULL;
	Node *entryList = NULL;

	resType = firstPassFileOpen(srcFile, symbolTable, instructionBinarysList,
			dataBinarysList, entryList);

	/*	TODO iterate over keys of symbol table add IC TO LABEL->ADRESS for labels of TYPE data */
	/*TODO check entry and extern dont overlap */
	if (resType) {
		/*first pass failed
		 TODO handle error ?? do not run secoundPass
		 */
		printf("\nERROR:First Pass has failed, can't move to second pass.\n");
//		return FIRST_PASS_FAILURE;
	} else {
		/* first pass sucsses :) */
		printf(
				"\nFIRST PASS - Was passed successfuly, moving over to second pass.\n");
	}

	foobar(entryList, symbolTable, srcFile);
//	TODO secoundPassAssembler();
	/* free heap meomory */
	deleteList(instructionBinarysList, deleteSet);
	deleteList(dataBinarysList, deleteSet);
	deleteTable(symbolTable, deleteString);

}

RESULT_TYPE foobar(Node *entryList, HashTable *symbolTable, char *srcFileName) {

	/*TODO write a function loop over entry list and write labels found in symbolTable to entry file
	 * if a label was not found delete the file and return failed RESULT_TYPE  */
//	String *temp = createEmptyString();
//	Node node = entryList;
//	while(node != NULL) {
//
//		String name = node->data;
//		Label *label = getValueByKey(symbolTable, name);
////	label ==NULL delete entry file and return error;
//		label->address;
//		//TODO turn addres to a char*
//		appendToString(name, addresChar);
//		// ""
//		// "loop 100\nfoo120
//		appendToString(temp, " addres\n");
//
//	}

	//write temp to file

	return SUCCESS;

}

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList) {

	RESULT_TYPE resType = SUCCESS;

	FILE *amFile = fopen(srcFile, "r");

	if (!amFile) {
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	/*firstPassAssembler actualy doing the passing*/
	resType = firstPassAssembler(amFile, symbolTable, instructionBinarysList,
			dataBinarysList, entryList);

	fclose(amFile);

	return resType;

}

RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList) {

	RESULT_TYPE lineProcesingResult = SUCCESS;
	RESULT_TYPE resType = SUCCESS;
	int lineNumber = 0;
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, amFile) != NULL) {

		lineNumber++;

		setStringValue(lineString, line);
		lineProcesingResult = lineFirstPass(lineString, symbolTable, instructionBinarysList,
				dataBinarysList, entryList);

		if (lineProcesingResult) {

			// TODO custom error messages for every resType
			printf("ERROR:   at line %d | resType %d \n", lineNumber, lineProcesingResult);

			if (resType == SUCCESS) {
				resType = lineProcesingResult;
			}

//			 break;/*TODO break?* should all errors in a file be printed and passed back up the chain*/
		}

	}

	deleteString(lineString);

	return lineProcesingResult;
}

RESULT_TYPE lineFirstPass(String *lineString, HashTable *labelTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList) {

	RESULT_TYPE resType = SUCCESS;
	int IC = 0, DC = 0;
	String *firstWord = popWord(lineString);

	if (isLabel(firstWord)) {

		resType = handleLabel(firstWord->value, labelTable, lineString,
				instructionBinarysList, dataBinarysList, entryList, &IC, &DC);
	} else {

		resType = handleNonLabel(firstWord->value, lineString, labelTable,
				instructionBinarysList, dataBinarysList, entryList, &IC, &DC);
		if (resType == ENTRY_CREATED || resType == EXTERN_CREATED) {
			resType = SUCCESS;
		}
	}

	deleteString(firstWord);

	return resType;

}

RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	int currDCAddres, currICAddres;
	String *firstWord;

	resType = checkLabelLegality(labelsTable, labelName);

	if (resType) {
		return resType;
	}

	currDCAddres = *DCPtr;
	currICAddres = *ICPtr;

	firstWord = popWord(line);

	resType = handleNonLabel(firstWord->value, line, labelsTable,
			instructionBinarysList, dataBinarysList, entryList, ICPtr, DCPtr);

	if (resType == SUCCESS) {
		if (currDCAddres != *DCPtr) {
			insertLabel(labelName, labelsTable, DATA, currDCAddres);
		} else {
			insertLabel(labelName, labelsTable, INSTRUCTION, currICAddres);
		}

	}

	deleteString(firstWord);

	if (resType == ENTRY_CREATED || resType == EXTERN_CREATED) {
		resType = SUCCESS;
	}

	return resType;

}

RESULT_TYPE handleNonLabel(char *word, String *line, HashTable *labelsTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	if (isData(word)) {

		resType = handleData(line, dataBinarysList, DCPtr);

	} else if (isStringData(word)) {

		resType = handleString(line, dataBinarysList, DCPtr);

	} else if (isExtern(word)) {

		resType = handleExtern(labelsTable, line);

	} else if (isEntry(word)) {
		resType = handleEntry(labelsTable, line, entryList);

	} else {

		/*TODO function that turns opcode to binary */
		/*TODO handle opcodes read string line and translate to opcode*/

	}

	return resType;
}

RESULT_TYPE handleData(String *line, Node *dataBinarysList, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;
	Set *binaryWord;
	Node *node;
	int size = 0, i = 0, currInt;
	int **intArrPtr;
	int *intArr = NULL;
	intArrPtr = &intArr;

	/* get intArrAllocates memory on the heap to intArr */
	resType = getIntArrfromStringArgs(line, intArrPtr, &size);

	if (resType) {
		return resType;
	}

	/* TODO handle intArr is empty || size == 0 meaning there were no arguments */
	for (i = 0; i < size; ++i) {

		currInt = intArr[i];
		binaryWord = intToBinaryWord(currInt);
		node = createNode(binaryWord, NULL);
		pushTail(node, &dataBinarysList);

	}

	free(intArr);
	*DCPtr += size;

	return resType;

}

RESULT_TYPE handleString(String *line, Node *dataBinarysList, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;
	int i = 1;
	String *quote;
	char *str;
	Set *binaryWord;
	Node *node;

	resType = checkStringIllegal(line->value);

	if (resType) {
		return resType;
	}

	quote = popWord(line);
	str = quote->value;

	while (str[i] != '"') {

		binaryWord = intToBinaryWord(str[i]);
		node = createNode(binaryWord, NULL);
		pushTail(node, &dataBinarysList);
		(*DCPtr)++;

	}

	binaryWord = intToBinaryWord('\0');
	node = createNode(binaryWord, NULL);
	pushTail(node, &dataBinarysList);
	(*DCPtr)++;

	deleteString(quote);

	return resType;

}

RESULT_TYPE handleExtern(HashTable *labelsTable, String *line) {

	RESULT_TYPE resType = EXTERN_CREATED;
	String *labelName = popWord(line);
	String *extraText;
	Label *label;

	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(labelsTable, labelName->value)) {
		label = (Label*) getValueByKey(labelsTable, labelName->value);

		if (label->type != EXTERNAL) {

			resType = LABEL_ALLREADY_EXISTS;
		}

	}

	extraText = popWord(line);

	if (extraText->size) {
		resType = EXTRANEOUS_TEXT;

	} else {
		label = createLabel(labelName->value);
		label->type = EXTERNAL;
		label->address = -1;
		insertToTable(labelsTable, labelName->value, label);

	}

	deleteString(labelName);
	deleteString(extraText);

	return resType;

}

RESULT_TYPE handleEntry(HashTable *labelsTable, String *line, Node *entryList) {

	RESULT_TYPE resType = ENTRY_CREATED;
	String *labelName = popWord(line);
	String *extraText;
	Label *label;
	Node *node;
	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(labelsTable, labelName->value)) {
		label = (Label*) getValueByKey(labelsTable, labelName->value);

		if (label->type == EXTERNAL) {

			resType = LABEL_EXTERNALY_EXISTS;
		}

	}

	extraText = popWord(line);

	if (extraText->size) {
		resType = EXTRANEOUS_TEXT;
		deleteString(labelName);

	} else {

		node = createNode(labelName, NULL);
		pushHead(node, &entryList);
	}

	deleteString(extraText);

	return resType;
}

void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type,
		int addres) {

	Label *label;
	label = createLabel(labelName);
	label->type = type;
	label->address = addres;
	insertToTable(labelsTable, labelName, label);

}

RESULT_TYPE checkLabelLegality(HashTable *labelsTable, char *labelName) {

	if (isKeyInTable(labelsTable, labelName)) {
		return LABEL_ALLREADY_EXISTS;
	}
	if (!isalpha(*labelName)) {
		return LABEL_ILLEGAL_DEFENITION;
	}
	if (strlen(labelName) >= MAX_LABEL_LENGTH) {
		return LABLE_INVALID_LENGTH;
	}

	return SUCCESS;

}

int isData(char *str) {
	return strcmp(str, ".data") == 0;
}

int isStringData(char *str) {
	return strcmp(str, ".string") == 0;
}
int isExtern(char *str) {
	return strcmp(str, ".extern") == 0;
}

int isEntry(char *str) {
	return strcmp(str, ".entry") == 0;
}

int isLabel(String *str) {
	return charAt(str, str->size - 1) == ':';

}

void secoundPassAssembly() {

	//TODO open extern file with w mode
	// A,R,E = 01
	// can have 2 extens with the same name

}

