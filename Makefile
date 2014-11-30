
all: pwd cat chmod

pwd: src/pwd.c
	$(CC) src/pwd.c -o bin/pwd

cat: src/cat.c
	$(CC) src/cat.c -o bin/cat

chmod: src/chmod.c
	$(CC) src/chmod.c -o bin/chmod

clean:
	rm bin/*
