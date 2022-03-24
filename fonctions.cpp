#include "fonctions.hpp"
#include <vector>


using namespace std;

void bestof::fix_W_mc(){
    if (n!=3){cout<<"Erreur, n !=3"<<endl; exit(-1);}
    vector<double> N(n);
    for (int i =0;i<n;i++){
        N.at(i)=sigma.at(i)*LN();
    }
    vector<vector<double>> A;
}
