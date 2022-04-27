#OBJS specifies which files to compile as part of the project
OBJS = main.cpp
SRCS = -I ./include
DEFS = -D DEBUG -g -Wall

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = run


#This is the target that compiles our executable
all : $(OBJS)
	g++ $(DEFS) $(SRCS) $(OBJS) -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -o $(OBJ_NAME) 


