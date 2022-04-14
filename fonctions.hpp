#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <string.h>

using namespace std;

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


    void Wt_estim();
    void St_estim();
    void St_estim_opp();

    void forward_MC_class(int nb_sim,string type);
    void forward_MC_minvar(int nb_sim,string type);

    void option(int nb_sim,string type);
};

double LN();
double mean(const vector<double>& v);
double var(const vector<double>& v);

double positiv(double x);

vector<double> linspace(double a, double b, int c);

void write_vector(const vector<double>& v,string file_name);
Matrice_carree cholesky(Matrice_carree M);

#endif // FONCTIONS_HPP
