#ifndef MATRICE_HPP
#define MATRICE_HPP
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

enum Error {err_load_graph,err_out_of_bounds};


class Matrice_carree
{
    int _dim;
    vector<vector <double> > _val;
    public:
        Matrice_carree();
        Matrice_carree(int n, double init_val);
        Matrice_carree(const Matrice_carree& M);

        Matrice_carree& operator=(const Matrice_carree &);
        double& operator()(int i, int j);
        double operator()(int i, int j) const;
        int get_dim() const;


        vector<double> lin(int i)const;
        vector<double>& lin(int i,vector<double> line);
        
};


std::ostream& operator<<(std::ostream& out, const Matrice_carree& M );
std::ostream& operator<<(std::ostream& out, vector<double> vect);



#endif