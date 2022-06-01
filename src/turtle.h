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

#include "include/enums.h"

#include "./modules_/debugmisc_module.h"

#include "./context_/window.h"
#include "./context_/eventengine.h"
#include "./context_/gpucodes.h"

#include "./attributes_/texture.h"
#include "./attributes_/pngtablefont.h"

#include "./attributes_/collider.h"
#include "./attributes_/state.h"
#include "./engines_/stateengine.h"
#include "./objects_/vectorizedobject.h"
#include "./objects_/instancedobject.h"
#include "./objects_/animatedobject2D.h"

#include "./objects_/colliderobject2D.h"
#include "./objects_/physicsobject2D.h"
#include "./objects_/fontobject2D.h"
#include "./modules_/geometry_module.h"
#include "./modules_/collisionhandlingmodule.h"

#include "./engines_/collisionengine.h"
#include "./context_/scene.h"







