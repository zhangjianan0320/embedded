edit : main.o list.o
	gcc main.o list.o -o edit
main.o:main.c list.h
	gcc -c main.c -o main.o
list.o:list.c list.h
	gcc -c list.c -o list.o

.PHONY:clean
clean:
	-rm -rf *.o

