/*
 * Entry.h
 *
 *  Created on: 31 Jan 2023
 *      Author: Adi
 */
#include "String.h"

#ifndef ENTRY_H_
#define ENTRY_H_

typedef struct {

	int hash;
	String * key;
	void * value;

} Entry;


/*
 *
 */
Entry* createEntry(int hash, String *key, void *value);
/*
 *
 */
void deleteEntry(Entry *entry);

#endif /* ENTRY_H_ */
