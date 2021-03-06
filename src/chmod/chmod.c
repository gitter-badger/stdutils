/*
 * Written by Alan Potteiger
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * chmod.c - Implementation of the `chmod` utility.
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include "../info.h"
#define AUTHORS "Alan Potteiger"
#define UTILITY "chmod"
#define ERROR(x) fprintf(stderr, "%s: Error: %s\n", called, (x));
bool is_octal(char*);
void update_mode(char*, long int, int);
void usage();
void version();
/* Under what name the program was executed */
static char *called;
int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	int R = 0;
	while ((o = getopt(argc, argv, "?hVR")) != -1) {
		switch (o) {
			case 'R':
				R++;
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
	/* Argument checks, need at least 2 (orther than -R) */
	int dif = argc - optind;	
	if (dif < 1) {
		ERROR("Missing mode and file arguments.");
		usage();
		return EXIT_SUCCESS;
	}
	if (dif < 2) {
		ERROR("Missing file argument(s).");
		usage();
		return EXIT_SUCCESS;
	}
	/* We have everything we need, now we just need to verify
		if it's in the correct format */
	
	/* Check if the value is octal representation */
	if (is_octal(argv[optind])) {
		/* Lets convert to an int and go! */
		long int octal_value;
		octal_value = strtol(argv[optind], NULL, 8);
		int i;
		for (i = (optind+1); i < argc; i++) {
			update_mode(argv[i], octal_value, R);
		}
		
	}
	return EXIT_SUCCESS;
}
/*
 * Updates the mode for the specified file
*/
void update_mode(char *file, long int input, int recursive)
{	
	struct stat stats;
	if (stat(file, &stats) == -1) {
		perror(strcat(called, ": Error"));
		return;
	}
	if (chmod(file, stats.st_mode | input) == -1) {
		perror(strcat(called, ": Error"));
		return;
	}
	/* Recursive? */
	if (recursive > 0) {
		/* Directory? */
		if (S_ISDIR(stats.st_mode)) {
			/* TODO: Look into possible infinite recursion issue here... */
			DIR *dir;
			struct dirent *entry;
			dir = opendir(file);
			if (dir != NULL) {
				while (entry = readdir(dir)) {
					/* Make sure they're not . or .. */
					if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {
						char buf[(strlen(file) + strlen(entry->d_name)) + 1];
						sprintf(buf, "%s/%s", file, entry->d_name);
						update_mode(buf, input, recursive);
					}
				}
			} else {
				perror(strcat(called, ": Error"));
				return;
			}
		}	
	}
}
/*
 * Determines whether or not a given string is an octal value
*/
bool is_octal(char* s)
{
	int i;
	for (i = 0; i < strlen(s); i++) {	
		switch (s[i]) {
			case '0': case '1': case '2': case '3': case '4': case '5':
			case '6': case '7':
			break;
			return false;
		}
	}
	return true;
}
/*
 * Print usage of `chmod` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [-R] mode file...\n"
		"Following is a list of options.\n"
		"\t-R\tChanges file mode bits (permissions) recursively, all files and directories below.\n"
		"\t-h, -?\tDisplay this help/usage screen.\n"
		"\t-V\tDisplay version information.\n"
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

