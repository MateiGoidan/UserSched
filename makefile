run: compile
	./bin/main

debug: compile
	gdb ./bin/main

compile: 
	g++ -g -o bin/main src/main.c
