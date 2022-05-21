CC = g++
XT = cpp
SOURCES = $(shell find src -type f -iname '*.cpp')
OBJECTS = $(foreach x, $(basename $(SOURCES)), $(x).o)
TARGET = Turtle2D
DEFS = -D DEBUG -g -Wall
LIBS = -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -lSDL2_image 
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run



lib: $(TARGET)

	
	
%.o: %.c
	echo 'mao'
	echo $@

$(TARGET): $(OBJECTS)
	echo 'iii'
	

clean:
	rm -rf *.app
	

