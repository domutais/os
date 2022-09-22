run: main.o
	./main.o
compile: compileF compileG compileMain
compileF: f.c f.h
	gcc -c f.c -Wall

compileG: g.c g.h
	gcc -c g.c -Wall

compileMain: f.o g.o main.c
	gcc -c main.c f.h g.h -Wall
	chmod +x main.o
