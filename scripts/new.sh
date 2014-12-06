#!/bin/sh
# Script to write a template for a new utility by only providing a name (I'm lazy)
# ./new.sh [UTILITY] [AUTHORS] 

# New directory for new utility
mkdir src/$1
# touch for a manpage later
touch src/$1/$1.1
# write out the template to ../src/$1/$1.c
echo \
"\
/*
 * Written by $2
 *
 * Licensed under the 2-Clause BSD License
 * See LICENSE in the root of the project
 * 
 * $1.c - 
 * 
*/
#include <stdio.h>
#include \"../info.h\"
#define AUTHORS \"$2\"
#define UTILITY \"$1\"
void usage();
void version();
/* Under what name the program was executed */
static char *called;

int main(int argc, char *argv[])
{
	called = argv[0];
	int o;
	while ((o = getopt(argc, argv, \"?hV\")) != -1) {
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
 * Print usage of \`$1\` to standard out.
*/
void usage()
{
	printf(
		\"Usage: %s \\\n\"
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
		\"%s (stdutils %s)\\\n\"
		\"Written by %s\\\n\"
		\"Licensed under the 2-Clause BSD License\\\n\"
		\"%s\\\n\"
		,
		UTILITY,
		VERSION,
		AUTHORS,
		HOMEPAGE
	);
}
" > src/$1/$1.c
