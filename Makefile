
all: pwd cat chmod true false head sleep more

pwd: src/pwd/pwd.c
	$(CC) src/pwd/pwd.c -o bin/pwd

cat: src/cat/cat.c
	$(CC) src/cat/cat.c -o bin/cat

chmod: src/chmod/chmod.c
	$(CC) src/chmod/chmod.c -o bin/chmod

true: src/true/true.c
	$(CC) src/true/true.c -o bin/true

false: src/false/false.c
	$(CC) src/false/false.c -o bin/false

head: src/head/head.c
	$(CC) src/head/head.c -o bin/head

sleep: src/sleep/sleep.c
	$(CC) src/sleep/sleep.c -o bin/sleep

clean:
	mv bin/.gitignore .gitignore
	rm bin/*
	mv .gitignore bin/.gitignore
