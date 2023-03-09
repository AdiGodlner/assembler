/*
 * assembly.h
 *
 *  Created on: 3 Mar 2023
 *      Author: Adi
 */

#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include "Label.h"
#include  "Result.h"
#include  "HashTable.h"
#include "macro.h"
#include <stdio.h>
#include <stdlib.h>
/*
 *
 */
RESULT_TYPE assembler(char *srcFile);

/*
 *
 */

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList);

/*
 *
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList);
/*
 *
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList);
/*
 *
 */
void secoundPassAssembler();

/*
 *
 */
int isLabel(String *str);



/*
 * This function get a lable name as a parameter,
 * it check if the name allready exists in the Lable table,
 * if so it printes an relevant error message.
 * it checkes that the lable name isn't longer than the MAX_LENGTH,
 *  if else printes an relevant error message.
 * Last check this function does it's checkint if the lable name starts with a letter,
 * if else printes an relevant error message.
 *
 */


/*
 *
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleNonLabel(char *word, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleData(String *line, Node *dataBinarysList, int *DCPtr);
/*
 *
 */
RESULT_TYPE handleString(String *line, Node *dataBinarysList, int *DCPtr);
/*
 *
 */
RESULT_TYPE handleExtern(String *line, Node *dataBinarysList, int *DCPtr);
/*
 *
 */
RESULT_TYPE handleEntry(String *line, Node *dataBinarysList, int *DCPtr);
/*
 *
 */
void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type, int address);





/*
 *
 */
int isData(char *str);

/*
 *
 */
int isStringData(char *str);

/*
 *
 */
int isExtern(char *str);

/*
 *
 */
int isEntry(char *str);

#endif /* ASSEMBLY_H_ */
