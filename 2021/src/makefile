CC=g++

CFLAGS=-std=gnu++11 -ggdb -O0


#DEPS = board.h config.h sprite_config.h ui.h controls.h

OBJ = 	main.o \
		day01.o \
		day02.o \
		day03.o \
		day04.o \
		day05.o \
		day06.o \

%.o: %.cpp
	$(CC) -c -o $@ $<  $(CFLAGS)

../aoc2021: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o
