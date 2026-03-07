TARGET = ./a.out
FILES = main.o matrix.o menu.o test.o
compile: *.c
		gcc main.c matrix.c menu.c test.c -g -o main
.PHONY: all clean install unistall
all: $(TARGET)
run: compile
	./main
main.o: main.c
	gcc -c -o main.o main.c
matrix.o: matrix.c
	gcc -c -o matrix.o matrix.c
menu.o: menu.c
	gcc -c -o menu.o menu.c
test.o: test.c
	gcc -c -o test.o test.c