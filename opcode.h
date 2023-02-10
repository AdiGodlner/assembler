/*
 * opcode.h
 *
 *  Created on: 9 Feb 2023
 *      Author: Adi
 */

#ifndef OPCODE_H_
#define OPCODE_H_

typedef struct {

	String * name;
	int code;
	set * s;
	int numOfParameters;
	set srcAddressing;
	set destAddressing;


} opcode;

/*
 *
 */
opcode * createOpcode(String * name, int code,int numOfParameters );





#endif /* OPCODE_H_ */
