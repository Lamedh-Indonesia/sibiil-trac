OBJ=reg-redis.o reg-tcp.o tra.o
WARNINGS=-Wall -W
CFLAGS=$(WARNINGS) -g

all: trac
trac: $(OBJ) hiredis/libhiredis.a
	gcc $(OBJ) hiredis/libhiredis.a -o trac -lev

# Deps (use make dep to generate this)
gvt.o: gvt.c gvt.h
reg-redis.o: reg-redis.c hiredis/hiredis.h hiredis/read.h hiredis/sds.h \
 hiredis/async.h hiredis/hiredis.h hiredis/adapters/libev.h \
 hiredis/adapters/../hiredis.h hiredis/adapters/../async.h reg-ev.h
reg-tcp.o: reg-tcp.c reg-ev.h
test.o: test.c gvt.h
tra.o: tra.c reg-ev.h

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
