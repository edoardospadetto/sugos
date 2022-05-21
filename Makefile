CC = g++
XT = cpp
EXAMPLE = JumpingShape
TDIR = examples
X = app


SRCPATH=src/bodies/
SRCS=$(shell find src -type f -iname '*.cpp' | cut -d'/' -f3- )
FILES=$(foreach x, $(basename $(SRCS)), $(x).o)
OBJECTS=$(patsubst %, obj/%, $(FILES))
SOURCES=$(patsubst %, src/bodies/%.cpp, $(SRCS))

TARGET = libturtle2d
DEFS = -D DEBUG -g -Wall
LIBS = -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -lSDL2_image
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run



example: 
	
	#CC=x86_64-w64-mingw32-g++
	#X=.exe
	
	$(CC) -c $(DEFS) $(TDIR)/$(EXAMPLE).$(XT) $(LIBS)  -o ./obj/example.o 
	$(CC)  $(DEFS)  ./obj/example.o libturtle2d.a $(LIBS)   -o $(EXAMPLE).$(X) 




lib: clean dirs $(FILES)
	ar rcs  $(TARGET).a $(OBJECTS)
 	
	

%.o:
	$(CC) -c $(CFLAGS)   $(SRCPATH)$(basename $@).cpp -o ./obj/$@ 2>err
	


dirs:	
	mkdir -p obj
	mkdir -p obj/objects
	mkdir -p obj/modules
	

clean:
	rm -rf *.app
	rm -rf obj
	

