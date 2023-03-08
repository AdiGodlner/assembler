/*
 * set
 *
 *  Created on: 30 Dec 2022
 *      Author: Adi
 */
#include "String.h"
#ifndef SET_
#define SET_

typedef struct {

	char bits[2];

} Set;

/*
 * TODO: add to desctiptions set only execpts non negative integers
 * this method populates a given set pointed to in '**s'
 * with the integers in 'intArr'
 * parameter size is the size of 'intArr' array
 */
void read_set(Set **s, int intArr[], int size);

/*
 *TODO description
 */
String* setToBinaryString(Set * s);
/*
 * this method returns a String representation of the given set 's'
 * if the set is empty this method returns "The set is empty\n"
 */
String* print_set(Set *s);
/*
 * this method performs the union operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void union_set(Set *s1, Set *s2, Set *s3);
/*
 * this method performs the intersection operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void intersect_set(Set *s1, Set *s2, Set *s3);
/*
 * this method performs the subtraction operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void sub_set();
/*
 * this method performs the symmetric difference  operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void symdiff_set();
/*
 * this method creates a new set
 * and allocates spaces for it on the heap
 */
Set* createNewSet();

/*
 *
 */
Set* duplicateSet(Set * src);
/*
 *
 */
void deleteSet(Set *set);

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
 * this method returns the length of the array used to store the members of the set
 */
int getLength(Set *s);



#endif /* SET_ */
