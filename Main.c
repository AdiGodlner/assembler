/*
 ============================================================================
 Name        : HashTable.c
 Author      : Adi
 Version     :
 Description : HashTable in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "String.h"
#include "Set.h"

int main(void) {


	set s = createNewSet();
	set stopCode = createNewSet();

	insertToSet(stopCode, 6);
	insertToSet(stopCode, 7);
	insertToSet(stopCode, 8);
	insertToSet(stopCode, 9);

	union_set(s, stopCode, s);
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
	String *macroName = createNewString("m1");
	String *macroValue = createNewString("some dsadsa");
	HashTable * macroTable = createDefualtHashTable();
	insertToTable(macroTable, macroName, macroValue);
	getValueByKey(macroTable, macroName);
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
/* ============================================== */
//	table

//	int i  =0;
	String *str = createNewString("Sunny");
	String * data = createNewString("foo");
	String * testStr = NULL;
//
//	for (i = 0; i < 13; ++i) {
//
//	appendCharToString(str, 33+i);
//	insertToTable(table, str, data);
//
//	}

	return EXIT_SUCCESS;

}
