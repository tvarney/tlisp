
EXEC=tlisp
INC=./inc
SRC=./src

CC=gcc
CFLAGS=-Wall -Wextra -Werror -c
LFLAGS=-Wall
LEX=flex
LEXFLAGS=-8
YACC=bison
YACCFLAGS=

OBJECTS=$(patsubst %.c,%.o,$(wildcard ${SRC}/*.c))

all: ${EXEC}

${EXEC}: parser lexer ${OBJECTS}

lexer: ${SRC}/lexer.l
	${LEX} ${LEXFLAGS} -o ${SRC}/lexer.c ${SRC}/lexer.l
	${CC} ${CFLAGS} -o ${SRC}/lexer.o ${SRC}/lexer.c
	rm ${SRC}/lexer.c ${SRC}/parser.tab.h

parser: ${SRC}/parser.y
	${YACC} ${YACCFLAGS} -o ${SRC}/parser.tab.c ${SRC}/parser.y
	${CC} ${CFLAGS} -o ${SRC}/parser.o ${SRC}/parser.tab.c
	rm ${SRC}/parser.tab.c

clean:
	rm -f ${SRC}/lexer.c
	rm -f ${SRC}/*.o
	rm -f ${EXEC}

%.o: %.c
	${CC} ${CFLAGS} $< -o $@
