/*
 * Written by Planet Earth
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * false.c - Implements the `false` utility.
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include "../info.h"
#define AUTHORS "Planet Earth"
#define UTILITY "false"
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
			break;
			case 'h':
			case '?':
				usage();
			break;
		}
	}
	/* non-zero */
	return 1;
}
/*
 * Print usage of `false` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [options]\n"
		"Returns false (non-zero) successfully, ambitious, but we'll get there eventually.\n"
		"Following are the options supported.\n"
		"\t-?, -h\tPrints out a help/usage screen like this.\n"
		"\t-V\tPrints out version information.\n"
		"Written by Planet Earth\n"
		"stdutils homepage <%s>\n"
		,
		called,
		HOMEPAGE
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

