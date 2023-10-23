# Makefile for use by NMAKE from the MSVC build tools.
#
# The preprocessor /D"main=SDL_main" is needed to give the code access to
# SDL's SDL_main function.

# The include and lib directories must exist in the SDL2_HOME directory.
INCLUDE_DIR=/I$(SDL2_HOME)\include /I..\..
LINK_DIR=/LIBPATH:"$(SDL2_HOME)\lib"

CC=cl
CFLAGS=/W3 /WX /EHsc
LIBS="SDL2.lib" "SDL2main.lib" "SDL2_ttf.lib" "SDL2_image.lib" "SDL2_mixer.lib" "kernel32.lib" "user32.lib" "shell32.lib"

SRC=..\..\*.cpp

all:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(SRC) /link $(LIBS) $(LINK_DIR) /SUBSYSTEM:WINDOWS -out:diabeetus.exe

debug:
	$(CC) $(CFLAGS) /JMC /D"_DEBUG" $(INCLUDE_DIR) $(SRC) /link $(LIBS) $(LINK_DIR) /SUBSYSTEM:CONSOLE -out:diabeetus.exe
