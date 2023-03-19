/*
 * Entry.h
 *
 *  Created on: 31 Jan 2023
 *      Author: Adi
 */
#include "String.h"

#ifndef ENTRY_H_
#define ENTRY_H_

/*Definition of entry to table*/
typedef struct {

	int hash;
	String * key;
	void * value;

} Entry;


/*
 * This method receives 'hash', 'key', 'value' as parameters and creates a entry to the Hash table.
 * It allocates memory from heap and creates an entry.
 * @param hash - the given has table to create an entry to.
 * @param key - the given key.
 * @param value - the given value.
 * @return - returns a ney entry.
 */
Entry* createEntry(int hash, String *key, void *value);

/*
 * This method receives 'entry', 'deleteDataFunc',and frees the  allocated memory from heap.
 * @param entry - the given param that needs to be free.
 * @param deleteDataFunc- deletes data fro hashTable. TODO ??
 */
void deleteEntry(Entry *entry, void (*deleteDataFunc)(void*));

#endif /* ENTRY_H_ */
