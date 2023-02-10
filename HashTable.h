/*
 * HashTable.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include "LinkedList.h"

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

typedef struct {

	int size;
	Node **bucketArr;
	int numEntrys;
	double loadFactor;

} HashTable;

/*
 *
 */
HashTable* createDefualtHashTable();
/*
 *
 */
HashTable* createHashTable(int tableSize);

/*
 *
 */
int hashcode(String *str);

/*
 *
 */
void resizeTable(HashTable *table);

/*
 *
 */
String* getValueByKey(HashTable *table, String *key);

/*
 *
 */
void insertToTable(HashTable *table, String *key, String *data);

/*
 *
 */
int getHashIndex(HashTable *table, int hash);

/*
 *
 */
void printTable(HashTable * table);

#endif /* HASHTABLE_H_ */
