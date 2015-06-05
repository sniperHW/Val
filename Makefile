all:
	gcc -g -o test test.c Val.c lookup8.c -llua -ldl -lrt -lm -Wall