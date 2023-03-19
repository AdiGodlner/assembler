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
 * This method dynamicly allocates memmory for future storing of opcode.
 * it checkes if the opcode and the received operands are valid.

 * This method receives 'name', 'code', 'numOfParameters', 'srcAddressingStr', 'destAddressingStr'.
 * @param name - the given line that needs to be transformt in to a binary code.
 * @param code - the given opcode command as: mov, cmp...stop gets placed  in 6-9 bits.
 * @param numOfParameters - the number of given parameters
 * example: mov, cmp, add, sub, lea - need to receive exactly two parametrs, srcParam and destParam. TODO ??
 * @param srcAddressingStr - the source operand get stored in 4-5 bits.
 * @param destAddressingStr - the dest operand  get stored in 2-3 bits.
 *
 * @return - returns an opcode.
 */
Opcode* createOpcode(char *name, int code, int numOfParameters,
		char *srcAddressingStr, char *destAddressingStr);

/*
 *
 */
void deleteOpcode(void* opCode);
/*
 * This method transforms the given parameter 'are' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param are - the 0-1 bits in 14-bits "word" in RAM.
 */
void writeAREToBinaryWord(Set *binaryWord, int are);

/*
 * This method transforms the given parameter 'dest' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param dest - the destanation operand of opCode command will get stored in 2-3 bits in 14-bits "word" in RAM.
 */
void writeDestOperandToBinaryWord(Set *binaryWord, int destOperand);

/*
 * This method transforms the given parameter 'src' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param src - the sorce operand of opCode command will get stored in 4-5 bits in 14-bits "word" in RAM.
 */
void writeSrcOperandToBinaryWord(Set *binaryWord, int srcOperand);

/*
 * This method transforms the given parameter 'code' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param code - the command code as'mov'...'stop'
 * will get stored in 6-9 bits in 14-bits "word" in RAM.
 */
void writeCodeToBinaryWord(Set *binaryWord, int code);

/*
 * This method transforms the given parameter 'operand' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param operand - the second operand will get stored in 10-11 bits in 14-bits "word" in RAM.
 */
void writeSecondParameterToBinaryWord(Set *binaryWord, int operand);

/*
 * This method transforms the given parameter 'operand' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param operand - the first operand will get stored in 12-13 bits in 14-bits "word" in RAM.
 */
void writeFirstParameterToBinaryWord(Set *binaryWord, int operand);

/*
 * This method transforms the given parameter 'reg' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param reg - the sorce register in 8-13 bits in 14-bits "word" in RAM.
 */
void writeSrcRegiserToBinaryWord(Set *binaryWord, int reg);

/*
 * This method transforms the given parameter 'reg' to a 14- bits "word" and insert it to the right place in RAM.
 * @param binaryWord - the transformed binary code.
 * @param reg - the destanation register in 2-7 bits in 14-bits "word" in RAM.
 */
void writeDestRegiserToBinaryWord(Set *binaryWord, int reg);

/*
 * This method convert the decimal value into binary code value.
 * It receives 'binaryWord', 'decimal', 'offset', 'length' as parameters.
 * @param binaryWord - the transformed binary code.
 * @param decimal - the given decimal value.
 * @param offset - the given offset where to start from in set.
 * @param length - the given length. TODO??
 */
void writeToBinaryWord(Set *binaryWord, int decimal, int offset, int length);

/*
 * This method checkes if the sorce and the dest operand
 * addressing has legal values, depending on the given comand as 'mov'...'stop'
 * For example only jmp,bne,jsr  all three have no sorce operand addressing and
 * only all three can have as a dest operand addressins a Relative mode.
 * @param addressingPtr - the poiner is passed to read_set() method.
 * @param addressingStr - the given operand addressing mode.
 */
void populateAddressingSet(Set **addressingPtr, char *addressingStr);

/*
 * this method receive a number that is passed to intToBinaryWordWithOffset() method for further handeling.
 * @param num - the given number that needs to be converted into binary code.
 * @return - returns a new set.
 */
Set* intToBinaryWord(int num);

/*
 * This method receive a decimal number that needs to be converted and placed to set.
 * @param num - the given nember that need to be converted.
 * @param offset - the given offset where to start from in set.
 * @return - returns a new set.
 */
Set* intToBinaryWordWithOffset(int num, int offset);

/*
 * This method receive a table where all opcode comand get in, and it defines what exact rules need to be folowed
 * so all comands are insert into the right place where they belong
 * depending of how much parameters a certain comand need to get
 * and on the addressing mode of every parameter they have.
 * @param table - the created table that all opcode comands go in.
 */
void initOpcode(HashTable *table);


#endif /* OPCODE_H_ */
