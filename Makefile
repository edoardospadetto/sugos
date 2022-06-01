#Supreme Utility for Graphics Overpowered Software
#Simple Utility for Graphics Oriented Software

CC = g++
XT = cpp
X = app


DEFS = -D DEBUG -ggdb3  -Wall

TARGET = sugos
 


LIBS = -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -lSDL2_image
SRC_DIR = src/
OBJ_DIR = build/
SRCS = $(wildcard $(SRC_DIR)*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))



foo: dirs $(OBJS)


%_ex:
	$(CC) -c $(DEFS) ./examples/$@.cpp $(LIBS) -I ./src/ -o ./build/$@.o 
	$(CC)  $(DEFS)  ./build/$@.o  $(TARGET).a $(LIBS) -o $@.$(X) 
	
lib: dirs $(OBJS)
	ar rcs  $(TARGET).a $(OBJS)




	

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	echo $@
	$(CC) $(CFLAGS) $(DEFS) $(CPPFLAGS) -c $< -o ./$@


dirs:	
	@mkdir -p build
	@mkdir -p build/objects_
	@mkdir -p build/modules_
	@mkdir -p build/context_
	@mkdir -p build/attributes_
	@mkdir -p build/engines_
	

clean:
	rm -rf *.app
	rm -rf build
	rm -rf 
	

