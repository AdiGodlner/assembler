/*
 * Entry.c
 *
 *  Created on: 31 Jan 2023
 *      Author: Adi
 */

#include <stdio.h>
#include <stdlib.h>
#include "String.h"
#include "Entry.h"

#define MEM_ERR "failed to allocate memory"

Entry * createEntry(int hash, String *key, void *value) {

	Entry * entry = malloc(sizeof(Entry));

	/*TODO maybe duplicate value not sure if its needed yet*/
	entry->value = value;
	entry->hash = hash;
	entry->key = duplicateString(key);

	return entry;

}


void deleteEntry(Entry *entry, void (*deleteDataFunc)(void*)) {

	if (entry != NULL) {

		deleteDataFunc(entry->value);
		free(entry->key);
		free(entry);

	}

}

