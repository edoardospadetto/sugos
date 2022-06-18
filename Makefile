FLAGS = -ggdb3  -Wall
DEFS0 = -D DEBUG #-D SHOWFPS




PRELOAD = --preload-file ./src/shaders_/vectorizedobject.shader --preload-file  ./etc/fonts/font.png
SRC_DIR = src/
OBJ_DIR = build/
SRCS = $(wildcard $(SRC_DIR)*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)%.cpp,$(OBJ_DIR)%.o,$(SRCS))


ifeq ($(SUGOSOUT),SUGOS_EMSCRIPTEN)
	CC = em++ -v
	XT = cpp
	X = html
	TARGET = libsugos_web
	LIBS = -Bstatic -w -lGLESv2 -lSDL2  -lSDL2_image -I ./src/include/ #-lpthread
	EMSFLAGS = -sUSE_SDL=2  -s USE_SDL_IMAGE=2 -sFULL_ES3 -sASYNCIFY
	DEFS = $(DEFS0) -D OPENGLES_MACRO  -D EMSCRIPTEN_MACRO
	ifeq ($(PRELOAD),"")
	%: force
		@echo "**** Warning: Preload each asset you are using for JavaScript *** "
	endif
else ifeq ($(SUGOSOUT),SUGOS_OPENGLES)
	CC = g++ 
	XT = cpp
	X = app
	TARGET = libsugos_es
	LIBS = -Bstatic -w -lGLESv2 -lSDL2  -lSDL2_image -I ./src/include/ #-lpthreadexport 
	DEFS = $(DEFS0) -D OPENGLES_MACRO  
else ifeq ($(SUGOSOUT),SUGOS_OPENGL)
	CC = g++ 
	XT = cpp
	X = app
	TARGET = libsugos
	DEFS = $(DEFS0) -D OPENGL_MACRO
	LIBS = -Bstatic -w -lGL -lGLU -lGLEW -lSDL2 -lpthread -lSDL2_image
else
%: force
	@echo "Error, configuration not specified $(SUGOSOUT)"
	exit 1
endif

force:
	

lib: dirs $(OBJS)
	ar rcs  $(TARGET).a $(OBJS)

%_ex:
	$(CC) -c $(DEFS) $(FLAGS) $(EMSFLAGS) ./etc/examples/$@.cpp $(LIBS) -I ./src/ -o ./build/$@.o 
	$(CC)  $(DEFS)  $(FLAGS) $(EMSFLAGS) ./build/$@.o  $(TARGET).a $(LIBS) -o $@.$(X) 

%_tool:
	$(CC) -c $(DEFS) $(FLAGS) $(EMSFLAGS) ./etc/tools/$@/$@.cpp $(LIBS) -I ./src/ -o ./build/$@.o 
	$(CC)  $(DEFS)  $(FLAGS) $(EMSFLAGS) ./build/$@.o  $(TARGET).a $(LIBS) -o $@.$(X) 	

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	echo $@
	$(CC) $(DEFS) $(FLAGS) $(CPPFLAGS) -c $< -o ./$@


dirs:	
	@mkdir -p build
	@mkdir -p build/objects_
	@mkdir -p build/modules_
	@mkdir -p build/context_
	@mkdir -p build/attributes_
	@mkdir -p build/engines_
	

clean:
	@rm -rf *.app
	@rm -rf *.html
	@rm -rf *.js
	@rm -rf *.wasm
	@rm -rf *.data
	@rm -rf build
	@rm -rf 
	
