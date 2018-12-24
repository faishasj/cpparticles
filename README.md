# CPParticles
A basic 2D physics library-ish written in C++ with included SFML demo programs. Made for practice and funsies with some guidance from 
[this Python tutorial](http://www.petercollingridge.co.uk/tutorials/pygame-physics-simulation/).

## Installation
To use CPParticles in your project, include the `include` and `src` folders in your project directory. The `cpparticles.hpp` header file includes all the header files in the library:
```cpp
#include "include/cpparticles.hpp"
```
Alternatively, you may also choose to include the individual header files. 

## Demo
This repository includes three demo files for your viewing pleasure (and also, in the meantime to serve as examples on how to use this library and 
demonstrate its capabilities because this readme is yet to be made fully extensive).

> Compiling the demo programs requires [SFML](https://www.sfml-dev.org/) to be installed.

### collisions.cpp
This program demonstrates particle physics in the library within the standard environment.

![Collisions demo](https://i.imgur.com/jmPa7Ti.gif)

### gas_cloud.cpp
This program demonstrates how changing the environment attributes in the library can be used to simulate a gas cloud.

![Gas cloud demo](https://i.imgur.com/FpGFm2q.gif)

### soft_body.cpp
This program demonstrates the use of springs to create a soft body.

![Soft body demo](https://i.imgur.com/egPJIZj.gif)
