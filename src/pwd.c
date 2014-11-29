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
void usage(char *name);
int pwd(size_t);
int main(int argc, char *argv[])
{
	int o;
	/* If this value is 0 there has been no option or the -L option selected
		If greater than 0 -P has been selected */
	int LP = 0;
	while ((o = getopt(argc, argv, "hLP")) != -1) {
		switch (o) {
			case 'L':
				LP = 0;		
			break;
			case 'P':
				LP++;
			break;
			case 'h':
				usage(argv[0]);
				return 0;
			break;
			case '?':
				usage(argv[0]);
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
	
	switch (errno) {
		case EINVAL:
			free(buf);
		return pwd(1024);
		case ERANGE:
			free(buf);
		return pwd(length*2);
		case EACCES:
			fprintf(stderr, "Permission denied.");
			free(buf);
		return 1;
		case ENOMEM:
			fprintf(stderr, "No memory.");
			free(buf);
		return 1;
	}
}
/*
 * Print usage of `pwd` to standard out.
*/
void usage(char *name)
{
	printf(
		"Usage: %s [-L|-P]\n"
		"Return name of working directory\n"
		"Following is a list of currently supported options.\n"
		
		"\t-h\tDisplay this help/usage screen.\n"
		,
		name
	);
}
