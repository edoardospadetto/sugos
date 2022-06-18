#ifdef OPENGL_MACRO
#ifndef GLHEADERS
#define GLHEADERS
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL_opengl.h>
#endif
#endif

#ifdef OPENGLES_MACRO
#ifndef GLESHEADERS
#define GLESHEADERS
//#include <GL/glew.h>
#include <GLES3/gl3.h>
#include <SDL2/SDL_opengles2.h>


#endif
#endif
