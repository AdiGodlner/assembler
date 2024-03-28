/*
 * assembly.c
 *
 *  Created on: 3 Mar 2023
 *      Author: Adi
 */

#include "HashTable.h"
#include "opcode.h"
#include "assembly.h"
#include "macro.h"
#include "Result.h"
#include "Label.h"
#include "Utils.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LEN 82/*adding two to max length, for new line and null charecter*/
#define MAX_LABEL_LENGTH 30
#define RAM_START_INDEX 100
#define INSTANT_ADDRESSING_TYPE 0
#define DIRECT_ADDRESSING_TYPE 1
#define RELATIVE_ADDRESSING_TYPE 2
#define DIRECT_REGISTER_ADDRESSING_TYPE 3

void assembler(char *srcFile, HashTable *opCodeTable) {

	/*src file is .am file*/
	RESULT_TYPE resType;
	HashTable *symbolTable = createDefualtHashTable();
	Node *instructionBinarysList = NULL;
	Node **instructionBinarysListPtr = &instructionBinarysList;
	Node *dataBinarysList = NULL;
	Node **dataBinarysListPtr = &dataBinarysList;
	int IC = 0, DC = 0;

	resType = firstPass(srcFile, symbolTable, opCodeTable,
			instructionBinarysListPtr, dataBinarysListPtr, &IC, &DC);
	if (resType) {
		/* firstPass Failed */
		deleteList(instructionBinarysList);
		deleteList(dataBinarysList);
		deleteTable(symbolTable, deleteLabel);

		return;
	}

	resType = secoundPassFileOpen(srcFile, symbolTable, instructionBinarysList,
			IC, DC);

	if (resType) {
		printf("\nERROR: Second Pass has failed.\n");

	} else {
		printf("\n Second PASS - Was passed successfully.\n");

	}

	deleteList(instructionBinarysList);
	deleteTable(symbolTable, deleteLabel);

}

RESULT_TYPE firstPass(char *srcFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, int *ICPtr, int *DCPtr) {

	Node *entryList = NULL;
	Node **entryListPtr = &entryList;

	RESULT_TYPE resType = SUCCESS;
	resType = firstPassFileOpen(srcFile, symbolTable, opCodeTable,
			instructionBinarysListPtr, dataBinarysListPtr, entryListPtr, ICPtr,
			DCPtr);


	if ((*ICPtr) + (*DCPtr) > 156) {
		resType = EXCEDING_MACHINE_MEMORY;
	} else {

		fixLabelCounters(symbolTable, (*ICPtr));
		resType = writeEntryToFile(srcFile, entryList, symbolTable);
		deleteList(entryList);
	}

	if (resType) {
		printf("\n ERROR:First Pass has failed, can't move to second pass.\n");
		return resType;

	} else {
		printf(
				"\n FIRST PASS - Was passed successfully, moving over to second pass.\n");
	}

	/*chain data after instruction in the ram */
	pushTail(*dataBinarysListPtr, instructionBinarysListPtr);

	return resType;

}

/*
 * iterate over keys of symbol table add IC
 *  TO LABEL->ADRESS for labels of TYPE data
 */
void fixLabelCounters(HashTable *symbolTable, int IC) {

	int i = 0;
	Node *currNode;
	Entry *entry;
	Label *label;
	for (i = 0; i < symbolTable->size; i++) {

		currNode = symbolTable->bucketArr[i];
		while (currNode) {

			entry = (Entry*) currNode->data;
			label = (Label*) entry->value;
			label->address += RAM_START_INDEX;
			if (label->type == DATA) {
				label->address += IC;
			}
			currNode = currNode->next;

		}

	}

}

RESULT_TYPE writeEntryToFile(char *srcFile, Node *entryList,
		HashTable *symbolTable) {

	RESULT_TYPE resType = SUCCESS;
	char *entSuffix = ".ent";
	String *destFile;
	FILE *entFile;

	if (entryList == NULL) {
		return SUCCESS;
	}

	destFile = filenameChange(srcFile, entSuffix);
	entFile = fopen(destFile->value, "w");

	if (!entFile) {
		return FILE_NOT_FOUND;

	}
	Node *node = entryList;

	while (node != NULL) {

		String *name = (String*) node->data;
		Label *label = (Label*) getValueByKey(symbolTable, name->value);

		if (label == NULL) {
			resType = UNDEFINED_ENTRY_LABLE;
			break;
		}

		int labelAddress = label->address;
		/* only labels of type extern have address of -1; */
		if (labelAddress < 0) {

			resType = LABEL_IS_EXTERN_AND_ENTRY;
			break;

		}
		char addrStr[4];/*3 digit address + \0*/
		sprintf(addrStr, "%03d", labelAddress);/*Printing to file in the requested format*/
		addrStr[3] = '\0';
		fprintf(entFile, "%s\t%s\n", name->value, addrStr);

		node = node->next;/*moving to next entry label in list*/

	}

	/*closing file after use*/
	fclose(entFile);

	/*If an error occurred ,delete the file */
	if (resType) {
		remove(destFile->value);
	}

	deleteString(destFile);

	return resType;

}

RESULT_TYPE firstPassFileOpen(char *srcFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPTR, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	FILE *amFile = fopen(srcFile, "r");

	if (!amFile) {
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	/*firstPassAssembler actualy doing the passing*/
	resType = firstPassAssembler(amFile, symbolTable, opCodeTable,
			instructionBinarysListPtr, dataBinarysListPtr, entryListPtr, ICPTR,
			DCPtr);

	fclose(amFile);

	return resType;

}

RESULT_TYPE firstPassAssembler(FILE *amFile, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE lineProcesingResult = SUCCESS;
	RESULT_TYPE resType = SUCCESS;
	int lineNumber = 0;
	char line[MAX_LINE_LEN];
	String *lineString = createEmptyString();

	while (fgets(line, MAX_LINE_LEN, amFile) != NULL) {

		lineNumber++;

		setStringValue(lineString, line);
		lineProcesingResult = lineFirstPass(lineString, symbolTable,
				opCodeTable, instructionBinarysListPtr, dataBinarysListPtr,
				entryListPtr, ICPtr, DCPtr);

		if (lineProcesingResult) {

			printf("ERROR:   at line %d | error message:\n %s \n", lineNumber,
					getResultMsg(lineProcesingResult));

			if (resType == SUCCESS) {
				resType = lineProcesingResult;
			}

		}

	}



	return resType;
}

RESULT_TYPE lineFirstPass(String *lineString, HashTable *symbolTable,
		HashTable *opCodeTable, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	String *firstWord = popWord(lineString);



	if (isLabel(firstWord)) {

		resType = handleLabel(firstWord->value, symbolTable, opCodeTable,
				lineString, instructionBinarysListPtr, dataBinarysListPtr,
				entryListPtr, ICPtr, DCPtr);
	} else {

		resType = handleNonLabel(firstWord->value, symbolTable, opCodeTable,
				lineString, instructionBinarysListPtr, dataBinarysListPtr,
				entryListPtr, ICPtr, DCPtr);
		if (resType == ENTRY_CREATED || resType == EXTERN_CREATED) {
			resType = SUCCESS;
		}
	}

	deleteString(firstWord);

	return resType;

}

RESULT_TYPE handleLabel(char *labelName, HashTable *symbolTable,
		HashTable *opCodeTable, String *line, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	int currDCAddres, currICAddres;
	String *firstWord;

	labelName[strlen(labelName) - 1] = '\0';
	if (isKeyInTable(symbolTable, labelName)) {
		return LABEL_ALLREADY_EXISTS;
	}

	resType = checkLabelLegality(labelName);

	if (resType) {
		return resType;
	}

	currDCAddres = *DCPtr;
	currICAddres = *ICPtr;

	firstWord = popWord(line);

	resType = handleNonLabel(firstWord->value, symbolTable, opCodeTable, line,
			instructionBinarysListPtr, dataBinarysListPtr, entryListPtr, ICPtr,
			DCPtr);

	if (resType == SUCCESS) {
		if (currDCAddres != *DCPtr) {
			insertLabel(labelName, symbolTable, DATA, currDCAddres);
		} else {
			insertLabel(labelName, symbolTable, INSTRUCTION, currICAddres);
		}

	}

	deleteString(firstWord);

	if (resType == ENTRY_CREATED || resType == EXTERN_CREATED) {
		resType = SUCCESS;
	}

	return resType;

}

RESULT_TYPE handleNonLabel(char *word, HashTable *symbolTable,
		HashTable *opCodeTable, String *line, Node **instructionBinarysListPtr,
		Node **dataBinarysListPtr, Node **entryListPtr, int *ICPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;

	if (isData(word)) {
		resType = handleData(line, dataBinarysListPtr, DCPtr);

	} else if (isStringData(word)) {

		resType = handleString(line, dataBinarysListPtr, DCPtr);

	} else if (isExtern(word)) {

		resType = handleExtern(symbolTable, line);

	} else if (isEntry(word)) {
		resType = handleEntry(symbolTable, line, entryListPtr);

	} else {

		resType = handleInstructions(word, opCodeTable, line,
				instructionBinarysListPtr, ICPtr);

	}

	return resType;
}

RESULT_TYPE handleInstructions(char *word, HashTable *opCodeTable, String *line,
		Node **instructionBinarysListPtr, int *ICPtr) {

	RESULT_TYPE resType = SUCCESS;
	Opcode *opCode = NULL;

	if (!isKeyInTable(opCodeTable, word)) {
		printf("in ILLEGAL_OPCODE with word '%s'",word);
		return ILLEGAL_OPCODE;
	}

	opCode = (Opcode*) getValueByKey(opCodeTable, word);

	/*check if opcode is jmp jsr or bne */
	if (isValueInSet(opCode->destAddressing, RELATIVE_ADDRESSING_TYPE)) {

		resType = handleAdvancedOpcode(line, opCode, instructionBinarysListPtr,
				ICPtr);

	} else {

		resType = handleSimpleOpcode(line, opCode, instructionBinarysListPtr,
				ICPtr);

	}

	return resType;
}

RESULT_TYPE handleAdvancedOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr) {

	int numOfWords = 0;
	RESULT_TYPE resType = SUCCESS;
	Set *opCodebinaryWord = NULL;
	Node *opCodeNode = NULL;
	String *extraText = NULL;

	opCodebinaryWord = createNewSet();
	writeCodeToBinaryWord(opCodebinaryWord, opCode->code);
	opCodeNode = createNode(opCodebinaryWord, SET, NULL);
	numOfWords++;

	if (containsChar(line, '(')) {

		resType = handleAdvancedOpcodeWIthParameters(line, opCode, opCodeNode,
				&numOfWords);

	} else {
		resType = handleAdvancedOpcodeWIthOutParameters(line, opCode,
				opCodeNode);
		numOfWords++;
	}

	if (resType) {
		deleteList(opCodeNode);
		return resType;
	}

	/* check for EXtra test */
	if (line->size > 0) {

		extraText = popWord(line);

		if (extraText->size > 0) {
			deleteString(extraText);
			deleteList(opCodeNode);
			return EXTRANEOUS_TEXT;
		}

		deleteString(extraText);

	}

	pushTail(opCodeNode, instructionBinarysListPtr);
	(*ICPtr) += numOfWords;

	return resType;
}

RESULT_TYPE handleAdvancedOpcodeWIthParameters(String *line, Opcode *opCode,
		Node *opCodeNode, int *numOfWordsPtr) {

	Set *opCodeBinary;
	RESULT_TYPE resType = SUCCESS;
	int isSrcRegister = 0;

	String *label = popByDeliminator(line, '(');

	if (label == NULL) {

		return MISSING_BRACKET;
	}

	String *firstParam = popByDeliminator(line, ',');
	if (firstParam == NULL) {

		deleteString(label);
		return MISSING_COMMA;
	}

	String *secoundParam = popByDeliminator(line, ')');
	if (secoundParam == NULL) {

		deleteString(label);
		deleteString(firstParam);
		return MISSING_COMMA;

	}

	resType = handleAdvancedOpcodeLabel(label, opCodeNode);

	if (resType == SUCCESS) {

		(*numOfWordsPtr)++;
		resType = handleFirstParameter(firstParam, opCodeNode, &isSrcRegister);
		if (resType == SUCCESS) {

			(*numOfWordsPtr)++;
			resType = handleSecondParameter(secoundParam, opCodeNode,
					isSrcRegister, numOfWordsPtr);

		}

	}

	if (resType == SUCCESS) {
		opCodeBinary = opCodeNode->data;
		writeDestOperandToBinaryWord(opCodeBinary, 2);
	}

	deleteString(label);
	deleteString(firstParam);
	deleteString(secoundParam);

	return resType;

}

RESULT_TYPE handleAdvancedOpcodeWIthOutParameters(String *line, Opcode *opCode,
		Node *opCodeNode) {

	RESULT_TYPE resType = SUCCESS;
	Set *opCodeBinary;
	String *label = popWord(line);

	resType = handleAdvancedOpcodeLabel(label, opCodeNode);
	deleteString(label);

	if (resType) {
		return resType;
	}

	opCodeBinary = opCodeNode->data;
	writeDestOperandToBinaryWord(opCodeBinary, 1);

	return resType;
}

RESULT_TYPE handleAdvancedOpcodeLabel(String *label, Node *opCodeNode) {

	RESULT_TYPE resType = SUCCESS;

	if (!label->size) {
		return MISSING_PARAMETER;
	}

	resType = checkLabelLegality(label->value);
	if (resType) {

		return resType;

	}

	Node *parambinaryNode = createParamBinaryWord(label, 1, 0);
	pushTail(parambinaryNode, &opCodeNode);

	return resType;

}

RESULT_TYPE handleSimpleOpcode(String *line, Opcode *opCode,
		Node **instructionBinarysListPtr, int *ICPtr) {

	int numOfWords = 0;
	RESULT_TYPE resType = SUCCESS;
	Node *opCodeNode = NULL;
	Set *opCodebinaryWord = createNewSet();
	writeCodeToBinaryWord(opCodebinaryWord, opCode->code);
	opCodeNode = createNode(opCodebinaryWord, SET, NULL);
	numOfWords++;

	handleOperands(line, opCode, opCodeNode, &numOfWords);

	if (resType) {
		deleteList(opCodeNode);
		return resType;
	}

	pushTail(opCodeNode, instructionBinarysListPtr);

	(*ICPtr) += numOfWords;

	return resType;

}

RESULT_TYPE handleOperands(String *line, Opcode *opCode, Node *opCodeNode,
		int *numOfWordsPtr) {

	RESULT_TYPE resType = SUCCESS;
	int isSrcRegister = 0;
	String *currParamPtr;

	if (opCode->numOfParameters != 0) {

		currParamPtr = createEmptyString();

		if (opCode->numOfParameters == 2) {

			resType = popArgument(line, currParamPtr, 0);
			if (resType) {
				deleteString(currParamPtr);
				return resType;
			}

			resType = handleSrcOperand(currParamPtr, opCode->srcAddressing,
					opCodeNode, &isSrcRegister);
			(*numOfWordsPtr) += 1;

			if (resType) {
				deleteString(currParamPtr);
				return resType;
			}

		}

		setStringValue(currParamPtr, "");
		resType = popArgument(line, currParamPtr, 1);

		if (resType) {
			deleteString(currParamPtr);
			return resType;
		}
		resType = handleDestOperand(currParamPtr, opCode->destAddressing,
				opCodeNode, isSrcRegister, numOfWordsPtr);
		deleteString(currParamPtr);
	}

	if (!isblankLine(line->value)) {
		return EXTRANEOUS_TEXT;
	}

	return resType;

}

RESULT_TYPE handleFirstParameter(String *currParamPtr, Node *opCodeNode,
		int *isSrcRegisterPtr) {

	RESULT_TYPE resType = SUCCESS;
	Set *opCodebinaryWord = (Set*) opCodeNode->data;
	Node *parambinaryNode = NULL;
	int addresingType = -1;

	if (!isInstructionParamValid(currParamPtr)) {
		return ILLEGAL_PARAM;
	}

	addresingType = getParamAddresingType(currParamPtr);

	writeFirstParameterToBinaryWord(opCodebinaryWord, addresingType);
	parambinaryNode = createParamBinaryWord(currParamPtr, addresingType, 1);
	pushTail(parambinaryNode, &opCodeNode);

	if (addresingType == 3) {
		(*isSrcRegisterPtr) = 1;
	}
	return resType;

}

RESULT_TYPE handleSecondParameter(String *currParamPtr, Node *opCodeNode,
		int isSrcRegister, int *numOfWords) {

	RESULT_TYPE resType = SUCCESS;
	Set *opCodebinaryWord = (Set*) opCodeNode->data;
	Node *parambinaryNode = NULL;
	int addresingType = -1;

	if (!isInstructionParamValid(currParamPtr)) {
		return ILLEGAL_PARAM;
	}

	addresingType = getParamAddresingType(currParamPtr);
	writeSecondParameterToBinaryWord(opCodebinaryWord, addresingType);

	if (isSrcRegister && addresingType == 3) {

		Node *srcNode = opCodeNode->next->next;
		Set *srcBinary = (Set*) srcNode->data;
		writeDestRegiserToBinaryWord(srcBinary, atoi(currParamPtr->value + 1));

	} else {

		parambinaryNode = createParamBinaryWord(currParamPtr, addresingType, 0);
		pushTail(parambinaryNode, &opCodeNode);
		(*numOfWords) += 1;

	}

	return resType;

}

RESULT_TYPE handleSrcOperand(String *currParamPtr, Set *addressing,
		Node *opCodeNode, int *isSrcRegisterPtr) {

	RESULT_TYPE resType = SUCCESS;
	Set *opCodebinaryWord = (Set*) opCodeNode->data;
	Node *parambinaryNode = NULL;
	int addresingType = -1;

	if (!isInstructionParamValid(currParamPtr)) {
		return ILLEGAL_PARAM;
	}

	addresingType = getParamAddresingType(currParamPtr);

	if (!isAddresingTypeValid(addressing, addresingType)) {
		return ILLEGAL_ADDRESSTYPE;
	}

	writeSrcOperandToBinaryWord(opCodebinaryWord, addresingType);
	parambinaryNode = createParamBinaryWord(currParamPtr, addresingType, 1);
	pushTail(parambinaryNode, &opCodeNode);

	if (addresingType == 3) {
		(*isSrcRegisterPtr) = 1;
	}
	return resType;

}

RESULT_TYPE handleDestOperand(String *currParamPtr, Set *addressing,
		Node *opCodeNode, int isSrcRegister, int *numOfWords) {

	RESULT_TYPE resType = SUCCESS;
	Set *opCodebinaryWord = (Set*) opCodeNode->data;
	Node *parambinaryNode = NULL;
	int addresingType = -1;

	if (!isInstructionParamValid(currParamPtr)) {
		return ILLEGAL_PARAM;
	}

	addresingType = getParamAddresingType(currParamPtr);

	if (!isAddresingTypeValid(addressing, addresingType)) {
		return ILLEGAL_ADDRESSTYPE;
	}

	writeDestOperandToBinaryWord(opCodebinaryWord, addresingType);

	if (isSrcRegister && addresingType == 3) {

		Node *srcNode = opCodeNode->next;
		Set *srcBinary = (Set*) srcNode->data;
		writeDestRegiserToBinaryWord(srcBinary, atoi(currParamPtr->value + 1));

	} else {

		parambinaryNode = createParamBinaryWord(currParamPtr, addresingType, 0);
		pushTail(parambinaryNode, &opCodeNode);
		(*numOfWords) += 1;

	}

	return resType;

}

int isAddresingTypeValid(Set *addresingSet, int addresingType) {

	return isValueInSet(addresingSet, addresingType);

}

Node* createParamBinaryWord(String *param, int addresingType, int isSrc) {

	Node *node = NULL;
	String *paramDup = NULL;
	Set *parambinaryWord;
	int num;

	if (addresingType == DIRECT_REGISTER_ADDRESSING_TYPE) {

		parambinaryWord = createNewSet();
		num = atoi(param->value + 1);
		if (isSrc) {
			writeSrcRegiserToBinaryWord(parambinaryWord, num);
		} else {
			writeDestRegiserToBinaryWord(parambinaryWord, num);
		}
		node = createNode(parambinaryWord, SET, NULL);
		node->TYPE = SET;

	} else if (addresingType == INSTANT_ADDRESSING_TYPE) {

		getIntFromName(param->value + 1, &num);
		parambinaryWord = intToBinaryWordWithOffset(num, 2);
		node = createNode(parambinaryWord, SET, NULL);
		node->TYPE = SET;

	} else {

		/* addresingType == 1  == DIRECT_ADDRESSING_TYPE*/
		paramDup = duplicateString(param);
		node = createNode(paramDup, STRING, NULL);
		node->TYPE = STRING;

	}

	return node;

}

int getParamAddresingType(String *param) {

	if (charAt(param, 0) == '#') {
		return 0;
	} else if (isRegister(param)) {
		return 3;

	} else {
		return 1;
	}

}

int isInstructionParamValid(String *param) {

	int ignore = 0;
	if (param->value[0] == '#') {
		if (getIntFromName((param->value) + 1, &ignore) == SUCCESS) {
			return 1;
		}

	} else if (checkLabelLegality(param->value) == SUCCESS) {

		return 1;
	} else if (isRegister(param)) {
		return 1;
	}

	return 0;

}

RESULT_TYPE handleData(String *line, Node **dataBinarysListPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;
	Set *binaryWord;
	Node *node;
	int size = 0, i = 0, currInt;
	int **intArrPtr;
	int *intArr = NULL;
	intArrPtr = &intArr;

	/* get intArrAllocates memory on the heap to intArr */
	resType = getIntArrfromStringArgs(line, intArrPtr, &size);

	if (resType) {
		return resType;
	}

	for (i = 0; i < size; ++i) {

		currInt = intArr[i];
		binaryWord = intToBinaryWord(currInt);
		node = createNode(binaryWord, SET, NULL);
		pushTail(node, dataBinarysListPtr);

	}

	free(intArr);
	(*DCPtr) += size;

	return resType;

}

RESULT_TYPE handleString(String *line, Node **dataBinarysListPtr, int *DCPtr) {

	RESULT_TYPE resType = SUCCESS;
	int i = 1;
	String *quote;
	char *str;
	Set *binaryWord;
	Node *node;

	resType = checkStringIllegal(line->value);

	if (resType) {
		return resType;
	}

	quote = popWord(line);
	str = quote->value;

	while (str[i] != '"') {

		binaryWord = intToBinaryWord(str[i]);
		node = createNode(binaryWord, SET, NULL);
		pushTail(node, dataBinarysListPtr);
		(*DCPtr)++;
		i++;

	}

	binaryWord = intToBinaryWord('\0');
	node = createNode(binaryWord, SET, NULL);
	pushTail(node, dataBinarysListPtr);
	(*DCPtr)++;

	deleteString(quote);

	return resType;

}

RESULT_TYPE handleExtern(HashTable *symbolTable, String *line) {

	RESULT_TYPE resType = EXTERN_CREATED;
	String *labelName = popWord(line);
	String *extraText;
	Label *label;

	resType = checkLabelLegality(labelName->value);
	if (resType) {
		deleteString(labelName);
		return resType;
	}

	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(symbolTable, labelName->value)) {
		label = (Label*) getValueByKey(symbolTable, labelName->value);

		if (label->type != EXTERNAL) {

			resType = LABEL_ALLREADY_EXISTS;
			deleteString(labelName);
			return resType;
		}

	}

	extraText = popWord(line);

	if (extraText->size) {
		resType = EXTRANEOUS_TEXT;

	} else {
		label = createLabel(labelName->value);
		label->type = EXTERNAL;
		label->address = -1;
		insertToTable(symbolTable, labelName->value, label);

	}

	deleteString(labelName);
	deleteString(extraText);

	return resType;

}

RESULT_TYPE handleEntry(HashTable *symbolTable, String *line,
		Node **entryListPtr) {

	RESULT_TYPE resType = ENTRY_CREATED;
	String *labelName = popWord(line);
	String *extraText;
	Label *label;
	Node *node;

	resType = checkLabelLegality(labelName->value);
	if (resType) {
		deleteString(labelName);
		return resType;
	}

	/* check if w is in table AND w that is in table is not extern */
	if (isKeyInTable(symbolTable, labelName->value)) {
		label = (Label*) getValueByKey(symbolTable, labelName->value);

		if (label->type == EXTERNAL) {

			resType = LABEL_EXTERNALY_EXISTS;
			deleteString(labelName);
			return resType;
		}

	}

	extraText = popWord(line);

	if (extraText->size) {
		resType = EXTRANEOUS_TEXT;
		deleteString(labelName);

	} else {

		node = createNode(labelName, STRING, NULL);
		pushHead(node, entryListPtr);
	}

	deleteString(extraText);

	return resType;
}

void insertLabel(char *labelName, HashTable *symbolTable, LABEL_TYPE type,
		int addres) {

	Label *label;
	label = createLabel(labelName);
	label->type = type;
	label->address = addres;
	insertToTable(symbolTable, labelName, label);

}

RESULT_TYPE checkLabelLegality(char *labelName) {

	int i = 0;
	if (!isLableNamevalid(labelName)) {
		return LABEL_IS_RESERVED;

	}

	if (!isalpha(*labelName)) {
		return LABEL_ILLEGAL_DEFENITION;
	}
	if (strlen(labelName) >= MAX_LABEL_LENGTH) {
		return LABLE_INVALID_LENGTH;
	}
	for (i = 1; i < strlen(labelName); ++i) {
		if (!isalnum(labelName[i])) {
			return LABEL_ILLEGAL_DEFENITION;
		}

	}

	return SUCCESS;

}

int isData(char *str) {
	return strcmp(str, ".data") == 0;
}

int isStringData(char *str) {
	return strcmp(str, ".string") == 0;
}
int isExtern(char *str) {
	return strcmp(str, ".extern") == 0;
}

int isEntry(char *str) {
	return strcmp(str, ".entry") == 0;
}

int isLabel(String *str) {
	return charAt(str, str->size - 1) == ':';

}
int isRegister(String *str) {
	return str->size == 2 && charAt(str, 0) == 'r' && charAt(str, 1) - '0' >= 0
			&& charAt(str, 1) - '0' < 8;
}

RESULT_TYPE secoundPassFileOpen(char *srcFile, HashTable *symbolTable,
		Node *binarysList, int IC, int DC) {

	RESULT_TYPE resType = SUCCESS;
	char *str, *obSuffix = ".ob", *externSuffix = ".ext";
	String *externFileName;
	String *obFileName;
	FILE *externFile, *obFile;

	obFileName = filenameChange(srcFile, obSuffix);
	obFile = fopen(obFileName->value, "w");

	if (!obFile) {
		deleteString(obFileName);
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	externFileName = filenameChange(srcFile, externSuffix);
	externFile = fopen(externFileName->value, "w");

	if (!externFile) {
		deleteString(obFileName);
		deleteString(externFileName);
		fclose(obFile);
		printFileError(srcFile);
		return FILE_NOT_FOUND;
	}

	str = malloc(sizeof(char) * 10);

	sprintf(str, "\t%d\t%d \n", IC, DC);
	fputs(str, obFile);
	free(str);
	resType = secoundPassAssembly(obFile, externFile, symbolTable, binarysList);

	fclose(obFile);
	fclose(externFile);

	if (resType) {
		/*error in second pass
		 * so we remove .ob file and .ext File
		 * we created  */
		remove(obFileName->value);
		remove(externFileName->value);

	}

	deleteString(obFileName);
	deleteString(externFileName);

	return resType;

}

RESULT_TYPE secoundPassAssembly(FILE *obFile, FILE *externFile,
		HashTable *symbolTable, Node *binarysList) {

	RESULT_TYPE resType = SUCCESS;
	Node *currNode = binarysList;
	String *labelName;
	Label *label;
	Set *binaryWord;
	Set *externBinaryWord = createNewSet();

	writeAREToBinaryWord(externBinaryWord, 1);

	int index = 100;

	while (currNode) {

		if (currNode->TYPE == STRING) {

			labelName = (String*) currNode->data;
			label = (Label*) getValueByKeyString(symbolTable, labelName);

			if (label == NULL) {

				resType = LABEL_DOESNOT_EXISTS;
				break;

			} else if (label->type == EXTERNAL) {
				/* write 01 binary to oFile AND write to extern FILE */
				writeToObFile(obFile, externBinaryWord, index);
				writeToExternFile(externFile, labelName, index);

			} else {

				binaryWord = intToBinaryWordWithOffset(label->address, 2);
				writeAREToBinaryWord(binaryWord, 2);
				writeToObFile(obFile, binaryWord, index);
				deleteSet(binaryWord);

			}
		} else {

			binaryWord = (Set*) currNode->data;
			writeToObFile(obFile, binaryWord, index);

		}

		currNode = currNode->next;
		index++;

	}

	deleteSet(externBinaryWord);

	return resType;
}

void writeToObFile(FILE *obFile, Set *binaryWord, int index) {

	String *outPut, *binaryStr;
	char *buffer = malloc(4);
	binaryStr = binaryWOrdToString(binaryWord);

	sprintf(buffer, "%d", index);

	outPut = createNewString("0");
	appendToString(outPut, buffer);
	appendToString(outPut, "	");
	concatStrings(outPut, binaryStr);
	appendCharToString(outPut, '\n');

	fputs(outPut->value, obFile);

	free(buffer);
	deleteString(binaryStr);
	deleteString(outPut);

}

void writeToExternFile(FILE *externFile, String *labelName, int index) {

	char *buffer = malloc(4);
	String *labelNameCopy = duplicateString(labelName);

	sprintf(buffer, " %d \n", index);
	appendToString(labelNameCopy, buffer);

	fputs(labelNameCopy->value, externFile);

	deleteString(labelNameCopy);
	free(buffer);

}

int isLableNamevalid(char *name) {

	/*List of commands and label names to check against*/
	char *names[] = { "move", "cmp", "add", "sub", "not", "clr", "lea", "inc",
			"dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop", ".string",
			".data", ".extrn", ".entry", "string", "data", "extrn", "entry",
			"r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7" };
	int i;
	/*Check if the name matches any command or labels*/
	for (i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
		if (strcmp(name, names[i]) == 0) {
			/*Name matches, so it's not a valid  macro name*/

			return 0;
		}
	}
	return 1;

}
