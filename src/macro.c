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

//TODO change to int and return corect value depending of what we want to do

void readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]) {

	String *macroBody = createNewString("");
	String *macroName;
	String *nameWarp = createNewString(line);
	macroName = popWord(nameWarp);

	if (getValueByKeyString(table, macroName) != NULL) {

		printf("error macro with %s is already defined", macroName->value);
		return;

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
					return;
				}

			}


			insertToTable(table, macroName->value, macroBody);
			deleteString(macroName);

			return;

		} else {
			appendToString(macroBody, line);
		}

	}

}


void macroParse(char *srcFile) {

	HashTable *table = createDefualtHashTable();
	char *amSuffix = ".am";
	String *destFile = filenameChange(srcFile, amSuffix);

	/*Open scr file .as*/
	FILE *asFile = fopen(srcFile, "r");/*read from file*/

	if (!asFile) {
		printFileError(srcFile);
		return;
	}

	/*Open dest file .am*/
	FILE *amFile = fopen(destFile->value, "w");/*read and write to the file*/
	if (!amFile) {
		printFileError(destFile->value);
		return;

	}

	/* Read input line by line till we see a macro,
	 * and copy the scr file into the dest file without the macro name wrap we found,
	 *  only macro body will be passed to .am file*/
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();
	String *firstWord;

	void *macroBody;

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {
		if(isblankLine(line)){
			continue;
		}
		textCorrecter(line);


		setStringValue(lineString, line);
		firstWord = popWord(lineString);

		if (strncmp(firstWord->value, "mcr", 3) == 0) {
			readMacro(asFile, table, line);

		} else {

			macroBody = getValueByKeyString(table, firstWord);

			if (macroBody != NULL) {

				fputs(((String*) macroBody)->value, amFile);

			} else {
				fputs(line, amFile);
			}

		}
//
		deleteString(firstWord);
	}

	printf("\nmacro where parsed successfully!\n");

	/*Close input and output files*/
	fclose(asFile);
	fclose(amFile);
	deleteString(destFile);
	deleteString(lineString);
	printTable(table); //*TODO delete print table-makes an error is deleteTable is used

}

String* filenameChange(char *fileName, char *suffix) {

	String *newFileName;
	char *dotPos;

	/*check the position of the last dot in the file name*/
	dotPos = strrchr(fileName, '.');
	if (!dotPos) {
		/*Wrong filename input file name does not contain a legal suffix*/
		//*TODO: check if dotpos = allowed suffix ".am" ".as" "/foo"
		printf("Error: Illegal file name\n");
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
			".data", ".extrn", ".entr" };
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

/*removes blank line and  extra spaces*/
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

int isbracketLegal(char * line){
	/*Check for illegal commas and missing brackets*/

	int i, len;
	int bracketCount = 0;

	len = strlen(line);

	for (i = 0; i < len; i++) {

		if ((line[i] == ')')|| (line[i] == '(')) {

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


int isquoteLegal(char * line){

	int i = 0;
	int quoteCount = 0;


	while (line[i] != '\0') {

		if (line[i] == '"'){
			/*if we fint quote we increment the count*/
			quoteCount++;

		}
		/*if quote count is even*/
		else if (quoteCount % 2 == 0) {
			i++;

		} else{
			/*if quote count is odd or the character isn't a quote we print an proper error message*/
			printf("ERROR: Missing quotes\n");
			return 0;
		}

	}

	return 1;


}

int isCommaLegal(char *line){

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

	fprintf(stdout, "\n************************************\n");
	fprintf(stdout, "   Error: Failed to open file %s\n", fileName);
	fprintf(stdout, "\n************************************\n");

}
