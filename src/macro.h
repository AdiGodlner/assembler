/*
 * macro.h
 *
 *  Created on: 15 Feb. 2023 г.
 *      Author: Daria
 */

#ifndef MACRO_H_
#define MACRO_H_


#define MAX_LINE_LEN 82
#define MAX_MACRO_NAME_LEN 32
//#define MAX_FILE_NAME 156
#define MAX_MACROS 1000
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>




/*
 * This function looks for a macros in the text.
 * When a macro is found this function checkes
 * if a macro with such name allready exists,
 * prints a relevant error message.
 * Else it places the macro name to a macro table,
 * and it designate the macro body to place it later in to the .am fila,
 */
void readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]);


/*
 * This function opens the source file for reading,
 * And when the macros are parsed successfully creates an .am file for writing.
 * the name of the file stays the same just the suffix changes,
 * (examle prog.as is changed to prog.am)
 * The .am file contain same input as the sorce file, but without the macro defenition,
 * just the macro body is placed in to the /am file.
 */
void macroParse(char *srcFile);

/*
 * This function changes the source file name  to .am file
 */
String* filenameChange(char *fileName, char *suffix);

/*
 * This function is used to print an error message when there is aproblem whith opening a file.
 */
void printFileError(char *fileName);


/*
 * This function gates a macro name as a parameter,
 * and chacks if it matches any of command or lable names,
 * if a match is found an error message is printed and we EXIT_FAILURE,
 * else we print a succcess message and EXIT_SUCCSESS.
 */
int ismcrNamevalid(char *name);


/*
 * This function resives a text and performs three tasks:
 * it removes blank lines and extra whitespace,
 * and ckecks for illegal commas and missing brackets.
 */
void textCorrecter(char *line);

/*TODO*/
int isblankLine( char *line);


#endif /* MACRO_H_ */
