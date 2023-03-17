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

void preAssembly(int argc, char **argv);
int main(int argc, char **argv) {


	 assembler(argv[1]);
	/*
	assembler("C:/Users/Adi/Desktop/foo.am");
	 preAssembly(argc, argv);
	 */

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

