#ifndef FONCTIONS_HPP
#define FONCTIONS_HPP

#include <vector>

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
    double P;

    bestof():n(3),r(0.02),rho(0.3),T(1.5),K(1)
    {S0= vector<double>(3,1); sigma =vector<double>(3,0.3);};
    bestof(int N,double rr, double rhoo, double t, double k, double s, double sig):n(N),r(rr),rho(rhoo),T(t),K(k)
    {S0= vector<double>(n,s); sigma =vector<double>(n,sig);};
    ~bestof();

    void Wt_esstim();
    void forward();
    void put();

};

double LN();


#endif // FONCTIONS_HPP


