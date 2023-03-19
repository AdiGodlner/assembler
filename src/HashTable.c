/*
 * HashTable.c
 *
 *  Created on: 30 Jan 2023
 *      Author: Adi
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "HashTable.h"
#include "opcode.h"
#include "LinkedList.h"
#include "String.h"
#include "Entry.h"

#define DEFAULT_TABLE_SIZE 16
#define DEFAULT_LOAD_FACTOR 0.75

HashTable* createDefualtHashTable() {

	return createHashTable(DEFAULT_TABLE_SIZE);

}

HashTable* createHashTable(int tableSize) {

	int i = 0;
	HashTable *hashTable = malloc(sizeof(HashTable));

	hashTable->bucketArr = malloc(sizeof(Node*) * tableSize);

	if (hashTable->bucketArr == NULL) {
		free(hashTable);
		return NULL;
	}

	hashTable->size = tableSize;
	hashTable->loadFactor = DEFAULT_LOAD_FACTOR;
	hashTable->numEntrys = 0;

	/* Initialise all pointers to linked lists in the bucketArr to NULL */
	for (i = 0; i < tableSize; ++i) {

		hashTable->bucketArr[i] = NULL;

	}

	return hashTable;

}

int isKeyInTable(HashTable *table, char *key) {
	return getValueByKey(table, key) != NULL;
}

void insertToTable(HashTable *table, char *key, void *data) {

	int hash, index;
	double capacity;
	Node *currNode = NULL, *newNode = NULL, *prevNode = NULL;
	Entry *currEntry = NULL, *newEntry = NULL;
	String *keyString = createNewString(key);
	hash = hashcode(keyString);
	index = getHashIndex(table, hash);
	currNode = table->bucketArr[index];

	while (currNode != NULL) {

		currEntry = (Entry*) currNode->data;
		/*it is faster to compare hashcodes of the entries instead of
		 * comparing the key values only of the hash is the same we check the key
		 */
		if (currEntry->hash == hash) {

			if (compareString(keyString, currEntry->key) == 0) {
				/* we found a table entry with the existing key
				 * so we override the existing pointer this may cause floating pointers
				 * but the responsibility should be on the caller
				 * */
				currEntry->value = data;
				printf("override %s = , %s \n", keyString->value,
						currEntry->key->value);

				return;
			}

		}

		prevNode = currNode;
		currNode = currNode->next;

	}

	/* if we got here it means there is no entry in the hashtable with the given key*/

	newEntry = createEntry(hash, keyString, data);
	newNode = createNode(newEntry, ENTRY, NULL);


	if (prevNode) {
		prevNode->next = newNode;
	} else {
		table->bucketArr[index] = newNode;
	}

	table->numEntrys += 1;
	capacity = (double) table->numEntrys / (double) table->size;

	if (capacity > table->loadFactor) {
		resizeTable(table);
	}

}

void resizeTable(HashTable *table) {

	int i = 0, index = 0, oldSize = 0;
	Node **newBucketArr = NULL;
	Node *currNode = NULL, *nextNode = NULL;
	Entry *entry = NULL;

	newBucketArr = malloc(sizeof(Node*) * table->size * 2);

	oldSize = table->size;
	table->size *= 2;

	for (i = 0; i < table->size; ++i) {

		newBucketArr[i] = NULL;

	}

	for (i = 0; i < oldSize; ++i) {

		currNode = table->bucketArr[i];
		while (currNode) {

			entry = (Entry*) currNode->data;
			index = getHashIndex(table, entry->hash);
			nextNode = currNode->next;
			pushHead(currNode, newBucketArr + index);
			currNode = nextNode;

		}

	}

	free(table->bucketArr);
	table->bucketArr = newBucketArr;

}

void* getValueByKey(HashTable *table, char *key) {

	String *keyString = createNewString(key);
	void *value = getValueByKeyString(table, keyString);
	deleteString(keyString);
	return value;
}

void* getValueByKeyString(HashTable *table, String *key) {

	int hash, index;
	Node *currNode = NULL;
	Entry *currEntry = NULL;

	hash = hashcode(key);
	index = getHashIndex(table, hash);
	currNode = table->bucketArr[index];

	while (currNode != NULL) {

		currEntry = (Entry*) currNode->data;
		/*it is faster to compare hash codes of the entries instead of
		 * comparing the key values only of the hash is the same we check the key
		 */
		if (currEntry->hash == hash) {
			if (compareString(key, currEntry->key) == 0) {
				return currEntry->value;
			}

		}

		currNode = currNode->next;

	}

	return NULL;

}

int getHashIndex(HashTable *table, int hash) {

	return hash & (table->size - 1);

}

int hashcode(String *str) {

	int i = 0, res = 0;
	char *strValue = str->value;
	int size = str->size;

	for (i = 0; i < size; ++i) {

		res += pow(strValue[i] * 31, size - i - 1);

	}

	return res;

}

void deleteTable(HashTable *table, void (*deleteDataFunc)(void*)) {

	cleanTable(table, deleteDataFunc);
	free(table->bucketArr);
	free(table);

}

void cleanTable(HashTable *table, void (*deleteDataFunc)(void*)) {

	int i = 0;
	Node *currNode, *nextNode;

	for (i = 0; i < table->size; ++i) {

		currNode = table->bucketArr[i];
		while (currNode) {

			nextNode = currNode->next;
			deleteEntry((Entry*) currNode->data, deleteDataFunc);
			free(currNode);
			currNode = nextNode;

		}

	}

}

