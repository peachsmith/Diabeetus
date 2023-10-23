# A Makefile for MinGW-w64.
#
# Used by running mingw32-make.exe
# This assumes all the dependencies are installed in an MSYS2 environment.
#
# The preprocessor -Dmain=SDL_main is needed to give the code access to
# SDL's SDL_main function.

CC=g++
LIBS=-lmingw32 -lSDL2main -lSDL2
SRC=../../*.cpp

all:
	$(CC) $(SRC) -o diabeetus $(LIBS)

debug:
	$(CC) -g $(SRC) -o diabeetus $(LIBS)
