run: compile
	./bin/main

runfcfs: compilefcfs
	./bin/fcfs

debug: compile
	gdb ./bin/main

debugf: compilefcfs
	gdb ./bin/fcfs

compile: 
	g++ -g -o bin/main src/main.c

compilefcfs:
	g++ -g -o bin/fcfs src/fcfs.c
