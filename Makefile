CC = g++
XT = cpp
EXAMPLE = InstancedRendering
TDIR = examples
X = app


SRCPATH=src/bodies/
SRCS=$(shell find src -type f -iname '*.cpp' | cut -d'/' -f3- )
FILES=$(foreach x, $(basename $(SRCS)), $(x).o)
OBJECTS=$(patsubst %, build/%, $(FILES))
SOURCES=$(patsubst %, src/bodies/%.cpp, $(SRCS))

TARGET = libturtle2d
DEFS = -o3 #-D DEBUG -ggdb3  -Wall
LIBS = -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -lSDL2_image
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run




example: 
	
	#CC=x86_64-w64-mingw32-g++
	#X=.exe
	
	$(CC) -c $(DEFS) $(TDIR)/$(EXAMPLE).$(XT) $(LIBS) -I ./src/  -o ./build/example.o 
	$(CC)  $(DEFS)  ./build/example.o libturtle2d.a $(LIBS)   -o $(EXAMPLE).$(X) 




lib: clean dirs $(FILES)
	ar rcs  $(TARGET).a $(OBJECTS)
 	
lib0:	
	ar rcs  $(TARGET).a $(OBJECTS)

%.o:
	$(CC) -c $(CFLAGS) $(DEFS)  $(SRCPATH)$(basename $@).cpp -o ./build/$@ 2>err
	


dirs:	
	mkdir -p build
	mkdir -p build/objects
	mkdir -p build/modules
	

clean:
	rm -rf *.app
	rm -rf build
	rm -rf 
	

