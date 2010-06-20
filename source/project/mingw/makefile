PROJECT_BIN = ../../../piranha.exe
PROJECT_SRC = ../../src
PROJECT_INC = ../../src
PROJECT_OBJ = ./obj

EXT_DIR = -L"../../lib/sdl/lib/mingw" -L"../../lib/gtl/lib/mingw"
EXT_LIB = $(EXT_DIR) -lmingw32 -mwindows -lSDLmain -lSDL -lgtl -lopengl32 -lglu32
EXT_INC = -I"../../lib/sdl/include" -I"../../lib/gtl/include"

CFG_CC = g++
CFG_OPT = -fexpensive-optimizations -O2 # -Wall -D DEBUG

OBJ = \
	$(PROJECT_OBJ)/scene/element.o\
	$(PROJECT_OBJ)/scene/element_author.o\
	$(PROJECT_OBJ)/scene/element_credits.o\
	$(PROJECT_OBJ)/scene/element_explode1.o\
	$(PROJECT_OBJ)/scene/element_explode2.o\
	$(PROJECT_OBJ)/scene/element_explode3.o\
	$(PROJECT_OBJ)/scene/element_fade.o\
	$(PROJECT_OBJ)/scene/element_loading.o\
	$(PROJECT_OBJ)/scene/element_terrain1.o\
	$(PROJECT_OBJ)/scene/element_terrain2.o\
	$(PROJECT_OBJ)/scene/element_terrain3.o\
	$(PROJECT_OBJ)/scene/element_terrain4.o\
	$(PROJECT_OBJ)/scene/element_terrain5.o\
	$(PROJECT_OBJ)/scene/element_terrain6.o\
	$(PROJECT_OBJ)/scene/element_terrain7.o\
	$(PROJECT_OBJ)/scene/element_title.o\
	$(PROJECT_OBJ)/scene/element_tunnel1.o\
	$(PROJECT_OBJ)/scene/element_tunnel2.o\
	$(PROJECT_OBJ)/scene/element_tunnel3.o\
	$(PROJECT_OBJ)/scene/element_tunnel4.o\
	$(PROJECT_OBJ)/scene/element_tunnel5.o\
	$(PROJECT_OBJ)/scene/element_tunnel6.o\
	$(PROJECT_OBJ)/scene/element_tunnel7.o\
	$(PROJECT_OBJ)/scene/element_tunnel8.o\
	$(PROJECT_OBJ)/scene/manager.o\
	$(PROJECT_OBJ)/file/manager.o\
	$(PROJECT_OBJ)/file/element.o\
	$(PROJECT_OBJ)/file/element_terrain.o\
	$(PROJECT_OBJ)/file/texture.o\
	$(PROJECT_OBJ)/file/texture_mipmaps2d.o\
	$(PROJECT_OBJ)/file/texture_rectangle.o\
	$(PROJECT_OBJ)/file/texture_texture2d.o\
	$(PROJECT_OBJ)/gl/camera.o\
	$(PROJECT_OBJ)/gl/fade.o\
	$(PROJECT_OBJ)/gl/object.o\
	$(PROJECT_OBJ)/gl/object_dl.o\
	$(PROJECT_OBJ)/gl/object_ge.o\
	$(PROJECT_OBJ)/gl/proc.o\
	$(PROJECT_OBJ)/gl/shader.o\
	$(PROJECT_OBJ)/gl/state_auto.o\
	$(PROJECT_OBJ)/gl/state_manu.o\
	$(PROJECT_OBJ)/particle/manager.o\
	$(PROJECT_OBJ)/particle/system.o\
	$(PROJECT_OBJ)/particle/system_cube.o\
	$(PROJECT_OBJ)/particle/system_death_planet.o\
	$(PROJECT_OBJ)/particle/system_explode.o\
	$(PROJECT_OBJ)/particle/system_fire.o\
	$(PROJECT_OBJ)/particle/system_fountain.o\
	$(PROJECT_OBJ)/particle/system_smoke.o\
	$(PROJECT_OBJ)/particle/system_stars.o\
	$(PROJECT_OBJ)/particle/system_trail.o\
	$(PROJECT_OBJ)/terrain/terrain.o\
	$(PROJECT_OBJ)/terrain/ground.o\
	$(PROJECT_OBJ)/terrain/lighting.o\
	$(PROJECT_OBJ)/terrain/sky.o\
	$(PROJECT_OBJ)/tinyxml/tinystr.o\
	$(PROJECT_OBJ)/tinyxml/tinyxml.o\
	$(PROJECT_OBJ)/tinyxml/tinyxmlerror.o\
	$(PROJECT_OBJ)/tinyxml/tinyxmlparser.o\
	$(PROJECT_OBJ)/util/common.o\
	$(PROJECT_OBJ)/util/singleton.o\
	$(PROJECT_OBJ)/util/smart.o\
	$(PROJECT_OBJ)/util/timer_global.o\
	$(PROJECT_OBJ)/util/timer_local.o\
	$(PROJECT_OBJ)/util/tracked.o\
	$(PROJECT_OBJ)/util/tracker.o\
	$(PROJECT_OBJ)/util/state_machine.o\
	$(PROJECT_OBJ)/window/main.o\
	$(PROJECT_OBJ)/window/hud.o\
	$(PROJECT_OBJ)/window/window.o\
	$(PROJECT_OBJ)/window/window_sdl.o

all: obj $(PROJECT_BIN)

obj:
	mkdir $(PROJECT_OBJ)
	mkdir $(PROJECT_OBJ)/scene
	mkdir $(PROJECT_OBJ)/file
	mkdir $(PROJECT_OBJ)/gl
	mkdir $(PROJECT_OBJ)/particle
	mkdir $(PROJECT_OBJ)/terrain
	mkdir $(PROJECT_OBJ)/tinyxml
	mkdir $(PROJECT_OBJ)/util
	mkdir $(PROJECT_OBJ)/window

clean:
	rm -R $(PROJECT_OBJ)

$(PROJECT_BIN): $(OBJ)
	$(CFG_CC) -o $(PROJECT_BIN) $(OBJ) $(EXT_LIB) -s

$(PROJECT_OBJ)/%.o: $(PROJECT_SRC)/%.cpp $(PROJECT_INC)/%.h
	$(CFG_CC) $(EXT_INC) $(CFG_OPT) -c $< -o $@
