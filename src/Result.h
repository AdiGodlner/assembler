/*
 * Result.h
 *
 *  Created on: 4 Jan 2023
 *      Author: Adi
 */

#include "String.h"
#ifndef ERROR_H_
#define ERROR_H_

/*Errors RESULT_TYPE definition*/
typedef enum {
	SUCCESS = 0,
	ENTRY_CREATED,
	LABEL_IS_EXTERN_AND_ENTRY,
	UNDEFINED_ENTRY_LABLE,
	EXTERN_CREATED,
	INPUT_IS_EMPTRY,
	UNDEFINED_COMMAND_NAME,
	MISSING_QUOTE,
	MISSING_BRACKET ,
	STRING_ILlEGAL_DEFENITION,
	FIRST_PASS_FAILURE,
	UNDEFINED_SET_NAME,
	VALUE_OUT_OF_RANGE ,
	VALUE_NOT_AN_INTEGER,
	LIST_NOT_TERMINATED_CORRECTLY,
	NO_ARGUMENT_FOUND,
	EXTRANEOUS_TEXT,
	CONSECUTIVE_COMMAS,
	MISSING_COMMA,
	MISSING_ARGUMNET,
	MISSING_PARAMETER,
	ILLEGAL_COMMA,
	UNEXPECTED_COMMA,
	MACRO_NAME_ALREADY_EXIST,
	MACRO_NAME_IS_RESERVED ,
	LABEL_ALLREADY_EXISTS,
	LABEL_DOESNOT_EXISTS,
	LABEL_EXTERNALY_EXISTS,
	LABEL_ILLEGAL_DEFENITION,
	LABEL_IS_RESERVED ,
	LABLE_INVALID_LENGTH,
	ILLEGAL_OPCODE,
	ILLEGAL_PARAM,
	ILLEGAL_ADDRESSTYPE,
	FILE_NOT_FOUND,
	FILE_OPEN_FAILURE,
	EXCEDING_MACHINE_MEMMORY,
	MEMMORY_ALLOCATION_FAILURE

} RESULT_TYPE;


/*
 * This method return the errType message.
 * @param errType - the given errType message.
 * @return - returns the String message according to each a given RESULT_TYPE 'resType'
 */
char* getResultMsg(RESULT_TYPE errType );


#endif /* Result.h */
