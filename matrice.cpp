#include "matrice.hpp"


 double& Matrice_carree::operator()(int i, int j)
 {  
     if (i<1||i>_dim)
     {
         cerr<<"Index i out of bounds"<<endl;
         return _val[0][0];
     }

     if (j<1||j>_dim)
     {
         cerr<<"Index j out of bounds"<<endl;
         return _val[0][0];
     }
     return _val[i-1][j-1];
 }


double  Matrice_carree::operator()(int i, int j) const
{
    if (i<1||i>_dim)
     {
         cerr<<"Index i out of bounds"<<endl;
         exit(err_out_of_bounds);
     }

     if (j<1||j>_dim)
     {
         cerr<<"Index j out of bounds"<<endl;
         exit(err_out_of_bounds);
     }

    return _val[i-1][j-1];
}



//get dim

int Matrice_carree::get_dim() const
{
    return _dim;
}



Matrice_carree::Matrice_carree(): _dim(0), _val(vector< vector<double> >())
{
}


Matrice_carree::Matrice_carree(int n, double init_val): _dim(n), _val(vector< vector<double> >(n))
{
    
    vector<double> ligne(n,init_val);
    for(int i=0;i<n;++i)
    {
        _val[i]=ligne;
    }
}


Matrice_carree::Matrice_carree(const Matrice_carree& M) : _dim(M.get_dim()), _val(vector< vector<double> >(M.get_dim()))
{

    vector<double> ligne(_dim);
    for(int i=0;i<_dim;++i)
    {
        for(int j=0;j<_dim;++j)
        {
            ligne[j]=M(i+1,j+1);
        }
        _val[i]=ligne;
    }
}

//ATTENTION PAS DE VERIFICATION DE LA DIM DE LA MATRICE COPIEE
Matrice_carree& Matrice_carree::operator=(const Matrice_carree& M)
{
    _dim=M.get_dim();
    _val=vector<vector <double> > (_dim,vector<double>(_dim));
    for(int i=1;i<=_dim;++i)
    {
        for(int j=1;j<=_dim;++j)
        {
            _val[i-1][j-1]=M(i,j);
        }
    }

    return *this;
}


//Affichage


std::ostream& operator<<(std::ostream& out, const Matrice_carree& M )
{
    int n= M.get_dim();
    for(int i=1;i<=n;++i)
    {   
       cout<<M.lin(i)<<endl;
    }

    return out;
}






/////////////////AUTRES
//Afficher un vecteur

std::ostream& operator<<(std::ostream& out, vector<double> vect)
{
    int n=vect.size();
    for(int i=0;i<n;++i)
    {
        out<<vect[i]<<" ";
    }

    return out;
}

vector<double> Matrice_carree::lin(int i) const
{

    return _val[i-1];

}


vector<double>& Matrice_carree::lin(int i,vector<double> line)
{   
    int dim_max=min(_dim,int(line.size()) );
    for(int k=0; k<dim_max;++k)
    {
        _val[i-1][k]=line[k];
    }
    return _val[i-1];
}

