# freebee Makefile

PROG =	freebee
OBJS =	anagram.o main.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS}

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
