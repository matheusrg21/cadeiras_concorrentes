.PHONY: run

run: main
	@./main

main: main.c
	@gcc -std=c99 -lpthread -o main main.c 
