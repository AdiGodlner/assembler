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
#include "macro.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


//TODO find all repeating macros and put them in one file with extern?
#define MAX_LINE_LEN 82/*adding two to max length, for new line and null charecter*/
#define MAX_LABEL_LENGTH 31/*adding one to max length, for null charecter*/

//TODO change char *srcFile to char **srcFiles
RESULT_TYPE assembler(char *srcFile) {

	//src file is .am file

	RESULT_TYPE resType;
	HashTable *symbolTable = createDefualtHashTable();
	Node *instructionBinarysList = NULL;
	Node *dataBinarysList = NULL;
	Node *entryList = NULL;//TODO add this to fisrtPassFileOpen and all functions down the line

	resType = firstPassFileOpen(srcFile, symbolTable, instructionBinarysList,
			dataBinarysList,entryList);

	//TODO loop over entry list and write labels found in symbolTable to entry file
	//TODO check entry and extern dont overlap
	if (resType) {
		//first pass failed
//		return resType; // TODO handle error ?? do not run secoundPass
		perror("\nERROR:First Pass has failed, can't move to second pass.\n");
		return FIRST_PASS_FAILURE;
	}else{
		pritnf("\nFIRST PASS - Was passed successfuly, moving over to second pass.\n");
		return SUCCESS;
	}
//TODO call secound pass
	secoundPassAssembler();

	/* free heap meomory */
	deleteList(instructionBinarysList, deleteSet);
	deleteList(dataBinarysList, deleteSet);
	deleteTable(symbolTable, deleteString);

}

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList,Node *entryList) {

	RESULT_TYPE resType = SUCCESS;

	FILE *amFile = fopen(srcFile, "r");/*Opening in reading mode, for the first pass*/

	if (!amFile) {
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	//firstPassAssembler actually doing the passing
	resType = firstPassAssembler(amFile, symbolTable, instructionBinarysList, dataBinarysList,entryList);

	fclose(amFile);

//	TODO iterate over keys of symbol table add IC TO LABEL->ADRESS for labels of TYPE data
	return resType;

}

RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node* entryList) {

	RESULT_TYPE resType = SUCCESS;
	int lineNumber = 1;
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, amFile) != NULL) {

		//line number is supposed to be used for error printing

		lineNumber++;

		setStringValue(lineString, line);
		resType = lineFirstPass(lineString, symbolTable, instructionBinarysList,
				dataBinarysList, entryList);

		if (resType) {
			//TODO print ERRORS with line number perror("");
			fprintf("ERROR:   at line %d\n", __LINE__);
			break;
		}

	}

	deleteString(lineString);

	return resType;
}

RESULT_TYPE lineFirstPass(String *lineString, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node * entryList) {

	RESULT_TYPE resType = SUCCESS;
	int IC = 0, DC = 0;
	String *firstWord = popWord(lineString);

	if (isLabel(firstWord)) {
		/*Handele the lable part, and insert it to the lable table after checking that lable is valid*/
		resType = handleLabel(firstWord->value, symbolTable, lineString,
				instructionBinarysList, dataBinarysList,entryList, &IC, &DC);
	} else {

		/*Passing the non lable part to the function, to check if the parameters after it are valid */
		resType = handleNonLabel(firstWord->value, lineString,
				instructionBinarysList, dataBinarysList,entryList, &IC, &DC);
	}

	deleteString(firstWord);

	return resType;

}
/*Handele the lable part, and insert it to the lable table after checking that lable is valid*/
RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList,Node * entryList, int *ICPtr,
		int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	int currDCAddres, currICAddres;
	String *firstWord;

	//TODO check label is legal ( length < max length && starts with a letter )
	if (isKeyInTable(labelsTable, labelName)) {

			//TODO handle error?
		return LABEL_ALLREADY_EXISTS;

	}
	if(!isalpha(labelName)){

		return LABEL_ILLEGAL_DEFENITION;
	}
	if(strlen(labelName)>= MAX_LABEL_LENGTH){

		return LABLE_INVALID_LENGTH;
	}
	return resType;







	currDCAddres = *DCPtr;
	currICAddres = *ICPtr;

	firstWord = popWord(line);

	//TODO if handleNonLabel line is extern skip
	resType = handleNonLabel(firstWord->value, line, instructionBinarysList,
			dataBinarysList,entryList, ICPtr, DCPtr);

	if (!resType) {
		//TODO check if there are other types of labels
		// TODO check if there are commands that labels are not allowed to have like .extern maybe?
		if (currDCAddres != *DCPtr) {
			insertLabel(labelName, labelsTable, DATA, currDCAddres);
		} else {
			insertLabel(labelName, labelsTable, INSTRUCTION, currICAddres);
		}

	}
	deleteString(firstWord);

	return resType;

}
/*Passing the non lable part to the function, to check if the parameters after it are valid */
RESULT_TYPE handleNonLabel(char *word, String *line,
		Node *instructionBinarysList, Node *dataBinarysList,Node * entryList, int *ICPtr,
		int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	if (isData(word)) {

//		resType = handleData(line, dataBinarysList, DCPtr);

	} else if (isStringData(word)) {

		//		TODO .string
		resType = handleString(line, dataBinarysList, DCPtr);

	} else if (isExtern(word)) {
		resType = handleExtern(line, dataBinarysList, DCPtr);

	} else if (isEntry(word)) {
		resType = handleEntry(line, dataBinarysList, DCPtr);

	}else{

		//TODO function that turns opcode to binary
		//TODO handle opcodes read string line and translate to opcode

	}

	return resType;
}


RESULT_TYPE handleData(String *line, Node *dataBinarysList, int *DCPtr) {

	int size = 0, i = 0, currInt;
	int **intArrPtr;
	int *intArr = NULL;
	intArrPtr = &intArr;
	RESULT_TYPE resType = SUCCESS;
	Set *binaryWord;
	Node *node;

	//get intArrAllocates memory on the heap to intArr
	resType = getIntArrfromStringArgs(line, intArrPtr, &size);
	if (resType) {
		//TODO handle error return ? free Label
		printf("ERROR");
		return resType;
	}

	//TODO handle intArr is empty || size == 0 meaning there were no arguments
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
	int i = 0;

	resType = isquoteLegal(line);

	if (!resType){
		printf("\nERROR: The String is ilegal, cause of missing quotes in the string.\n");
		return MISSING_QUOTE;
	}
	char *restOfString;
	if(!isalpha(restOfString)){

		if(!isdigit(restOfString)||!ispunct(restOfString)){

			return STRING_ILlEGAL_DEFENITION;
		}


	}

	while(restOfString[i] != '\0'){

		if (restOfString[i] == ','){
			printf("\nERROR: The String is ilegal,commas aren't alowed in the string.\n");
			return ILLEGAL_COMMA;
		}

	}

	return SUCCESS;

}
RESULT_TYPE handleExtern( char *destFile, String *line, Node *dataBinarysList, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;
	/*Opening extern file in writing mode, to pass the exttern lables that where found*/
	FILE *extFile = fopen(destFile, "w");
/*If we couldnt open the extern file, we print a proper error message*/
	if (!extFile) {
		printFileError(destFile);
		return FILE_NOT_FOUND;
	}

	//TODO open extern file with w mode
	// A,R,E = 01
	// can have 2 extens with the same name
	return SUCCESS;
	fclose(extFile);
}
RESULT_TYPE handleEntry(char *destFile,String *line, Node *dataBinarysList, int *DCPtr) {
	//TODO open entry file with w mode
	RESULT_TYPE resType = SUCCESS;
		/*Opening entry file in writing mode, to pass the entry lables that where found*/
		FILE *entFile = fopen(destFile, "w");
	/*If we couldnt open the entry file, we print a proper error message*/
		if (!entFile) {
			printFileError(destFile);
			return FILE_NOT_FOUND;
		}

		//TODO open extern file with w mode
		// A,R,E = 01
		// can have 2 extens with the same name
		return SUCCESS;
		fclose(entFile);
}

void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type,
		int addres) {

	Label *label;
	label = createLabel(labelName);
	label->type = type;
	label->address = addres;
	insertToTable(labelsTable, labelName, label);

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

void secoundPassAssembler() {

}


