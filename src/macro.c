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

/*TODO change to int and return correct value depending of what we want to do */

RESULT_TYPE readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]) {

	String *macroBody = createNewString("");
	String *macroName;
	String *nameWarp = createNewString(line);
	macroName = popWord(nameWarp);

	if (getValueByKeyString(table, macroName) != NULL) {

		printf("error macro with %s is already defined", macroName->value);
		return MACRO_NAME_ALREADY_EXIST;

	}
	deleteString(nameWarp);

	if (!ismcrNamevalid(macroName->value)) {
		printf("Invalid macro name %s, It matches a command or lable name.\n",
				macroName->value);
	}

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {

		int i;

		/*Find the end of the macro definition*/
		char *macroEnd = strstr(line, "endmcr");
		if (macroEnd) {
			for (i = 6; i < strlen(macroEnd); i++) {

				if (!isspace(macroEnd[i])) {

					printf("\n ERROR: Illegal parametrs after end of macro.\n");
					return EXTRANEOUS_TEXT;
				}

			}


			insertToTable(table, macroName->value, macroBody);
			deleteString(macroName);

			return SUCCESS;

		} else {
			appendToString(macroBody, line);
		}

	}
	return SUCCESS;

}


RESULT_TYPE macroParse(char *srcFile) {

	char *amSuffix = ".am";
	char line[MAX_LINE_LEN];
	void *macroBody;
	HashTable *table = createDefualtHashTable();
	String *destFile = filenameChange(srcFile, amSuffix);
	String *firstWord, *lineString ;
	FILE *amFile ;

	/*Open scr file .as*/
	FILE *asFile = fopen(srcFile, "r");/*read from file*/

	if (!asFile) {
		printFileError(srcFile);
		return FILE_OPEN_FAILURE;
	}

	/*Open dest file .am*/
	amFile = fopen(destFile->value, "w");/*read and write to the file*/
	if (!amFile) {
		printFileError(destFile->value);
		return FILE_OPEN_FAILURE;

	}

	/* Read input line by line till we see a macro,
	 * and copy the scr file into the dest file without the macro name wrap we found,
	 *  only macro body will be passed to .am file*/

	lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {
		if(isblankLine(line)){
			continue;
		}
		textCorrecter(line);


		setStringValue(lineString, line);
		firstWord = popWord(lineString);

		if (strncmp(firstWord->value, "mcr", 3) == 0) {
			readMacro(asFile, table, lineString->value);

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

	printf("\nmacro where parsed successfully!\n");

	/*Close input and output files*/
	fclose(asFile);
	fclose(amFile);

	/*free space on the heap*/
	deleteString(destFile);
	deleteString(lineString);
	deleteTable(table, deleteString);
	return SUCCESS;

}

String* filenameChange(char *fileName, char *suffix) {

	String *newFileName;
	char *dotPos;

	/*check the position of the last dot in the file name*/
	dotPos = strrchr(fileName, '.');
	if (!dotPos) {
		/*Wrong filename input file name does not contain a legal suffix*/
		/*TODO: check if dotpos = allowed suffix ".am" ".as" "/foo" */
		printf("Error: Illegal file name.\n");
		return NULL;
	}

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

/*Check that there aren't any illegal commas, brackets and if there is a blank line removes it same for extra spaces*/
void textCorrecter(char *line) {

	int i, j, k, len;

	len = strlen(line);




	/*Remove extra whitespace*/
	for (i = j = 0; i < len; i++) {
		if (!isspace(line[i])) {
			line[j] = line[i];
			j++;

		} else {
			k = i+1;
			while(isspace(line[k])){
				k++;
			}
			i = k-1;
			line[j] = ' ';
			j++;


		}
	}
	/* we remove extra whitespace*/
	line[j] = '\n';
	j++;
	line[j] = '\0';
}


int isblankLine(char *line){


	int i;
	int len = strlen(line);

	/*Removes blank lines*/
	for(i= 0; i< len; i++){
		if (isspace(line[i])){
			if(line[i] =='\n'){
			return 1;
			}

		}else{
			return 0;
		}

	}
	return 0;

}


/*Print if an error uccured with opening file */
void printFileError(char *fileName) {

	fprintf(stderr, "\n************************************\n");
	fprintf(stderr, "   Error: Failed to open file %s\n", fileName);
	fprintf(stderr, "\n************************************\n");

}
