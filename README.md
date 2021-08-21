# CPPND: Mandelbrot Set

This is my Capstone project for the Udacity C++ nanodegree.In this project, the mandelbrot set is ploted and displayed using C++ and SDL2.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`.
![Result](/images/result.png)
## File and Class Structure
The src folder of the project contains 2 cpp files - main and mandelbrot. In main.cpp, the entire logic to display the mandelbrot set using sdl2 is handled.

It is done by assigning every pixel in the window colour according to the logic written in mandelbrot.cpp, which handles all the calculations to plot the mandelbrot set and has a function get_rgb which returns respective RGB values for each pixel.

The include folder has 2 header files mandelbrot and domain. In domain.h , a class called domain in defined which will be used to describe the range of x and y for the mandelbrot set.

The project also contains cmake files and a text file called values.txt containing the window dimensions and range of mandelbrot set.

On running the executable file Mandelbrot , a window should pop up displaying the mandelbrot set.

## Rubric Points
1. Compiling and Testing : The project code compiles and runs without any errors using cmake and make
2. The project demonstrates an understanding of C++ functions and control structures : In main.cpp different processes like initialization , plotting and closing(deleting) are clearly organised in functions. The init function in main.cpp uses control structures including nested if else.
3. The project uses Object Oriented Programming techniques : In mandelbrot.cpp, a class called Mandelbrot is defined  with class attributes to hold the data and class methods to perform tasks.
4. Class constructors utilize member initialization lists : mandelbrot.h line 12 and 13 uses member initialization lists to initialise all class members.
5. Templates generalize functions in the project: in domain.h, Domain class uses template. 
6. Classes use appropriate access specifiers for class members: All class data members in mandelbrot.h  are explicitly specified as public, protected, or private.
7. Classes encapsulate behavior: In domain.h , Domain class hides it's member data from its user to change directly and rather the state is accesed using member functions.
8. The project reads data from a file and process the data, or the program writes data to a file.: In main.cpp , function readValues reads data from an external txt file.
