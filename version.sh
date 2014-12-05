#!/bin/sh
# Creates a version header file in src/ so utilities know the version of stdutils
echo \
"#ifndef VERSION
#define VERSION \""\
`git describe`"\"
#endif" > src/version.h
