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
 *this method creates an empty HashTable with defualt size and allocates
 * space to it on the heap
 * @returns a pointer to the hashTable
 */
HashTable* createDefualtHashTable();

/*
 * This method creates an empty HashTable of a given size
 * the size refers to the size of the  initial bucket array
 *and allocates
 * space to it on the heap
 * @returns a pointer to the hashTable
 */
HashTable* createHashTable(int tableSize);

/*
 * this method returns a number repesnting the hash of the given string
 */
int hashcode(String *str);

/*
 * this method iterates over all the values stored in the HashTable
 * and deletes them using the given deleteDataFunc
 *
 * the deallocates the space of the HashTable on the heap
 *
 */
void deleteTable(HashTable *table, void (*deleteDataFunc)(void*));

/*
 * this method iterates over all the values stored in the HashTable
 * and deletes them using the given deleteDataFunc
 */
void cleanTable(HashTable *table, void (*deleteDataFunc)(void*));

/*
 *	this method increases the size of bucketArr list in given HashTable
 *	table  and
 *	re positions all the value stored in the table to there new index on the bucketArr
 *
 */
void resizeTable(HashTable *table);

/*
 * this method returns the value stored in the HashTable that
 * has a key given by value stored in key String
 * this method returns NULL if there is no value with the given key
 * stored in the HashTable table
 */
void* getValueByKeyString(HashTable *table, String *key);
/*
 * this method returns the value stored in the HashTable that
 * has a key given by 'key'
 * this method returns NULL if there is no value with the given key
 * stored in the HashTable table
 */
void* getValueByKey(HashTable *table, char *key);

/*
 * this method returns 1 if there is a value in the given table
 * with the same key as the given 'key'
 */
int isKeyInTable(HashTable *table, char *key);

/*
 *	this method inserts a value 'data' to the given table
 *	with the key 'key'
 *
 *	if a value already exists with the same key this method
 *	method puts the new value in its place which can result in a dangling pointer
 *	for the last value stored in place key thus leading to memory leak if not managed
 *	properly
 *
 */
void insertToTable(HashTable *table, char *key, void *data);

/*
 * this method get the index in the bucket array of a given hash
 */
int getHashIndex(HashTable *table, int hash);

#endif /* HASHTABLE_H_ */
