/*
 * Just some macros for consistent error reporting
*/
/* Base macro, prints utility name, "error:", then the specified message. eg. cat: error: Specified file doesn't exist. */
#define ERROR(x) fprintf(stderr, "%s: error: %s\n", called, (x))
/* Print an error message then exit the program immediately. Accepts value to return then the error string */
#define ERRORX(x, y) ERROR((x)); exit((y));
