# Makefile for MacOS.
#
# This file assumes that SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer are
# installed in the /Library/Frameworks directory.
#
# The preprocessor definition -D_main=_SDL_main is needed to give the code
# access to SDL's SDL_main function.

# MacOS
CC=clang++
MAIN_DEF=-D_main=_SDL_main

INCLUDE_DIR=-I/Library/Frameworks/SDL2.framework/Headers -I../..
LINK_DIR=-F/Library/Frameworks -L.

CFLAGS=-Wall -Werror
LIBS=-framework SDL2

tootnsploot-debug:
	$(CC) -g $(MAIN_DEF) ../../*.cpp -o diabeetus $(INCLUDE_DIR) $(LINK_DIR) $(LIBS)

all:
	$(CC) $(MAIN_DEF) ../../*.cpp -o diabeetus $(INCLUDE_DIR) $(LINK_DIR) $(LIBS)
