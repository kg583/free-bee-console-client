# freebee Makefile

CC ?=		cc
CFLAGS ?=	-O2 -pipe
CFLAGS +=	-I/usr/local/include

# Remove if your system doesn't have
# arc4random_uniform(3) and/or strlcat(3)
CFLAGS +=	-DHAVE_ARC4RANDOM_UNIFORM -DHAVE_STRLCAT

# Uncomment if you don't want to install
# or if you plan to install the dictionary somewhere
# other than /usr/local/share/freebee/sowpods.txt
#CFLAGS +=	-DDICTIONARY="\"sowpods.txt\""

PREFIX ?=	/usr/local
BINDIR ?=	${PREFIX}/bin
MANDIR ?=	${PREFIX}/man/man6
SHAREDIR ?=	${PREFIX}/share/freebee

PROG =	freebee
OBJS =	anagram.o arc4random_uniform.o dir.o game.o main.o net.o rank.o strlcat.o

all: ${OBJS}
	${CC} ${LDFLAGS} -o ${PROG} ${OBJS} -lncurses -L/usr/local/lib -lcurl

install:
	/usr/bin/install -d -m 755 ${BINDIR}
	/usr/bin/install -d -m 755 ${MANDIR}
	/usr/bin/install -d -m 755 ${SHAREDIR}
	/usr/bin/install -c -s -m 555 freebee ${BINDIR}
	/usr/bin/install -c -m 444 freebee.6 ${MANDIR}
	/usr/bin/install -c -m 444 sowpods.txt ${SHAREDIR}

clean:
	rm -f ${PROG} ${OBJS} ${PROG}.core
