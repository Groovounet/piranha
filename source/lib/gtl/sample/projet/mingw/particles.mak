#************************************************
# GTL
# Copyright (c) 2003-2004, G-Truc Creation.	
#************************************************
# G-Truc Creation, www.g-truc.net		
# par Groove, groove@g-truc.net		
#************************************************
# 03/10/2004
#************************************************

PROJET_BIN = ../../build/particles
PROJET_SRC = ../../src/particle
PROJET_INC = ../../src/particle
PROJET_OBJ = ./obj

EXT_INC = -I"../../lib/sdl/include" -I"../../../include"
EXT_DIR = -L"../../lib/sdl/lib/mingw" -L"../../../lib/mingw" 
EXT_LIB = -lmingw32 -mwindows -lSDLmain -lSDL -lgtl -lopengl32 -lglu32

CC = g++
OPTIMISATION = -Wall -pipe -g0 -O3 -fno-rtti -fno-exceptions -fexpensive-optimizations

OBJ = \
	$(PROJET_OBJ)/sample.o\
	$(PROJET_OBJ)/window_sdl.o\
	$(PROJET_OBJ)/terrain.o\
	$(PROJET_OBJ)/particle_element.o\
	$(PROJET_OBJ)/particle_system.o\
	$(PROJET_OBJ)/timer.o\
	$(PROJET_OBJ)/main.o

all: rep $(PROJET_BIN) clean

rep:
	mkdir $(PROJET_OBJ)

$(PROJET_BIN): $(OBJ)
	$(CC) -s -o $(PROJET_BIN) $^ $(EXT_DIR) $(EXT_LIB)

$(PROJET_OBJ)/%.o: $(PROJET_SRC)/%.cpp $(PROJET_INC)/%.h
	$(CC) -o $@ -c $< $(OPTIMISATION) $(EXT_INC)

clean:
	rm -R $(PROJET_OBJ)
