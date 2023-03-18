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
 * This method iterate over keys in symbol table, and add's IC
 * To LABEL->ADRESS for labels of TYPE data.
 * It receives 'symboltable' and 'IC' as parameters.
 * @param symbolTable - the symbol table, that IC is added to lables of type DATA in it.
 * @param IC - the counter that set all decimal address in RAM to start from 0100.
 */
void fixLabelCounters(HashTable *symbolTable, int IC);
/*
 * This method receives 'srcFile','entryListand','symbolTable' as parameters.
 * It check if there where any entry lables in the text file,
 * If so it stores the entry lables in the entry lable list, to check later that an entry lable is
 * defined in the text,
 * if the entry lable is undefined, we throw a proper error message,
 * After what we create an entry file and open it in writing mode.
 * the entry lable name and address is writen into an .ent file in a format as: LABLE     100.
 * If no entry lables were found we're deleting the .ent file if it has been already created.
 * @param srcFile - the source file we look in for labels.
 * @param entryList - the list that the entry labels will be stored in.
 * @param symbolTable - the symbol table that the labels are stored in by there name and address value.
 * @return - returns the resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
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
 * If an error appears in the pass, we'll print a proper error message,
 * then stop reading the current file and move to the next one if exists.
 */
void assembler(char *srcFile);


/*
 * This method receives 'scrFile', 'symbolTable', 'instructionBinarysListPtr',
 * 'dataBinarysListPtr',,'ICPtr', 'DCPtr' as parameters.
 * @param srcFile - the given sorce file.
 * @param symbolTable - the symbol table that all labels are stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov'...'stop'
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to  empty place in list that the next .entry label will get stored in.
 * @param ICPtr - the instruction counter is passed to handleLabel().
 * @param DCPtr - the data counter is passed to handleLabel().
 * @return - returns resType of SUCCESS if the first pass was passed succesfully
 * or a proper error message that First Pass has failed.
 */
RESULT_TYPE firstPass(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr, int *ICPtr,
		int *DCPtr);
/*
 *
 * This method open the srcFile (.am file) in reading mode.
 * It receives 'scrFile', 'symbolTable', 'instructionBinarysListPtr','dataBinarysListPtr',
 * 'entryListPtr','ICPtr', 'DCPtr' as parameters and passes
 * them to firstPassAssembler() method for further handeling.
 * @param srcFile - the given sorce file.
 * @param symbolTable - the symbol table that all labels are stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to  empty place in list that the next .entry label will get stored in.
 * @param ICPtr - the instruction counter is passed to handleLabel().
 * @param DCPtr - the data counter is passed to handleLabel().
 * @return - returns resType of SUCCESS if the first pass was passed succesfully
 * or a proper error message that First Pass has failed.
 */
RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPTR, int *DCPtr);

/*
 * This method  receives 'amFile', 'symbolTable', 'instructionBinarysListPtr', 'dataBinarysListPtr',
 * 'entryListPtr','ICPtr', 'DCPtr'  as parameters.
 * It prints the number of line where an error has accurued.
 * All parameters are passed to lineFirstPass() method for further handeling.
 * @param amFile - the given .am file.
 * @param symbolTable - the symbol table that all labels are stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov'..'stop'.
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data',
 * @param entryListPtr - pointes to the next empty place in list that the .entry label will get stored in.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 * This method receives String 'lineString', 'symbolTable', 'instructionBinarysListPtr', 'dataBinarysListPtr',
 * 'entryListPtr', 'ICPtr', 'DCPtr' as parameters.
 * It take the text of a currerent line and divide the text into two "cases"
 * handleLabel(), handleNonLabel().
 * The first take care only of the label that is found in the line and check if is legal.
 * The second take care of rest of the line from the label part and till the ent of line.
 * @param lineString - the given line represented as String.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov'...'stop'.
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data.
 * @param entryListPtr - pointes to the next empty place in list that the .entry label will get stored in.
 * @param ICPtr - the instruction counter is passed to handleLabel().
 * @param DCPtr - the data counter is passed to handleLabel().
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *symbolTable,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 * This method receives a sorce file, and creates an extern file and an object file and opens them in writing mode.
 * It  receives 'srcFile', 'symbolTable', 'binarysList',
 * 'IC', 'DC' as parameters.
 * @param scrFile - the given source file after macro parse.
 * @param symbolTable - the symbol table that all labels name and address will be taken from.
 * @param binarysList - the list that the binary data is stored in. TODO??
 * @param IC - the number of the instraction values represented in RAM.
 * @param DC - the number of the data values represented in RAM.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE secoundPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *binarysList, int IC, int DC);

/*
 * This method receives an extern file and an object file.
 * After what all .extern lable,from simbolTable are writen to the .extern file,(if they exist).
 * All  missing labels address get complited, the "words" of 14-bits get insert to RAM.
 * The "words" in RAM get writen to an .ob file in a special binary symbols code
 * which are represanted by: 0 = '.' & 1 = '/'.
 * @param obFile - the given object file that the "words" in RAM are writen to.
 * @param externFile - the given extern file that all .extern lables are writen to.
 * @param symbolTable - the symbol table that all labels name and address will be taken from.
 * @param binarysList - pointes to all instruction commands as 'mov',
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE secoundPassAssembly(FILE *obFile, FILE *externFile,
		HashTable *symbolTable, Node *binarysList);

/*
 * This method receives 'obFile','binaryWord','index' as parameters.
 * After what the RAM 14- bits "words" are writen to the
 * .ob file in a special binary symbol code as: 1 = '/' & 0 = '.'.
 * @param obFile - the given file we write in.
 * @param binaryWord - the special binary symbol code.
 * @param index - the given index value.
 */
void writeToObFile(FILE *obFile, Set *binaryWord, int index);

/*
 * This method receives 'externFile','lableName','index' as parameters.
 * It check if there where any extern lables in the text file,
 * If so it pulls them from the symbolTable.
 * After what we create an extern file and open it in writing mode.
 * the extern lable name and address is writen into the .extern file in a format as: LABLE     100.
 * If no extern lables were found we're deleting the .ext file if it has been already created.
 * @param externFile - the source file we look in for labels.
 * @param labelName - the given label name.
 * @param index - the given index value.
 */
void writeToExternFile(FILE *externFile, String *labelName, int index) ;

/*
 * This method receives a String, and check if a label is defined corectly,
 * @param str - the given String that we search for label in it.
 * @return - returns the index of the placeholder after ':' , if the method has failed returns -1.
 */
int isLabel(String *str);

/*
 * This method receives 'str' parameter and checks is the given 'str' is a corect definition of a register.
 * The registers can be only r0-r7, if so return true, else false value.
 * @param str - the given str, to be checked.
 * @return - returns the true or false value.
 */
int isRegister(String *str);

/*
 * This method receives 'labelName', 'symbolTable', 'line' 'instructionBinarysListPtr', 'dataBinarysListPtr',
 * 'entryListPtr', 'ICPtr', 'DCPtr' as parameters.
 * It take care only of the label that is found in the line, check if is legal.
 * @param labelName - the given label name.
 * @param symbolTable - the symbol table that all labels are stored in.
 * @param line - the current line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label are stored in.
 * @param ICPtr - the instruction counter.
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *symbolTable, String *line,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method receives  'word', 'symbolTable', 'line', 'instructionBinarysListPtr', 'dataBinarysListPtr',
 * 'entryListPtr', 'ICPtr', 'DCPtr' as parameters.
 * It take care of rest of the line from the "after label part" and till the ent of line.
 * @param word - the given curent word that we're on in the line String.
 * @param symbolTable - the symbol table that all labels will get stored in.
 * @param line - the current line.
 * @param instructionBinarysListPtr - pointes to all instruction commands as 'mov',
 * @param dataBinarysListPtr - pointes to all data type as '.string' , '.data,
 * @param entryListPtr - pointes to the next empty place in list that the .entry label are stored in.
 * @param ICPtr - the instraction counter.
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleNonLabel(char *word, HashTable *symbolTable, String *line,
		Node **instructionBinarysListPtr, Node **dataBinarysListPtr,
		Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method places the 'word' in the given line in binary code to the RAM 14-bits "word".
 * This method receives  'word',  'line',  'instructionBinarysListPtr',  'ICPtr'.
 * @param word - the current word we're pointing at.
 * @param line - the current line.
 * @param instructionBinarysListPtr -  helps insert the  instruction
 * commands as 'mov'...'stop' to the right place of the list.
 * @param ICPtr - the instraction counter.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleInstructions(char *word, String *line,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method places the found data to the end of list so at the end we receive
 * a list of instruction and then the data as we were ask in the project.
 * This method receives  'line', 'dataBinarysListPtr','DCPtr'.
 * @param line - the current line.
 * @param dataBinarysListPtr - pointes to all data  as: .data 1,2,-3,
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleData(String *line, Node **dataBinarysListPtr, int *DCPtr);

/*
 * This method places the found data to the end of list so at the end we receive
 * a list of instruction and then the data as we were ask in the project.
 * This method receives  'line', 'dataBinarysListPtr','DCPtr'.
 * @param line - the current line.
 * @param dataBinarysListPtr - helps insert all the String's
 * data in ASCII value  as: .string "abc" to data binary list.
 * @param DCPtr - the data counter.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleString(String *line, Node **dataBinarysListPtr, int *DCPtr);

/*
 * This method searches for the  extern lable name and address in the Simbol table.
 * This method receives  'SimbolTable', 'line'.
 * @param SimbolTable - the simbol table that we take the extern lable address from if exists.
 * @param line - the current line..
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleExtern(HashTable *symbolTable, String *line);
/*
 * This method takes the lable name from the lable entry list if exists,
 * and searches for the  entry lable address in the Simbol table.
 * This method receives  'SimbolTable', 'line','entryListPtr'.
 * @param SimbolTable - the simbol table that we take the entry lable address from,
 * if such lable exist in the entryList.
 * @param line - the current line.
 * @param EntryListPtr - helps insert the entry lable to the entry list.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleEntry(HashTable *symbolTable, String *line,
		Node **entryListPtr);

/*
 * This method check if a lable name is valid and isn't one of the reserved words.
 * @param name - the given lable name.
 * @return - returns 0 - if lable name maches one of the reserved words, else 1.
 */
int isLableNamevalid(char *name);
/*
 * This method receives 'labelName', 'SimbolTable', 'type', 'address'.
 * @param labelName - the given name.
 * @param SimbolTable - the simbol table that we insert lable to it by type and address.
 * @type - the given lable type entry/extern.
 * @address - the specific line address the lable was stored in the text file,
 * the lable is insert by it to the Simbol table.
 */
void insertLabel(char *labelName, HashTable *symbolTable, LABEL_TYPE type,
		int addres);
/*
 * This method check if the lable name is legal.
 * if the lable name starts with a lower or capital letter and only leters
 * or numbers apears after it as: "LABLE:".
 * if the length of label name is not longer than 30.
 * @param lable name  - the given lable name tha needs to be checked.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE checkLabelLegality(char *labelName);

/*
 * This method convert the line with the opcode to a 14- bits "word" and insert it to the right place in RAM.
 * This method receives 'line', 'opcode', 'instructionBinarysListPtr', 'ICPtr'.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: mov, cmp...stop gets placed  in 6-9 bits.
 * @param instructionBinarysListPtr - helps insert the instruction commands to the right place of the list.
 * @param ICPtr - the instraction counter.
 * gets increased when an instruction is found and shows where the next instruction will get placed.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method convert the line with the opcode to a 14- bits "word" and insert it to the right place in RAM.
 * This method receives 'line', 'opcode', 'instructionBinarysListPtr', 'ICPtr'.
 * It check
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: jmp,jsr,bne gets placed  in 6-9 bits.
 * @param instructionBinarysListPtr - helps insert the instruction commands to the right place of the list.
 * @param ICPtr - the instruction counter.
 * gets increased when an instruction is found and shows where the next instruction will get placed.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleAdvancedOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method take care of case when the opcode comands as: jmp,jsr,bne
 * have only one operand with no parameters. Example: bne END
 * It check that the operend is a destanation operand, and that it's a label.
 * All the parameters are passed to handleAdvancedOpcodeLabel() to be converted
 * and insert  to the right place in RAM.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: jmp,jsr,bne gets placed  in 6-9 bits.
 * @param opCodeNode - the binary code node. TODO ??
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleAdvancedOpcodeWIthOutBackets(String *line, Opcode *opCode,
		Node *opCodeNode);
/*
 * This method take care of case when the opcode comands as: jmp,jsr,bne
 * have  one operand with two parameters. Example: jmp L1(#-1,r6)
 * It check that the operend is a destanation operand,
 * and that the operand and the parameters are valid.
 * comand name (jmp,jsr,bne) space the lable then an opening bracket first param
 * then comma then second param and closing brackets.
 * All the parameters are passed to handleAdvancedOpcode() to be converted
 * and insert to the right place in RAM.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: jmp,jsr,bne gets placed  in 6-9 bits.
 * @param opCodeNode - the binary code node gets placed  in 2-3 bits and 10-11, 12-13 bits. TODO ??
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleAdvancedOpcodeWIthBackets(String *line, Opcode *opCode,
		Node *opCodeNode, int *numOfWordsPtr);
/*
 * This method check if the lable definition is legal convert it to binary and places it to right place in RAM.
 * It receives 'lable', 'opCodeNode'.
 * @param lable - the given lable that need to be checked.
 * @param opCodeNode - the binary representation of lable. TODO??
 * @raturn - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleAdvancedOpcodeLabel(String *label, Node *opCodeNode);
/*
 * This method switch the line with the parameters to a 14- bits "word" and insert it to the right place in RAM.
 * This method receives 'line', 'opcode', 'opCodeNode', 'numOfWords'.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: mov, cmp...stop gets placed  in 6-9 bits.
 * and the opcode operrands get placed in 2-3 and 4-5 bits.
 * @param opCodeNode - gets passed to handlescrParam() and handledestParam().
 * @param numOfWords - the word counter - check if the number of operands are valid for current command opcode.
 * example: mov, cmp, add, sub, lea - need to receive exactly two operands, srcParam and destParam.
 * gets increased when an word opeares, it's added to the numOfWords count.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleParameters(String *line, Opcode *opCode, Node *opCodeNode,
		int *numOfWords);
/*
 * This method switch the line with the parameters to a 14- bits "word" and insert it to the right place in RAM.
 * This method receives 'line', 'opcode', 'opCodeNode', 'numOfWords'.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: mov, cmp...stop gets placed  in 6-9 bits.
 * and the opcode operrands if it's a src register 2-7
 * @param opCodeNode - are passed from handleParameters() to be checked.
 * @param isSrcRegisterPtr - check if the source operand is a register.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleSrcParam(String *line, Opcode *opCode, Node *opCodeNode,
		int *isSrcRegisterPtr);
/*
 * This method switch the line with the parameters to a 14- bits "word" and insert it to the right place in RAM.
 * This method receives 'line', 'opcode', 'opCodeNode','isSrcRegister' ,'numOfWords'.
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: 'mov''...'stop' gets placed  in 6-9 bits.
 * and the opcode operrands if it's a dest register gets placed  in 8-13 bits.
 * @param opCodeNode - the Node that was passed from handelParameters() to be checked.
 * @param isSrcRegister - check if the dest operand is a register.
 * @param numOfWords - check if both of the operands are registers- they will share
 * the same "word" in RAM srcRegister 2-7 bits and destRegister 8-13 bits.
 * @return - returns resType SUCCESS if every thing was hendeled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleDestParam(String *line, Opcode *opCode, Node *opCodeNode,
		int isSrcRegister, int *numOfWords);

/*
 * This method receives 'addresingSet', 'addresingType'.
 * @param addresingSet - is passed to isValueinSet() method.
 * @param addresingType - is passed to isValueinSet() method.
 * @return - returns 0 if address type is Invalid or else the received value
 * from isValueinSet() method.
 */
int isAddresingTypeValid(Set *addresingSet, int addresingType);

/*
 * This method receives 'param', 'addresingType', and check is the param a number,
 * a register or a lable depending on the given addresingType
 * @param param - the given param.
 * @param addresingType - the given addresing type that the param will be insert to RAM based on it.
 * Example: addresingType == 0 Instant mode, addresingType == 1 means is a Direct mode,
 * addresingType == 2 is a Relative mode,addresingType == 3 Direct Register mode.
 * @return - returns the node.
 */
Node * createParamBinaryWord(String *param, int addresingType);


/*
 * This method checks is the 'param' has valid number definition,
 * Example: #-1, #2. if a hashh opeares before the number and the negetive number has a minus definer '-',
 * is considerate to be valide.
 * @param param - the given param.
 * @return - returns 1 if it's a valid number definition
 * or else returns 0.
 */
int isInstructionParamValid(String *param);

/*
 * This method checks what type of addressing is the 'param'.
 * @param param - the given param.
 * @return - returns 0 if it's anumber
 * returns 3 if it's a register(r0-r7) or else if it's a label returns 1.
 */
int getParamAddresingType(String *param);

/*
 * This method checks if the given 'str' matches the data definition,
 * @param str - the given Sring.
 * @return - returns 0 if matches the data definition, returns -1 if str < ".data",
 * it means the String is to short, or else returns 1 if it's to long.
 */
int isData(char *str);

/*
 * This method checks if the given 'str' matches the data definition,
 * @param str - the given Sring.
 * @return - returns 0 if matches the data definition, returns -1 if str < ".string",
 * it means the String is to short, or else returns 1 if it's to long.
 */
int isStringData(char *str);

/*
 * This method checks if the given 'str' matches the data definition,
 * @param str - the given Sring.
 * @return - returns 0 if matches the data definition, returns -1 if str < ".extern",
 * it means the String is to short, or else returns 1 if it's to long.
 */
int isExtern(char *str);

/*
 * This method checks if the given 'str' matches the data definition,
 * @param str - the given Sring.
 * @return - returns 0 if matches the data definition, returns -1 if str < ".entry",
 * it means the String is to short, or else returns 1 if it's to long.
 */
int isEntry(char *str);

#endif /* ASSEMBLY_H_ */
