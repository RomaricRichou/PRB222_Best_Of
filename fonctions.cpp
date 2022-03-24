#include <stdlib.h>
#include <math.h>
#include "fonctions.hpp"

const double PI=4*atan(1);

double LN()
{
    double u=rand()/(double) RAND_MAX;
    double v=rand()/(double) RAND_MAX;
    return sqrt(-2*log(u))*cos(2*PI*v);
}
