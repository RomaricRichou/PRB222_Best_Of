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

double repartition(double x )  //Estimation de la fonction de répartion donnée en annexe dans le sujet
{

    double b0,b1,b2,b3,b4,b5;
    b0=0.2316419;
    b1=0.319381530;
    b2=-0.356563782;
    b3=1.781477937;
    b4=-1.821255978;
    b5=1.330274429;

    double t=1./(1+b0*x);


    if (x>0)
    {
        return 1 - (1./sqrt(2*PI))*exp(-0.5*x*x)*(b1*t+b2*pow(t,2)+b3*pow(t,3)+b4*pow(t,4)+b5*pow(t,5));
    }

    else
    {
        t=1./(1-b0*x);
        return (1./sqrt(2*PI))*exp(-0.5*x*x)*(b1*t+b2*pow(t,2)+b3*pow(t,3)+b4*pow(t,4)+b5*pow(t,5));
    }

}


double LN()  // Box-Muller
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
    double som=0.;
    int s =v.size();
    for (int i = 0; i < v.size(); i++)
    {
        som+=(long double)(v[i]);
    }
    return som/s;

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

Matrice_carree cholesky(const Matrice_carree& A)
{
    int n=A.get_dim();
    Matrice_carree L(n,0.);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
        float sum = 0;
        for (int k = 0; k < j; k++)
            sum += L(i+1,k+1)*L(j+1,k+1);
            if (i == j){
            L(i+1,j+1) = sqrt(A(i+1,i+1) - sum);}
            else
                {L(i+1,j+1) = (1.0 / L(j+1,j+1) * (A(i+1,j+1) - sum));}
        }
    }
    return L;
}



void bestof::Wt_estim() // Generateur des (W_t) pour t>=0
{
  W.resize(n);
  vector<double> gaussien(n,0.);
  for (int i = 0; i < n; i++){
    gaussien[i]=sqrt(T)*LN();
  }
  Matrice_carree A(n,0.);
  for (int i=0;i<n;i++){
      for (int j=0; j<n;j++){
          if (i==j){
              A(i+1,i+1)=1;
          }
          else{
              A(i+1,j+1)=rho;
          }
      }
  }
  A=cholesky(A);

  // On forme W

  for (int i = 0; i < n; i++){
      W[i]=0;
      for ( int j = 0; j < n; j++){
        W[i]+=A(i+1,j+1)*gaussien[j];
      }
  }
}


void bestof::St_estim() // Generateur de Prix (S_t) dans le modele BS
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
    err=sqrt(varr)*1.645/sqrt(double(nb_sim));
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
        MC[i]=ind_type*exp(-r*T)*(price-K);
        price=*max_element(S.begin(),S.end());
        MC[i]=ind_type*exp(-r*T)*(price-K);
    }

    P= mean(MC);
    varr= var(MC);
    IC[0]=P-(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    IC[1]=P+(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    err=sqrt(varr)*1.645/sqrt(double(nb_sim));
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
        MC[i]=exp(-r*T)*positiv(ind_type*(price-K))/2;
        St_estim_opp();
        price=*max_element(S.begin(),S.end());
        MC[i]+=exp(-r*T)*positiv(ind_type*(price-K))/2;
    }

    P= mean(MC);
    varr= var(MC);
    IC[0]=P-(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    IC[1]=P+(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    err=sqrt(varr)*1.645/sqrt(double(nb_sim));
}

void bestof::option_ctrl(int nb_sim,int indice,string type)  //type de l'option put / call avec variable
                                                                                       // de controle
{
    if (indice>=n){cout<<"Erreur i>=n option_ctrl";exit(-1);}
    vector<double> MC(nb_sim,0.);

    int ind_type=1;
    if (type.compare("put")==0)
    { ind_type=-1;}


    for (int i = 0; i < nb_sim; i++)
    {
        Wt_estim();
        St_estim();

        double price=*max_element(S.begin(),S.end());
        MC[i]=exp(-r*T)*(positiv(ind_type*(price-K))-positiv(ind_type*(S[indice]-K)))/2;
        St_estim_opp();
        price=*max_element(S.begin(),S.end());
        MC[i]+=exp(-r*T)*(positiv(ind_type*(price-K))-positiv(ind_type*(S[indice]-K)))/2;
    }

    if (type.compare("put")==0){
        P= mean(MC)+put(indice);
    }
    else{
        P= mean(MC)+call(indice);
    }
    varr= var(MC);
    IC[0]=P-(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    IC[1]=P+(sqrt(varr)*1.645/sqrt(double(nb_sim)));
    err=sqrt(varr)*1.645/sqrt(double(nb_sim));
}

vector<double> linspace(double a, double b, int c){
    vector<double> line(c);
    double delta =(b-a)/(double)(c-1);
    for (int i=0; i<c; i++){
            line[i]=a + (i*delta);
    }
    return line;
}


// Pour ecrire les resultats dans un fichier et l'utiliser pour tracer les courbes avec python
void write_vector(const vector<double>& v,string file_name){
    ofstream file;
    remove(file_name.c_str());
    file.open(file_name);
    for (int i=0;i+1<v.size();i++){
        file<<v[i]<<";";
    }
    file<<v[v.size()-1];
    file.close();
}

// Call de l'actif i 
double bestof::call(int i){
    if (i>=n){cout<<"Erreur i>=n";exit(-1);}
    double d1= 1/sigma[i]/sqrt(T)*(log(S0[i]/K)+(r+sigma[i]*sigma[i]/2)*T);
    double d2= d1 - sigma[i]*sqrt(T);
    double price = S0[i]*repartition(d1)-K*repartition(d2)*exp(-r*T);
    return(price);
}


// Call de l'actif i 
double bestof::put(int i){
    if (i>=n){cout<<"Erreur i>=n";exit(-1);}
    double d1= 1/sigma[i]/sqrt(T)*(log(S0[i]/K)+(r+sigma[i]*sigma[i]/2)*T);
    double d2= d1 - sigma[i]*sqrt(T);
    double price = -S0[i]*repartition(-d1)+K*repartition(-d2)*exp(-r*T);
    return(price);
}
