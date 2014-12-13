/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * tty.c - Implementation of the `tty` utility
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../info.h"
#include "../error.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "tty"
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
	/* Is standard input a terminal? */
	if (!isatty(fileno(stdin))) {
		printf("not a tty\n");
		return 1;
	}
	/* Fetch string */
	char *name = ttyname(fileno(stdin));
	/* Return >2 since error occurred */	
	if (name == NULL)
		return 2;
	/* Write out the terminal name and return successfully */
	printf("%s\n", name);
	return 0;
}
/*
 * Print usage of `tty` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s\n"
		"Returns name of user's terminal\n"
		"Following is a list of supported options.\n"
		"\t-?, -h\tDisplays a help/usage screen like this.\n"
		"\t-V\tDisplays version information.\t\n"
		"stdutils homepage <%s>\n"
		,
		called, HOMEPAGE
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

