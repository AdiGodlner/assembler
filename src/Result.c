/*
 * Result.c
 *
 *  Created on: 4 Jan 2023
 *      Author: Adi
 */

#include "Result.h"

#define SUCCESS_STR "SUCCESS!\n"
#define ENTRY_CREATED_STR "Entry has been created.\n"
#define LABEL_IS_EXTERN_AND_ENTRY_STR "ERROR: The label name is defined as both entry and extern.\n"
#define UNDEFINED_ENTRY_LABLE_STR "ERROR: The entry label name is undefined.\n"
#define INPUT_IS_EMPTY_STR "The given file is empty.\n"
#define UNDEFINED_COMMAND_NAME_STR "ERROR: Undefined command name.\n"
#define MISSING_QUOTE_STR "ERROR: Missing QUOTE.\n"
#define MISSING_BRACKET_STR "ERROR: Missing bracket.\n"
#define STRING_ILLEGAL_DEFENITION_STR "ERROR: Illegal String definition.\n"
#define VALUE_NOT_AN_INTEGER_STR "ERROR: VALUE NOT AN INTEGER \n"
#define EXTRANEOUS_TEXT_STR "ERROR: Extraneous text.\n"
#define CONSECUTIVE_COMMAS_STR "ERROR: Multiple consecutive commas\n"
#define MISSING_COMMA_STR  "ERROR: Missing comma.\n"
#define MISSING_PARAMETER_STR "ERROR: MISSING PARAMETER.\n"
#define UNEXPECTED_COMMA_STR "ERROR: Unexpected comma.\n"
#define MACRO_NAME_ALREADY_EXIST_STR  "ERROR: Macro name already exist.\n"
#define LABEL_ALLREADY_EXISTS_STR  "ERROR: Label name already exist.\n"
#define LABEL_DOESNOT_EXISTS_STR "ERROR: Label name doesn't exist.\n"
#define LABEL_EXTERNALY_EXISTS_STR "ERROR: The label name is already defined as EXTERNAL.\n"
#define LABEL_ILLEGAL_DEFENITION_STR  "ERROR: Illegal label definition.\n"
#define LABLE_INVALID_LENGTH_STR  "ERROR: The label name is to long.\n"
#define ILLEGAL_OPCODE_STR "ERROR: Illegal OPCODE definition.\n"
#define ILLEGAL_PARAM_STR "ERROR: Illegal parameter definition.\n"
#define ILLEGAL_ADDRESSTYPE_STR "ERROR: parameter addressing type not allowed for given opCode.\n"
#define FILE_NOT_FOUND_STR  "ERROR: FILE NOT FOUND.\n"
#define FILE_OPEN_FAILURE_STR  "ERROR: FILE COULD NOT BE OPEN.\n"

char* getResultMsg(RESULT_TYPE resType) {

	switch (resType) {
	case SUCCESS:
		return SUCCESS_STR;
		break;
	case ENTRY_CREATED:
		return ENTRY_CREATED_STR;
		break;
	case LABEL_IS_EXTERN_AND_ENTRY:
		return LABEL_IS_EXTERN_AND_ENTRY_STR;

		break;
	case UNDEFINED_ENTRY_LABLE:
		return UNDEFINED_ENTRY_LABLE_STR;
		break;
	case MISSING_QUOTE:
		return MISSING_QUOTE_STR;

		break;
	case MISSING_BRACKET:
		return MISSING_BRACKET_STR;

		break;
	case STRING_ILlEGAL_DEFENITION:
		return STRING_ILLEGAL_DEFENITION_STR;

		break;
	case VALUE_NOT_AN_INTEGER:
		return VALUE_NOT_AN_INTEGER_STR;

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
	case MISSING_PARAMETER:
		return MISSING_PARAMETER_STR;

		break;
	case UNEXPECTED_COMMA:
		return UNEXPECTED_COMMA_STR;

		break;

	case MACRO_NAME_ALREADY_EXIST:
		return MACRO_NAME_ALREADY_EXIST_STR;

		break;
	case LABEL_ALLREADY_EXISTS:
		return LABEL_ALLREADY_EXISTS_STR;

		break;
	case LABEL_DOESNOT_EXISTS:
		return LABEL_DOESNOT_EXISTS_STR;

		break;
	case LABEL_EXTERNALY_EXISTS:
		return LABEL_EXTERNALY_EXISTS_STR;

		break;
	case LABEL_ILLEGAL_DEFENITION:
		return LABEL_ILLEGAL_DEFENITION_STR;

		break;
	case LABLE_INVALID_LENGTH:
		return LABLE_INVALID_LENGTH_STR;

		break;
	case ILLEGAL_OPCODE:
		return ILLEGAL_OPCODE_STR;

		break;
	case ILLEGAL_PARAM:
		return ILLEGAL_PARAM_STR;

		break;
	case ILLEGAL_ADDRESSTYPE:
		return ILLEGAL_ADDRESSTYPE_STR;

		break;
	case FILE_NOT_FOUND:
		return FILE_NOT_FOUND_STR;

		break;
	case FILE_OPEN_FAILURE:
		return FILE_OPEN_FAILURE_STR;

		break;

	default:
		return "default";
		break;
	}

}
