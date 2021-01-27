CC = g++
CFLAGS = -I include
EXE = bst.x

${EXE}:
	${CC} ${CFLAGS} main.cpp -o ${EXE}

.PHONY: clean
clean:
	rm -f *.x *.o
