#object = main.o list.o add.o
source = $(wildcard *.c)
object = $(patsubst %.c,%.o,$(source))

OBJ = edit

$(OBJ) : $(object)
	cc $(object) -o $(OBJ)

$(object):list.h

#main.o: list.h#
#list.o: list.h#

.PHONY:clean
clean:
	rm -rf *.o $(OBJ)

