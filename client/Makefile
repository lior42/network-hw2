# Name of the program - will be located at OUTDIR
BIN=test
# Compiler
CC=gcc
# Flags, -g was added for debugging
override CFLAGS+=-Wall -g
# build directory
OUTDIR=build

# From this point - dont touch... never
OBJS=$(patsubst src/%.c,%.o, $(wildcard src/*.c))

all: ${BIN}

clean: ${OUTDIR}
	${RM} -rf ${OUTDIR}

${BIN}: ${OBJS} ${OUTDIR}
	${CC} ${CFLAGS} ${OUTDIR}/objs/${OBJS} -o ${OUTDIR}/${BIN}

${OUTDIR}:
	mkdir -p ${OUTDIR}
	mkdir -p ${OUTDIR}/objs

%.o: src/%.c ${OUTDIR}
	${CC} ${CFLAGS} -c $< -o ${OUTDIR}/objs/$@