CC = gcc
CFLAGS = -Wall -Werror -std=c99
LIBS = libprog2.a -lm

SRC = Cbitbank.c linkedlist.c test.c
OBJ = $(SRC:.c=.o)

TARGET = cbitbank

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
