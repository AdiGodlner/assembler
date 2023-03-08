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
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//TODO find all repeating macros and put them in one file with extern?
#define MAX_LINE_LEN 82
#define MAX_LABEL_LENGTH 30

//TODO change char *srcFile to char **srcFiles
void assemble(char *srcFile) {

	RESULT_TYPE resType;
	HashTable *symbolTable = createDefualtHashTable();
	Node *instructionBinarysList = NULL;
	Node *dataBinarysList = NULL;
	resType = firstPassAssembly(srcFile, symbolTable, instructionBinarysList,
			dataBinarysList);

	if (resType) {
//		return resType; // TODO handle error ?? do not run secoundPass
	}
//TODO call secound pass

	/* free heap meomory */
	deleteNodeRecursive(instructionBinarysList, deleteSet);
	deleteNodeRecursive(dataBinarysList, deleteSet);
	deleteTable(symbolTable, deleteString);

}

RESULT_TYPE firstPassAssembly(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList) {

	int IC = 0, DC = 0, lineNumber = 0;
	RESULT_TYPE resType = SUCCESS;

	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();
	String *firstWord;

	FILE *amFile = fopen(srcFile, "r");

	if (!amFile) {
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	while (fgets(line, MAX_LINE_LEN, amFile) != NULL) {

		//line number is supposed to e used for error printing
		lineNumber++;

		setStringValue(lineString, line);
		firstWord = popWord(lineString);

		if (isLabel(firstWord)) {

			resType = handleLabel(firstWord->value, symbolTable, lineString,
					instructionBinarysList, dataBinarysList, &IC, &DC);
		} else {

			resType = handleNonLabel(firstWord->value, lineString,
					instructionBinarysList, dataBinarysList, &IC, &DC);
		}

		deleteString(firstWord);

		if (resType) {
			break;
		}

	}

	fclose(amFile);
	deleteString(lineString);

//	TODO iterate over keys of symbol table add IC TO LABEL->ADRESS for labels of TYPE data
	return resType;

}

RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, int *ICPtr,
		int *DCPtr) {

	int currDCAddres, currICAddres;
	RESULT_TYPE resType = SUCCESS;
	String *firstWord;

	//TODO check label is legal ( length < max length && starts with a letter )
	if (isKeyInTable(labelsTable, labelName)) {
		//TODO handle error?
		return LABEL_ALLREADY_EXISTS;
	}

	currDCAddres = *DCPtr;
	currICAddres = *ICPtr;
	firstWord = popWord(line);

	resType = handleNonLabel(firstWord->value, line, instructionBinarysList,
			dataBinarysList, ICPtr, DCPtr);

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

RESULT_TYPE handleNonLabel(char *word, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, int *ICPtr,
		int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	if (isData(word)) {

		resType = handleData(line, dataBinarysList, DCPtr);

	} else if (isStringData(word)) {

		//		TODO .string

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

void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type,
		int addres) {

	Label *label;
	label = createLabel(labelName);
	label->type = type;
	label->address = addres;
	//done handling data insert label to table
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

void secoundPassAssembly() {

}

RESULT_TYPE popArgument(String *arguments, String *dest) {

	int argStart = 0, argEnd = 0, nonBlankCharIndex = 0, size = 0;
	char currChar = EOF;
	int startSubStr, lenSubStr, i = 0;
	String *temp;
	char testChar;

	/*skip the leading blank spaces before the argument */
	argStart = findNextNonBlankCharLocation(arguments, 0);
	if (argStart == -1) {
		return NO_ARGUMENT_FOUND;
	}

	setStringValue(dest, "");
	size = arguments->size;

	/* copy argument */
	for (argEnd = argStart; argEnd < size; ++argEnd) {

		currChar = arguments->value[argEnd];

		if (currChar == ',' || currChar == ' ' || currChar == '\t'
				|| currChar == '\n') {

			break;
		} else {
			appendCharToString(dest, currChar);

		}

	}
	if (argStart == argEnd) {
		/*
		 if argStart  == argEnd then there is nothing but blank chars
		 between the argument start and another ','
		 that can mean either an ILLEAGAL_COMMA or a CONSECUTIVE_COMMAS
		 ERROR we return an UNEXPECTED_COMMA ERROR and let the caller function
		 Differentiate between the possible ERROR types because it has all the data to
		 differentiate between the different possible RESULT_TYPES
		 in the command given by the user
		 or it is the end of the string which means that there was NO_ARGUMENT_FOUND
		 */
		if (currChar == ',') {
			return UNEXPECTED_COMMA;

		} else {
			return NO_ARGUMENT_FOUND;
		}

	}

	nonBlankCharIndex = findNextNonBlankCharLocation(arguments, argEnd);

	testChar = arguments->value[nonBlankCharIndex];
	if (testChar != ',' && testChar != '\n') {

		/* we found non blank chars in the end of the argument that is not a ','
		 * meaning
		 * there is a missing comma or EXTRANEOUS_TEXT or
		 */
		return MISSING_COMMA;
	}

	/* after the argument there are only blank chars and a comma *
	 * pop the argument from the input string; */
	startSubStr = nonBlankCharIndex + 1;
	lenSubStr = size - (nonBlankCharIndex + 1);
	temp = createEmptyString();

	for (i = 0; i < lenSubStr; ++i) {
		appendCharToString(temp, arguments->value[startSubStr + i]);
	}

	appendCharToString(temp, arguments->value[startSubStr + i]);
	setStringValue(arguments, temp->value);
	deleteString(temp);

	return SUCCESS;

}

//TODO change description in H file
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size) {

	RESULT_TYPE resType;
	int tempSize = 0, num = 0;
	int *numPtr = &num;
	int *intArr = NULL;
	int *temp = NULL;

	String *numStr = createEmptyString();

	while (1) {

		resType = popArgument(arguments, numStr);

		if (resType) {
			if (resType == NO_ARGUMENT_FOUND) {
				resType = SUCCESS;
			}
			break;

		}

		resType = getIntFromName(numStr->value, numPtr);

		if (resType) {
//			current arguments is not an integer VALUE_NOT_AN_INTEGER ERROR
			printString(numStr);
			//TODO handle this case ?
			break;

		}

		tempSize++;
		temp = realloc(intArr, sizeof(int) * tempSize);

		if (temp == NULL) {
			/*  realloc failed to  allocate memory successfully */
			//TODO write memory allocation function that exists on failed meomer allocation
			resType = MEMMORY_ALLOCATION_FAILURE;
			break;
		}

		intArr = temp;
		intArr[tempSize - 1] = num;

	}

	deleteString(numStr);
	if (resType) {
		if (temp != NULL) {
			// TODO is this if even needed can't I just free  NULL;
			/* in case there is an error we free the space we allocated on the heap */
			free(temp);
		}
		return resType;
	}

	*intArrPtr = intArr;
	*size = tempSize;

	return SUCCESS;

}

RESULT_TYPE getIntFromName(char *str, int *numDest) {

	int i = 0, digit = 0, temp = 0, isNegative = 0, decimalPlace = 1;
	int j = 0;

	char currChar = str[0];

	if (currChar == '-') {
		if (strlen(str) == 1) {
			return VALUE_NOT_AN_INTEGER;
		}
		isNegative = 1;
		i++;
	} else if (currChar == '+') {
		if (strlen(str) == 1) {
			return VALUE_NOT_AN_INTEGER;
		}
		i++;
	}

	for (j = strlen(str) - 1; j >= i; j--) {

		currChar = str[j];
		if (!isdigit(currChar)) {
			return VALUE_NOT_AN_INTEGER;
		}

		digit = (currChar - '0');
		temp += decimalPlace * digit;
		decimalPlace *= 10;

	}

	temp *= isNegative ? -1 : 1;
	*numDest = temp;

	return SUCCESS;

}
