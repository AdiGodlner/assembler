/*
 * String.c
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */

#include "String.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

String* createEmptyString() {

	return createNewString("");

}

String* createNewString(char *charArr) {

	String *str = (String*) malloc(sizeof(String));
	str->value = NULL;
	str->size = 0;
	setStringValue(str, charArr);
	return str;

}

String* duplicateString(String *str) {

	return createNewString(str->value);

}

void setStringValue(String *str, char *charArr) {

	char *temp;

	str->size = strlen(charArr);
	temp = realloc(str->value, sizeof(char) * (str->size + 1));

	if (temp != NULL) {
		str->value = temp;
	}

	str->value = strcpy(str->value, charArr);
	str->value[str->size] = '\0';

}

/*
 *
 */
String* stringNCopy(char *src, int count) {

	int i = 0;
	String *strRes = createEmptyString();

	for (i = 0; i < count; ++i) {
		appendCharToString(strRes, src[i]);
	}

	return strRes;

}

char charAt(String *str, int index) {
	if (index > str->size || index < 0) {
		return -1;
	}
	return str->value[index];
}

void concatStrings(String *str1, String *str2) {

	appendToString(str1, str2->value);

}

void appendToString(String *str1, char *charArr) {

	str1->size += strlen(charArr);
	str1->value = (char*) realloc(str1->value,
			(sizeof(char) * (str1->size + 1)));
	/* check if string value is null i.e if realloc failed to allocate memory */
	str1->value = strcat(str1->value, charArr);

}

void appendCharToString(String *str, char c) {

	str->size += 1;
	str->value = (char*) realloc(str->value, sizeof(char) * (str->size + 1));
	str->value[str->size - 1] = c;
	str->value[str->size] = '\0';

}

void deleteString(void *str) {
	if (str != NULL) {
		free(((String*) str)->value);
		free(str);

	}

}

void printString(String *str) {

	printf("%s", str->value);

}

int compareString(String *str1, String *str2) {

	return strcmp(str1->value, str2->value);
}

int findNextNonBlankCharLocation(String *str, int offset) {

	int i = offset;
	char currChar;

	for (; i < str->size; ++i) {

		currChar = str->value[i];
		if (!isspace(currChar) || currChar == '\n') {

			return i;

		}

	}

	return -1;

}

String* popWord(String *str) {

	String *newStr = createEmptyString();
	String *temp = createEmptyString();
	char currChar;
	int subStart = 0, subEnd = 0, size = 0, lenSubStr = 0;
	int startSubStr = 0, i = 0;

	for (subStart = 0; subStart < str->size; ++subStart) {

		currChar = str->value[subStart];
		if (!isspace(currChar)) {
			break;
		}

	}

	for (subEnd = subStart; subEnd < str->size; subEnd++) {

		currChar = str->value[subEnd];
		if (isspace(currChar)) {
			break;
		}
		appendCharToString(newStr, currChar);

	}

	startSubStr = subEnd + 1;
	size = str->size;
	lenSubStr = size - (subEnd + 1);

	for (i = 0; i < lenSubStr; ++i) {
		appendCharToString(temp, str->value[startSubStr + i]);

	}

	appendCharToString(temp, str->value[startSubStr + i]);
	setStringValue(str, temp->value);
	deleteString(temp);

	return newStr;

}
char* fromDecimalToBinary(int decimal){

	/*Convert decimal to binary with 14 bits*/
	char *binary = (char*)malloc(15 * sizeof(char));
	sprintf(binary, "%014d", decimal);
	char A_R_E[3];/*including NULL charector*/
	char destOp[3];
	char srcOp[3];
	char opcode[5];
	char operand2[3];
	char operand1[3];

	strncpy(A_R_E, binary, 2);
	A_R_E[2] = '\0';

	strncpy(destOp, binary+2, 2);
	destOp[2] = '\0';

	strncpy(srcOp, binary+4, 2);
	srcOp[2] = '\0';

	strncpy(opcode, binary+6, 4);
	opcode[4] = '\0';

	strncpy(operand2, binary+10, 2);
	operand2[2] = '\0';

	strncpy(operand1, binary+12, 2);
	operand1[2] = '\0';

	char *result = (char*)malloc(15 * sizeof(char));

	sprintf(result, "%s%s%s%s%s%s", operand1, operand2, opcode, srcOp, destOp, A_R_E);

	return result;
//TODO DO we free here???
	free(binary);

}

