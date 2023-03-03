/*
 ============================================================================
 Name        : HW_22.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 ============================================================================
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Result.h"
#include "set.h"
#include "String.h"

#define SET_PREFIX "SET"
#define SET_ARR_SIZE 6
#define READ_SET "read_set"
#define PRINT_SET "print_set"
#define UNION_SET "union_set"
#define INTERSECT_SET "intersect_set"
#define SUB_SET "sub_set"
#define SYMDIFF_SET "symdiff_set"
#define STOP "stop"

RESULT_TYPE handleUserInput(String *userCmnd, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE sendTofunction(char *operand, String *arguments,
		Set *setArr[SET_ARR_SIZE]);

RESULT_TYPE handleReadSet(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handlePrintSet(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handleUnionSet(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handleIntersectSet(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handleSubset(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handleSymdiffSet(String *arguments, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE handleStop(char *operand, String *arguments);

RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size);
RESULT_TYPE getSetsFromStringArgs(String *arguments, Set *setArr[SET_ARR_SIZE],
		Set *currSetsArr[], int currSetsArrSize, int checkExtraneousText);
RESULT_TYPE getSetFromName(Set **dest, char *setName, Set *setArr[SET_ARR_SIZE]);
RESULT_TYPE popArgument(String *arguments, String *dest);
RESULT_TYPE getIntFromName(char *str, int *numDest);

void getLine(String *str);
void printResultMsg(RESULT_TYPE resType);


/*
 * this method handles the String userCmnd given by the user
 * and send it to the relent function requested by the user
 * this method returns:
 * SUCCESS if the user command is a valid command as specified in the white paper,
 * IGNORE if the string given by the user is filled with only blank spaces
 * UNEXPECTED_EOF if there is an unexpected EOF,
 * UNDEFINED_COMMAND_NAME if the command name given by the user is not one of the allowed possibilities specified in the white paper,
 */
RESULT_TYPE handleUserInput(String *userCmnd, Set *setArr[SET_ARR_SIZE]) {

	String *operand = NULL;
	char lastChar;
	RESULT_TYPE resType = SUCCESS;

	operand = popWord(userCmnd);

	if (operand->size == 1) {

		if (operand->value[0] == '\n') {
			/* if user entered an empty line we ignore it */
			resType = IGNORE;
		} else if (operand->value[0] == EOF) {
			resType = UNEXPECTED_EOF;
		} else {
			resType = UNDEFINED_COMMAND_NAME;
		}

	} else {

		lastChar = userCmnd->value[(userCmnd->size) - 1];

		if (lastChar == EOF) {
			if (strcmp(operand->value, STOP) == 0) {
				resType = handleStop(operand->value, userCmnd);
				resType = resType == EXIT ? resType : UNEXPECTED_EOF;
			} else {
				resType = UNEXPECTED_EOF;
			}

		} else {
			resType = sendTofunction(operand->value, userCmnd, setArr);
		}

	}

	deleteString(operand);
	return resType;

}

/*
 * this method differentiates between the different user commands in 'operand'
 * and send it to be handled by its relevant function
 */
RESULT_TYPE sendTofunction(char *operand, String *arguments,
		Set *setArr[SET_ARR_SIZE]) {

	RESULT_TYPE resType = SUCCESS;

	if (strcmp(operand, READ_SET) == 0) {
		resType = handleReadSet(arguments, setArr);

	} else if (strcmp(operand, PRINT_SET) == 0) {
		resType = handlePrintSet(arguments, setArr);

	} else if (strcmp(operand, UNION_SET) == 0) {
		resType = handleUnionSet(arguments, setArr);

	} else if (strcmp(operand, INTERSECT_SET) == 0) {
		resType = handleIntersectSet(arguments, setArr);

	} else if (strcmp(operand, SUB_SET) == 0) {
		resType = handleSubset(arguments, setArr);

	} else if (strcmp(operand, SYMDIFF_SET) == 0) {
		resType = handleSymdiffSet(arguments, setArr);
	} else if (strcmp(operand, STOP) == 0) {
		resType = handleStop(operand, arguments);

	} else {
		resType = UNDEFINED_COMMAND_NAME;
	}

	return resType;
}

/*
 *  this method handles the user cmnd for  stop
 */
RESULT_TYPE handleStop(char *operand, String *arguments) {

	RESULT_TYPE resType = EXIT;
	String *tempStr = popWord(arguments);
	char *temp = tempStr->value;

	if (tempStr->size == 1) {
		if (temp[0] == '\n' || temp[0] == EOF) {
			resType = EXIT;
		} else {
			resType = EXTRANEOUS_TEXT;
		}
	} else {

		resType = EXTRANEOUS_TEXT;
	}

	deleteString(tempStr);
	return resType;

}
/*
 * this method handles the user cmnd for  read_set
 */
RESULT_TYPE handleReadSet(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	RESULT_TYPE resType;
	Set *currSetsArr[1];
	int size = 0;
	int **intArrPtr;
	int *intArr = NULL;
	intArrPtr = &intArr;

	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 1, 0);

	if (resType) {
		return resType;
	}

	resType = getIntArrfromStringArgs(arguments, intArrPtr, &size);
	if (resType) {
		return resType;
	}

	read_set(currSetsArr, intArr, size);

	/* getIntArrfromStringArgs allocates memory on the heap for intArr that we need to free*/
	free(intArr);

	return SUCCESS;

}

/*
 * this method handles the user cmnd for  print_set
 */
RESULT_TYPE handlePrintSet(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	RESULT_TYPE resType;
	Set *currSetsArr[1];
	String *setStr = NULL;
	String *extraneousText;

	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 1, 0);

	if (resType) {
		return resType;
	}

	/* check for EXTRANEOUS_TEXT */
	extraneousText = popWord(arguments);
	if (extraneousText->size) {
		deleteString(extraneousText);
		return EXTRANEOUS_TEXT;
	}
	deleteString(extraneousText);

	setStr = print_set(currSetsArr[0]);
	printString(setStr);
	deleteString(setStr);

	return SUCCESS;
}

/*
 * this method handles the user cmnd for  UNION_SET
 */
RESULT_TYPE handleUnionSet(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	Set *currSetsArr[3];

	RESULT_TYPE resType;
	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 3, 1);

	if (resType) {
		return resType;
	} else {

		union_set(currSetsArr[0], currSetsArr[1], currSetsArr[2]);
		return SUCCESS;

	}

}
/*
 * this method handles the user cmnd for  symdiff_set
 */
RESULT_TYPE handleSymdiffSet(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	Set *currSetsArr[3];

	RESULT_TYPE resType;
	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 3, 1);

	if (resType) {
		return resType;
	} else {

		symdiff_set(currSetsArr[0], currSetsArr[1], currSetsArr[2]);
		return SUCCESS;

	}

}
/*
 * this method handles the user cmnd for  sub_set
 */
RESULT_TYPE handleSubset(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	Set *currSetsArr[3];

	RESULT_TYPE resType;
	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 3, 1);

	if (resType) {
		return resType;
	} else {

		sub_set(currSetsArr[0], currSetsArr[1], currSetsArr[2]);
		return SUCCESS;

	}

}
/*
 * this method handles the user cmnd for  intersect_set
 */
RESULT_TYPE handleIntersectSet(String *arguments, Set *setArr[SET_ARR_SIZE]) {

	Set *currSetsArr[3];

	RESULT_TYPE resType;
	resType = getSetsFromStringArgs(arguments, setArr, currSetsArr, 3, 1);

	if (resType) {
		return resType;
	} else {

		intersect_set(currSetsArr[0], currSetsArr[1], currSetsArr[2]);
		return SUCCESS;

	}

}

/*
 * this method pops all arguments from String arguments checks if they are integers
 * and populates an integerArr pointed to by 'intArrPtr' with their integer representation
 * this method returns LIST_NOT_TERMINATED_CORRECTLY if the last argument is not -1
 * VALUE_OUT_OF_RANGE if the int represented in the argument is not between 0 and 127 or -1 the terminator integer
 * EXTRANEOUS_TEXT if there is extraneous text after the -1 argument
 * CONSECUTIVE_COMMAS if there are consecutive commas
 * MISSING_COMMA if there is a missing comma
 */
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size) {

	RESULT_TYPE resType;
	int tempSize = 0, num = 0;
	int *numPtr = &num;
	int *intArr = NULL;
	int *temp = NULL;
	String *extraneousText = NULL;
	String *numStr = createEmptyString();

	while (1) {

		resType = popArgument(arguments, numStr);

		if (resType) {
			resType =
					resType == MISSING_PARAMETER ?
							LIST_NOT_TERMINATED_CORRECTLY : CONSECUTIVE_COMMAS;

			break;
		}

		resType = getIntFromName(numStr->value, numPtr);
		if (resType) {
			printString(numStr);
			break;
		} else if (num == -1) {

			extraneousText = popWord(arguments);

			if (extraneousText->size) {
				resType = EXTRANEOUS_TEXT;

			}
			deleteString(extraneousText);
			break;

		} else if (num < 0 || num > 127) {

			resType = VALUE_OUT_OF_RANGE;
			break;
		}

		tempSize++;
		temp = realloc(intArr, sizeof(int) * tempSize);

		if (temp == NULL) {
			/*  realloc failed to  allocate memory successfully */
			resType = MEMMORY_ALLOCATION_FAILURE;
			break;
		}

		intArr = temp;
		intArr[tempSize - 1] = num;

	}

	deleteString(numStr);
	if (resType) {
		if (temp != NULL) {
			/* in case there is an error we free the space we allocated on the heap */
			free(temp);
		}
		return resType;
	}

	*intArrPtr = intArr;
	*size = tempSize;

	return SUCCESS;

}
/*
 * this method takes an int represented in the string 'str' and puts it in 'numDest'
 * the method returns SUCCESS if the it was able to convert the string to an int
 * and VALUE_NOT_AN_INTEGER if it couldn't
 */
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

/*
 * this method pops set name arguments from String  'arguments'
 * finds the sets represented by that name in 'setArr' and populates
 *    'currSetsArr' with a pointer to that set
 * parameters :
 * 'arguments' = a String containing the set names separated by a comma
 * 'setArr' = array with pointers to the sets represented by the setNames
 * 'currSetsArr' = array to populate with the pointers to the requested strings
 * 'currSetsArrSize' = size of currSetsArr and the number of sets to pop from 'arguments'
 * 'checkExtraneousText' = a flag to check if there is ExtraneousText after popping all the requested sets
 */
RESULT_TYPE getSetsFromStringArgs(String *arguments, Set *setArr[SET_ARR_SIZE],
		Set *currSetsArr[], int currSetsArrSize, int checkExtraneousText) {
	int i = 0;
	RESULT_TYPE resType;
	String *setName = createEmptyString();
	String *extraneousText = NULL;

	/*find the set named in the arguments given by the user and populate the 'currSetsArr' with them  */
	for (i = 0; i < currSetsArrSize; ++i) {

		resType = popArgument(arguments, setName);
		if (resType) {
			/* giving more accurate errorTypes if needed */
			if (resType == MISSING_COMMA) {
				resType = i == 2 ? EXTRANEOUS_TEXT : MISSING_COMMA;
			} else if (resType == UNEXPECTED_COMMA) {
				resType = i == 0 ? ILLEGAL_COMMA : CONSECUTIVE_COMMAS;
			}
			break;
		}

		resType = getSetFromName(&currSetsArr[i], setName->value, setArr);

		if (resType) {
			break;
		}
	}

	deleteString(setName);

	if (resType) {
		return resType;
	}
	/*check for non blank chars after last set argument */
	if (checkExtraneousText) {
		extraneousText = popWord(arguments);
		if (extraneousText->size) {
			resType = EXTRANEOUS_TEXT;
		}
		deleteString(extraneousText);
	}

	return resType;

}

/*
 * this method pops the next argument in a the given String 'arguments' and stores
 * it in the String 'dest';
 *
 * this method returns 'SUCCESS' RESULT_TYPE only if it found a valid argument
 * a valid argument is a string of non blank chars that can have a prefix of blank chars
 * and and a suffix of blank chars that is terminated by a ',' or '\n'
 * otherwise this method returns a MISSING_COMMA RESULT_TYPE if there are two strings of non blank chars
 * separated  by a a blank char
 * or an UNEXPECTED_COMMA if the first non blank char of the string is a ','
 * this method considers a blank char to be either ' ' or '\t'
 */
RESULT_TYPE popArgument(String *arguments, String *dest) {

	int argStart = 0, argEnd = 0, nonBlankCharIndex = 0, size = 0;
	char currChar = EOF;
	int startSubStr, lenSubStr, i = 0;
	String *foo;
	char testChar;

	/*skip the leading blank spaces before the argument */
	argStart = findNextNonBlankCharLocation(arguments, 0);
	if (argStart == -1) {
		return MISSING_PARAMETER;
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
		 or it is the end of the string which means that there is a MISSING_PARAMETER
		 */
		if (currChar == ',') {
			return UNEXPECTED_COMMA;

		} else {
			return MISSING_PARAMETER;
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
	foo = createEmptyString();

	for (i = 0; i < lenSubStr; ++i) {
		appendCharToString(foo, arguments->value[startSubStr + i]);
	}

	appendCharToString(foo, arguments->value[startSubStr + i]);
	setStringValue(arguments, foo->value);
	deleteString(foo);

	return SUCCESS;

}

/*
 * this method finds the set represented by the string 'setName'
 * and puts a pointer to it in '**dest'
 *
 * the method returns SUCCESS if it found a set with represented by that
 * UNDEFINED_SET_NAME if a set with 'setName' does not exist
 * the possible set names are SETA ,SETB ,SETC ,SETD ,SETE ,SETF
 */
RESULT_TYPE getSetFromName(Set **dest, char *setName, Set *setArr[SET_ARR_SIZE]) {

	int setSuffix;
	if (strlen(setName) != 4) {
		/* is this an undefined set name needs testing for diffrent inputs */
		printf("setName = |%s|", setName);
		return UNDEFINED_SET_NAME;
	}
	if (strncmp(SET_PREFIX, setName, strlen(SET_PREFIX)) != 0) {

		return UNDEFINED_SET_NAME;
	}

	setSuffix = setName[3] - 'A';
	if (setSuffix < 0 || setSuffix > 6) {
		return UNDEFINED_SET_NAME;
	}

	*dest = setArr[setSuffix];

	return SUCCESS;

}

/*
 * this method gets a line of input from the user
 * the input ends when the user enters '\n' or EOF
 */
void getLine(String *str) {

	char c;
	setStringValue(str, "");

	while (1) {

		c = getc(stdin);
		appendCharToString(str, c);
		if (c == EOF || c == '\n') {
			return;
		}
	}

}

/*
 *this method prints the  result message associated to the given RESULT_TYPE
 */
void printResultMsg(RESULT_TYPE resType) {

	printf("%s\n", getResultMsg(resType));

}
