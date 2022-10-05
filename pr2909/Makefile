compile0: main0.c
	gcc main0.c -o main0.o -lm

run0: main0.o
	./main0.o

compile2: main2.c
	gcc main2.c -o main2.o -lm

run2: main2.o
	./main2.o

compile3: main3.c students.h students.c
	gcc -c students.c -lm
	gcc main3.c -o main3.o -lm students.c

run3: main3.o
	./main3.o
