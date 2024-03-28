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
#include "Utils.h"
#include "HashTable.h"
#include "assembly.h"
#include "set.h"
#include "opcode.h"
#include "macro.h"

int main(int argc, char **argv) {

	int i = 0;
	RESULT_TYPE resType;
	String * fileName ;

	HashTable * opCodeTable = createDefualtHashTable();
	initOpcode(opCodeTable);

	if (argc > 1) {

		for (i = 1; i < argc; i++) {

			fileName = createNewString(argv[i]);
			appendToString(fileName, ".as");
			resType = macroParse(fileName->value);

			if (!resType) {

				String *amFileName = filenameChange(fileName->value, ".am");
				assembler(amFileName->value, opCodeTable);
				deleteString(amFileName);
			
			}

			deleteString(fileName);

		}
	}

	deleteTable(opCodeTable,deleteOpcode);

	printf("\n end  :-)\n");


	return 0;
}


