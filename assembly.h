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
 * This function gets a srcFile, and check if there wer any entry lables in the text file,
 * If so it stores the entry lables in the entry lable list, to check that an entry lable has
 * a definition in our text, if the entry lable is undefined, we throw a proper error,
 * else if a lable with definition is found we store it in the lableTable with it's address.
 * After it we put the entry lable name and address in an .ent file in a format as: LABLE     100.
 * If no entry lables were found were not deleting the .ent file if already it has been created.
 */
RESULT_TYPE entryPassToFile(char *srcFile, Node *entryList, HashTable *symbolTable);
/*
 *
 */
void assembler(char *srcFile);

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
		int address);
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
