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
#include "String.h"
#include "HashTable.h"
#include "assembly.h"
#include "Set.h"
#include "opcode.h"
#include "macro.h"

void initOpcode(HashTable *table);
void preAssembly(int argc, char **argv);

int main(int argc, char **argv) {

//	HashTable * opcodeTable = createDefualtHashTable();
//	initOpcode(opcodeTable);
//	preAssembly(argc, argv);
	assemble("C:/Users/Adi/Desktop/foo.am");
	printf("\nend :-)");

	return EXIT_SUCCESS;

}

void preAssembly(int argc, char **argv) {

	int i = 0;
	char *fileName;

	if (argc > 1) {
		for (i = 1; i < argc; i++) {

			fileName = argv[i];
			macroParse(fileName);

		}
	}

}

void initOpcode(HashTable *table) {

//	char *addres0123 = "0,1,2,3";
	char *addres013 = "0,1,3";
	char *addres123 = "1,2,3";
	char *addres13 = "1,3";
//	char *addres12 = "1,2";
	char *addres1 = "1";
	char *empty = "";

	Opcode *moveOpCode = createOpcode("move", 0, 2, addres013, addres13);
	Opcode *cmpOpCode = createOpcode("cmp", 1, 2, addres013, addres013);
	Opcode *addOpCode = createOpcode("add", 2, 2, addres013, addres13);
	Opcode *subOpCode = createOpcode("sub", 3, 2, addres013, addres13);
	Opcode *notOpCode = createOpcode("not", 4, 1, empty, addres13);
	Opcode *clrOpCode = createOpcode("clr", 5, 1, empty, addres13);
	Opcode *leaOpCode = createOpcode("lea", 6, 2, addres1, addres13);
	Opcode *incOpCode = createOpcode("inc", 7, 1, empty, addres13);
	Opcode *decOpCode = createOpcode("dec", 8, 1, empty, addres13);
	Opcode *jmpOpCode = createOpcode("jmp", 9, 1, empty, addres123);
	Opcode *bneOpCode = createOpcode("bne", 10, 1, empty, addres123);
	Opcode *redOpCode = createOpcode("red", 11, 1, empty, addres13);
	Opcode *prnOpCode = createOpcode("prn", 12, 1, empty, addres013);
	Opcode *jsrOpCode = createOpcode("jsr", 13, 1, empty, addres123);
	Opcode *rtsOpCode = createOpcode("rts", 14, 0, empty, empty);
	Opcode *stopOpCode = createOpcode("stop", 15, 0, empty, empty);

	insertToTable(table, "move", moveOpCode);
	insertToTable(table, "cmp", cmpOpCode);
	insertToTable(table, "add", addOpCode);
	insertToTable(table, "sub", subOpCode);
	insertToTable(table, "not", notOpCode);
	insertToTable(table, "clr", clrOpCode);
	insertToTable(table, "lea", leaOpCode);
	insertToTable(table, "inc", incOpCode);
	insertToTable(table, "dec", decOpCode);
	insertToTable(table, "jmp", jmpOpCode);
	insertToTable(table, "bne", bneOpCode);
	insertToTable(table, "red", redOpCode);
	insertToTable(table, "prn", prnOpCode);
	insertToTable(table, "jsr", jsrOpCode);
	insertToTable(table, "rts", rtsOpCode);
	insertToTable(table, "stop", stopOpCode);

}
