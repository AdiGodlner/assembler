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
 * This method receives a sorce file and looks for a macros in the text,
 * when a macro is found this method checkes if a macro with such name allready exists,
 * if not it places the macro name into a macro table,
 * and it designate the macro body to place it later in to the .am file,
 * @param asFile - the given sorce file to search for macros in.
 * @param table - the table we'll store macros in (if exist in file).
 * @param line - the max line lenghth a line can be till the '\n' sign.
 * @return - returns  resType SUCCESS if every thing was hendeled with success,
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
 * @param srcFile - the sorce file after macro parssing, that need to be changed to .am file.
 * @return - returns  resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
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
 * and chacks if it matches any of command or lable names.
 * @param name - the macro name that need to be checked.
 * @return - returns 0 if a match is found, else 1.
 */
int ismcrNamevalid(char *name);


/*
 * This method resives a text line and it removes extra whitespace if found,
 * @param line - the cureent line.
 */
void textCorrecter(char *line);

/*
 * This method resives a text line and it removes blank lines if found,
 * @param line - the cureent line.
 */
int isblankLine( char *line);


#endif /* MACRO_H_ */
