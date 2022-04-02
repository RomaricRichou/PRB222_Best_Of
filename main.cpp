#include "fonctions.hpp"
#include "matrice.hpp"
#include <stdlib.h>
#include <iostream>
#include<math.h>
#include <time.h>


const double PI=4*atan(1.);


int main()
{
    srand(time(NULL));
    //test fonction LN
    for ( int i = 0; i < 10; i++)
    {
        double s=LN();
        cout<<s<<endl;
    }


    // test contructeurs
    bestof best;
    cout<<best.r<<endl;
    cout<<best.sigma.at(0)<<endl;

    //test Wt-estimateur

    best.Wt_estim();
    cout<<best.W<<endl;

    // test St_estimateur
    best.St_estim();
    cout<<best.S<<endl;

    //test Monte Carlo classique
    cout<<best.forward_MC_class(100)<<endl;




    return 0;
    }
    
