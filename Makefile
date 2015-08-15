OBJ=reg-redis.o reg-tcp.o gvt.o ht.o
WARNINGS=-Wall -W
CFLAGS=$(WARNINGS) -g

all: trac tra.o
trac: $(OBJ) tra.o hiredis/libhiredis.a
	gcc $(OBJ) tra.o hiredis/libhiredis.a -o trac -lev

# Deps (use make dep to generate this)
gvt.o: gvt.c gvt.h
ht.o: ht.c ht.h
reg-redis.o: reg-redis.c hiredis/hiredis.h hiredis/read.h hiredis/sds.h \
 hiredis/async.h hiredis/hiredis.h hiredis/adapters/libev.h \
 hiredis/adapters/../hiredis.h hiredis/adapters/../async.h reg-ev.h
reg-tcp.o: reg-tcp.c hiredis/hiredis.h hiredis/read.h hiredis/sds.h \
 hiredis/async.h hiredis/hiredis.h reg-ev.h gvt.h
test.o: test.c gvt.h ht.h
tra.o: tra.c reg-ev.h

hiredis/libhiredis.a:
	cd hiredis && $(MAKE)

test: dotest
	./dotest
dotest: $(OBJ) hiredis/libhiredis.a test.o
	gcc $(OBJ) hiredis/libhiredis.a test.o -lev -o dotest

.c.o:
	$(CC) -std=c99 -pedantic -c $(CFLAGS) $<

clean:
	rm *.o dotest trac
	cd hiredis && $(MAKE) clean

dep:
	$(CC) -MM *.c

.PHONY: all test clean dep
