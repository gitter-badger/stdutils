
all: pwd cat

pwd: src/pwd.c
	$(CC) src/pwd.c -o bin/pwd

cat: src/cat.c
	$(CC) src/cat.c -o bin/cat

clean:
	rm bin/*
