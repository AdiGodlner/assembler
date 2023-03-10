/*
 * Utils.h
 *
 *  Created on: 8 Mar 2023
 *      Author: Adi
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "Result.h"
/*
 * this method pops the next argument in a the given String 'arguments' and stores
 * it in the String 'dest';
 *
 * this method returns 'SUCCESS' RESULT_TYPE only if it found a valid argument
 * a valid argument is a string of non blank chars that can have a prefix of blank chars
 * and and a suffix of blank chars that is terminated by a ',' or '\n'
 * otherwise this method returns a MISSING_COMMA RESULT_TYPE if there are two strings of non blank chars
 * separated  by a a blank char
 * or an UNEXPECTED_COMMA if the first non blank char of the string is a ','
 * this method considers a blank char to be either ' ' or '\t'
 */
RESULT_TYPE popArgument(String *arguments, String *dest);

/*
 * this method pops all arguments from String arguments checks if they are integers
 * and populates an integerArr pointed to by 'intArrPtr' with their integer representation
 * this method returns LIST_NOT_TERMINATED_CORRECTLY if the last argument is not -1
 * VALUE_OUT_OF_RANGE if the int represented in the argument is not between 0 and 127 or -1 the terminator integer
 * EXTRANEOUS_TEXT if there is extraneous text after the -1 argument
 * CONSECUTIVE_COMMAS if there are consecutive commas
 * MISSING_COMMA if there is a missing comma
 */
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size);
/*
 * this method takes an int represented in the string 'str' and puts it in 'numDest'
 * the method returns SUCCESS if the it was able to convert the string to an int
 * and VALUE_NOT_AN_INTEGER if it couldn't
 */
RESULT_TYPE getIntFromName(char *str, int *numDest);


/*
 * This function ckecks for illegal position or missing brackets.
 */
int isbracketLegal(char * line);

/*
 * This function ckecks for illegal quotes in the text, and return 1, if is legal.
 */
RESULT_TYPE checkStringIllegal(char *line);

/*
 * This function ckecks for illegal commas in the text, and return 1, if is legal.
 */
int isCommaLegal(char *line);

#endif /* SRC_UTILS_H_ */
