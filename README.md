# Simple Utility for Graphics Oriented Software 

Library based on OpenGL and SDL2.

- 2D animations
- 3D object rendering (primitive stage) 
- particle systems with instanced rendering
- SAT collisions
- Font rendering

### Build

Build based on Makefile:
Define output configuration trough:
``` export sugos_out = "OPENGL [OPENGLES, EMSCRIPTEN]" ```

then ``` make lib ``` builds static library ```sugos.a```

``` make <examplename>_ex ``` builds the respective example in ```etc/examples```

``` make <toolname>_tool ``` builds the respective tool in ```etc/tools```

If you want to modify any build option that has to be done manually on the Makefile.

### etc/examples

Examples contains a list of example of usage of the library and its utility.
Refer to the README.md in the corresponding folder.

### Tools

Set of tools that could speedup the workflow using the library

- Collider Tool 


