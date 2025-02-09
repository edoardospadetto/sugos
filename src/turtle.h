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
#include "include/safe_include_SDLGL_OpenGL.h"
//GLM MATH
//#include <glm/glm.hpp>
//#include <glm/ext.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>

#include "./enums.h"

#include "./modules_/debugmisc_module.h"

#include "./context_/window.h"
#include "./context_/eventengine.h"
#include "./context_/camera_2D.h"
#include "./context_/gpucodes.h"
#include "./attributes.h"
#include "./engines_/stateengine.h"
#include "./objects.h"
#include "./modules_/geometry_module.h"
#include "./modules_/noise_module.h"
#include "./modules_/collisionhandlingmodule.h"
#include "./modules_/parse_module.h"

#include "./engines_/collisionengine.h"
#include "./context_/scene.h"
