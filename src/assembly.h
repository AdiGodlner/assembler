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
void fixLabelCounters(HashTable *symbolTable, int IC);
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
RESULT_TYPE firstPass(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr, int *ICPtr,
		int *DCPtr);
/*
 *
 */
RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPTR, int *DCPtr);

/*
 *
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 *
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *labelTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 *
 */
RESULT_TYPE secoundPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *binarysList, int IC, int DC);

/*
 *
 */
RESULT_TYPE secoundPassAssembly(FILE *oFile, FILE *externFile,
		HashTable *symbolTable, Node *binarysList);

/*
 *
 */
void writeToOFile(FILE *oFile, Set *binaryWord, int index);
/*
 *
 */
void writeToExternFile(FILE *externFile, String *labelName, int index) ;
/*
 *
 */
int isLabel(String *str);
/*
 *
 */
int isRegister(String *str);
/*
 *
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleNonLabel(char *word, String *line, HashTable *labelsTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 *
 */
RESULT_TYPE handleInstructions(char *word, String *line,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 *
 */
RESULT_TYPE handleData(String *line, Node **dataBinarysListPtr, int *DCPtr);
/*
 *
 */
RESULT_TYPE handleString(String *line, Node **dataBinarysListPtr, int *DCPtr);
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

/*
 *
 */
RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 *
 */
RESULT_TYPE handleAdvancedOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 *
 */
RESULT_TYPE handleAdvancedOpcodeWIthOutBackets(String *line, Opcode *opCode,
		Node *opCodeNode);
/*
 *
 */
RESULT_TYPE handleAdvancedOpcodeWIthBackets(String *line, Opcode *opCode,
		Node *opCodeNode, int *numOfWordsPtr);

RESULT_TYPE handleAdvancedOpcodeLabel(String *label, Node *opCodeNode);
/*
 *
 */
RESULT_TYPE handleParameters(String *line, Opcode *opCode, Node *opCodeNode,
		int *numOfWords);
/*
 *
 */
RESULT_TYPE handleSrcParam(String *line, Opcode *opCode, Node *opCodeNode,
		int *isSrcRegisterPtr);
/*
 *
 */
RESULT_TYPE handleDestParam(String *line, Opcode *opCode, Node *opCodeNode,
		int isSrcRegister, int *numOfWords);

/*
 *
 */
int isAddresingTypeValid(Set *addresingSet, int addresingType);
/*
 *
 */
Node* createParamBinaryWord(String *param, int addresingType);
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
