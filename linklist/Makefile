object = main.o list.o

edit : $(object)
	cc $(object) -o edit

$(object):list.h

#main.o: list.h#
#list.o: list.h#

.PHONY:clean
clean:
	rm -rf *.o

