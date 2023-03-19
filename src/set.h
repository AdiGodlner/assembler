/*
 * set
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */
#include "String.h"
#ifndef SET_
#define SET_

/*Definition of set*/
typedef struct {

	char bits[2];

} Set;

/*
 * this method creates a new set and stores the pointer pointed to
 * with the integers in 'intArr'
 * parameter size is the size of 'intArr' array
 */
void read_set(Set **s, int intArr[], int size);

/*
 *
 */
void insertArrToSet(Set *s, int intArr[], int size);
/*
 * this method creates a new set
 * and allocates spaces for it on the heap
 */
Set* createNewSet();

/*
 *
 */
void deleteSet(void *set);

/*
 * this method inserts one integer to a given set 's'
 * this method only inserts non negative integers
 */
void insertToSet(Set *s, int num);
/*
 * removes all elements from the set
 * it does not free the space allocated to the set on the heap
 */
void clearSet(Set* s1 );
/*
 *
 */
int isValueInSet(Set * set, int value);

#endif /* SET_ */
