# Simple Utility for Graphics Oriented Software 

Library based on OpenGL and SDL2.

- 2D animations
- particle systems with instanced rendering
- SAT collisions
- Font rendering

### Build

Build based on Makefile:
``` export SUGOSOUT = "SUGOS_OPENGL [SUGOS_OPENGL, SUGOS_WEB]" ```

then ``` make lib ``` builds static library ```sugos.a```

``` make <examplename>_ex ``` builds the respective example in ```etc/examples```

``` make <toolname>_tool ``` builds the respective tool in ```etc/tools```

If you want to modify any build option that has to be done manually on the Makefile.

### Examples

Examples contains a list of example of usage of the library

### Tools

Set of tools that could speedup the workflow using the library

- Collider Tool (almost finished)


