all: appserver.c
	gcc -o appserver appserver.c -pthread
