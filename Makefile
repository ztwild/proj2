all: appserver.c
	gcc -o appserver appserver.c -pthread
test: test.c
	gcc -o test test.c
