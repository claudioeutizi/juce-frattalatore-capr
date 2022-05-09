#include "Fractal.h"


int ricorsioniMandelbrot(double cr, double ci, int max_iterations) {
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
