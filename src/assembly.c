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
void assembler(char *srcFile) {

	/*src file is .am file*/

	RESULT_TYPE resType;
	HashTable *symbolTable = createDefualtHashTable();
	Node *instructionBinarysList = NULL;
	Node *dataBinarysList = NULL;
	Node *entryList = NULL;
	Node **entryListPtr = &entryList;

	resType = firstPassFileOpen(srcFile, symbolTable, instructionBinarysList,
			dataBinarysList, entryListPtr);

	printTable(symbolTable, labelToString);
	/*	TODO iterate over keys of symbol table add IC TO LABEL->ADRESS for labels of TYPE data */

	if (entryList != NULL) {
		writeEntryToFile(srcFile, entryList, symbolTable);
	}

	if (resType) {
		/*first pass failed
		 TODO handle error do not run secoundPass
		 */
		printf("\nERROR:First Pass has failed, can't move to second pass.\n");
//		return FIRST_PASS_FAILURE;
	} else {
		/* first pass sucsses :) */
		printf(
				"\nFIRST PASS - Was passed successfuly, moving over to second pass.\n");
	}

	//	TODO secoundPassAssembler();
	/* free heap meomory */
	deleteList(instructionBinarysList, deleteSet);
	deleteList(dataBinarysList, deleteSet);
	deleteTable(symbolTable, deleteString);

}

RESULT_TYPE writeEntryToFile(char *srcFile, Node *entryList,
		HashTable *symbolTable) {

	RESULT_TYPE resType = SUCCESS;
	char *entSuffix = ".ent";
	String *destFile = filenameChange(srcFile, entSuffix);
	FILE *entFile = fopen(destFile->value, "w");

	if (!entFile) {
		return FILE_NOT_FOUND;

	}
	Node *node = entryList;

	while (node != NULL) {

		String *name = (String*) node->data;
		Label *label = (Label*) getValueByKey(symbolTable, name->value);

		if (label == NULL) {
			resType = UNDEFINED_ENTRY_LABLE;
			break;
		}

		int labelAddress = label->address;
		// only labels of type extern have address of -1;
		if (labelAddress < 0) {

			resType = LABEL_IS_EXTERN_AND_ENTRY;
			break;

		}
		char addrStr[4];/*3 digit address + \0*/
		sprintf(addrStr, "%03d", labelAddress);/*Printing to file in the requested format*/
		addrStr[3] = '\0';
		fprintf(entFile, "%s\t%s\n", name->value, addrStr);/*LABLE    100*/

		node = node->next;/*moving to next entry lable in list*/

	}

	/*closing file after use*/
	fclose(entFile);

	/*If an error occurred ,delete the file */
	if (resType) {
		remove(destFile->value);
	}

	deleteString(destFile);

	return resType;

}

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr) {

	RESULT_TYPE resType = SUCCESS;

	FILE *amFile = fopen(srcFile, "r");

	if (!amFile) {
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	/*firstPassAssembler actualy doing the passing*/
	resType = firstPassAssembler(amFile, symbolTable, instructionBinarysList,
			dataBinarysList, entryListPtr);

	fclose(amFile);

	return resType;

}

RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr) {

	int IC = 0, DC = 0;
	RESULT_TYPE lineProcesingResult = SUCCESS;
	RESULT_TYPE resType = SUCCESS;
	int lineNumber = 0;
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, amFile) != NULL) {

		lineNumber++;

		setStringValue(lineString, line);
		lineProcesingResult = lineFirstPass(lineString, symbolTable,
				instructionBinarysList, dataBinarysList, entryListPtr, &IC,
				&DC);

		if (lineProcesingResult) {

			// TODO custom error messages for every resType
			// TODO print all errors here
			printf("ERROR:   at line %d | resType %d \n", lineNumber,
					lineProcesingResult);

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
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	String *firstWord = popWord(lineString);

	if (isLabel(firstWord)) {

		resType = handleLabel(firstWord->value, labelTable, lineString,
				instructionBinarysList, dataBinarysList, entryListPtr, ICPtr,
				DCPtr);
	} else {

		resType = handleNonLabel(firstWord->value, lineString, labelTable,
				instructionBinarysList, dataBinarysList, entryListPtr, ICPtr,
				DCPtr);
		if (resType == ENTRY_CREATED || resType == EXTERN_CREATED) {
			resType = SUCCESS;
		}
	}

	deleteString(firstWord);

	return resType;

}

RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	int currDCAddres, currICAddres;
	String *firstWord;

	labelName[strlen(labelName) - 1] = '\0';
	if (isKeyInTable(labelsTable, labelName)) {
		return LABEL_ALLREADY_EXISTS;
	}

	resType = checkLabelLegality(labelName);

	if (resType) {
		return resType;
	}

	currDCAddres = *DCPtr;
	currICAddres = *ICPtr;

	firstWord = popWord(line);

	resType = handleNonLabel(firstWord->value, line, labelsTable,
			instructionBinarysList, dataBinarysList, entryListPtr, ICPtr,
			DCPtr);

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
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	if (isData(word)) {
		resType = handleData(line, dataBinarysList, DCPtr);

	} else if (isStringData(word)) {

		resType = handleString(line, dataBinarysList, DCPtr);

	} else if (isExtern(word)) {

		resType = handleExtern(labelsTable, line);

	} else if (isEntry(word)) {
		resType = handleEntry(labelsTable, line, entryListPtr);

	} else {

		resType = handleInstructions(word, line, instructionBinarysList, ICPtr);

	}

	return resType;
}

RESULT_TYPE handleInstructions(char *word, String *line,
		Node *instructionBinarysList, int *ICPtr) {

	static HashTable *opCodeTable = NULL;
	RESULT_TYPE resType = SUCCESS;
	Opcode *opCode = NULL;

	if (!opCodeTable) {
		opCodeTable = createDefualtHashTable();
		initOpcode(opCodeTable);
	}
	if (!isKeyInTable(opCodeTable, word)) {
		return ILLEGAL_OPCODE;
	}

	opCode = (Opcode*) getValueByKey(opCodeTable, word);

	//check if opcode is jmp jsr or bne
	if (isValueInSet(opCode->destAddressing, 2)) {
		//TODO handle jsr jmp and bne
//TODO change name of function
//		handleComplexOpcode();
	} else {
		resType = handleSimpleOpcode(line, opCode, instructionBinarysList,
				ICPtr);

	}

	return resType;
}

//TODO change name of function
RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node *instructionBinarysList, int *ICPtr) {

	int i = 0, j = 0, isAddresingTypeValid = -1, isSrcParam = -1,
			isSrcRegister = -1;
	RESULT_TYPE resType = SUCCESS;
	int addresingType = -1;
	String *currParam;
	Set **paramArr = NULL;
	Set *opCodebinaryWord = NULL;
	Set *parambinaryWord = NULL;
	Node *newNode;

	opCodebinaryWord = createNewSet();
	writeCodeToBinaryWord(opCodebinaryWord, opCode->code);

	paramArr = malloc(sizeof(String*) * opCode->numOfParameters);

	for (i = 0; i < opCode->numOfParameters; i++) {

		resType = popArgument(line, currParam,
				i == (opCode->numOfParameters - 1));

		if (resType) {
			break;
		}

		if (!isInstructionParamValid(currParam)) {
			resType = ILLEGAL_PARAM;
			break;
		}

		addresingType = getParamAddresingType(currParam);
		isSrcParam = (opCode->numOfParameters == 2 && i == 0);
		// check if its a src parameter or dest parameter
		if (isSrcParam) {
			//check if parameter type is allowed
			isAddresingTypeValid = isValueInSet(opCode->srcAddressing,
					addresingType);
		} else {
			//check if parameter type is allowed
			isAddresingTypeValid = isValueInSet(opCode->destAddressing,
					addresingType);
		}

		if (!isAddresingTypeValid) {
			resType = ILLEGAL_ADDRESSTYPE;
			break;
		}

		//write address to opCodeBinary
		if (isSrcParam) {

			isSrcRegister = addresingType == 3;
			parambinaryWord = createParamBinaryWord(currParam, addresingType);
			paramArr[i] = parambinaryWord;
			writeSrcToBinaryWord(opCodebinaryWord, addresingType);

		} else {
			if (isSrcRegister && addresingType == 3) {

				writeDestRegiserToBinaryWord(paramArr[i],
						atoi(currParam->value + 1));

			} else {

				parambinaryWord = createParamBinaryWord(currParam,
						addresingType);

				paramArr[i] = parambinaryWord;
			}

			writeDestToBinaryWord(opCodebinaryWord, addresingType);

		}

	}

	//TODO check for EXTRANEOUS_TEXT

	if (resType) {
		//TODO handle erros
		return resType;
	}

	newNode = createNode(opCodebinaryWord, NULL);
	pushTail(newNode, &instructionBinarysList);

	for (j = 0; j < i; ++j) {
		newNode = createNode(paramArr[j], NULL);
		pushTail(newNode, &instructionBinarysList);
	}

	(*ICPtr) += 1 + i;
	free(paramArr);

	return resType;

}

Set* createParamBinaryWord(String *param, int addresingType) {

	Set *parambinaryWord;
	int num;
	if (addresingType == 3) {
		parambinaryWord = createNewSet();
		num = atoi(param->value + 1);
		writeSrcRegiserToBinaryWord(parambinaryWord, num);
		return parambinaryWord;

	} else if (addresingType == 2) {
		//TODO handle jmo and jsr
		return NULL;

	} else if (addresingType == 0) {
		num = atoi(param->value);
		parambinaryWord = intToBinaryWordWithOffset(num, 2);
		return parambinaryWord;

	} else {
		// addresingType == 1
		return NULL;

	}

}

int getParamAddresingType(String *param) {

	if (param->value[0] == '#') {
		return 0;
	} else if (param->size == 2 && param->value[0] == 'r'
			&& param->value[1] - '0' >= 0 && param->value[1] - '0' < 8) {
		return 3;

	} else {
		return 2;
	}

}

int isInstructionParamValid(String *param) {

	int *ignore = NULL;
	if (param->value[0] == '#') {
		if (getIntFromName((param->value) + 1, ignore) == SUCCESS) {
			return 1;
		}

	} else if (checkLabelLegality(param->value) == SUCCESS) {

		return 1;
	}

	return 0;
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

	for (i = 0; i < size; ++i) {

		currInt = intArr[i];
		binaryWord = intToBinaryWord(currInt);
		node = createNode(binaryWord, NULL);
		pushTail(node, &dataBinarysList);

	}

	free(intArr);
	(*DCPtr) += size;

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

	resType = checkLabelLegality(labelName->value);
	if (resType) {
		deleteString(labelName);
		return resType;
	}

	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(labelsTable, labelName->value)) {
		label = (Label*) getValueByKey(labelsTable, labelName->value);

		if (label->type != EXTERNAL) {

			resType = LABEL_ALLREADY_EXISTS;
			deleteString(labelName);
			return resType;
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

RESULT_TYPE handleEntry(HashTable *labelsTable, String *line,
		Node **entryListPtr) {

	RESULT_TYPE resType = ENTRY_CREATED;
	String *labelName = popWord(line);
	String *extraText;
	Label *label;
	Node *node;

	resType = checkLabelLegality(labelName->value);
	if (resType) {
		deleteString(labelName);
		return resType;
	}

	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(labelsTable, labelName->value)) {
		label = (Label*) getValueByKey(labelsTable, labelName->value);

		if (label->type == EXTERNAL) {

			resType = LABEL_EXTERNALY_EXISTS;
			deleteString(labelName);
			return resType;
		}

	}

	extraText = popWord(line);

	if (extraText->size) {
		resType = EXTRANEOUS_TEXT;
		deleteString(labelName);

	} else {

		node = createNode(labelName, NULL);
		pushHead(node, entryListPtr);
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

RESULT_TYPE checkLabelLegality(char *labelName) {

	//TODO check that label is not a reserved words like jmp or bne like we did in macro
	int i = 0;

	if (!isalpha(*labelName)) {
		return LABEL_ILLEGAL_DEFENITION;
	}
	for (i = 1; i < strlen(labelName); ++i) {
		if (!isalnum(labelName[i])) {
			return LABEL_ILLEGAL_DEFENITION;
		}

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

