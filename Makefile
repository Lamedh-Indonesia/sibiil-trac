all: tra.o redis
	gcc tra.o hiredis/libhiredis.a -o trac -lev
redis:
	cd hiredis && $(MAKE)
tra.o: tra.c
	gcc -c tra.c

.PHONY: all redis
