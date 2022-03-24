#include <stdlib.h>
#include <math.h>
#include "fonctions.hpp"
#include <vector>

<<<<<<< HEAD
const double PI=4*atan(1);

double LN()
{
    double u=rand()/(double) RAND_MAX;
    double v=rand()/(double) RAND_MAX;
    return sqrt(-2*log(u))*cos(2*PI*v);
=======

using namespace std;

void bestof::fix_W_mc(){
    if (n!=3){cout<<"Erreur, n !=3"<<endl; exit(-1);}
    vector<double> N(n);
    for (int i =0;i<n;i++){
        N.at(i)=sigma.at(i)*LN();
    }
    vector<vector<double>> A;
>>>>>>> d8d35847701ab02ea73b29786da6646c152cec32
}
