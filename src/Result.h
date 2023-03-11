/*
 * Result.h
 *
 *  Created on: 4 Jan 2023
 *      Author: Adi
 */

#include "String.h"
#ifndef ERROR_H_
#define ERROR_H_

typedef enum {
	SUCCESS = 0, CATSTROPIC_FAILURE = 1,
	ENTRY_CREATED,
	NO_ENTRY_LABEL_FOUND,
	LABEL_IS_EXTERN_AND_ENTRY,
	UNDEFINED_ENTRY_LABLE,
	EXTERN_CREATED,
	INPUT_IS_EMPTRY,
	UNDEFINED_COMMAND_NAME,
	MISSING_QUOTE,
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
	ILLEGAL_COMMA,
	UNEXPECTED_COMMA,
	UNEXPECTED_EOF,
	EXIT,
	IGNORE,
	LABEL_ALLREADY_EXISTS,
	LABEL_EXTERNALY_EXISTS,
	LABEL_ILLEGAL_DEFENITION,
	LABLE_INVALID_LENGTH,
	FILE_NOT_FOUND,
	MEMMORY_ALLOCATION_FAILURE

} RESULT_TYPE;


/*
 * this method returns the string message  associated  to each a given RESULT_TYPE 'resType'
 */
char* getResultMsg(RESULT_TYPE errType );


#endif /* Result.h */
