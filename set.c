#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "String.h"

set* createNewSet() {

	set *newSet;
	newSet = (set*) malloc(sizeof(set));
	clearSet(newSet);

	return newSet;

}

void insertToSet(set *s, int num) {

	int location = num / 8;
	unsigned int bit = 1 << (num % 8);
	unsigned int byte = s->bits[location];
	byte = byte | bit;
	s->bits[location] = byte;

}

void read_set(set **s, int intArr[], int size) {

	int i = 0;

	if (*s != NULL) {
		free(*s);
	}

	*s = createNewSet();

	for (i = 0; i < size; ++i) {

		insertToSet(*s, intArr[i]);

	}

}

//void printSetBinary(set * s){
//
//	int i = 0;
//	for (i= 0; i < s->bits ; ++var) {
//
//	}
//
//}

String* print_set(set *s) {

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

void union_set(set *s1, set *s2, set *s3) {

	int i = 0;

	for (i = 0; i < getLength(s3); i++) {

		s3->bits[i] = s1->bits[i] | s2->bits[i];

	}

}

void intersect_set(set *s1, set *s2, set *s3) {

	int i = 0;

	for (i = 0; i < getLength(s3); ++i) {

		s3->bits[i] = s1->bits[i] & s2->bits[i];

	}

}

void sub_set(set *s1, set *s2, set *s3) {

	int i = 0;

	for (i = 0; i < getLength(s3); ++i) {

		s3->bits[i] = s1->bits[i] & ~(s2->bits[i]);

	}

}

void symdiff_set(set *s1, set *s2, set *s3) {

	int i = 0;

	for (i = 0; i < getLength(s3); ++i) {

		s3->bits[i] = s1->bits[i] ^ (s2->bits[i]);

	}

}

void clearSet(set *s1) {

	memset(s1->bits, 0, sizeof(s1->bits));

}

int getLength(set *s) {

	return sizeof((s)->bits) / sizeof(char);
}

