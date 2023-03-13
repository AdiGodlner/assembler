/*
 * assembly.h
 *
 *  Created on: 3 Mar 2023
 *      Author: Adi
 */

#ifndef ASSEMBLY_H_
#define ASSEMBLY_H_

#include <stdio.h>

#include "HashTable.h"
#include "Label.h"
#include "LinkedList.h"
#include "opcode.h"
#include "Result.h"
#include "String.h"

/*
 *
 */
/*
 * This function gets a srcFile, and check if there wer any entry lables in the text file,
 * If so it stores the entry lables in the entry lable list, to check that an entry lable has
 * a definition in our text, if the entry lable is undefined, we throw a proper error,
 * else if a lable with definition is found we store it in the lableTable with it's address.
 * After it we put the entry lable name and address in an .ent file in a format as: LABLE     100.
 * If no entry lables were found were not deleting the .ent file if already it has been created.
 */
RESULT_TYPE writeEntryToFile(char *srcFile, Node *entryList,
		HashTable *symbolTable);
/*
 *
 */
void assembler(char *srcFile);

/*
 *
 */

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr);

/*
 *
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr);
/*
 *
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *labelTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
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
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleNonLabel(char *word, String *line, HashTable *labelsTable,
		Node *instructionBinarysList, Node *dataBinarysList,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleInstructions(char *word, String *line,
		Node *instructionBinarysList, int *ICPtr);
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
RESULT_TYPE handleEntry(HashTable *labelsTable, String *line,
		Node **entryListPtr);
/*
 *
 */
void insertLabel(char *labelName, HashTable *labelsTable, LABEL_TYPE type,
		int addres);
/*
 *
 */
RESULT_TYPE checkLabelLegality(char *labelName);

RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node *instructionBinarysList, int *ICPtr);

/*
 *
 */
Set* createParamBinaryWord(String *param, int addresingType);
int isInstructionParamValid(String *param);

int getParamAddresingType(String *param);
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
