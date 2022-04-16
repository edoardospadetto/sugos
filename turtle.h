//Using SDL, SDL OpenGL, GLEW, standard IO, and strings
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>
#include <sstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
#include <fstream>
#include <thread>
#include <exception>

#define STB_IMAGE_IMPLEMENTATION
#include "external/stb_image.h"

#include <iostream>
#include <functional>

#include "src/misc.cpp"
#include "src/shader.h"
#include "src/window.h"
#include "src/texture.h"
#include "src/vectorizedobject.h"
#include "src/objstate.h"
#include "src/animatedobject2d.h"
#include "src/objstate.cpp"
#include "src/scene.h"
#include "src/geometrymisc.cpp"



