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
	math/vec2.cpp\
	math/vec3.cpp\
	math/vec4.cpp\
	math/mat3.cpp\
	math/mat4.cpp\
	math/curves.cpp\
	graphics/misc/window.cpp\
	graphics/misc/texture.cpp\
	graphics/program/program.cpp\
	graphics/program/shader.cpp\
	graphics/model/mesh.cpp\
	graphics/model/model.cpp\
    phys2/world.cpp\
    phys2/body.cpp\
    phys2/shape.cpp\
    phys2/contact.cpp
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
FLAGS=$(FCPPS) $(FINCS) $(FLDIR) $(FLIBS) -DGLEW_STATIC

# Rules
all:
ifeq ($(OS),Windows_NT)
	g++ $(FLAGS) -o $(EXE) -std=c++11 -mwindows -static -static-libgcc -static-libstdc++
else
	g++ $(FLAGS) -o $(EXE) -std=c++11
endif
