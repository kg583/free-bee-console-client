# free bee Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe
CFLAGS +=	-I/usr/local/include

PREFIX ?=	/usr/local

PROG =	freebee
OBJS =	anagram.o dir.o game.o main.o net.o rank.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} -lncurses -L/usr/local/lib -lcurl

install:
	/usr/bin/install -d -m 755 ${PREFIX}/bin
	/usr/bin/install -d -m 755 ${PREFIX}/share/freebee
	/usr/bin/install -c -s -m 555 freebee ${PREFIX}/bin
	/usr/bin/install -c -m 444 sowpods.txt ${PREFIX}/share/freebee

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
