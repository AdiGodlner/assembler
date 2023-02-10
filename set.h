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

} set;

/*
 * this method populates a given set pointed to in '**s'
 * with the integers in 'intArr'
 * parameter size is the size of 'intArr' array
 */
void read_set(set **s, int intArr[], int size);
/*
 * this method returns a String representation of the given set 's'
 * if the set is empty this method returns "The set is empty\n"
 */
String* print_set(set *s);
/*
 * this method performs the union operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void union_set(set *s1, set *s2, set *s3);
/*
 * this method performs the intersection operation between two sets 's1' and 's2' and
 * puts the resulting set in 's3'
 */
void intersect_set(set *s1, set *s2, set *s3);
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
set* createNewSet();
/*
 * this method inserts one integer to a given set 's'
 */
void insertToSet(set *s, int num);
/*
 * removes all elements from the set
 * it does not free the space allocated to the set on the heap
 */
void clearSet(set* s1 );
/*
 * this method returns the length of the array used to store the members of the set
 */
int getLength(set *s);



#endif /* SET_ */
