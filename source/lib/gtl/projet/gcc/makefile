#************************************************
# GTL
# Copyright (c) 2003 - 2004, G-Truc Creation.	
#************************************************
# G-Truc Creation, www.g-truc.net		
# par Groove, groove@g-truc.net		
#************************************************
# Makefile, 19/09/2004			
#************************************************

BIN = libgtl.a

REP_LIB = ../../lib/gcc
REP_SOURCE = ../../src
REP_INCLUDE = ../../include
REP_OBJ = ./obj

OPT_GL = -lGL -lGLU
OPT_INCLUDE = -I$(REP_INCLUDE)

CC = g++
OPTIMISATION = -O3 -Wall

DO_CC=$(CC) $(OPTIMISATION) $(OPT_INCLUDE) -c $< -o $@

OBJ = \
	$(REP_OBJ)/gtl_camera.o \
	$(REP_OBJ)/gtl_color3.o \
	$(REP_OBJ)/gtl_color4.o \
	$(REP_OBJ)/gtl_complex_algebraic.o \
	$(REP_OBJ)/gtl_complex_polar.o \
	$(REP_OBJ)/gtl_font.o \
	$(REP_OBJ)/gtl_font_tga.o \
	$(REP_OBJ)/gtl_gl.o \
	$(REP_OBJ)/gtl_glext.o \
	$(REP_OBJ)/gtl_image_bmp.o \
	$(REP_OBJ)/gtl_image_tga.o \
	$(REP_OBJ)/gtl_image_raw.o \
	$(REP_OBJ)/gtl_math.o \
	$(REP_OBJ)/gtl_matrix2x2.o \
	$(REP_OBJ)/gtl_matrix3x3.o \
	$(REP_OBJ)/gtl_matrix4x4.o \
	$(REP_OBJ)/gtl_polynomial.o \
	$(REP_OBJ)/gtl_quaternion.o \
	$(REP_OBJ)/gtl_rand.o \
	$(REP_OBJ)/gtl_screenshot.o \
	$(REP_OBJ)/gtl_shader.o \
	$(REP_OBJ)/gtl_vector2.o \
	$(REP_OBJ)/gtl_vector3.o \
	$(REP_OBJ)/gtl_vector4.o

gtl: obj $(BIN) mv clean

clean:
	rm -f $(BIN)
	rm -R $(REP_OBJ)
mv:
	mv $(BIN) $(REP_LIB)

obj:
	mkdir $(REP_OBJ)
	
install:
	mkdir /usr/include/gtl
	cp -R ../../include/* /usr/include/gtl
	cp ../../lib/$(BIN) /usr/lib

uninstall:
	rm -R /usr/include/gtl
	rm /usr/lib/$(BIN)

$(BIN): $(OBJ)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN)

$(REP_OBJ)/%.o: $(REP_SOURCE)/%.cpp $(REP_INCLUDE)/%.h
	$(DO_CC)

