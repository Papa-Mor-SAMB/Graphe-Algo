#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

//Classe abstraite graphe
class Sommet;

class Graphe{
public:
    Graphe() = default;
    virtual void ajouterSommet(const Sommet& s) = 0;
    virtual void supprimerSommet(int s) = 0;
    virtual Sommet getSommet(int s) const = 0;
    virtual int  nombreDeSommets() const = 0;
    virtual void printSommets() const = 0;
    virtual void setOriente(bool oriente) = 0;
    virtual bool estOriente() const = 0;
    virtual void setValue(bool value) = 0;
    virtual bool estValue() const = 0;
    virtual void afficher(const vector<int>& tab) const = 0;
    virtual void lireGraphe(string nomDuFicher) = 0;
    virtual void ecrireGraphe(string nomDuFicher) = 0;
};


#endif // GRAPHE_H_INCLUDED
