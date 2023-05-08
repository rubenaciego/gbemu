
NAME = gbemu
CC = g++
CPPFLAGS = -Isrc -g

all:
	${CC} ${CPPFLAGS} src/*.cpp src/mbcs/*.cpp -o ${NAME}
	
clean:
	rm ${NAME}
