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

int isPramsLegalforRealativeMode(char *line) {
	/*Check for illegal comma and missing brackets*/

	int i, len;
	int bracketCount = 0;
	String *label, *param1, *param2;
	len = strlen(line);
	label = createEmptyString();

	for (i = 0; i < len; i++) {

		if (isspace(line[i])) {
			return 0;
		} else if (i == 0 && !isalpha(line[i])) {
			return 0;
		} else if (!isalnum(line[i])) {
			return 0;
		} else if (line[i] == '(') {
			bracketCount++;
			break;
		} else {
			appendCharToString(label, line[i]);
		}
	}

	param1 = createEmptyString();
	for (; i < len; i++) {

		if (isspace(line[i])) {
			return 0;
		} else if (line[i] == ',') {
			break;
		} else {
			appendCharToString(param1, line[i]);
		}

	}

	param2 = createEmptyString();
	for (; i < len; i++) {

		if (isspace(line[i])) {
			return 0;
		} else if (line[i] == ')') {
			break;
		} else {
			appendCharToString(param2, line[i]);
		}

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
				i++; /*TODO does this work????*/
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

/*TODO fix pop argument for missing comma */
RESULT_TYPE popArgument(String *argumernts, String *dest, int isLastArgument) {

	RESULT_TYPE resType = SUCCESS;
	int i = 0;
	char currChar;
	String *newStr = createEmptyString();
	String *temp;

	for (i = 0; i <= argumernts->size; ++i) {

		currChar = charAt(argumernts, i);
		if (isspace(currChar)) {
			/*TODO check for missing comma */
			continue;
		}

		else if (currChar == ',' || currChar == '\n' || currChar == '\0') {

			if (isLastArgument && currChar == ',') {
				resType = UNEXPECTED_COMMA; /*TODO maybe change this resType */

			} else if (newStr->size == 0 && currChar == ',') {
				resType = CONSECUTIVE_COMMAS;

			} else if (newStr->size == 0 && i == argumernts->size) {
				resType = INPUT_IS_EMPTRY;

			}

			break;

		} else {
			appendCharToString(newStr, currChar);
		}

	}

	if (resType) {
		/* in case there is an error we free the space we allocated on the heap */
		deleteString(newStr);

	}
	/*new str is the argument
	we need to pop it froom arguments*/
	temp = createNewString(argumernts->value + i + 1);
	setStringValue(argumernts, temp->value);
	*dest = *newStr;
	deleteString(temp);

	return resType;

}


