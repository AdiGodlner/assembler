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

/*TODO change description in H file */
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
/*			current arguments is not an integer VALUE_NOT_AN_INTEGER ERROR */
			printString(numStr);
			/*TODO handle this case ?*/
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

		deleteString(numStr);

	}

	if (resType) {
		/* in case there is an error we free the space we allocated on the heap */
		deleteString(numStr);
		free(temp);

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
