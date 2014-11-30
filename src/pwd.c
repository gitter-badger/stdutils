/*
 * Copyright (C) 2014 Alan Potteiger
 *
 * Licensed under the 2 Clause (Free)BSD License
 * License can be found in `LICENSE` in the root directory of this project
 *
 * pwd.c - Implementation of the `pwd` utility
 *
*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
void usage();
int pwd(size_t);
void version();
/* Under what name the program was execeuted. ex. `pwd`, `bin/pwd` */
static char *called;
int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	/* If this value is 0 there has been no option or the -L option selected
		If greater than 0 -P has been selected */
	int LP = 0;
	while ((o = getopt(argc, argv, "?hVLP")) != -1) {
		switch (o) {
			case 'L':
				LP = 0;		
			break;
			case 'P':
				LP++;
			break;
			case 'V':
				version();
			return 0;
			case 'h':
				usage();
				return 0;
			break;
			case '?':
				usage();
			return 0;
		}
	}
	if (LP > 0) {
		return pwd(PATH_MAX);
	}
	char *path = getenv("PWD");
	if (path != NULL) {
		printf("%s\n", path);
		return 0;
	}
	fprintf(stderr, "Missing environment variable \"PWD\"");
	return 1;
}
/*
 * Print working directory (physical path)
*/
int pwd(size_t length)
{
	char *buf =  malloc(sizeof(char)*length);
	if (getcwd(buf, length) != NULL) {
		printf("%s\n", buf);
		return 0;
	}
	/* We haven't returned yet, so something went wrong */
	/* Check for any recoverable errors, try to fix them */
	switch (errno) {
		case EINVAL:
			free(buf);
		return pwd(1024);
		case ERANGE:
			free(buf);
		return pwd(length*2);
	}
	/* Couldn't recover, free memory, print message, and return. */
	free(buf);
	perror(strcat(called, ": Error"));
	return 1;
}
/*
 * Print usage of `pwd` to standard out.
*/
void usage()
{
	printf(
		"Usage: %s [-L|-P]\n"
		"Return name of working directory\n"
		"Following is a list of currently supported options.\n"
		"\t-L\tLogical path, includes symlinks, default option.\n"
		"\t-P\tPhysical path, ignores symlinks.\n"	
		"\t-h, -?\tDisplay this help/usage screen.\n"
		"\t-V\tDisplay version information.\n"
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
		"pwd (stdutils)\n"
		"Copyright (C) 2014 Alan Potteiger\n"
		"Licensed under the 2-Clause BSD License\n\n"
		"Written by Alan Potteiger\n"
		"https://github.com/APott/stdutils\n"
	);
}
