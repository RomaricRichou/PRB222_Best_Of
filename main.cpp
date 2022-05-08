#include "matrice.hpp"
#include "fonctions.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <cstring>
#include <string.h>

const double PI=4*atan(1.);
int nbsim=10000; //debut
int nbsim_opt=500000; // Pour le forward et pour le put sur best of aussi

int nbint=5;
int nb_boucle=100; //nombre de pas
int n = 5;

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
    best.forward_MC_class(nbsim,"call");
    cout<<"Affichage estimation forward:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur:"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;


    //test Monte Carlo minvar
    best.forward_MC_minvar(nbsim,"call");
    cout<<"Affichage estimation forward minvar:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur:"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo option
    best.option(nbsim,"put");
    cout<<"Affichage estimation option put:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur :"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    best.option(nbsim,"call");
    cout<<"Affichage estimation option call:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur:"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //test Monte Carlo option variable de controle
    best.option_ctrl(nbsim,0,"put");
    cout<<"Affichage estimation option put avec variable de controle:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur :"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    best.option_ctrl(nbsim,0,"call");
    cout<<"Affichage estimation option call avec variable de controle:"<<endl<<best.P<<endl<<best.varr<<endl;
    cout<<"Erreur:"<<best.err<<endl;
    cout<<"IC=["<<best.IC[0]<<","<<best.IC[1]<<"]"<<endl<<endl;

    //Calcul Forward = f(nbsim)
    vector<double> nb_sims(nb_boucle);
    vector<double> prices1(nb_boucle);
    vector<double> varr1(nb_boucle);
    vector<double> err1(nb_boucle);
    vector<double> IC11(nb_boucle);
    vector<double> IC21(nb_boucle);
    int nb_sim=10000;
    for (int i=0;i<nb_boucle;i++){
        best=bestof(3,0.02,0.3,1.5,1,1,0.3);
        best.forward_MC_minvar(nb_sim,"call");
        prices1[i]=best.P;
        varr1[i]=best.varr;
        IC11[i]=best.IC[0];
        IC21[i]=best.IC[1];
        nb_sims[i]=nb_sim;
        nb_sim=nb_sim+10000;
        err1[i]=best.err;
    }
    cout<<"Affichage prix forward = f(nb_sims)"<<endl<<prices1<<endl<<endl;
    write_vector(nb_sims,"nb_sims.txt");
    write_vector(err1,"err1.txt");
    write_vector(prices1,"prices1.txt");
    write_vector(varr1,"varr1.txt");
    write_vector(IC11,"IC11.txt");
    write_vector(IC21,"IC21.txt");


    //calcul forward = f(rho)
    vector<double> rho = linspace(-0.49,0.99,nbint);
    vector<double> prices2(nbint);
    vector<double> err2(nbint);
    vector<double> varr2(nbint);
    vector<double> IC12(nbint);
    vector<double> IC22(nbint);
    for (int i=0;i<nbint;i++){
        best=bestof(3,0.02,rho[i],1.5,1,1,0.3);
        best.forward_MC_minvar(nbsim,"call");
        prices2[i]=best.P;
        varr2[i]=best.varr;
        IC12[i]=best.IC[0];
        IC22[i]=best.IC[1];
        err2[i]=best.err;
    }
    cout<<"Affichage prix forward = f(rho)"<<endl<<prices2<<endl<<endl;
    write_vector(rho,"rho.txt");
    write_vector(prices2,"prices2.txt");
    write_vector(varr2,"varr2.txt");
    write_vector(IC12,"IC12.txt");
    write_vector(IC22,"IC22.txt");
    write_vector(err2,"err2.txt");

    //Calcul Put = f(nbsim)
    vector<double> prices3(nb_boucle);
    vector<double> varr3(nb_boucle);
    vector<double> err3(nb_boucle);
    vector<double> IC13(nb_boucle);
    vector<double> IC23(nb_boucle);
    nb_sim=10000;
    for (int i=0;i<nb_boucle;i++){
        best=bestof(3,0.02,0.3,1.5,1,1,0.3);
        best.option(nb_sim,"put");
        prices3[i]=best.P;
        varr3[i]=best.varr;
        IC13[i]=best.IC[0];
        IC23[i]=best.IC[1];
        nb_sims[i]=nb_sim;
        nb_sim=nb_sim+10000;
        err3[i]=best.err;
    }
    cout<<"Affichage prix put = f(nb_sims)"<<endl<<prices3<<endl<<endl;
    write_vector(err3,"err3.txt");
    write_vector(prices3,"prices3.txt");
    write_vector(varr3,"varr3.txt");
    write_vector(IC13,"IC13.txt");
    write_vector(IC23,"IC23.txt");


    //calcul put = f(rho)
    vector<double> control(nbint);
    vector<double> prices4(nbint);
    vector<double> err4(nbint);
    vector<double> varr4(nbint);
    vector<double> IC14(nbint);
    vector<double> IC24(nbint);
    bestof ctrl=bestof(1,0.02,0,1.5,1,1,0.3);
    ctrl.option(nbsim_opt,"put");
    double put=ctrl.P;
    for (int i=0;i<nbint;i++){
        best=bestof(3,0.02,rho[i],1.5,1,1,0.3);
        best.option(nbsim_opt,"put");
        prices4[i]=best.P;
        varr4[i]=best.varr;
        IC14[i]=best.IC[0];
        IC24[i]=best.IC[1];
        err4[i]=best.err;
        control[i]=put;
    }
    cout<<"Affichage prix put = f(rho)"<<endl<<prices4<<endl<<endl;
    write_vector(prices4,"prices4.txt");
    write_vector(varr4,"varr4.txt");
    write_vector(IC14,"IC14.txt");
    write_vector(IC24,"IC24.txt");
    write_vector(err4,"err4.txt");
    write_vector(control,"ctrl.txt");

    //calcul put = f(rho) avec variable de controle
    vector<double> prices5(nbint);
    vector<double> err5(nbint);
    vector<double> varr5(nbint);
    vector<double> IC15(nbint);
    vector<double> IC25(nbint);
    for (int i=0;i<nbint;i++){
        best=bestof(3,0.02,rho[i],1.5,1,1,0.3);
        best.option_ctrl(nbsim_opt,0,"put");
        prices5[i]=best.P;
        varr5[i]=best.varr;
        IC15[i]=best.IC[0];
        IC25[i]=best.IC[1];
        err5[i]=best.err;
    }
    cout<<"Affichage prix put = f(rho) avec variable de controle"<<endl<<prices4<<endl<<endl;
    write_vector(prices5,"prices5.txt");
    write_vector(varr5,"varr5.txt");
    write_vector(IC15,"IC15.txt");
    write_vector(IC25,"IC25.txt");
    write_vector(err5,"err5.txt"); 

//calcul bestof put et put = f(S1_0)
    vector<double> S10=linspace(0,2,nbint);
    vector<double> prices6(nbint);
    vector<double> prices7(nbint);
    vector<double> err6(nbint);
    vector<double> varr6(nbint);
    vector<double> IC16(nbint);
    vector<double> IC26(nbint);

    best=bestof(n,0.02,0.3,1.5,1,1,0.3);

    for (int i=0;i<nbint;i++){
        best.S0[0]=S10[i];
        best.option(nbsim,"put");
        prices6[i]=best.P;
        varr6[i]=best.varr;
        IC16[i]=best.IC[0];
        IC26[i]=best.IC[1];
        err6[i]=best.err;
        prices7[i]=best.put(0);
    }
    write_vector(prices6,"prices6.txt");
    write_vector(varr6,"varr6.txt");
    write_vector(IC16,"IC16.txt");
    write_vector(IC26,"IC26.txt");
    write_vector(err6,"err6.txt");
    write_vector(prices7,"prices7.txt");
    write_vector(S10,"S10.txt");

  //calcul bestof put et put = f(nombre d'actifs, rho)
    vector<double> prices_rho1(4);
    vector<double> prices_rho2(4);
    vector<double> prices_rho3(4);
    
    vector<double> N={1,3,10,25};
    double rho1[]={0,0.5,1};
    
    for (int j = 0; j<4; j++)
    {
        best=bestof(N[j],0.02,rho1[0],1.5,1,1,0.3);
        best.option(nbsim_opt,"put");
        prices_rho1[j]=best.P;
    }

     for (int j = 0; j<4; j++)
    {
        
        best=bestof(N[j],0.02,rho1[1],1.5,1,1,0.3);
        best.option(nbsim_opt,"put");
        prices_rho2[j]=best.P;
    }

     for (int j = 0; j<4; j++)
    {
        
        best=bestof(N[j],0.02,rho1[2],1.5,1,1,0.3);
        best.option(nbsim_opt,"put");
        prices_rho3[j]=best.P;
    }

    write_vector(prices_rho1,"prices_rho1.txt");
    write_vector(prices_rho2,"prices_rho2.txt");
    write_vector(prices_rho3,"prices_rho3.txt");
    write_vector(N,"N.txt");


    

    return 0;
    }

