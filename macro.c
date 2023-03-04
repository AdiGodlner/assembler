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

void readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]) {

	String *macroBody = createNewString("");
	String *macroName;
	String *nameWarp = createNewString(line + 4);
	macroName = popWord(nameWarp);

	if(getValueByKeyString(table, macroName) != NULL){

		printf("error macro with %s is already defined", macroName->value);
		EXIT_FAILURE;

	}
	deleteString(nameWarp);
	EXIT_SUCCESS;


//*		//TODO: check all chars after end of macro name
//*		//TODO: exit after this error or stop file processing?

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {

//*		//TODO check if macro name is not an illegal name like "mov"
		checkmcrName("LOOP");


		/*Find the end of the macro definition*/
		char *macroEnd = strstr(line, "endmcr");
		if (macroEnd) {

			if(!isspace(macroEnd+1)){
				//TODO: check all chars after end of macro
				/*Illegal parametrs after end of of macro*/
				printf("ERROR: Illegal parametrs after end of macro.");
				EXIT_FAILURE;
			}

//*			//TODO: exit after this error or stop file processing?
			insertToTable(table, macroName->value, macroBody);
			deleteString(macroName);

			EXIT_SUCCESS;

		} else {
			appendToString(macroBody, line);
		}

	}

}

/*
 * opens src copies macros to macro table
 * and unroll them to am file
 ** TODO add tabs to format lables
 */
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

	/*Read input line by line till we see a macro, and copy the scr file into the dest file without the macros we found*/
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();
	String *firstWord;
	void * macroBody;

	while (fgets(line, MAX_LINE_LEN, asFile) != NULL) {

		if (strncmp(line, "mcr ", 4) == 0) {
			readMacro(asFile, table, line);

		}
		else {

			setStringValue(lineString, line);
			firstWord = popWord(lineString);
			printf("|%s|", firstWord->value);
			macroBody = getValueByKeyString(table, firstWord);

			if (macroBody != NULL ) {

				fputs(((String*)macroBody)->value, amFile);
				deleteString(firstWord);

			}else{
				fputs(line, amFile);
			}


		}
	}
	/*Close input and output files*/
	fclose(asFile);
	fclose(amFile);
	deleteString(destFile);
	deleteString(lineString);
	printTable(table);//*TODO delete print table-makes an error is deleteTable is used
	printf("macro parsed successfully");

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

void checkmcrName(char *name){

	/*List of commands and label names to check against*/
    char *names[] = {"move", "cmp", "add", "sub",
    		"not","clr","lea","inc","dec","jmp",
			"bne", "red", "prn", "jsr","rts","stop",
			"MAIN", "LOOP", "L1", "END",
    		"STR", "LENGTH", "K"
    };
    int i;
    /*Check if the name matches any command or labels*/
    for (i=0; i < sizeof(names)/sizeof(names[0]); i++){
    	if (strcmp(name, names[i]) == 0){
    	/*Name matches, so it's not a valid  macro name*/
    	printf("Invalid macro name %s, It matches a command or lable name.\n", name);

    	EXIT_FAILURE;
        }
    }
       /*Name does'nt match any of the command or lable names*/
       printf("Macro name %s is valid.\n", name);
       EXIT_SUCCESS;
}





/*Print if an error uccured with opening file */
void printFileError(char *fileName) {

	fprintf(stderr, "\n************************************\n");
	fprintf(stderr, "   Error: Failed to open file %s\n", fileName);
	fprintf(stderr, "\n************************************\n");

}

