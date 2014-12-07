/*
 * Written by Planet Earth
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * true.c - Implementation of the `true` utility.
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include "../info.h"
#define AUTHORS "Planet Earth"
#define UTILITY "true"
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
 * Print usage of `true` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [option]\n"
		"Simply returns true (0).\n"
		"Following are the two valid options.\n"
		"\t-?, -h\tDisplay this help/usage page.\n"
		"\t-V\tDisplay version information.\n"
		"Written by Planet Earth.\n"
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

