#include "mandelbrot.h"

std::complex<double> Mandelbrot::scale(int x_init, int y_init)
{
	double y = (double)y_init / (double)_ScreenHeight;
	y = _Range.y_max() - y * _Range.height();
	double x = (double)x_init / (double)_ScreenWidth;
	x = _Range.x_min() + x * _Range.width();
	std::complex<double> final(x, y);
	return final;
}

int Mandelbrot::get_number_iterations(std::complex<double> point)
{
	std::complex<double> z(0);
	int iter = 0;

	while (abs(z) < 2.0 && iter < iter_max)
	{
		z = z * z + point;
		iter++;
	}

	return iter;
}

std::tuple<int, int, int> Mandelbrot::get_rgb_from_iteration(int n)
{
	int N = 256; // colors per element
	int N3 = N * N * N;
	// map n on the 0 to 1 interval (real numbers)
	double t = (double)n / (double)iter_max;
	// expand n on the 0 .. 256^3 interval (integers)
	n = (int)(t * (double)N3);

	int b = n / (N * N);
	int nn = n - b * N * N;
	int r = nn / N;
	int g = nn - r * N;
	return std::tuple<int, int, int>(r, g, b);
}

std::tuple<int, int, int> Mandelbrot::get_rgb(int x, int y)
{
	int iterations = Mandelbrot::get_number_iterations(Mandelbrot::scale(x, y));
	std::tuple<int, int, int> rgb = Mandelbrot::get_rgb_from_iteration(iterations);
	return rgb;
}
