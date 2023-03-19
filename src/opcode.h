/*
 * opcode.h
 *
 *  Created on: 9 Feb 2023
 *      Author: Adi
 */
#ifndef OPCODE_H_
#define OPCODE_H_

#include "set.h"
#include "HashTable.h"

/*Definition of Opcode*/
typedef struct {

	String *name;
	int code;
	int numOfParameters;
	Set *srcAddressing;
	Set *destAddressing;

} Opcode;

/*
 * This method allocates memory for opcode and creates Opcode.
 * @param name - the name of the opCode
 * @param code - the number of the opCode
 * @param numOfParameters - the number of given parameters
 * example: mov, cmp, add, sub, lea - need to receive exactly two parameters
 * @param srcAddressingStr - a string of numbers separated by a ',' representing
 *  the allowed addressing types for the src operands
 * @param destAddressingStr -a string of numbers separated by a ',' representing
 *  the allowed addressing types for the dest operands
 * @return - returns an opcode.
 */
Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr);

/*
 * This method frees the space allocated on the heap to a given opCOde
 * @param opCode - given opCode to free.
 */
void deleteOpcode(void *opCode);
/*
 * This method populates the ARE bits in given binaryWord with the binary representation
 * of 'are'.
 * @param binaryWord - a set representing a binary word.
 * @param 'are' - a decimal number to write it binary representation to place in the relevant ARE bits
 * of the given word binaryWord.
 */
void writeAREToBinaryWord(Set *binaryWord, int are);

/*
 *  This method populates the destination operand addressing type bits in given binaryWord
 *  with the binary representation of destOperand.
 * @param binaryWord - a set representing a binary word.
 * @param destOperand -  a decimal number to write it binary representation the destination operand bits
 * of the given word binaryWord.
 */
void writeDestOperandToBinaryWord(Set *binaryWord, int destOperand);

/*
 * This method populates the source operand addressing type bits in given binaryWord
 * with the binary representation of srcOperand.
 * @param binaryWord - a set representing a binary word.
 * @param srcOperand -  a decimal number to write it binary representation the source operand bits
 * of the given word binaryWord.
 */
void writeSrcOperandToBinaryWord(Set *binaryWord, int srcOperand);

/*
 * This method populates the operation code bits in given binaryWord
 * with the binary representation of code.
 * @param binaryWord - a set representing a binary word.
 * @param code -  a decimal number to write it binary representation the operation code bits
 * of the given word binaryWord.
 */
void writeCodeToBinaryWord(Set *binaryWord, int code);

/*
 * This method populates the second Parameter addressing type bits in given binaryWord
 * with the binary representation of secondParameter.
 * @param binaryWord - a set representing a binary word.
 * @param secondParameter -  a decimal number to write it binary representation the secondParameter bits
 * of the given word binaryWord.
 */
void writeSecondParameterToBinaryWord(Set *binaryWord, int secondParameter);

/*
 * This method populates the first Parameter addressing type bits in given binaryWord
 * with the binary representation of firstParameter.
 * @param binaryWord - a set representing a binary word.
 * @param firstParameter -  a decimal number to write it binary representation the firstParameter bits
 * of the given word binaryWord.
 */
void writeFirstParameterToBinaryWord(Set *binaryWord, int firstParameter);

/*
 * This method converts the given source srcReg to binary and writes it to its source register.
 * @param binaryWord - a set representing a binary word.
 * @param srcReg - the source register
 */
void writeSrcRegiserToBinaryWord(Set *binaryWord, int srcReg);

/*
 * This method converts the given destination destReg to binary and writes it to its destination register.
 * @param binaryWord - a set representing a binary word.
 * @param destReg - the destination register.
 */
void writeDestRegiserToBinaryWord(Set *binaryWord, int destReg);

/*
 * This method convert the decimal value into binary code represented by length number of bits
 * and writes it to the binary word starting from position offset .
 * @param binaryWord - a set representing a binary word.
 * @param decimal - the given decimal value.
 * @param offset - the given offset where to start from in set.
 * @param length - the given length.
 */
void writeToBinaryWord(Set *binaryWord, int decimal, int offset, int length);

/*
 * This method takes a string of numbers separated by a ',' and populates
 * the given set with it's numbers.
 * @param addressingPtr - a pointer to a pointer to a set
 * @param addressingStr -a string of numbers separated by a ','.
 */
void populateAddressingSet(Set **addressingPtr, char *addressingStr);

/*
 * This method receive a number and converts it to a binary word represented by a Set .
 * @param num - the given number that needs to be converted into binary code.
 * @return - binary word represented by a new Set.
 */
Set* intToBinaryWord(int num);

/*
 * This method receive a number and converts it to a binary word represented by a Set .
 * starting from offset.
 * @param num - the given nember that need to be converted.
 * @param offset - the given offset where to start from in set.
 * @return - binary word represented by a new Set.
 */
Set* intToBinaryWordWithOffset(int num, int offset);

/*
 * This method initialises a given table by populating it with
 * Opcodes as they where defined in the white paper.
 * @param table - a created table that all opcode commands go in.
 */
void initOpcode(HashTable *table);

#endif /* OPCODE_H_ */
