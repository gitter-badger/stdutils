/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * sleep.c - Implementation of the `sleep` utility 
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "../info.h"
#include "../error.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "sleep"
void naptime(time_t);
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
	if (argc == optind) {
		ERRORX("Missing operand, need time in seconds.", 1);
	}
	/* how long to sleep */
	time_t seconds = atoll(argv[optind]);
	naptime(seconds);
	return EXIT_SUCCESS;
}
void naptime(time_t seconds)
{
	time_t now = time(NULL);
	time_t until = now + seconds;
	sleep(seconds);
	/* Sleep long enough? */
	now = time(NULL);
	if (now < until) {
		naptime(until - now);
	}
}
/*
 * Print usage of `sleep` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s time in seconds...\n"
		"The sleep utility pauses the amount of time specified in seconds\n"
		"Following is a list of supported options.\n"
		"\t-?, -h\tDisplays a help/usage screen like this.\n"
		"\t-V\tDisplays version information.\t\n"
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

