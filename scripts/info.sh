#!/bin/sh
# Creates a info.h header in ../src for utilities to include for basic, required information
HOMEPAGE="https://github.com/apott/stdutils"

echo \
"#ifndef VERSION
#define VERSION \""\
`git describe`"\"
#define HOMEPAGE \"$HOMEPAGE\"
#endif" > src/info.h
