/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * cat.c - Implementation of the `cat` utility
 * 
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../info.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "cat"
void output_file(FILE*);
void usage();
void version();
/* Under what name the program was executed */
static char *called;
int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	while ((o = getopt(argc, argv, "?hVu")) != -1) {
		switch (o) {
			case 'u':
				/* From reading he spec it appears that this option
					doesn't really do anything, it's just there... */
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
	int i;
	for (i = optind; i < argc; i++) {
		if (strcmp(argv[i], "-") != 0) {
			FILE *file;
			if ((file = fopen(argv[i], "r")) != NULL) {
				struct stat statbuf;
				stat(argv[i], &statbuf);
				if (!S_ISDIR(statbuf.st_mode))
					output_file(file);
				else
					fprintf(stderr, "Error: Specified file (%s) is a directory.\n", argv[i]);
			} else {
				perror(strcat(argv[0], ": Error"));
			}
			continue;
		}
		output_file(stdin);
	}
	if (optind == argc)
		output_file(stdin);
	return EXIT_SUCCESS;
}
/*
 * Reads the specified file line by line and writes it to stdout
*/
void output_file(FILE *file)
{
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, file) != -1) {
		printf("%s", line);
	}
	free(line);
}
/*
 * Print usage of `cat` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [-u] [file...]\n"
		"Concatenate and print files (including standard input)\n"
		"Following is a list of valid options.\n"
		"\t-u\tIgnored, normal execution.\n"
		"\t-h, -?\tDisplays this help/usage screen.\n"
		"\t-V\tDisplays version information.\n"
		"Just \"-\" will read from standard input, Ctrl+D signifies end of file.\n"
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

