/*
 * HashTable.h
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */

#include "LinkedList.h"
#include "Entry.h"

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
void deleteTable(HashTable *table, void (*deleteDataFunc)(void*));

/*
 *
 */
void cleanTable(HashTable *table, void (*deleteDataFunc)(void*));

/*
 *
 */
void resizeTable(HashTable *table);

/*
 *
 */
void* getValueByKeyString(HashTable *table, String *key);
/*
 *
 */
void* getValueByKey(HashTable *table, char *key);

/*
 *
 */
int isKeyInTable(HashTable *table, char *key);
/*
 *
 */
int insertToTableIfNotExists(HashTable *table, char *key, void *data);
/*
 *
 */
void insertToTable(HashTable *table, char *key, void *data);

/*
 *
 */
int getHashIndex(HashTable *table, int hash);

/*
 *
 */
void printTable(HashTable *table, String* (*func)(void*));

#endif /* HASHTABLE_H_ */
