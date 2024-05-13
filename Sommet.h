#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include "iostream"
#include <vector>
using namespace std;

class Sommet{
public:
    Sommet();
    Sommet(int numero, const string& nom);
    int getNumeroSommet() const;
    string getNomSommet() const;
    void setNumeroSommet(int numero);
    void setNomSommet(string nom);
private:
    int numeroSommet;
    string nomSommet;

};



#endif // SOMMET_H_INCLUDED
