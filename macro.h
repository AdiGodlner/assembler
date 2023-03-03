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



/*Structure to hold macro information*/
typedef struct {
    char *mcr_name[MAX_MACRO_NAME_LEN];
    char *begin;
    char *end;
}MacroInfo;



/*
 *
 */
void insertMacro(HashTable *macroTable, char *mcrName, char *begin,
		char *end);

/*
 *
 */
MacroInfo* find_macro(const char* mcr_name);

/*
 *
 */

void readMacro(FILE *asFile, HashTable *table, char line[MAX_LINE_LEN]);
/*
 *
 */
void macroParse(char *srcFile) ;

/*
 *
 */
String* filenameChange(char *fileName, char *suffix);

/*
 *
 */
void printFileError(char *fileName);


#endif /* MACRO_H_ */
