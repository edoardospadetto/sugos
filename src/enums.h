// enum defs
#ifndef ENUMS
#define ENUMS
#include <SDL2/SDL.h>
#include "./include/safe_include_SDLGL_OpenGL.h"


enum Graphics {GPU = 0, CPU=1};
enum ButtonAction { PRESSED = 2 , RELEASED = 1, STEADY_DOWN = 3 , STEADY_UP = 0 , INVALID=-1};
enum Direction { ON_PRESS = 0 , ON_RELEASE = 1, UNDEFINED = -1 };
enum Polygon {GENERIC =0, SQUARE = 1};
enum CollisionStatus { NOT_COLLIDING = 0 , COLLIDING = 1, ON_CHECK=2 , TO_CHECK=3};
enum MouseButton {LEFT =1 , WHEEL = 2, RIGHT = 4};
static const SDL_Scancode TIME_OUT = static_cast<SDL_Scancode>(-1);
static const GLenum GSLS_FUNCTION_VEC4IO = static_cast<GLenum>(11100);
#endif
