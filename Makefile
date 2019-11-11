.PHONY: run

run: main
	@./main

main: main.c
	@gcc -std=c99 -o main main.c -lpthread 
