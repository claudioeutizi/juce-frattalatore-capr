#include <JuceHeader.h>
#pragma once
class Fractal
{

public:
    Fractal();
    ~Fractal();
    int ricorsioniMandelbrot(double cr, double ci, int max_iterations);
    void drawFractal(juce::Image& i);
    int getW() { return W; };
    int getH() { return H; };

private:
    const int max_iter{ 128 };
    //num. di iterazioni della funz. ricorisva
    const double min_re{ -2 };//valore minimo asse reale
    const double max_re{ 2 };//valore max asse reale
    const double min_im{ -2 };//valore min. asse immaginario
    const double max_im{ 2 };//valore max asse immaginario
    const int W{ 600 };
    const int H{ 600 };
};
