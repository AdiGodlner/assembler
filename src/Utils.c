/*
 * Utils.c
 *
 *  Created on: 8 Mar 2023
 *      Author: Adi
 */
#include "Result.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


RESULT_TYPE fooma(String* argumernts, Node **headPtrPtr){

	RESULT_TYPE resType = SUCCESS;
	int i =0, num = 0, elementIndex = 0;
	char currChar;
	String * currNumStr = createEmptyString();
	int *numPtr = &num;
	Node * head = NULL;
	Node * newNode = NULL;
	*headPtrPtr = head;

	for (i = 0; i <= argumernts->size; ++i) {

		currChar = charAt(argumernts, i);
		if (isspace(currChar)) {
			continue;
		}

		else if (currChar == ',' || currChar == '\n' || currChar == '\0') {

			resType = getIntFromName(currNumStr->value, numPtr);
			if (resType) {

				break;
			}

			newNode = createNode(*numPtr, NULL);
			pushTail(newNode , headPtrPtr);
			setStringValue(currNumStr, "");

		}else{

			appendCharToString(currNumStr, currChar);

		}



	}

	deleteString(currNumStr);
	return resType;

}

/*TODO change description in H file */
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size) {

	RESULT_TYPE resType = SUCCESS;
	int tempSize = 0, num = 0;
	int *numPtr = &num;
	int *intArr = NULL;
	int *temp = NULL;
	String * numStr;

	while (resType == SUCCESS) {

//		fooma(arguments, headPtrPtr);
//		numStr = popArgument(arguments );

		if (numStr->size == 0 ) {

			if (arguments->size != 0) {
				resType = CONSECUTIVE_COMMAS;
			}
			break;

		}

		resType = getIntFromName(numStr->value, numPtr);
		deleteString(numStr);

		if (resType) {
			break;
		}

		tempSize++;
		temp = realloc(intArr, sizeof(int) * tempSize);

		if (temp == NULL) {
			/*  realloc failed to  allocate memory successfully */
			/*TODO write memory allocation function that exists on failed meomer allocation */
			resType = MEMMORY_ALLOCATION_FAILURE;
			break;
		}

		intArr = temp;
		intArr[tempSize - 1] = num;

	}

	if (resType) {
		/* in case there is an error we free the space we allocated on the heap */
		free(temp);

		return resType;
	}

	*intArrPtr = intArr;
	*size = tempSize;

	return SUCCESS;

}

RESULT_TYPE getIntFromName(char *str, int *numDest) {

	int i = 0, digit = 0, temp = 0, isNegative = 0, decimalPlace = 1;
	int j = 0, size;
	char currChar = str[0];
	size = strlen(str);

	if (size == 0) {
		return INPUT_IS_EMPTRY;
	}

	if (currChar == '-') {
		if (size == 1) {
			return VALUE_NOT_AN_INTEGER;
		}
		isNegative = 1;
		i++;
	} else if (currChar == '+') {
		if (size == 1) {
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

int isbracketLegal(char *line) {
	/*Check for illegal commas and missing brackets*/

	int i, len;
	int bracketCount = 0;

	len = strlen(line);

	for (i = 0; i < len; i++) {

		if ((line[i] == ')') || (line[i] == '(')) {

			bracketCount++;
			if ((i == 0 || isspace(line[i - 1]))
					|| (i + 1 < len && isspace(line[i + 1]))) {
				/*Printing proper error message if an illegal comma is found*/
				printf("ERROR: Illegal bracket position %d\n", i);
			}
			/*Checking that both brackets appear*/
		} else if (line[i] == '(') {
			bracketCount++;

		} else if (line[i] == ')') {
			bracketCount--;

		}
	}
	if (bracketCount != 0) {
		/*if one of the brackes is missing or there are too many brackes, we print an proper error message*/
		printf("ERROR: Missing brackets\n");
		return 0;
	}
	return 1;

}

RESULT_TYPE checkStringIllegal(char *line) {

	int i = 0;
	int quoteCount = 0;

	for (i = 0; i < strlen(line); i++) {

		if (line[i] == '"') {
			/*if we fint quote we increment the count*/
			quoteCount++;
			if (quoteCount == 2) {
				i++; //TODO does this work????
				break;
			}
		}

		if (!isalnum(line[i]) && !ispunct(line[i])) {

			return STRING_ILlEGAL_DEFENITION;

		}
	}

	for (; i < strlen(line); i++) {
		if (!isspace(line[i])) {
			return EXTRANEOUS_TEXT;
		}
	}

	return SUCCESS;

}

int isCommaLegal(char *line) {

	int i, len;
	int commaCount = 0;

	len = strlen(line);

	for (i = 0; i < len; i++) {

		if (line[i] == ',') {

			commaCount++;
			if ((i == 0 || isspace(line[i - 1]))
					|| (i + 1 < len && isspace(line[i + 1]))) {
				/*Printing proper error message if an illegal comma is found*/
				printf("ERROR: Illegal comma position %d\n", i);
				return 0;
			}
		}
	}
	return 1;
}

