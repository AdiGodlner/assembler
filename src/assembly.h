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
 * This method receives a srcFile, an entryListand a symbolTable as parameters.
 * It check if there where any entry lables in the text file,
 * If so it stores the entry lables in the entry lable list, to check later that an entry lable is
 * defined in the scrFile text.
 * @param srcFile - the source file we look in for labels.
 * @param entryList - the list that the entry labels will be stored in.
 * @param symbolTable - the symbol table that the labels are stored in by there name and address value.
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
 * After we ensure that the entry lable was defined in the text,
 * we put the entry lable name and address in an .ent file.
 * The .ent file is opened in a writing mode and we print to it
 * in a format as: LABLE     100.
 * If no entry lables were found we're deleting the .ent file if it has been already created.
 * @return - returns the resType.
 * if the entry lable is undefined in the text,we return RESULT_TYPE error message.
 * In the end we close the opened .entFile and we free all poiners, that were dynamicly allocated.
 */
RESULT_TYPE writeEntryToFile(char *srcFile, Node *entryList,
		HashTable *symbolTable);
/*
 * This method receives a sorce file(.am).
 * @param src - The received sorce file.
 * build the Simbol table, build a ICList, a DCList, and a EntryList,
 * and poineters to each one of them.
 * It check for all labels that apeares in the .am file content.
 * If an .entry label is found,
 * it gets printed in to a separated .ent file with the writeEntryToFile() method.
 * and buildes the 14- bits "words" line in RAM ,excluding the Labels address,
 * that are going to be stored in only in second pass.
 * If an error appears in the pass, we'll print aproper error message,
 * then stop reading the current file and move to the next one if exists.
 */
void assembler(char *srcFile);


/*
 *
 */
RESULT_TYPE firstPass(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr, int *ICPtr,
		int *DCPtr);
/*
 * This method receives a scrFile, which is changed to be an .am file.
 * It receives symbolTable, instructionBinarysListPtr, dataBinarysListPtr,
 * This entryListPtr as parameters, wich are passed by the assembler method to it.
 * and is passed to firstPassFileOpen() method.
 * @param srcFile - the given sorce file.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the next .entry label will get stored in.
 * @return - returns resType of SUCCESS if the first pass was passed succesfully
 * or a proper error message that First Pass has failed.
 */
RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPTR, int *DCPtr);

/*
 * This method opens an amFile, it receives amFile, symbolTable, instructionBinarysListPtr, dataBinarysListPtr,
 * This entryListPtr as parameters, wich are passed by the firstPassFileOpen() method to it.
 * It prints the number of line where an error has accurued.
 * All parameters are passed to lineFirstPass() method.
 * @param amFile - the given source  file after macro parse.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label will get stored in.
 * @return - returns resType
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 * This method receives String lineString, symbolTable, instructionBinarysListPtr, dataBinarysListPtr,
 * This entryListPtr, ICPtr and DCPtr as parameters.
 * It take the text of a currerent line and divide the text to two "cases"
 * handleLabel(), handleNonLabel().
 * The first take care only of the label that is found in the line, check if is legal.
 * The second take care of rest of the line from the label part and till the ent of line.
 * @param lineString - the given source  file after macro parse.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label will get stored in.
 * @param ICPtr - the instruction counter is passed to handleLabel().
 * @param DCPtr - the data counter is passed to handleLabel().
 * @return - returns resType SUCCESS
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *labelTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 * This method opens an amFile, it receives amFile, symbolTable, instructionBinarysListPtr, dataBinarysListPtr,
 * This extrListPtr as parameters, wich are passed by the secondPassFileOpen() method to it.
 * It prints the number of line where an error has accurued. ???TODO
 * All parameters are passed to lineSecondPass() method.
 * @param amFile - the given source file after macro parse.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param extrnListPtr - pointes to the next empty place in list that the .extern label will get stored in.
 * @return - returns resType
 *
 * in Second pass: we're completing the missing address of lables in binary code,
 * using the simbol table and the extrList, all "words" in RAM get converted to a special binary
 * symbols which are represanted by:[ '0' = '.' & '1' = '/'] and they get writen to an .ob file.
 * If an .extern label was found in the text, we write it to  an .extern file.
 * If an error occurred in the second pass,
 * we'll stop reading the current file and move to the next one if exists.
 *
 */
RESULT_TYPE secoundPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *binarysList, int IC, int DC);

/*
 * This method receives a String, and check if a label is defined corectly,
 * the length of label name is not longer than 30,
 * The lable name starts with a lower or capital letter and only leters
 * or numbers apears after it as: "LABLE:".
 * @param str - the given String that we search for label in it.
 * @return - returns the index of the placeholder after ':' , if the method has failed returns -1.
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
 * This method receives a labelName, symbolTable, line instructionBinarysListPtr, dataBinarysListPtr,
 * This entryListPtr, ICPtr and DCPtr as parameters.
 * It take care only of the label that is found in the line, check if is legal.
 * @param labelName - the given label name.
 * @param symbolTable - the symbol table that all labels are stored in.
 * @param line - the current line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label are stored in.
 * @param ICPtr - the instruction counter.
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS
 */
int isRegister(String *str);
/*
 *
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *labelsTable, String *line,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method receives a word, symbolTable, line instructionBinarysListPtr, dataBinarysListPtr,
 * This entryListPtr, ICPtr and DCPtr as parameters.
 * It take care of rest of the line from the "after label part" and till the ent of line.
 * @param word - the given curent word that we're on in the line String.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param line - the current line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label are stored in.
 * @param ICPtr - the instraction counter.
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS
 */
RESULT_TYPE handleNonLabel(char *word, HashTable *labelsTable, String *line,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method places the 'word' in the given line in binary code to the RAM 14-bits "word".
 * This method receives a word, a line, an instructionBinarysListPtr, int *ICPtr.
 * @param word - the curent word we're pointing at.
 * @param line - the curent line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param ICPtr - the instraction counter.
 * @return - returns resType SUCCESS
 */
RESULT_TYPE handleInstructions(char *word, String *line,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method places the 'word' in the given line in binary code to the 14-bits "word" in RAM.
 * This method receives a word, a line, an instructionBinarysListPtr, int *ICPtr.
 * @param word - the curent word we're pointing at.
 * @param line - the curent line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param ICPtr - the instraction counter.
 * @return - returns resType SUCCESS
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

int isLableNamevalid(char *name);
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
