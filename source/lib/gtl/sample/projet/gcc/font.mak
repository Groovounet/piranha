#************************************************
# GTL
# Copyright (c) 2003-2004, G-Truc Creation.	
#************************************************
# G-Truc Creation, www.g-truc.net		
# par Groove, groove@g-truc.net		
#************************************************
# 09/10/2004
#************************************************

PROJET_BIN = ../../build/font
PROJET_SRC = ../../src/font
PROJET_INC = ../../src/font
PROJET_OBJ = ./obj

EXT_DIR = -L"../../../lib/gcc" 
EXT_LIB = -lGL -lGLU -lm -lgtl

CC = g++
OPTIMISATION = -Wall -pipe -g0 -O3 -fno-rtti -fno-exceptions -fexpensive-optimizations

OBJ = \
	$(PROJET_OBJ)/sample.o\
	$(PROJET_OBJ)/window_sdl.o\
	$(PROJET_OBJ)/main.o

all: rep $(PROJET_BIN) clean

rep:
	mkdir $(PROJET_OBJ)

$(PROJET_BIN): $(OBJ)
	$(CC) -s -o $(PROJET_BIN) $^ $(EXT_DIR) $(EXT_LIB) `sdl-config --libs`

$(PROJET_OBJ)/%.o: $(PROJET_SRC)/%.cpp $(PROJET_INC)/%.h
	$(CC) -o $@ -c $< $(OPTIMISATION) `sdl-config --cflags`

clean:
	rm -R $(PROJET_OBJ)
