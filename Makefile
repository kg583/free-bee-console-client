# free bee Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe
CFLAGS +=	-I/usr/local/include

PROG =	freebee
OBJS =	anagram.o dir.o game.o main.o net.o rank.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} -lncurses -L/usr/local/lib -lcurl

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
