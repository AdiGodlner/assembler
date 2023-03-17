#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "String.h"

Set* createNewSet() {

	Set *newSet;
	newSet = (Set*) malloc(sizeof(Set));
	clearSet(newSet);

	return newSet;

}

Set* duplicateSet(Set *src) {

	Set *newSet = createNewSet();
	union_set(src, src, newSet);

	return newSet;

}

void deleteSet(void *set) {

	free(set);
}

void insertToSet(Set *s, int num) {

	int location;
	unsigned int bit, byte;
	if (num < 0) {
		return;
	}
	location = num / 8;
	bit = 1 << (num % 8);
	byte = s->bits[location];
	byte = byte | bit;
	s->bits[location] = byte;

}

void read_set(Set **s, int intArr[], int size) {

	int i = 0;

	if (*s != NULL) {
		free(*s);
	}

	*s = createNewSet();

	for (i = 0; i < size; ++i) {

		insertToSet(*s, intArr[i]);

	}

}

void insertArrToSet(Set *s, int intArr[], int size){

	int i =0;
	for (i = 0; i < size; ++i) {

		insertToSet(s, intArr[i]);

	}

}


String* setToBinaryString(Set *s) {

	int i = 0, j = 0, temp;
	char currChar;
	char *bits;
	String *binStr = createEmptyString();

	for (i = 0; i < 2; ++i) {
		bits = s->bits;
		currChar = bits[i];

		for (j = 0; j < 8; ++j) {

			temp = (currChar & (1 << j));
			appendCharToString(binStr, temp ? '1' : '0');

		}
	}

	return binStr;
}

String* print_set(Set *s) {

	int i, j, original = 0, count = 0;
	unsigned int byte, bit;
	char charArr[5];
	String *setStr = createNewString("{ ");

	for (i = 0; i < sizeof(s->bits); ++i) {

		byte = s->bits[i];
		for (j = 0; j < 8; ++j) {

			bit = byte & (1 << j);
			if (bit) {

				original = i * 8 + j;
				sprintf(charArr, "%d ,", original);
				appendToString(setStr, charArr);
				count++;

				if (count == 16) {

					appendToString(setStr, "\n");
					count = 0;

				}
			}

		}

	}

	if (setStr->size == 2) {

		setStringValue(setStr, "The set is empty\n");

		return setStr;

	} else {

		i = setStr->size - 1;
		setStr->value[i] = '}';
		appendCharToString(setStr, '\n');

		return setStr;

	}

}

void union_set(Set *s1, Set *s2, Set *s3) {

	int i = 0;

	for (i = 0; i < getLength(s3); i++) {

		s3->bits[i] = s1->bits[i] | s2->bits[i];

	}

}


void clearSet(Set *s1) {

	memset(s1->bits, 0, sizeof(s1->bits));

}

int isValueInSet(Set *set, int value) {

	int location;
	unsigned int bit;

	if (value < 0) {
		return 0;
	}

	location = value / 8;
	bit = 1 << (value % 8);
	return set->bits[location] & bit;

}


int getLength(Set *s) {

	return sizeof((s)->bits) / sizeof(char);
}

