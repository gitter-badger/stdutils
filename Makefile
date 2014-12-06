
all: pwd cat chmod true false

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

clean:
	rm bin/*
	echo "This is to keep bin/ tracked" > bin/README
