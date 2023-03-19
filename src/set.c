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

