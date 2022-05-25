
// STD C++ LIB
#include <sstream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <string>
#include <map>
#include <limits>
#include <fstream>
#include <thread>
#include <exception>
#include <iostream>
#include <functional>

// SDL OPENGL GLU GLEW
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>

//GLM MATH
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// enum defs
enum Graphics {GPU = 0, CPU=1};
enum Direction { ON_PRESS = 0 , ON_RELEASE = 1, UNDEFINED = -1 };
enum Polygon {GENERIC =0, SQUARE = 1};
enum CollisionStatus { NOT_COLLIDING = 0 , COLLIDING = 1, ON_CHECK=2 , TO_CHECK=3};


static const SDL_Scancode TIME_OUT = static_cast<SDL_Scancode>(-1);

// modules 

#include "./modules/debugmisc_module.h"



//headers 
#include "./headers/window.h"
#include "./headers/gpucodes.h"

#include "./headers/texture.h"
#include "./modules/pngtablefont.h"

#include "./headers/collider.h"
#include "./headers/state.h"
#include "./headers/stateengine.h"
#include "./headers/vectorizedobject.h"
#include "./headers/objects/instancedobject.h"
#include "./headers/objects/animatedobject2D.h"
#include "./headers/objects/colliderobject2D.h"
#include "./headers/objects/physicsobject2D.h"
#include "./headers/objects/fontobject2D.h"
#include "./modules/geometry_module.h"

#include "./headers/collisionengine.h"
#include "./headers/scene.h"







