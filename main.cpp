#include "fonctions.hpp"
#include "matrice.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <cstring>
#include <string.h>

const double PI=4*atan(1.);
int nbsim=100000;
int nbint=20;
int nb_boucle=20;

int main(){
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
    best.forward_MC_class(nbsim,"put");
    cout<<"Affichage estimation forward:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo minvar
    best.forward_MC_minvar(nbsim,"put");
    cout<<"Affichage estimation forward minvar:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo option
    best.option(nbsim,"put");
    cout<<"Affichage estimation option put:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    best.option(nbsim,"call");
    cout<<"Affichage estimation option call:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //calcul option put = f(rho)
    vector<double> rho = linspace(-0.49,0.99,nbint);
    vector<double> prices(nbint);
    vector<double> err(nbint);
    vector<double> varr(nbint);
    vector<double> IC1(nbint);
    vector<double> IC2(nbint);
    for (int i=0;i<nbint;i++){
        best=bestof(3,0.02,rho[i],1.5,1,1,0.3);
        best.forward_MC_minvar(nbsim,"call");
        prices[i]=best.P;
        varr[i]=best.varr;
        IC1[i]=best.IC[0];
        IC2[i]=best.IC[1];
        err[i]=best.err;
    }
    cout<<"Affichage prix put = f(rho)"<<endl<<prices<<endl<<endl;
    w_vector(rho,"rho.txt");
    w_vector(prices,"prices.txt");
    w_vector(varr,"varr.txt");
    w_vector(IC1,"IC1.txt");
    w_vector(IC2,"IC2.txt");
    w_vector(err,"err.txt");

    vector<double> nb_sims(nb_boucle);
    vector<double> prices2(nb_boucle);
    vector<double> varr2(nb_boucle);
    vector<double> err2(nb_boucle);
    vector<double> IC12(nb_boucle);
    vector<double> IC22(nb_boucle);

    int nb_sim=10000;
    for (int i=0;i<nb_boucle;i++)
    {
        best=bestof(3,0.02,0.3,1.5,1,1,0.3);
        best.forward_MC_minvar(nb_sim,"call");
        prices2[i]=best.P;
        varr2[i]=best.varr;
        IC12[i]=best.IC[0];
        IC22[i]=best.IC[1];
        nb_sims[i]=nb_sim;
        nb_sim=int(nb_sim*1.5);
        err2[i]=best.err;
    }
    cout<<"Affichage prix put = f(nb_sims)"<<endl<<prices2<<endl<<endl;
    w_vector(nb_sims,"nb_sims.txt");
    w_vector(err2,"err2.txt");
    w_vector(prices2,"prices2.txt");
    w_vector(varr2,"varr2.txt");
    w_vector(IC12,"IC12.txt");
    w_vector(IC22,"IC22.txt");

    return 0;
    }