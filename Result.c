/*
 * Result.c
 *
 *  Created on: 4 Jan 2023
 *      Author: Adi
 */

#include "Result.h"

#define SUCCESS_STR "user command executed successfully\n"
#define UNDEFINED_SET_STR "Undefined set name\n"
#define UNDEFINED_COMMAND_NAME_STR "Undefined command name\n"
#define VALUE_OUT_OF_RANGE_STR "Invalid set member – value out of range\n"
#define VALUE_NOT_AN_INTEGER_STR "Invalid set member – not an integer\n"
#define LIST_NOT_TERMINATED_CORRECTLY_STR "List of set members is not terminated correctly\n"
#define MISSING_PARAMETER_STR "Missing parameter\n"
#define EXTRANEOUS_TEXT_STR "Extraneous text after end of command\n"
#define CONSECUTIVE_COMMAS_STR "Multiple consecutive commas\n"
#define MISSING_COMMA_STR "Missing comma\n"
#define ILLEGAL_COMMA_STR "Illegal comma\n"
#define UNEXPECTED_COMMA_STR "UNEXPECTED_COMMA\n"
#define UNEXPECTED_EOF_STR "Unexpected EOF (end of file)\n"
#define MEMMORY_ALLOCATION_FAILURE_STR "Memory allocation failure\n"
#define STOP_STR  "STOP\n"

char* getResultMsg(RESULT_TYPE resType) {

	switch (resType) {
	case SUCCESS:
		return SUCCESS_STR;
		break;
	case UNDEFINED_SET_NAME:
		return UNDEFINED_SET_STR;
		break;
	case UNDEFINED_COMMAND_NAME:
		return UNDEFINED_COMMAND_NAME_STR;

		break;
	case VALUE_OUT_OF_RANGE:
		return VALUE_OUT_OF_RANGE_STR;

		break;
	case VALUE_NOT_AN_INTEGER:
		return VALUE_NOT_AN_INTEGER_STR;

		break;
	case LIST_NOT_TERMINATED_CORRECTLY:
		return LIST_NOT_TERMINATED_CORRECTLY_STR;

		break;
	case MISSING_PARAMETER:
		return MISSING_PARAMETER_STR;

		break;
	case EXTRANEOUS_TEXT:
		return EXTRANEOUS_TEXT_STR;

		break;
	case CONSECUTIVE_COMMAS:
		return CONSECUTIVE_COMMAS_STR;

		break;
	case MISSING_COMMA:
		return MISSING_COMMA_STR;

		break;
	case ILLEGAL_COMMA:
		return ILLEGAL_COMMA_STR;

		break;
	case UNEXPECTED_COMMA:
		return UNEXPECTED_COMMA_STR;

		break;
	case UNEXPECTED_EOF:
		return UNEXPECTED_EOF_STR;

		break;
	case MEMMORY_ALLOCATION_FAILURE:
		return MEMMORY_ALLOCATION_FAILURE_STR;
	case EXIT:
		return STOP_STR;

		break;
	case CATSTROPIC_FAILURE:
		return " CATSTROPIC_FAILURE \n";
		break;
	default:
		return "default";
		break;
	}

}
