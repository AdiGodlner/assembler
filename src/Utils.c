/*
 * Utils.c
 *
 *  Created on: 8 Mar 2023
 *      Author: Adi
 */
#include "Result.h"
#include "Utils.h"
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

RESULT_TYPE getIntArrfromStringArgs(String *argumernts, int **intArrPtr,
		int *size) {

	RESULT_TYPE resType = SUCCESS;
	int i = 0, num = 0, elementIndex = 0;
	char currChar;
	String *currNumStr = createEmptyString();
	int *numPtr = &num;
	int *temp = NULL;
	int *intArr = NULL;

	for (i = 0; i <= argumernts->size; ++i) {

		currChar = charAt(argumernts, i);
		if (isspace(currChar)) {
			continue;
		}

		else if (currChar == ',' || currChar == '\n' || currChar == '\0') {

			resType = getIntFromName(currNumStr->value, numPtr);
			if (resType) {

				if (resType == INPUT_IS_EMPTRY) {
					if (i == argumernts->size) {
						if (elementIndex != 0) {
							resType = MISSING_ARGUMNET;
						} else {
							resType = INPUT_IS_EMPTRY;
						}
					} else {
						resType = CONSECUTIVE_COMMAS;
					}

				}

				break;

			}

			elementIndex++;
			temp = realloc(intArr, sizeof(int) * elementIndex);

			intArr = temp;
			intArr[elementIndex - 1] = num;

			setStringValue(currNumStr, "");

		} else {

			appendCharToString(currNumStr, currChar);

		}

	}

	deleteString(currNumStr);

	if (resType) {
		/* in case there is an error we free the space we allocated on the heap */
		free(temp);

		return resType;
	}

	*intArrPtr = intArr;
	*size = elementIndex;

	return resType;

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

RESULT_TYPE checkStringIllegal(char *line) {

	int i = 0;
	int quoteCount = 0;
	char currChar;
	for (i = 0; i < strlen(line); i++) {

		currChar = line[i];
		if (currChar == '"') {
			/*if we fint quote we increment the count*/
			quoteCount++;
			if (quoteCount == 2) {
				i++;
				break;
			}
		}

		if (!isalnum(currChar) && !ispunct(currChar)) {

			return STRING_ILlEGAL_DEFENITION;

		}
	}

	for (; i < strlen(line); i++) {
		currChar = line[i];
		if (!isspace(currChar)) {
			return EXTRANEOUS_TEXT;
		}
	}

	return SUCCESS;

}

RESULT_TYPE popArgument(String *argumernts, String *dest, int isLastArgument) {

	RESULT_TYPE resType = SUCCESS;
	int i = 0, foundArgumentStart = 0, foundArgumentEnd = 0 ;
	char currChar;
	String *newStr = createEmptyString();
	String *temp;

	for (i = 0; i <= argumernts->size; ++i) {

		currChar = charAt(argumernts, i);
		if (isspace(currChar)) {
			if (foundArgumentStart) {
				foundArgumentEnd =1;
			}
			continue;
		}

		else if (currChar == ',' || currChar == '\n' || currChar == '\0') {

			if (isLastArgument && currChar == ',') {
				resType = UNEXPECTED_COMMA;

			} else if (newStr->size == 0 && currChar == ',') {
				resType = CONSECUTIVE_COMMAS;

			} else if (newStr->size == 0 && i == argumernts->size) {
				resType = INPUT_IS_EMPTRY;

			}

			break;

		} else {

			if (foundArgumentStart == 0) {
				foundArgumentStart = 1;
			}
			if (foundArgumentEnd) {
				resType = MISSING_COMMA;
				break;
			}

			appendCharToString(newStr, currChar);
		}

	}

	if (resType) {
		/* in case there is an error we free the space we allocated on the heap */
		deleteString(newStr);
		return resType;
	}

	/*new str is the argument
	 we need to pop it from arguments*/
	temp = createNewString(argumernts->value + i + 1);
	setStringValue(argumernts, temp->value);
	setStringValue(dest, newStr->value);
	deleteString(temp);
	deleteString(newStr);

	return resType;

}

String* binaryWOrdToString(Set *set) {

	int i = 0;
	String *str = createEmptyString();
	char byte;
	int bit, temp;

	byte = set->bits[1];
	for (i = 5; i >= 0; i--) {

		temp = (1 << i);
		bit = byte & temp;
		if (bit) {

			appendCharToString(str, '/');

		} else {
			appendCharToString(str, '.');
		}

	}

	byte = set->bits[0];

	for (i = 7; i >= 0; i--) {
		temp = (1 << i);
		bit = byte & temp;
		if (bit) {

			appendCharToString(str, '/');

		} else {
			appendCharToString(str, '.');
		}

	}

	return str;

}

