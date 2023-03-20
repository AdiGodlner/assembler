/*
 * macro.h
 *
 *  Created on: 15 Feb. 2023 г.
 *      Author: Daria
 */

#ifndef MACRO_H_
#define MACRO_H_


#define MAX_LINE_LEN 82
#include "HashTable.h"
#include "Result.h"
#include <stdio.h>
#include <stdlib.h>




/*
 * This method receives a source file and looks for a macros in the text,
 * when a macro is found this method checks if a macro with such name already exists,
 * if not it checks if macro name is not a reserved name like 'mov' or 'jmp'
 *	if it is not a reserved name then
 *  it inserts it  to the table with the macro name as key
 * and macro body (i.e the macro definition )as the value
 * @param asFile - the given source file to search for macros in.
 * @param table - the table we'll store macros in (if exist in file).
 * @param line - the max line length a line can be till the '\n' sign.
 * @return - returns  resType SUCCESS a macro with the same name did not already exist,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]);


/*
 * This method opens the source file for reading,
 * And when the macros are parsed successfully creates an .am file for writing.
 * the name of the file stays the same just the suffix changes,
 * (example prog.as is changed to prog.am)
 * The .am file contain same input as the src file, but without the macro definition,
 * just the macro body is placed in to the .am file.
 * @param srcFile - the source file name
 * @return - returns  resType SUCCESS if all macros defined in the srcFile are valid
 * a valid macro is defined in the documentation of readMacro
 *  otherwise that method returns a RESULT_TYPE based on the error it found
 */
RESULT_TYPE macroParse(char *srcFile);

/*
 * This method receives 'fileName', 'suffix' as parameters.
 * @param fileName - the .as file name that need to be changed.
 * @param suffix - the suffix .am changes the .as file  to .am file.
 * @return - returns the ne file name.
 */
String* filenameChange(char *fileName, char *suffix);

/*
 * This method is used to print an error message when there is a problem with opening a file.
 * @param fileName - the file name of the text file that can't be opened.
 */
void printFileError(char *fileName);


/*
 * This method gates a macro 'name' as a parameter,
 * and checks if it matches any of command or label names.
 * @param name - the macro name that need to be checked.
 * @return - returns 0 if a match is found, else 1.
 */
int ismcrNamevalid(char *name);


/*
 * This method gets a text line and it removes extra whitespace if found,
 * @param line - the cureent line.
 */
void textCorrecter(char *line);

/*
 * This method checks if a given string 'line' is only filled with blank spaces ,
 * @param line - the cureent line.
 */
int isblankLine( char *line);


#endif /* MACRO_H_ */
