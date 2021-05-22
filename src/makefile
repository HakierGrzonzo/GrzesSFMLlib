CFILES   = $(wildcard *.c)
CPPFILES = $(wildcard *.cpp)
OBJFILES = $(CFILES:.c=.o) $(CPPFILES:.cpp=.o)
OUT      = main

LOADLIBES = -lm -lsfml-graphics -lsfml-window -lsfml-system -lbox2d
CXXFLAGS = -Wall -O2 -g -fPIC

CC = g++

$(OUT): $(OBJFILES)

run: $(OUT)
	./$(OUT)

.PHONY: clean
clean:
	rm -f $(OBJFILES) $(OUT) vgcore.*
