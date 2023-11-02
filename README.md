# Hells-Dungeon


Developement repository of the game framework "Photonica".

Dependencies:

**-SDL2:** window management, user input, audio, file management, threading

**-GLAD:** OpenGL accelerated graphics and shaders

These dependencies are included in the repository, the only additional software needed for development is the GCC compiler and GDB debugger, which can be installed using MSYS2 following: https://code.visualstudio.com/docs/languages/cpp

GCC and GDB **MUST** be included in the PATH system variable or else compilation will not work.

## Development Roadmap:

This section goes over the main systems for development, add resources and ideas if you want.

### implementation of core systems
The development needed to get a core game development framework going

- core rendering system
  - shader loading and rendering- finished
  - basic texture rendering- finished
  
  - primitive rendering
    -rectangles done
  
  - state manager
  
  - texture loading and rendering

- core user input system
  
- world object

- entity component system- Finished

- camera system

- player character system

- UI system

- physics system
  -particles system done
  -aggregate bodies in working
  rigid bodies to come
   

### Further systems
These systems are additions that are specific for Photonica

- world chunk system

- weapons system

- world generation

- additional video fx

