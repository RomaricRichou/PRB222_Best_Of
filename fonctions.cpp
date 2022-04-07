#include <stdlib.h>
#include <math.h>
#include <vector>
#include "fonctions.hpp"
#include "matrice.hpp"
#include <algorithm>
#include <time.h>
#include <cstring>
#include <string.h>

const double PI=4*atan(1);

double LN()
{

    double u=rand()/(double) RAND_MAX;
    while (u==0){
        u=rand()/(double) RAND_MAX;
    }
    double v=rand()/(double) RAND_MAX;
    return sqrt(-2*log(u))*cos(2*PI*v);
}

double mean(const vector<double>& v)
{
    long double som=0.;
    int s =v.size();
    for (int i = 0; i < v.size(); i++)
    {
        som+=(long double)(v[i])/s;
    }
    return som;

}

double var(const vector<double>& v){
    int n=v.size();
    vector<double> v2(n);
    for (int i = 0; i < n; i++)
    {
        v2[i]=v[i]*v[i];
    }

    double varr=(mean(v2)-mean(v)*mean(v))*(double(n)/(n-1)); // estimateur non biaisé de la variance
    return varr;
}


void bestof::Wt_estim()
{
  if (n!=3){cout<<"Erreur, bestof cod� uniquement pour n=3 pour le moment!"<<endl;exit(-1);}
  W.resize(n);
  vector<double> gaussien(n,0.);
  for (int i = 0; i < n; i++){
    gaussien[i]=sqrt(T)*LN();
  }
  Matrice_carree A(n,0.);
  A(1,1)=1;
  A(2,1)=rho;
  A(3,1)=rho;
  A(2,2)=sqrt(1-rho*rho);
  A(3,2)=rho*sqrt((1-rho)/(1+rho));
  A(2,2)=sqrt(1-2*rho*rho/(1+rho));


    // On forme W

    for (int i = 0; i < n; i++){
        W[i]=0;
        for ( int j = 0; j < n; j++){
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

void bestof::St_estim_opp()
{
    S.resize(n);
    for (int i = 0; i < n; i++)
    {
        S[i]=S0[i]*exp(r*T-0.5*sigma[i]*sigma[i]*T-W[i]*sigma[i]);
    }

}



void bestof::forward_MC_minvar(int nb_sim,string type) //type de l'option put / call
{
    vector<double> MC(nb_sim,0.);

    int ind_type=1;
    if (type.compare("put")==0) { ind_type=-1;}

    for (int i = 0; i < nb_sim; i++)
    {
        Wt_estim();
        St_estim();

        double price=*max_element(S.begin(),S.end());
        MC[i]=ind_type*exp(-r*T)*(price-K)/2;
        St_estim_opp();
        price=*max_element(S.begin(),S.end());
        MC[i]+=ind_type*exp(-r*T)*(price-K)/2;
    }

    P= mean(MC);
    varr= var(MC);

    IC[0]=P-(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    IC[1]=P+(sqrt(varr)*1.645/sqrt(double(nb_sim)));
  

}

void bestof::forward_MC_class(int nb_sim,string type)  //type de l'option put / call
{
    vector<double> MC(nb_sim,0.);

    int ind_type=1;
    if (type.compare("put")==0)
    { ind_type=-1;}

    for (int i = 0; i < nb_sim; i++)
    {
        Wt_estim();
        St_estim();

        double price=*max_element(S.begin(),S.end());
        MC[i]=exp(-r*T)*(price-K);
        price=*max_element(S.begin(),S.end());
        MC[i]=ind_type*exp(-r*T)*(K-price);
    }

    P= mean(MC);
    varr= var(MC);
    if (P>0) {
        IC[0]=P*(1-(sqrt(varr)*1.645/sqrt(double(nb_sim))));
        IC[1]=P*(1+(sqrt(varr)*1.645/sqrt(double(nb_sim))));
    }
    else{
        IC[0]=P*(1+(sqrt(varr)*1.645/sqrt(double(nb_sim))));
        IC[1]=P*(1-(sqrt(varr)*1.645/sqrt(double(nb_sim))));
    }
}


double positiv(double x){
  double res =0;
  if (x>0){
    res=x;
  }
  return(res);
};

void bestof::option(int nb_sim,string type)  //type de l'option put / call
{
    vector<double> MC(nb_sim,0.);

    int ind_type=1;
    if (type.compare("put")==0)
    { ind_type=-1;}


    for (int i = 0; i < nb_sim; i++)
    {
        Wt_estim();
        St_estim();

        double price=*max_element(S.begin(),S.end());
        MC[i]=exp(-r*T)*positiv(price-K)/2;
        St_estim_opp();
        price=*max_element(S.begin(),S.end());
        MC[i]+=ind_type*exp(-r*T)*positiv(price-K)/2;
    }

    P= mean(MC);
    varr= var(MC);
    if (P>0) {
        IC[0]=P*(1-(sqrt(varr)*1.645/sqrt(double(nb_sim))));
        IC[1]=P*(1+(sqrt(varr)*1.645/sqrt(double(nb_sim))));
    }
    else{
        IC[0]=P*(1+(sqrt(varr)*1.645/sqrt(double(nb_sim))));
        IC[1]=P*(1-(sqrt(varr)*1.645/sqrt(double(nb_sim))));
    }
}

vector<double> linspace(double a, double b, int c){
    vector<double> line(c);
    double delta =(b-a)/(double)(c-1);
    for (int i=0; i<c; i++){
            line[i]=a + (i*delta);
    }
    return line;
}

void w_vector(const vector<double>& v,string file_name){
    ofstream file;
    remove(file_name.c_str());
    file.open(file_name);
    for (int i=0;i<v.size();i++){
        file<<v[i]<<" ;";
    }
    file.close();
}
