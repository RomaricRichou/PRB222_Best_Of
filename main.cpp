#include "fonctions.hpp"
#include <stdlib.h>
#include <iostream>
#include<math.h>


const double PI=4*atan(1);



double LN()
{
    double u=rand()/(double) RAND_MAX;
    double v=rand()/(double) RAND_MAX;
    return sqrt(-2*log(u))*cos(2*PI*v);
}




int main()
{
    //test fonction LN
    for ( int i = 0; i < 10; i++)
    {
        double s=LN();
        std::cout<<s<<endl;
    }


    // test contructeurs
    bestof best;
    std::cout<<best.r<<endl;
    std::cout<<best.sigma.at(0)<<endl;

    return 0;
    }
    
