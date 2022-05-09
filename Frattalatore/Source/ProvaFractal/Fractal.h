#pragma once
class Fractal
{
public:
	Fractal() {};
	int ricorsioniMandelbrot(double cr, double ci, int max_iterations);
private:
	int max_iter{128};

};

