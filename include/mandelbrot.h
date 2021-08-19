#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "domain.h"
#include <complex>
#include <tuple>
class Mandelbrot
{
private:
    int _ScreenWidth, _ScreenHeight;
    Domain<double> _Range;
    // max number of iterations
    int iter_max = 500;
    // coverts the x and y coordinates of a pixel in SDL coordinate system to complex points as required
    std::complex<double> scale(int x, int y);
    // gives the number of iterations required to escape for a complex point
    int get_number_iterations(std::complex<double> point);
    // returns a tuple of rgb values for a complex point using the number of iterations
    std::tuple<int, int, int> get_rgb_from_iteration(int n);

public:
   // default constructor 
    Mandelbrot(int screenW, int screenH, Domain<double> range) : _ScreenWidth(screenW), _ScreenHeight(screenH), _Range(range)
    {
    }
    // public method to get rgb values from x and y coordinates of a pixel 
    std::tuple<int, int, int> get_rgb(int x, int y);
};

#endif