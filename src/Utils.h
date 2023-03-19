/*
 * Utils.h
 *
 *  Created on: 8 Mar 2023
 *      Author: Adi
 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include "Result.h"
#include "set.h"
#include "LinkedList.h"
#include<stdio.h>

/*
 *
 * This method pops the next argument in the given String 'arguments' and stores
 * it in the String 'dest'.
 * @param argumernts - the String array to pop arguments from.
 * @param dest - the String to put the popped argument in.
 * @isLastArgument - checks if the last argument is an illegal param.
 * @return - returns 'SUCCESS'  only if it found a valid argument
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
 * @param arguments  - the String array to pop arguments from.
 * @param intArrPtr  - the integer array pointer.
 * @param size - the size to check that no out of bounds.
 * @return -returns LIST_NOT_TERMINATED_CORRECTLY if the last argument is not -1
 * VALUE_OUT_OF_RANGE if the int represented in the argument is not between 0
 * and 127 or -1 the terminator integer
 * EXTRANEOUS_TEXT if there is extraneous text after the -1 argument
 * CONSECUTIVE_COMMAS if there are consecutive commas
 * MISSING_COMMA if there is a missing comma
 */
RESULT_TYPE getIntArrfromStringArgs(String *arguments, int **intArrPtr,
		int *size);

/*
 * This method takes an int represented in the string 'str' and puts it in 'numDest'
 * @param str - the given str that needs to bee checked
 * @param numDest - the digit representation with '+' for positive value and '-' for negative.
 * @return - returns SUCCESS if  was able to convert the string to an int
 * and VALUE_NOT_AN_INTEGER if it couldn't.
 */
RESULT_TYPE getIntFromName(char *str, int *numDest);

/*
 * This method receives a line as a param, and checks for illegal string representation in the text.
 * @param line - the given line.
 * @return - returns the resType SUCCESS if the string is leagal ,
 * or RESULT_TYPE depending on the error.
 */
RESULT_TYPE checkStringIllegal(char *line);



/*
 * This method receives a set parameter that need to be transformed into a special binary symbol code
 * where insted of '1' we use '/' and insted of '0' we use '.'
 * We use this method for writing the .ob file.
 * @param set - the set that needs to be transformed into special binary symbol code.
 * @return - returns the new String in special binary symbol code format.
 */
String* binaryWOrdToString(Set *set) ;

#endif /* SRC_UTILS_H_ */
