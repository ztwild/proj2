all: appserver-coarse.c
	gcc -o appserver-coarse appserver-coarse.c -pthread

run: appserver-coarse
	./appserver-coarse 5 5 out
