/*
 * String.h
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */

#ifndef STRING_H_
#define STRING_H_

/* String definition*/
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
 * @param str - the given String that a given character
 * that is going to be added to the end of it.
 * @param c - the given char that need to be append to end of given String.
 */
void appendCharToString(String *str, char c);
/*
 * This method receive two Strings str1, str2 as parameters and concat them,
 * then stores them in the first received String.
 * @param str1 - the given String that both connected String are going to be stored in.
 * @param str2 - the second String that going to be concat to the end of the first one.
 */
void concatStrings(String *str1, String *str2);
/*
 * This method receives a String that needs to be freed to avoid memory leak,
 * that can be caused if a memory is allocated dynamically on the heap and isn't freed.
 * @param str - the given String that need to be freed.
 */
void deleteString(void *str);
/*
 * This method sets the Strings 'str' value to the given char array 'charArr'
 * and reallocates the Strings 'str' memory to the new size of 'charArr'.
 * @param str - the given String to be set to the given char array 'charArr'.
 * @param charArr - the given character array.
 */
void setStringValue(String *str, char *charArr);

/*
 * This method check if a given char 'c' is present in the String 'str'.
 * @param str - the given String we look in for certain char.
 * @param c - the character we looking for in String.
 * @return - returns 1 if found else 0.
 */
int containsChar(String * str, char c);

/*
 * this method looks for the given delimiter in given String.
 * @param str - the given String we look in for a certain delimiter as comma, space, bracket e.t.c
 * @param delim - the delimeter we're looking for in the String.
 * @return - returns the new String.
 */
String* popByDeliminator(String *str, char delim);

/*
 * This method receive a String 'str' as a parameter, that includes words and blank spaces.
 * it pops out the first word that appears in the String.
 * this method considers a word to be any number of blank chars followed by any number of non blank chars
 * followed by a single blank space.
 * @param str - the given String we pop from.
 * @return - this method returns a String representation of the next
 * word in the string 'str' ,and removes this word from 'str'.
 */
String* popWord(String *str);



#endif /* STRING_H_ */
