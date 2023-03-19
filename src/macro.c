/*
 *  Name       : macro.c
 *  Author     : Daria K
 *  Version    : 12.02.2023
 *
 */

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "macro.h"
#include "HashTable.h"
#include "Result.h"

RESULT_TYPE readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]) {

	String *macroBody = createNewString("");
	String *macroName;
	String *nameWarp = createNewString(line);
	macroName = popWord(nameWarp);

	if (getValueByKeyString(table, macroName) != NULL) {

		printf("error macro with %s is already defined", macroName->value);

		deleteString(nameWarp);
		deleteString(macroName);

		return MACRO_NAME_ALREADY_EXIST;

	}

	deleteString(nameWarp);

	if (!ismcrNamevalid(macroName->value)) {

		deleteString(macroName);
		printf("Invalid macro name %s, It matches a command or lable name.\n",
				macroName->value);

		return MACRO_NAME_IS_RESERVED;

	}

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {

		int i;

		/*Find the end of the macro definition*/
		char *macroEnd = strstr(line, "endmcr");
		if (macroEnd) {
			for (i = 6; i < strlen(macroEnd); i++) {

				if (!isspace(macroEnd[i])) {

					printf("\n ERROR: Illegal parametrs after end of macro.\n");
					deleteString(macroName);
					deleteString(macroBody);
					return EXTRANEOUS_TEXT;
				}

			}

			insertToTable(table, macroName->value, macroBody);
			deleteString(macroName);

			return SUCCESS;

		} else {
			if (line[0] == ';') {
				/* this line is a comment and we do not copy it to the am file */
				continue;
			}
			if (isblankLine(line)) {
				continue;
			}

			textCorrecter(line);
			appendToString(macroBody, line);

		}

	}
	return SUCCESS;

}

RESULT_TYPE macroParse(char *srcFile) {

	RESULT_TYPE resType = SUCCESS;
	char *amSuffix = ".am";
	char line[MAX_LINE_LEN];
	void *macroBody;
	HashTable *table = createDefualtHashTable();
	String *amFileName = filenameChange(srcFile, amSuffix);
	String *firstWord, *lineString;
	FILE *amFile;

	/*Open .as src file to read from */
	FILE *asFile = fopen(srcFile, "r");

	if (!asFile) {
		deleteTable(table, deleteString);
		deleteString(amFileName);
		printFileError(srcFile);
		return FILE_OPEN_FAILURE;
	}

	/*Open .am file to write to */
	amFile = fopen(amFileName->value, "w");

	if (!amFile) {

		deleteTable(table, deleteString);
		deleteString(amFileName);
		printFileError(amFileName->value);
		return FILE_OPEN_FAILURE;

	}

	/* Read input line by line till we see a macro,
	 * and copy the src file into the dest file without the macro name wrap we found,
	 *  only macro body will be passed to .am file*/

	lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {

		if (line[0] == ';') {
			/* this line is a comment and we do not copy it to the am file */
			continue;
		}
		if (isblankLine(line)) {
			continue;
		}

		textCorrecter(line);

		setStringValue(lineString, line);
		firstWord = popWord(lineString);

		if (strncmp(firstWord->value, "mcr", 3) == 0) {

			resType = readMacro(asFile, table, lineString->value);
			if (resType) {
				deleteString(firstWord);
				break;
			}
		} else {

			macroBody = getValueByKeyString(table, firstWord);

			if (macroBody != NULL) {

				fputs(((String*) macroBody)->value, amFile);

			} else {
				fputs(line, amFile);
			}

		}

		deleteString(firstWord);

	}

	/*Close input and output files*/
	fclose(asFile);
	fclose(amFile);

	if (resType) {
		/* Encountered an error while preprocessing so we delete the .am file */
		remove(amFileName->value);

	} else {

		printf("\n %s was preprocessed successfully !\n", srcFile);
		printf(" and written to %s \n", amFileName->value);

	}

	/*free space on the heap*/
	deleteString(amFileName);
	deleteString(lineString);
	deleteTable(table, deleteString);

	return resType;

}

String* filenameChange(char *fileName, char *suffix) {

	String *newFileName;
	char *dotPos;

	/*check the position of the last dot in the file name*/
	dotPos = strrchr(fileName, '.');

	/*Copy filename up to dot position */
	newFileName = stringNCopy(fileName, dotPos - fileName);

	/*Add the new filename extension */
	appendToString(newFileName, suffix);

	return newFileName;

}
int ismcrNamevalid(char *name) {

	/*List of commands and label names to check against*/
	char *names[] = { "move", "cmp", "add", "sub", "not", "clr", "lea", "inc",
			"dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", ".string",
			".data", ".extrn", ".entry", "string", "data", "extrn", "entry",
			"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };
	int i;
	/*Check if the name matches any command or labels*/
	for (i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
		if (strcmp(name, names[i]) == 0) {
			/*Name matches, so it's not a valid  macro name*/

			return 0;
		}
	}
	return 1;

}

/* removes extra blank spaces*/
void textCorrecter(char *line) {

	int i, j, k, len;

	len = strlen(line);

	/*Remove extra whitespace*/
	for (i = j = 0; i < len; i++) {
		if (!isspace(line[i])) {
			line[j] = line[i];
			j++;

		} else {
			k = i + 1;
			while (isspace(line[k])) {
				k++;
			}
			i = k - 1;
			line[j] = ' ';
			j++;

		}
	}

	line[j] = '\n';
	j++;
	line[j] = '\0';
}

int isblankLine(char *line) {

	int i;
	int len = strlen(line);

	/*check if line contains only blank spaces */
	for (i = 0; i < len; i++) {
		if (isspace(line[i])) {
			if (line[i] == '\n') {
				return 1;
			}

		} else {
			return 0;
		}

	}
	return 0;

}

/*Print if an error occurred when trying to open file */
void printFileError(char *fileName) {

	fprintf(stderr, "\n**************************************************\n");
	fprintf(stderr, "   Error: Failed to open file %s\n", fileName);
	fprintf(stderr, "\n**************************************************\n");

}
