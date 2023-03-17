/*
 * String.h
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */

#ifndef STRING_H_
#define STRING_H_

/* String represantation in struct of value and size.*/
typedef struct {

	char *value;
	int size;

} String;


/* This method receives a 'str' and the 'index' as a param.
 * @param str - the given String.
 * @param index - the given index.
 * @return - this method returns the char at index, 'index' in String str
 * or null if index > length of the string or if the index is < 0.
 */
char charAt(String * str, int index);

/*
 * This methods copies exactly count num of elements from the given 'src' String,
 * to the new String.
 * @param src - the given String.
 * @param count - the number of elements that need to be copied
 * @return - this method returns a new String,
 */
String * stringNCopy( char * src, int count);
/*
 * This method compares between two given Srings str1, str2 by there ASCII value
 * @param str1 - the first given String that need to be compared with the second given String.
 * @param str2 - the second given String that need to be compared with the first given String.
 * @return -  if both are equal return 0, else if str1 < str2 returns a negative value,
 * else return a positive value.
 */
int compareString(String * str1 , String * str2);
/*
 * This method receives a String 'str' as a parameter,
 * and creates a new String exact same value as the given one.
 * @param str - the given String.
 * @return - returns a pointer to the new String.
 */
String* duplicateString(String *str);
/*
 * This method creates a new Empty String.
 * @return - returns a pointer to the created String.
 * String creation allocates memory on the heap that needs to be freed with
 * the method deleteString.
 */
String* createEmptyString();
/*
 * This method creates a new String from an input character array 'charARr' recieved
 * as a parameter.
 * @param charArr - the given character array.
 * @return -  returns a pointer to the new String.
 * String creation allocates memory on the heap that needs to be freed with
 * the method deleteString.
 */
String* createNewString(char *charArr);
/*
 * This method appends a char array 'charArr' to the end of String 'str1'.
 * @param str1 - the given String.
 * @param charArr - the given character array.
 */
void appendToString(String *str1, char *charArr);
/*
 * This method appends one char at a time to the end of String 'str'.
 * @param str - the given String that a given charecter
 * that is going to be added to the end of it.
 * @param c - the given char that need to be apend to end of given String.
 */
void appendCharToString(String *str, char c);
/*
 * This method recieve two Strings str1, str2 as parameters and concat them,
 * then stores them in the first received String.
 * @param str1 - the given String that both concated String are going to be stored in.
 * @param str2 - the second String that going to be concat to the end of the first one.
 */
void concatStrings(String *str1, String *str2);
/*
 * This method recieve a String that needs to be freed to avoid memory leak,
 * that can be caused if a memory is allocated dynamically on the heap and isn't freed.
 * @param str - the given String that need to be freed.
 */
void deleteString(void *str);
/*
 * This method sets the Strings 'str' value to the given char array 'charArr'
 * and reallocates the Strings 'str' memory to the new size of 'charArr'.
 * this method recieves two parameters, 'str' and 'chaArr'.
 * @param str - the given String to be set to the given char array 'charArr'.
 * @param charArr - the given character array.
 */
void setStringValue(String *str, char *charArr);
/*
 * This method receives a 'str' parameter and prints the given value of it as a String.
 * @param str - the String that need to be printed.
 */
void printString(String *str);

/*
 * This method receives two parameters 'str' and 'offset' and find the first
 * none blanck char location in a String 'str' starting from given 'offset'.
 * a blank char is defined as a space or a tab or any whitechar that exist in isspace function.
 * @param str - the given String.
 * @param offset - the given offset that we need to start loking from it in the given String.
 * @raturn -
 * this method returns an integer location of that char in the Strings-> value of char array
 * if the method reached the end of the string without finding a blank space it returns -1.
 */
int findNextNonBlankCharLocation(String *str, int offset);

/*
 *
 */
int containsChar(String * str, char c);

/*
 *
 */
String* popByDeliminator(String *str, char delim);

/*
 * This method receive a String 'str' as a parameter, that includes words and blanck spaces.
 * it pops out the first word that opears in the String.
 * this method considers a word to be any number of blank chars followed by any number of non blank chars
 * followed by a single blank space.
 * @param str - the given String we pop from.
 * @return - this method returns a String representation of the next
 * word in the string 'str' ,and removes this word from 'str'.
 */
String* popWord(String *str);



#endif /* STRING_H_ */
