run: main.o
	./main.o
compile: compileF compileG compileMain
compileF: f.c f.h
	gcc -c f.c -lm -Wall

compileG: g.c g.h
	gcc -c g.c -lm -Wall

compileMain: f.o g.o main.c
	gcc main.c -o main.o f.c g.c -lm
	chmod +x main.o
