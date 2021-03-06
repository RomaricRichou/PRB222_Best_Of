#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include "matrice.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;

double repartition(double x );

class bestof
{
public:
    int n;
    double r;
    double rho;
    double T;
    double K;
    vector<double> S0;
    vector<double> sigma;
    vector<double> W;
    vector<double> S;
    double err;
    double P;
    double varr;
    vector<double> IC=vector<double>(2);

    bestof():n(3),r(0.02),rho(0.3),T(1.5),K(1)
    {S0= vector<double>(3,1); sigma =vector<double>(3,0.3);};
    bestof(int N,double rr, double rhoo, double t, double k, double s, double sig):n(N),r(rr),rho(rhoo),T(t),K(k)
    {S0= vector<double>(n,s); sigma =vector<double>(n,sig);};
    bestof(int N,double rr, double rhoo, double t, double k, vector<double> s, vector<double> sig):n(N),r(rr),rho(rhoo),T(t),K(k)
    {S0= s; sigma =sig;};


    void Wt_estim();
    void St_estim();
    void St_estim_opp();

    void forward_MC_class(int nb_sim,string type);
    void forward_MC_minvar(int nb_sim,string type);

    void option(int nb_sim,string type);

    double put(int i);
    double call(int i);
    void option_ctrl(int nb_sim,int indice,string type);
};

double LN();
double mean(const vector<double>& v);
double var(const vector<double>& v);

double positiv(double x);

vector<double> linspace(double a, double b, int c);

void write_vector(const vector<double>& v,string file_name);

Matrice_carree cholesky(const Matrice_carree& A);

#endif // FONCTIONS_HPP


