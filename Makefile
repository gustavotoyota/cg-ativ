# Paths
SRC=src
DEPS=\
	deps/SDL/include\
	deps/glew/include\
	deps/stb/include
INCS=$(SRC) $(DEPS)
LDIR=\
	deps/SDL/lib\
	deps/glew/lib

# Files
EXE=cg-ativ
CPPS=\
	main.cpp\
	misc/utils.cpp\
	math/ivec2.cpp\
	math/vec2.cpp\
	math/vec3.cpp\
	math/vec4.cpp\
	math/mat4.cpp\
	graphics/misc/window.cpp\
	graphics/misc/texture.cpp\
	graphics/program/program.cpp\
	graphics/program/shader.cpp\
	graphics/model/mesh.cpp\
	graphics/model/model.cpp
ifeq ($(OS),Windows_NT)
LIBS=\
	SDL2main\
	SDL2\
	glew32s\
    opengl32
else
LIBS=\
	SDL2main\
	SDL2\
	GLEW\
	GL
endif

# Flags
FINCS=$(foreach i, $(INCS), -I $i)
FCPPS=$(foreach i, $(CPPS), $(SRC)/$i)
FLDIR=$(foreach i, $(LDIR), -L $i)
FLIBS=$(foreach i, $(LIBS), -l $i)
FLAGS=-DGLEW_STATIC $(FCPPS) $(FINCS) $(FLDIR) $(FLIBS)

# Rules
all:
ifneq ($(OS),Windows_NT)
ifneq ($(shell bash -c 'read -p "Install dependencies? (y\\n): " inst; echo $$inst'),n)
	sudo apt-get -qq install libglew-dev
	sudo apt-get -qq install libsdl2-dev
endif
	g++ $(FLAGS) -o $(EXE) -std=c++11
else
	g++ $(FLAGS) -o $(EXE) -std=c++11 -mwindows
endif
