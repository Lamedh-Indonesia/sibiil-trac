WARNINGS=-Wall -W
CFLAGS=$(WARNINGS)

all: tra.o redis test
	gcc tra.o hiredis/libhiredis.a -o trac -lev

# Deps (use make dep to generate this)
gvt.o: gvt.c gvt.h
test.o: test.c gvt.h
tra.o: tra.c hiredis/hiredis.h hiredis/read.h hiredis/sds.h \
 hiredis/async.h hiredis/hiredis.h hiredis/adapters/libev.h \
 hiredis/adapters/../hiredis.h hiredis/adapters/../async.h

redis:
	cd hiredis && $(MAKE)

test: dotest
	./dotest
dotest: test.o gvt.o
	gcc test.o gvt.o -o dotest

.c.o:
	$(CC) -std=c99 -pedantic -c $(CFLAGS) $<

clean:
	rm *.o dotest trac

dep:
	$(CC) -MM *.c

.PHONY: all redis test clean dep
