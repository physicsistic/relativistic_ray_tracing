BASE = main

all: $(BASE)

OS := $(shell uname -s)

ifdef OPT 
  #turn on optimization
  CXXFLAGS += -O2
else 
  #turn on debugging
  CXXFLAGS += -g
endif

ifeq ($(OS), Darwin) # Assume OS X
  CPPFLAGS += -D__MAC__
  LDFLAGS += -framework GLUT -framework OpenGL
endif

CXX = g++ 

OBJ = $(BASE).o light.o material.o object.o sphere.o plane.o box.o cylinder.o scene.o ray.o

$(BASE): $(OBJ)
	$(LINK.cpp) -o $@ $^

clean:
	rm -f $(OBJ) $(BASE)
