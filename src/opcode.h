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

/*Definition of an Opcode*/
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
 * @param offset - the given offset.
 * @param length - the given length. TODO??
 */
void writeToBinaryWord(Set *binaryWord, int decimal, int offset, int length);
/*
 *
 */
void populateAddressingSet(Set **addressingPtr, char *addressingStr);

/*
 *
 */
Set* intToBinaryWord(int num);

/*
 *
 */
Set* intToBinaryWordWithOffset(int num, int offset);

/*
 *
 */
void initOpcode(HashTable *table);


#endif /* OPCODE_H_ */
