#include "Sommet.h"

Sommet::Sommet()
{}

Sommet::Sommet(int numero, const std::string& nom)
    : numeroSommet{numero}, nomSommet{nom}
{

}

int Sommet::getNumeroSommet() const
{
    return numeroSommet;
}

std::string Sommet::getNomSommet() const
{
    return nomSommet;
}

void Sommet::setNumeroSommet(int numero)
{
    numeroSommet = numero;
}

void Sommet::setNomSommet(std::string nom)
{
    nomSommet = nom;
}
