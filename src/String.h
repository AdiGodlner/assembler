/*
 * String.h
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */

#ifndef STRING_H_
#define STRING_H_

typedef struct {

	char *value;
	int size;

} String;


/*
 * this method returns the char at index index in String str
 * this method returns null if index > length of the string
 * or if the index is < 0
 */
char charAt(String * str, int index);
/*
 *
 */
String * stringNCopy( char * src, int count);
/*
 * TODO add description
 */
int compareString(String * str1 , String * str2);
/*
 * TODO: maybe change the description
 * this method creates a new String containing the
 * same value as the given String 'str'
 * and returns a pointer to the new String
 */
String* duplicateString(String *str);
/*
 * this method creates a new Empty String
 * and returns a pointer to it
 * String creation allocates memory on the heap that needs to be freed with
 * the method deleteString
 */
String* createEmptyString();
/*
 * this method creates a new String  from an input character array 'charARr'
 * and returns a pointer to it
 * String creation allocates memory on the heap that needs to be freed with
 * the method deleteString
 */
String* createNewString(char *charArr);
/*
 * this method appends a char array 'charArr' to the end of String 'str'
 */
void appendToString(String *str1, char *charArr);
/*
 * this method appends one char to the end of String 'str'
 */
void appendCharToString(String *str, char c);
/*
 * this method concatenates two input Strings into the first String;
 */
void concatStrings(String *str1, String *str2);
/*
 * this method frees the spaces allocated to String on the heap
 */
void deleteString(void *str);
/*
 *
 * this method sets the Strings 'str' value to the given char array 'charArr'
 * and reallocates the Strings 'str' memory to the new size of 'charArr'
 */
void setStringValue(String *str, char *charArr);
/*
 * this method prints the value of a given String 'str'
 */
void printString(String *str);

/*
 * this method finds the next char in a String 'str' that isn't a blank char starting from given offset 'offset'
 * a blank char is defined as a space or a tab
 *
 * this method returns an integer location of that char in the Strings-> value char array
 * if the method reached the end of the string without finding a blank space it returns -1
 */
int findNextNonBlankCharLocation(String *str, int offset);
/*
 * this method returns a String representation of the next
 * word in the string 'str'
 * and removes this word from 'str'
 * this method considers a word to be any number of blank chars followed by any number of non blank chars
 * followed by a single blank space
 */
String* popWord(String *str);

#endif /* STRING_H_ */
