
all: pwd cat chmod

pwd: src/pwd/pwd.c
	$(CC) src/pwd/pwd.c -o bin/pwd

cat: src/cat/cat.c
	$(CC) src/cat/cat.c -o bin/cat

chmod: src/chmod/chmod.c
	$(CC) src/chmod/chmod.c -o bin/chmod

clean:
	rm bin/*
	echo "This is to keep bin/ tracked" > bin/README
