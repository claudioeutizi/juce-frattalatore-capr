#pragma once
#include "threeValuesArray.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shader.hpp>
//TODO: checking the types
using namespace sf;
class Fractal
{
public:
	//Fractal();

	//methods for the rgb
	int ricorsioniMandelbrot(double cr, double ci, int max_iterations);
	int ricorsioniJuliaSet1(double cr, double ci, int max_iterations);
	int ricorsioniJuliaSet2(double cr, double ci, int max_iterations);
	int ricorsioniBurning_ship(double cr, double ci, int max_iterations);
	sf::Color paint_fractal(int n, int max_iter);
	//get methods
	int getMaxIter() { return max_iter; };
	double getMinRe() { return min_re; };
	double getMaxRe() { return max_re; };
	double getMinIm() { return min_im; };
	double getMaxIm() { return max_im; };
	int getW() { return W; };
	int getH() { return H; };
	int getXfp() { return x_fp; };
	void setXfp(double x_mouse);
	void setYfp(double y_mouse);
	int getYfp() { return y_fp; };
	double getXpoint() { return xPoint; };
	void setXpoint(double x);
	double getYpoint() { return yPoint; };
	void setYpoint(double y);

private:
	const int max_iter { 128 };     //number of iterations
	const double min_re { -2.0 };     //minimum value real axis
	const double max_re { 2.0 };      //maximum value real axis
	const double min_im { -2.0 };    //minimum value immaginary axis
	const double max_im { 2.0 };  
	const int W{ 600 };
	const int H{ 600 };
	int x_fp {0};
	int y_fp {0};
	double xPoint;
	double yPoint;

	const std::vector<sf::Color> colors {
   {0,0,0},
   {213,67,31},
   {251,255,121},
   {62,223,89},
   {43,30,218},
   {0,255,247}
	};

	threeValuesArray arrayToFill;

};

