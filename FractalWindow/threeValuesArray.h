#pragma once
#include <vector>



class threeValuesArray
{
    //threeValuesArray();

    //couple of coordinates + number of iterations + fr_im_screen
    struct threeValues
    {
        double x;
        double y;
        float perc;
    };

public:
    std::vector <threeValues> calcoloMandelbrot(double cr, double ci, int iterazioni_user);
    std::vector <threeValues> calcoloJuliaSet1(double cr, double ci, int iterazioni_user);
    std::vector <threeValues> calcoloJuliaSet2(double cr, double ci, int iterazioni_user);
    std::vector <threeValues> calcoloBurninhShip(double cr, double ci, int iterazioni_user);
   // void stampaThreevalues(threeValues vectorToPrint);

private:
 
};

