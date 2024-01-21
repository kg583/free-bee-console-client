# freebee Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe
CFLAGS +=	-I/usr/local/include

PREFIX ?=	/usr/local
BINDIR ?=	${PREFIX}/bin
MANDIR ?=	${PREFIX}/man/man6

PROG =	freebee
OBJS =	anagram.o arc4random_uniform.o dir.o game.o main.o net.o rank.o \
	strlcat.o strtonum.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} -lncurses -L/usr/local/lib -lcurl

install:
	/usr/bin/install -d -m 755 ${BINDIR}
	/usr/bin/install -d -m 755 ${MANDIR}
	/usr/bin/install -c -s -m 555 freebee ${BINDIR}
	/usr/bin/install -c -m 444 freebee.6 ${MANDIR}

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
