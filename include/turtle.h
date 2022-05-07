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
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <limits>

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

#include <iostream>
#include <functional>


static const SDL_Scancode TIME_OUT = static_cast<SDL_Scancode>(-1);

#include "../src/misc.cpp"
#include "../src/shader.h"
#include "../src/window.h"
#include "../src/texture.h"
#include "../src/collider.h"
#include "../src/vectorizedobject.h"
#include "../src/objstate.h"

#include "../src/objects/animatedobject2D.h"
#include "../src/objects/colliderobject2D.h"
#include "../src/objects/physicsobject2D.h"

#include "../src/objstate.cpp"
#include "../src/collisionengine.h"
#include "../src/scene.h"
#include "../src/geometrymisc.cpp"
#include "../src/collider.cpp"





