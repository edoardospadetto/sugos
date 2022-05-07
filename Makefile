TARGET = CollidersExample
TDIR = examples
CC = g++
XT = cpp
X = app

#CC=x86_64-w64-mingw32-g++
#X=.exe


MAIN = examples/$(TARGET)
#OBJS specifies which files to compile as part of the project

SRCS = -I ./include
DEFS = -D DEBUG -g -Wall

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run




#This is the target that compiles our executable
$(MAIN): 
	make clean
	$(CC) $(DEFS) $(SRCS) $(TDIR)/$(TARGET).$(XT) -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -o $(TARGET).$(X) 

clean:
	rm -rf *.app
	
	

