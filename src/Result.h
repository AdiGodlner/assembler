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
	MISSING_QUOTE,
	MISSING_BRACKET ,
	STRING_ILlEGAL_DEFENITION,
	VALUE_NOT_AN_INTEGER,
	EXTRANEOUS_TEXT,
	CONSECUTIVE_COMMAS,
	MISSING_COMMA,
	MISSING_PARAMETER,
	EXCEDING_MACHINE_MEMORY,
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
	INPUT_IS_EMPTRY,
	MISSING_ARGUMNET,
	ILLEGAL_PARAM,
	ILLEGAL_ADDRESSTYPE,
	FILE_NOT_FOUND,
	FILE_OPEN_FAILURE

} RESULT_TYPE;


/*
 * This method return the errType message. for every given  RESULT_TYPE
 * @param errType - the given errType message.
 * @return - returns the String message according to each a given RESULT_TYPE 'resType'
 */
char* getResultMsg(RESULT_TYPE errType );


#endif /* Result.h */
