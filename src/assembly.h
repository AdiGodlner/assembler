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
#include <stdio.h>
#include <stdlib.h>



/*
 *
 */
RESULT_TYPE foobar(Node *entryList, HashTable *symbolTable, char *srcFileName);
/*
 *
 */
void assemble(char *srcFile);

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
void secoundPassAssembly();

/*
 *
 */
int isLabel(String *str);
/*
 *
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleNonLabel(char *word, String *line, HashTable * labelsTable,
		Node *instructionBinarysList, Node *dataBinarysList, Node *entryList,
		int *ICPtr, int *DCPtr) ;

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
RESULT_TYPE handleExtern(HashTable *labelsTable, String *line);
/*
 *
 */
RESULT_TYPE handleEntry(HashTable *labelsTable, String *line, Node *entryList) ;
/*
 *
 */
void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type,
		int addres);
/*
 *
 */
RESULT_TYPE checkLabelLegality(HashTable *labelsTable, char *labelName) ;
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
