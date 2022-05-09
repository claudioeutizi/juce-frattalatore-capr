#include "Fractal.h"

Fractal::Fractal()
{

}
Fractal::~Fractal()
{

}

int Fractal::ricorsioniMandelbrot(double cr, double ci, int max_iterations) {
    double parteRealeZ = 0, parteImmaginariaZ = 0;
    int numeroRicorsioni = 0;

    while (numeroRicorsioni < max_iter && parteRealeZ * parteRealeZ + parteImmaginariaZ * parteImmaginariaZ < 4.0)
    {
        double temp = parteRealeZ * parteRealeZ - parteImmaginariaZ * parteImmaginariaZ + cr;
        parteImmaginariaZ = 2.0 * parteRealeZ * parteImmaginariaZ + ci;
        parteRealeZ = temp;
        numeroRicorsioni++;
    }
    return numeroRicorsioni;
}

void Fractal::drawFractal(juce::Image& i) {

    for (int y = 0; y < H; y++)
    {
        for (int x = 0; x < W; x++)
        {
            //calcolo gli intervalli del set 
            double cr = min_re + (max_re - min_re) * x / W;
            double ci = min_im + (max_im - min_im) * y / H;
            int n = ricorsioniMandelbrot(cr, ci, max_iter);
            int r = ((int)(n * sinf(n)) % 256);
            int g = ((n * 3) % 256);
            int b = (n % 256);
            i.setPixelAt(x, y, juce::Colour(r, g, b));
        }
    }
}