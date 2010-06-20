#************************************************
# GTL
# Copyright (c) 2003-2004, G-Truc Creation.	
#************************************************
# G-Truc Creation, www.g-truc.net		
# par Groove, groove@g-truc.net		
#************************************************
# makefile, 02/10/2004			
#************************************************

BIN = libgtl.a

REP_LIB = ../../lib/mingw
REP_SOURCE = ../../src
REP_INCLUDE = ../../include
REP_OBJ = ./obj

CC = g++
OPTIMISATION = -Wall -pipe -g0 -O2 -fno-rtti -fno-exceptions -fexpensive-optimizations

DO_CC=$(CC) $(OPTIMISATION) -I$(REP_INCLUDE) -c $< -o $@

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
	mkdir obj
	
$(BIN): $(OBJ)
	ar r $(BIN) $(OBJ)
	ranlib $(BIN)

$(REP_OBJ)/%.o: $(REP_SOURCE)/%.cpp $(REP_INCLUDE)/%.h
	$(DO_CC)
