# free bee Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe

PROG =	freebee
OBJS =	anagram.o game.o main.o rank.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS}

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
