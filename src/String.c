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

	char *temp = NULL;

	str->size = strlen(charArr);
	temp = (char*) realloc(str->value, sizeof(char) * (str->size + 1));

	if (temp != NULL) {
		str->value = temp;
	}

	str->value = strcpy(str->value, charArr);
	str->value[str->size] = '\0';

}

String* stringNCopy(char *src, int count) {

	int i = 0;
	String *strRes = createEmptyString();

	for (i = 0; i < count; ++i) {
		appendCharToString(strRes, src[i]);
	}

	return strRes;

}

char charAt(String *str, int index) {
	if (str == NULL) {
		printf("str == NULL\n");
		return -1;
	}
	if (index > str->size || index < 0) {
		printf("index out of bounds\n");
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

	String *strString;

	if (str != NULL) {

		strString = (String*) str;
		free(strString->value);
		free(str);

	}

}

int compareString(String *str1, String *str2) {

	return strcmp(str1->value, str2->value);
}

String* popByDeliminator(String *str, char delim) {

	int i = 0;
	String *newStr, *temp ;
	char currChar;

	if (!containsChar(str, delim)) {
		return NULL;
	}
	newStr = createEmptyString();

	for (i = 0; i < str->size; ++i) {

		currChar = charAt(str, i);
		if (currChar == delim) {
			break;
		}

		appendCharToString(newStr, currChar);

	}

	temp = createNewString(str->value + i + 1);
	setStringValue(str, temp->value);
	deleteString(temp);

	return newStr;

}

int containsChar(String *str, char c) {

	int i = 0;
	for (i = 0; i < str->size; ++i) {

		if (str->value[i] == c) {
			return 1;
		}

	}

	return 0;

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

/*	appendCharToString(temp, str->value[startSubStr + i]); */
	setStringValue(str, temp->value);
	deleteString(temp);

	return newStr;

}

