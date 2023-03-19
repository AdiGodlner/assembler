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
 * This method iterate over keys in symbol table, and add's IC + RAM stating index
 * To LABEL->ADRESS for labels of TYPE data.
 * and TO labels of TYPE INSTRUCTION adds RAM stating index
 * It receives 'symbolTable' and 'IC' as parameters.
 * @param symbolTable - the table containing all the labels in the file,
 * @param IC - last number of the instruction counter (IC).
 */
void fixLabelCounters(HashTable *symbolTable, int IC);
/*
 * This method checks that every label in entryList list was defined in the srcFile
 * and was not also defined as an .extern label
 * the entry label name and address is written into an .ent file in a format as: label     100.
 * @param srcFile - the source file we look in for labels.
 * @param entryList - a list of all entry labels found in src file.
 * @param symbolTable - the table containing all the labels in the file.
 * @return - returns the resType SUCCESS if all entry labels in the list were found in symbol table
 * and where not also defined as .extern
 * returns FILE_NOT_FOUND if the method could not open a .ent file,
 * returns UNDEFINED_ENTRY_LABLE if a labels in enteryList was not defined,
 * returns LABEL_IS_EXTERN_AND_ENTRY if a label was defined both as entry and as extern.
 */
RESULT_TYPE writeEntryToFile(char *srcFile, Node *entryList,
		HashTable *symbolTable);
/*
 * This method translated the simplified assembly code after preprocessing given in srcFile
 * to binary machine code and writes it to a 'srcFile'.ob file
 * if external or entry labels exists it writes them to
 * 'srcFile'.ext and 'srcFile'.ent respectively  (as specified in the white paper )
 * @param srcFile - the file name of the given src file.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * If an error appears in the pass, we'll print a proper error message.
 */
void assembler(char *srcFile, HashTable *opCodeTable);

/*
 * This method does the first pass of the assembly process
 *	if entry labels where found it creates the .ent file
 *
 * @param srcFile - the given source file.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * or a proper error message that First Pass has failed.
 * otherwise it will print an error message and
 *  returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE firstPass(char *srcFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, int *ICPtr, int *DCPtr);
/*
 * This method open the srcFile (.am file) in reading mode.
 * and continues the first pass of the assembly process
 * @param srcFile - the given source file.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * or a proper error message that First Pass has failed.
 * otherwise it returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPTR, int *DCPtr);

/* This method continues the first pass of the assembly process,
 * If an error appears in the pass, we'll print a proper error message
 * with number of line where the error has occurred.
 * @param amFile - the given .am file.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * otherwise it returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr);
/*
 * This method excepts a line String form .am file and continues the first pass of the assembly process
 * on that given line
 * @param lineString - the given line represented as String.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * otherwise it returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE lineFirstPass(String *lineString, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method  continues the first pass of the assembly process
 * of lines containing a label deceleration.
 *
 * @param labelName - first word of the line or the first.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param line - the current line.
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * otherwise it returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE handleLabel(char *labelName, HashTable *symbolTable,
		HashTable *opCodeTable, String *line, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method  continues the first pass of the assembly process
 * of lines which do not contain a label or
 * if a line contians a label this method processes the part after the label name
 *
 * @param word - first word of the line or the first word of the line after the label deceleration
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param line - the current line.
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param entryListPtr - a linked list to store all entry labels.
 * @param ICPtr - a pointer to the instruction counter.
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType of SUCCESS if the first pass was passed successfully
 * otherwise it returns a different RESULT_TYPE based on the error it encountered.
 */
RESULT_TYPE handleNonLabel(char *word, HashTable *symbolTable,
		HashTable *opCodeTable, String *line, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr);

/*
 * This method continues the first pass of the assembly process
 * for instructions if an instruction line is valid
 * this method creates the known binary words and pushes them to the end 'instructionBinarysList' list
 * and if a labelName is used a node containing the label name is pushed to 'instructionBinarysList'
 * in its relevant position
 *
 * @param word - the current word we're pointing at.
 * @param opCodeTable  - a table containing all of the Opcode commands (as specified in the white paper )
 * @param line - the current line.
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param ICPtr - a pointer to the instruction counter.
 * @return - returns resType SUCCESS if instruction line is valid
 * and the function was able to create the binary words described above
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE handleInstructions(char *word, HashTable *opCodeTable, String *line,
		Node **instructionBinarysListPtr, int *ICPtr);

/*
 * This method continues the first pass of the assembly process
 * for data if the .data line is valid
 * This method creates binary words representing the integers
 * given in the .data line and places them to the end of 'dataBinarysList' list.
 *
 * @param line - the current line.
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType SUCCESS if data line is valid
 * and the function was able to create the binary words described above
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE handleData(String *line, Node **dataBinarysListPtr, int *DCPtr);

/*
 * This method continues the first pass of the assembly process
 * for data of type .string  if the .string line is valid
 * This method creates binary words each binary word represents
 * ASCII value of a char in the string.
 * and pushes them to the end of 'dataBinarysList' list.
 *
 * @param line - the current line.
 * @param dataBinarysListPtr -  a linked list to all data type such as '.string' , '.data,
 * @param DCPtr - a pointer to the data counter.
 * @return - returns resType SUCCESS if data line is valid
 * and the function was able to create the binary words described above
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE handleString(String *line, Node **dataBinarysListPtr, int *DCPtr);

/*
 * This method checks if a line that started with .extern is valid
 * if it is it inserts the label into the symbolTable.
 *
 * if the label name is already
 * defined and the label has a LABEL_TYPE the is not EXTERNAL
 * then this method returns an error
 *
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param line - the current line..
 * @return - returns resType SUCCESS if the current .extern line is valid
 * or a proper error per the description above RESULT_TYPE.
 */
RESULT_TYPE handleExtern(HashTable *symbolTable, String *line);

/*
 * This method searches for the entry label in the Symbol table
 * if it finds a label of type EXTERNAL it returns an error otherwise it adds the .entry label to
 * the entryList
 *
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param line - the current line.
 * @param entryListPtr - a linked list to store all entry labels.
 * @return - returns resType SUCCESS if the entry label was added successfully to the list ,
 * proper error per the description above RESULT_TYPE.
 */
RESULT_TYPE handleEntry(HashTable *symbolTable, String *line,
		Node **entryListPtr);

/*
 * This method check if a label name is valid and isn't one of the reserved words.
 * @param name - the given label name.
 * @return - returns 0 if label name matches one of the reserved words or is not a valid label name
 * (as specified in the white paper )
 * , else 1.
 */
int isLableNamevalid(char *name);

/*
 * This method inserts the label  into the symbolTable.
 * @param labelName - the given name.
 * @param symbolTable - the symbol table that all labels will be stored in.
 * @param type - the given label type DATA/INSTRUCTION/EXTERNAL.
 * @param address - the specific line address ( IC / DC ) of the label.
 */
void insertLabel(char *labelName, HashTable *symbolTable, LABEL_TYPE type,
		int addres);
/*
 * This method check if the label name is legal. a label name is legal
 * if the label name starts with a lower or capital letter and only contains
 * alphanumeric chars after,
 * and the length of label name is not longer than 30.
 * and if the label name is not a reserved name such as 'r3' or 'mov'
 *
 * @param label name  - the given label name that needs to be checked.
 * @return - returns resType SUCCESS if the given label name is legal as described above
 * or  RESULT_TYPE depending on the error encountered.
 */
RESULT_TYPE checkLabelLegality(char *labelName);

/*
 * This method checks if a given line is a valid for simple Opcodes
 * ( we consider simple opcode those who do not have
 * Addressing mode of type 2 (jump addressing with parameters))
 *
 * if the line is valid then the method creates the relevant binary words and pushes them to the end of
 * instructionBinarysList and advances IC by the number of binary words created
 *
 * a line will be considered valid if the given number of  operands  is equal to the allowed number of
 *  operands for a given opCode
 *  and the operands given to it are valid operands for the given opCode
 * for example src operand of mov can be a label a register or a number
 * but the dest operand of move can only be a register or a label
 * if this method finds the dest operand in to be a label when the opCode represents move
 * then the line will not be considered valid because a label dest operand is not allowed for an opCode of
 * type move (as specified in the white paper )
 *	and the line does not contain any extra text after the allowed  operands
 *
 * @param line - the given line that needs to be translated in to a binary code.
 * @param opcode - the given opcode of the command (such as: mov, cmp...stop)
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param ICPtr - a pointer to the instruction counter.
 * @return - returns resType SUCCESS if the given line is valid and all binary words were successfully created
 * or different RESULT_TYPE depending on the error it encountered.
 */
RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method checks if a given line is a valid for advanced Opcodes
 * ( we consider an advanced opcode those who have
 * Addressing mode of type 2 (jump addressing with parameters))
 *
 * if the line is valid then the method creates the relevant binary words and pushes them to the end of
 * instructionBinarysList and advances IC by the number of binary words created
 *
 * a line will be considered valid if the line only contains a valid label name
 * or if it contains a valid label name followed by parenthesis containing valid parameters
 *  separated by a comma (as specified in the white paper )
 without any extra text after the label in the former case or after the parenthesis after the latter

 *
 * @param line - the given line that needs to be translated in to a binary code.
 * @param opcode - the given opcode of the command (such as: jmp, bne)
 * @param instructionBinarysListPtr - a linked list to all instruction commands such as 'mov'...'stop'
 * @param ICPtr - a pointer to the instruction counter.
 * @return - returns resType SUCCESS if the given line is valid and all binary words were successfully created
 * or different RESULT_TYPE depending on the error it encountered.
 */
RESULT_TYPE handleAdvancedOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr);
/*
 * This method take care of case when the opcode comands as: jmp,jsr,bne
 * have only one operand with no parameters. Example: bne END
 * It check that the operend is a label.
 * if it is a label and does not contain any extra text after it
 * the method creates the relevent binary words and pushes them to the end of opCodeNode list
 *
 * @param line - the given line that needs to be transform in to a binary code.
 * @param opcode - the given opcode of the command (such as: jmp, bne)
 * @param opCodeNode - a list Node containing the binary word of the opCode
 * @return - returns resType SUCCESS if the line is valid as per described above ,
 * or different RESULT_TYPE depending on the error it encountered.
 */
RESULT_TYPE handleAdvancedOpcodeWIthOutParameters(String *line, Opcode *opCode,
		Node *opCodeNode);
/*
 This method take care of case when the opcode comands as: jmp,jsr,bne
 *	this method checks that the line is a valid line
 *  a line will be considered valid if the line only contains a valid label
 *  name followed by parenthesis containing valid parameters
 *  separated by a comma (as specified in the white paper )
 *  without any extra text after the parenthesis after
 *
 *	if the line is valid it create the relvent binary words and pushes them to the end of opCodeNode
 *	which is a list containing the binary word representing Opcode
 *
 *	then the method inserts the number of binary words it created to numOfWordsPtr\
 *
 * @param line - the given line that needs to be transform in to a binary code.
 * @param opcode - the given opcode of the command (such as: jmp, bne)
 * @param opCodeNode - a list Node containing the binary word of the opCode
 * @param numOfWordsPtr -  a pointer to store the number of binary words this method created
 * @return - returns resType SUCCESS if the line is valid as per described above ,
 * or different RESULT_TYPE depending on the error it encountered.
 */
RESULT_TYPE handleAdvancedOpcodeWIthParameters(String *line, Opcode *opCode,
		Node *opCodeNode, int *numOfWordsPtr);
/*
 * This method check if the label definition is legal convert it to binary word
 * and pushes it to the end of opCodeNode list
 * It receives 'label', 'opCodeNode'.
 * @param label - the given label that need to be checked.
 * @param opCodeNode - the binary representation of label. TODO??
 * @raturn - returns resType SUCCESS the label is leagal as described above,
 * or RESULT_TYPE describing the error that occurred.
 */
RESULT_TYPE handleAdvancedOpcodeLabel(String *label, Node *opCodeNode);

/*
 * this method checks if the given currParamPtr is a valid( i.e either a number a label or a register )
 * if it is create a binary word and pushes it to the tail of opCodeNode list
 * if the parameter is of type register then the method sets the value pointed to by isSrcRegisterPtr to 1

 this method also writes the first parameter addressing type to the relevant place in opCodebinary word stored in the
 first node of opCodeNode

 * @param currParamPtr - a string representing the given first parameter
 * @param opCodeNode - a node containing the binary word of the opCode
 * @param isSrcRegisterPtr - int to write to if the parameter is of type register
 * @raturn - returns resType SUCCESS the label is legal as described above,
 * or RESULT_TYPE describing the error that occurred.
 *
 */
RESULT_TYPE handleFirstParameter(String *currParamPtr, Node *opCodeNode,
		int *isSrcRegisterPtr);

/*
 * * this method checks if the given currParamPtr is a valid( i.e either a number a label or a register )
 *
 *
 * if it is then the method checks if the current parameter is of type register
 * if the previous parameter was also a register as indicated by the value of isSrcRegister
 * then the method writes the binary representation of the register to the binary word
 * created by the first parameter
 * which is in the 3 node in the opCodeNode list
 *
 * if either this param is not a register or the first param was not a register then this method
 * create a binary word and pushes it to the tail of opCodeNode list

 this method adds the number of new binary words it created and pushed to the numOfWords pointer

 * @param currParamPtr - a string representing the given first parameter
 * @param opCodeNode - a node containing the binary word of the opCode
 * @param isSrcRegisterPtr - int declaring if the previous param was of type register
 * @param numOfWords - a pointer to write the number of words created by this method
 * @raturn - returns resType SUCCESS the label is legal as described above,
 * or RESULT_TYPE describing the error that occurred.
 *
 */
RESULT_TYPE handleSecondParameter(String *currParamPtr, Node *opCodeNode,
		int isSrcRegister, int *numOfWords);

/*
 *
 * this method handles the creation of binary words for operands for simple Opcodes
 *  ( we consider simple opcode those who do not have
 * Addressing mode of type 2 (jump addressing with parameters))
 * if the given line is valid i.e operands are of a type allowed to the given type of opcode
 * and the number of parameters is equal to the number of parameters expected b given opcode
 * and opCode does not contain any extra text after the operand
 *
 * then this method creates the relevant binary words and pushes them to the end of opCodeNode list
 *	and writes the number of words it created to numOfWords
 *
 *	the method also writes the addressing types of the operands to the binary word of opcode
 *	which resides in the first node of opCodeNode list
 *
 * @param line - the given line that needs to be transformt in to a binary code.
 * @param opcode - the given opcode command as: mov, cmp...stop
 * @param opCodeNode - a node containing the binary word of the opCode
 * @param numOfWords - a pointer to write the number of words created by this method
 * @return - returns resType SUCCESS if the operands are valid as described above,
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE handleOperands(String *line, Opcode *opCode, Node *opCodeNode,
		int *numOfWords);
/*
 * this method handles the src operand of simple opcode
 * ( we consider simple opcode those who do not have
 * Addressing mode of type 2 (jump addressing with parameters))
 *
 *	this method takes the first operand from the given line and checks if its valid
 *	(as specified in the white paper )
 *	if it is then this method creates the binary representation of that operand and pushes it
 *	to the end of opCodeNode
 *
 *	the method also writes the addressing types of the operands to the binary word of opcode
 *	which resides in the first node of opCodeNode list
 *
 * @param line - the given line that needs to be transformed in to a binary code.
 * @param addressing - the set representing the allowed operand addressing types
 *  e.g (operand->destAddressing or operand->srcAddressing)
 *
 * @param opCodeNode - a node containing the binary word of the opCode
 * @param isSrcRegisterPtr - a parameter to set if the given operand is of type register
 * @return - returns resType SUCCESS if every thing was handled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleSrcOperand(String *line, Set *addressing, Node *opCodeNode,
		int *isSrcRegisterPtr);
/*
 * this method handles the dest operand of simple opcode
 * ( we consider simple opcode those who do not have
 * Addressing mode of type 2 (jump addressing with parameters))
 *
 *	this method takes the dest operand from the given line and checks if its valid
 *	(as specified in the white paper )
 *	 if it is then the method checks if the current operand is of type register
 * if the previous operand was also a register as indicated by the value of isSrcRegister
 * then the method writes the binary representation of the register to the binary word
 * created by the first node
 * which is in the 2 node in the opCodeNode list
 *
 * if either this operand is not a register or the first operand was not a register then this method
 * create a binary word and pushes it to the tail of opCodeNode list
 *
 *	the method also writes the addressing types of the operands to the binary word of opcode
 *	which resides in the first node of opCodeNode list
 *
 * @param line - the given line that needs to be transformed in to a binary code.
 * @param addressing - the set representing the allowed operand addressing types
 *  e.g (operand->destAddressing or operand->srcAddressing)
 *
 * @param opCodeNode - a node containing the binary word of the opCode
 * @param isSrcRegisterPtr - a parameter to note if the src operand was of type register
 * @param numOfWords - a pointer to the number of words created by this method
 *
 * @return - returns resType SUCCESS if every thing was handled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE handleDestOperand(String *line, Set *addressing, Node *opCodeNode,
		int isSrcRegister, int *numOfWords);

/*
 * this method checks if the addresing type represented by the number 'addresingType'
 * exsists in the addressing Set 'addresingSet'
 *
 * @param addresingSet - the set representing the allowed addressing types
 *  e.g (operand->destAddressing or operand->srcAddressing.
 * @param addresingType - integer representing the addressing type.
 * @return - returns 0 if address type is Invalid and 1 if it is valid
 */
int isAddresingTypeValid(Set *addresingSet, int addresingType);

/*
 * This method creates a node containing a binaryWord of the given param
 * or if the given param is of addresingType = 1 i.e is a label then the method creates a
 * node containing a string with the name of the label
 *
 * a register or a label depending on the given addresingType
 * @param param - the given param.
 * @param addresingType - the given addressing type that the param will be insert to RAM based on it.
 * Example: addresingType == 0 Instant mode, addresingType == 1 means is a Direct mode,
 * addresingType == 2 is a Relative mode,addresingType == 3 Direct Register mode.
 * @return - returns a node containng either a binary word represented by a set
 * or if the paramm is Label then the node contains a String containing the name of the label .
 */
Node* createParamBinaryWord(String *param, int addresingType, int isSrc);

/*
 * This method receives a source file, and creates a .ob file
 * containing the binary code and a .ext file (as specified in the white paper )

 * @param srrcFile - the src file Name .
 * @param symbolTable - the symbol table that all labels name and address .
 * @param binarysList - the list that the binary data is stored in.
 * @param IC - the number of the instruction binaryWords
 * @param DC - the number of the data binaryWords.
 * @return - returns resType SUCCESS if it successfully created the binary .ob file wrote to  it
 * the binady code needed and if needed created the .ext file and wrote to it all the calls to labels
 * that are stored in .ext file ,
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE secoundPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *binarysList, int IC, int DC);

/*
 * This method receives a source file, and creates a .ob file
 * containing the binary code and a .ext file (as specified in the white paper )
 *
 * @param obFile - the given object file to write the binary into s
 * @param externFile - the given extern file that all .extern labels are written to.
 * @param symbolTable - the symbol table that all labels name and address will be taken from.
 * @param binarysList - pointes to all instruction commands as 'mov',
 * @return - returns resType SUCCESS if every thing was handled with success,
 * or a proper error RESULT_TYPE message.
 */
RESULT_TYPE secoundPassAssembly(FILE *obFile, FILE *externFile,
		HashTable *symbolTable, Node *binarysList);

/*
 * This method writes a binary word to the .ob file
 *
 *	in the following format
 *	A\tB
 *	where A is four letter number representing the place in RAM given by index
 *	and B is the binary word written when insted of normal binary
	 1 is replaced with '/'  is replaced with 0 = '.'.
 *
 * @param obFile - the given file we write in.
 * @param binaryWord - a set representing the binary WOrd.
 * @param index - the given index value in RAM.
 */
void writeToObFile(FILE *obFile, Set *binaryWord, int index);

/*
 * this method writes to externFile in the following format
 * A\tB where
 * A is the labelName
 * and B is a three digit number representing the place in RAM given by index
 * @param externFile - the .ext to write to .
 * @param labelName - the given label name.
 * @param index - the given index value in RAM.
 */
void writeToExternFile(FILE *externFile, String *labelName, int index);

/*
 * This method receives a String, and check if it ends with ':',
 * @param str - the given String that we search for label in it.
 * @return - returns 0 if the string does not end in ':' and 1 if it does
 */
int isLabel(String *str);

/*
 * This method receives 'str' parameter and checks is the given 'str' is a correct definition of a register.
 * The registers can be only r0-r7, if so return true, else false value.
 * @param str - the given str, to be checked.
 * @return - returns the 1 if the string represnts a register or 0 if it does not .
 */
int isRegister(String *str);

/*
 * This method checks is the 'param' has valid number definition,
 * Example: #-1, #2. if a hash operas before the number and the negetive number has a minus definer '-',
 * is considerate to be valide.
 * @param param - the given param.
 * @return - returns 1 if it's a valid number definition
 * or else returns 0.
 */
int isInstructionParamValid(String *param);

/*
 * This method returns what type of addressing is the 'param'.
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
