/*
 * Utils.h
 *
 *  Created on: 8 Mar 2023
 *      Author: Adi
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "Result.h"
#include "LinkedList.h"
#include<stdio.h>
/*
 * TODO check description
 *
 * This method pops the next argument in the given String 'arguments' and stores
 * it in the String 'dest'.
 * @param argumernts -
 * @param dest -
 * @isLastArgument -
 * @return - RESULT_TYPE
 * This method returns 'SUCCESS'  only if it found a valid argument
 * a valid argument is a string of non blank chars that can have a prefix of blank chars
 * and and a suffix of blank chars that is terminated by a ',' or '\n'
 * otherwise this method returns a MISSING_COMMA
 * if there are two strings of non blank chars separated  by a blank char
 * or an UNEXPECTED_COMMA if the first non blank char of the string is a ','
 * this method considers a blank char to be either ' ' or '\t'
 */
RESULT_TYPE popArgument(String *argumernts, String * dest, int isLastArgument);

/*
 * this method pops all arguments from String arguments checks if they are integers,
 * and populates an integerArr pointer to be 'intArrPtr' with their integer representation.
 * @param arguments  -
 * @param intArrPtr  -
 * @param size -
 * @return -
 * this method returns LIST_NOT_TERMINATED_CORRECTLY if the last argument is not -1
 * VALUE_OUT_OF_RANGE if the int represented in the argument is not between 0 and 127 or -1 the terminator integer
 * EXTRANEOUS_TEXT if there is extraneous text after the -1 argument
 * CONSECUTIVE_COMMAS if there are consecutive commas
 * MISSING_COMMA if there is a missing comma
 */
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size);

/*
 * This method takes an int represented in the string 'str' and puts it in 'numDest'
 * @param str -
 * @param numDest -
 * @return -
 * the method returns SUCCESS if the it was able to convert the string to an int
 * and VALUE_NOT_AN_INTEGER if it couldn't
 */
RESULT_TYPE getIntFromName(char *str, int *numDest);


/* This method receives a line and ckecks for illegal position of spaces, commas or missing brackets.
 * @param line -
 * @return -
 * if both of the parameters for RELATIVE_MODE (jmp, bne, jsr) are in valid position, as example: "jmp L1(#5,L)"
 * command name then space, then a lable,
 * close to it without any spaces we have an opening bracket then param1 comma and param2 closing bracket,
 * if the representation in the line is like shown above returns 1, else returns 0 and a proper error message.
 *
 */
int isPramsLegalforRealativeMode(char *line);

/*
 * This method receives a line as a param, and ckecks for illegal string representation in the text.
 * @param line -
 * @return - RESULT_TYPE and a proper error message.
 */
RESULT_TYPE checkStringIllegal(char *line);





#endif /* SRC_UTILS_H_ */
