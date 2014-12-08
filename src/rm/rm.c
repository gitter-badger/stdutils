/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * rm.c - 
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include "../info.h"
#include "../error.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "rm"
void usage();
void version();
/* Under what name the program was executed */
static char *called;

int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	while ((o = getopt(argc, argv, "?hV")) != -1) {
		switch (o) {
			
			case 'V':
				version();
			return EXIT_SUCCESS;
			case 'h':
			case '?':
				usage();
			return EXIT_SUCCESS;
		}
	}
	
	return EXIT_SUCCESS;
}

/*
 * Print usage of `rm` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s \n"

		"Following is a list of supported options.\n"
		"\t-?, -h\tDisplays a help/usage screen like this.\n"
		"\t-V\tDisplays version information.\t"
		,
		called
	);
}
/*
 * Displays version information
*/
void version()
{
	printf(
		"%s (stdutils %s)\n"
		"Written by %s\n"
		"Licensed under the 2-Clause BSD License\n"
		"%s\n"
		,
		UTILITY,
		VERSION,
		AUTHORS,
		HOMEPAGE
	);
}

