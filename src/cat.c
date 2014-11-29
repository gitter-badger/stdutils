/*
 * Copyright (c) 2014 Alan Potteiger
 *
 * Licensed under the 2 Clause (Free)BSD License
 * License can be found in `LICENSE` in the root directory of this project
 *
 * cat.c - Implementation of the `cat` utility
 * 
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
void output_file(FILE*);
void usage(char*);
int main(int argc, char *argv[])
{
	int o;
	while ((o = getopt(argc, argv, "hu")) != -1) {
		switch (o) {
			case 'u':
				/* From reading the spec if appears that this option doesn't
					really do anything, it's just there... */
			break;
			case 'h':
				usage(argv[0]);
			return 0;
			case '?':
				usage(argv[0]);
			return 0;
		}
	}
	int i;
	for (i = optind; i < argc; i++) {
		if (strcmp(argv[i], "-") != 0) {
			FILE *file;
			file = fopen(argv[i], "r");
			if (file != NULL) {
				output_file(file);
			} else {
				switch (errno) {
					case EISDIR:
						fprintf(stderr, "Error: Specified file (%s) is a directory.", argv[i]);
					break;
					case ELOOP:
						fprintf(stderr, "Error: A loop exists in symbolic links, trying to open: %s", argv[i]);
					break;
					case EACCES:
						fprintf(stderr, "Error: Permission denied. Trying to open: %s", argv[i]);
					break;
				}
			}
			continue;		
		}
		output_file(stdin);
	}
	if (optind == argc)
		output_file(stdin);
	return 0;
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
 * Print usage of `cat`
*/
void usage(char *name)
{
	printf(
		"Usage: %s [-u] [file...]\n"
		"Concatenate and print files (including standard input)\n"
		"Following is a list of valid options.\n"
		"\t-u\tIgnored, normal execution.\n"
		"\t-h\tDisplays this help/usage screen.\n"
		"Just \"-\" will read from standard input, Ctrl+D signifies end of file.\n"
		,
		name
	);
}
