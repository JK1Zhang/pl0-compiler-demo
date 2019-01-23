#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "common/common.h"
#include "lex/pl0_lex.h"
#include "error/pl0_error.h"

void show_help(const char * arg0)
{
	printf("Usage: %s <src> <dst>\n\n", arg0);
}

int main(int argc, char * argv[])
{
	/* Parse arguments */
	 if (argc != 3)
	 {
	 	show_help(argv[0]);
	 	exit(-1);
	 }
	 fin = fopen(argv[1], "rb");
	 if (!fin)
	 {
	 	printf("Fatal: Cannot open file for reading: %s\n", argv[1]);
	 	exit(-1);
	 }
	fout=fopen(argv[2],"wb");
	if (!fout)
	 {
	 	printf("Fatal: Cannot create file for writing: %s\n", argv[2]);
	 	exit(-1);
	 }
	/* Start */
	printf("=== This is the program for PL/0 testing ===\n");

	/* Setup */
	compiler = PL0Compiler_create();
    	PL0Lex * lex = compiler->lex;


	/*test syntax ayalysis*/
	LexInit(lex);

	
	program(lex);

	/* Cleanup */
	fclose(fin);

	/* Finish */
	printf("=== Normal end for testing. ===\n");
	return 0;
}
