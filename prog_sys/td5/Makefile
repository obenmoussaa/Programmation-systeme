LDFLAGS=-L.
LDLIBS=-lutils
CFLAGS+= -D_GNU_SOURCE -Wall -Werror

libutils.a: utils.o
	ar r $@ $?

clean:
	rm -f *~ *.o libutils.a

