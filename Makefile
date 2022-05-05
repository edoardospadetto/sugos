TARGET = VectObjShader
TDIR = examples
CC = g++
XT = cpp



MAIN = examples/$(TARGET)
#OBJS specifies which files to compile as part of the project

SRCS = -I ./include
DEFS = -D DEBUG -g -Wall

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run




#This is the target that compiles our executable
$(MAIN): 
	$(CC) $(DEFS) $(SRCS) $(TDIR)/$(TARGET).$(XT) -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -o $(TARGET).app 

clean:
	rm -r *.app
