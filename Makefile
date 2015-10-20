TARGET = rand_data.bin

CC = gcc -O3
CC_PARAMTERS = 
RM = rm -f
EDIT_TMP_FILES = *~ *.data
BIN_FILES = *.bin
CONSOLE_OUTPUT = -D CONSOLE_OUTPUT

build: 
	${CC} *.c ${CC_PARAMTERS} -o ${TARGET}
	
clean:
	${RM} ${TARGET} $(EDIT_TMP_FILES) ${BIN_FILES} 

test:
	${CC} test.c -o ${TARGET}
