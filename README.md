# stdutils
### What?
This is an attempt at writing standard POSIX comformant utilities. Hence
std (standard) utils (utilities). The goal is to be as conformant as
possible with the POSIX(2008) standards. In the implementation only POSIX
or standard library functions should be used (no GNU extensions).

### Why?
Why not? <insert other reason here I may use down the road>

### How do I get it?
Since it's not really ready for use yet (just in the beginnings) there are
no packages or anything available for download. If you want to test the code
or hack on it, of course you can clone the git repository at
<https://github.com/apott/stdutils>.
```sh
git clone https://github.com/apott/stdutils
```
Now you're all set!

### What's Implemented?
I will be updating this list as I go along, obviously there's not much in
the beginning but hopefully the list will grow. There are two lists, complete,
and incomplete. The items in the complete list seem to be up to the POSIX
specification in my opinion and in my testing, this of course may not be the
case, so just email me if that's what you find (info at bottom). The items in
the incomplete list may just not be complete (not up to the specification) or
may have bugs, I will list the reason with it. Utilities that have absolutely
no code are not in either list, the utilities that should be implemented will
be discussed later.
	
Complete:
- pwd
- cat
- true
- false
- head
- sleep
	
Incomplete:
- chmod: Symbolic modes not implemented yet. (I'm lazy)

### What should be implemented?
Good question! Obviously not every utility listed by POSIX should be
implemented in my opinion. Some utilities are obsolete or irrelevant, or are
too large to be implemented in this package and should be in their own. For a
utility to be in this package it should be logical and maintainable to be
implemented in one (two if you include shared code) file. For example: the 
`sh` utility (the shell) is listed by POSIX as a utility, obviously with all
the features and operations it performs, it would be illogical to maintain the
codebase in one file. This also holds true with compilers, or other complex
utilities. Of course, there are some exceptions to this, we'll cross that 
bridge when it gets here.

### Directory Structure
Directory structure, nothing to crazy here (hopefully). I'll write out a
little tree here for you. (Anything with / after it is a directory)
	
Tree:
- bin/        Destination for binaries, none should be tracked.
- scripts/    Contains various scripts to run to make hacking easier.
- src/        Mainly contains source.
- Makefile    Makefile to compile the code.
- LICENSE     License for the project, 2-Clause BSD License to be specific
- README      You're looking at it.
			
### Source Stucture
The src/ directory should be kept quite clean, mostly source but there's a
few exceptions. At the top level of src/ there should only be directories for
various utilities eg. `pwd/`, some header files or universal code to be used
by utilities, or maybe some documentation. Within directories for utilities
there should be 2 files (maybe more). First is the source file, eg. `pwd.c`,
second is a manual page for the utility, eg. `pwd.1`. 

### Source Code
Most code is and should be written in C, no C++, just plain C using only the
standard C libraries, no GNU extensions (trying to keep this portable). Coding
style will be enumerated at a later date, really depends who jumps on board
first, I'm using mine at the moment.

### Manual Pages
They're not neccessary quite yet, but should be written eventually. I tend
to write one (not neccessarily the most thorough) once I believe I've
completed a utility, helps me review, check whether I've implemented
everything.

### Scripts
Currently there are two scripts within scripts/. `new.sh` is a script that
automates the creation of boiler plate code for a new utility. It creates a
new directory in src/, a source file including boiler plate code, and an empty
file for a manual page. The second script is `info.sh`. `info.sh` simply
updates information in the info.h header file within src/. It updates the
VERSION macro defined in info.h to the latest information from git. Details on
these scripts can be seen in scripts/.

### Building
To build stdutils all you need is the source, a C compiler that compiles
standard C and it would be best to have an implementation of `make` installed,
such as GNU Make.

It's quite easy to build:
```sh
make
```
This compiles everything and places binaries in bin/.
Of course if you want to only compile a specific utility for efficiency:
```sh
make pwd
```
would only compile the `pwd` utility.
If you would like to remove binaries from bin/ simply:
```sh
make clean
```
and you're all set.
	
There is no automated installation at this point because the codebase is still
unstable and it's best not to replace the tried and true GNU coreutils you
likely have installed.

### Contributing
If you're interested in contributing that would be awesome. Eventually I
will accept pull requests but not at this time, still trying to get things
in a good state for the future. If you're interested in contributing and
helping out with the project in the long term what would be great. 

### License
stdutils is licensed under the 2-Clause BSD License, terms of this license
are in the LICENSE file.

### Contact
If you wish to contact me about contributing or anything else please feel
free to email me, <alanpotteiger@gmail.com>. I check my email quite frequently
but I probably won't reply INSTANTLY, but at the very most a day.

### What Now?
Well... I suppose you could check out some of the code, test some, or write
some of your own and check about contributing? Or you could send me some spam,
or some hate mail. Once someone sends me hate mail, I know I've really made it
so feel free to send me some hate mail. 

Thanks for the read and checking out stdutils.
~ Alan Potteiger
