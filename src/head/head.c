/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * head.c - Implementation the `head` utility.
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../info.h"
#include "../error.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "head"
void print_lines(FILE*, int);
void usage();
void version();
/* Under what name the program was executed */
static char *called;
int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	/* Contains value of -n argument */
	char *n = NULL;
	while ((o = getopt(argc, argv, "?hVn:")) != -1) {
		switch (o) {
			case 'n':
				n = optarg;
			break;
			case 'V':
				version();
			return EXIT_SUCCESS;
			case 'h':
			case '?':
				usage();
			return EXIT_SUCCESS;
		}
	}
	int lines;
	if (n == NULL) {
		lines = 10;
	} else {
		lines = atoi(n);
		if (lines == 0) {
			ERRORX("Improper line number, looking for a positive integer.", 0);
		}
	}
	/* Find/loop through file arguments */
	if (optind < argc) {
		int i;
		for (i = optind; i < argc; i++) {
			if (strcmp(argv[i], "-") == 0)
				argv[i] = "stdin";
			if ((argc - optind) > 1) {
				if ((argc - optind) > (argc - i))
					printf("\n");
				printf("==> %s <==\n", argv[i]);
			}
			if (strcmp(argv[i], "stdin") == 0) {
				print_lines(stdin, lines);
				continue;
			}
			FILE *file = fopen(argv[i], "r");
			if (file == NULL) {
				perror(called);
				exit(EXIT_FAILURE);
			}
			print_lines(file, lines);
		}
		return EXIT_SUCCESS;
	}
	print_lines(stdin, lines);
	return EXIT_SUCCESS;
}
/*
 * Print the number of lines specified from a file (including standard input if passed)
*/
void print_lines(FILE *file, int count)
{
	char *line = NULL;
	size_t size = NULL;
	if (count > 0) {
		int comp = 0;
		while (getline(&line, &size, file) != -1 && count > comp) {
			printf("%s", line);
			comp++;
			if (!(count > comp))
				break;
		}
		free(line);
		return;
	}
	while (getline(&line, &size, file) != -1) {
		printf("%s", line);
	}
	free(line);
}
/*
 * Print usage of `head` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [-n number of lines] [files...]\n"
		"Prints the first part of files (including stdin) to standard output.\n"
		"Following are options supported.\n"
		"\t-n number\tSpecifies the number of lines to print to standard out, if option is omitted then it defaults to 10.\n"
		"\t-?, -h\tDisplays this help/usage page.\n"
		"\t-V\tDisplays version information.\n"
		"Use - to use standard input.\n"
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

