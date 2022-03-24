#include <stdlib.h>
#include <math.h>
#include <vector>
#include "fonctions.hpp"
#include "matrice.hpp"
#include <algorithm>
const double PI=4*atan(1);

double LN()
{
    double u=rand()/(double) RAND_MAX;
    double v=rand()/(double) RAND_MAX;
    return sqrt(-2*log(u))*cos(2*PI*v);
}

double mean(vector<double> v)
{
    double som=0.;
    for (int i = 0; i < v.size(); i++)
    {
        som+=v[i];
    }
    return som/v.size();
    
}


void bestof::Wt_estim()
{
  W.resize(n);
  vector<double> gaussien(n,0.);
  for (int i = 0; i < n; i++)
  {
      gaussien[i]=LN();
}
    Matrice_carree A(n,0.);
    A(1,1)=1;
    A(2,1)=rho;
    A(3,1)=rho;
    A(2,2)=sqrt(1-rho*rho);
    A(3,2)=rho*sqrt((1-rho)/(1+rho));
    A(2,2)=sqrt(1-2*rho*rho/(1+rho));
    

    // On forme W 

    for (int i = 0; i < n; i++)
    {
        for ( int j = 0; j < n; j++)
        {
            W[i]+=A(i+1,j+1)*gaussien[j];
        }
        
    }

}

void bestof::St_estim()
{
    S.resize(n);
    for (int i = 0; i < n; i++)
    {
        S[i]=S0[i]*exp(r*T-0.5*sigma[i]*sigma[i]*T+W[i]*sigma[i]);
    }
    
}




    
double bestof::forward_MC_class(int nb_sim)
{
    vector<double> MC(nb_sim,0.);
    for (int i = 0; i < nb_sim; i++)
    {
        Wt_estim();
        St_estim();
        double price=*max_element(S.begin(),S.end());
        MC[i]=exp(-r*T)*(price-K);
        
    }
    return mean(MC);

}



