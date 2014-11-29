
all: pwd

pwd: src/pwd.c
	$(CC) src/pwd.c -o bin/pwd

clean:
	rm bin/*
