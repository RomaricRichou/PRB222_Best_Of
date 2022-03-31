#include "fonctions.hpp"
#include "matrice.hpp"
#include <stdlib.h>
#include <iostream>
#include<math.h>
//#include "matplotlibcpp.h"
//namespace plt = matplotlibcpp;

const double PI=4*atan(1.);


int main()
{
    //Initialisation
    int nbsim= 100000;
    int nbint=20;

    srand(time(NULL));



    //test fonction LN
    cout<<"Affichage de tirages gaussiens:"<<endl;
    for ( int i = 0; i < 10; i++){
        double s=LN();
        cout<<s<<endl;
    }
    cout<<endl;


    // test contructeurs
    bestof best;
    cout<<"Affichage de r et sigma_0:"<<endl;
    cout<<best.r<<endl;
    cout<<best.sigma.at(0)<<endl;

    //test Wt-estimateur

    best.Wt_estim();
    cout<<"Affichage W:"<<best.W<<endl;

    // test St_estimateur
    best.St_estim();
    cout<<"Affichage S:"<<best.S<<endl<<endl;

    //test Monte Carlo classique
    best.forward_MC_class(nbsim,false);
    cout<<"Affichage estimation forward:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo minvar
    best.forward_MC_minvar(nbsim,false);
    cout<<"Affichage estimation forward minvar:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo option
    best.option(nbsim,false);
    cout<<"Affichage estimation option put:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    best.option(nbsim,true);
    cout<<"Affichage estimation option call:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //calcul option put = f(rho)
    vector<double> rho = linspace(-0.49,0.99,nbint);
    vector<double> prices(nbint);
    vector<double> varr(nbint);
    vector<double> IC1(nbint);
    vector<double> IC2(nbint);
    for (int i=0;i<nbint;i++){
        best=bestof(3,0.02,rho[i],1.5,1,1,0.3);
        best.option(nbsim,false);
        prices[i]=best.P;
        varr[i]=best.varr;
        IC1[i]=best.IC[0];
        IC2[i]=best.IC[1];
    }
    cout<<"Affichage prix put = f(rho)"<<endl<<prices<<endl<<endl;
    w_vector(rho,"rho.txt");
    w_vector(varr,"var.txt");
    w_vector(IC1,"IC1.txt");
    w_vector(IC2,"IC2.txt");


    return 0;
    }

