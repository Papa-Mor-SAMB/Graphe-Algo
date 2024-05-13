#include "GrapheAPartirDeMatriceAdjacente.h"
#include "Graphe.h"
#include "Sommet.h"
#include <vector>
#include <fstream>
#include "GrapheAPartirDeFsAps.h"

using std::vector;

GrapheAPartirDeMatriceAdjacente::GrapheAPartirDeMatriceAdjacente(bool oriente, bool value)
    : Graphe{}, d_adj{}, d_sommets{}, d_oriente{oriente}, d_value{value}
{

}

GrapheAPartirDeMatriceAdjacente::GrapheAPartirDeMatriceAdjacente(const GrapheAPartirDeFsAps g)
    : Graphe {} , d_adj{}, d_sommets{}, d_oriente{g.estOriente()}, d_value{g.estValue()}
{
    fsAps2matAdj(g);
}

void GrapheAPartirDeMatriceAdjacente :: fsAps2matAdj(const GrapheAPartirDeFsAps g)
{
    int k;
    int n=g.nombreDeSommets();
    d_adj.resize(g.nombreDeSommets());
    for (int i = 0; i < n; i++)
    {
        d_adj[i].resize(n+1, 0);
    }
    for (int i = 1; i <= n; i++)
    {
         k = g.getAPS()[i];
         while ( g.getFS()[k] != 0 )
         {
             d_adj[i-1][g.getFS()[k]] = g.getPoids()[k];
             k++;
         }
    }
}

void GrapheAPartirDeMatriceAdjacente::ajouterSommet(const Sommet& s){
    int n = nombreDeSommets();
    d_adj.push_back(std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i)
        d_adj[i].push_back(0);
    d_sommets.push_back(s);
}
void GrapheAPartirDeMatriceAdjacente::supprimerSommet(int s){
  d_adj.erase(d_adj.begin() + s);
  int n = nombreDeSommets();
  for (int i = 0; i <= n; ++i)
    d_adj[i].erase(d_adj[i].begin() + s);
}

Sommet GrapheAPartirDeMatriceAdjacente::getSommet(int s) const
{
  return d_sommets[s];
}

int GrapheAPartirDeMatriceAdjacente::nombreDeSommets() const
{
  return d_adj.size();
}

void GrapheAPartirDeMatriceAdjacente::setOriente(bool oriente)
{
    d_oriente = oriente;
}

bool GrapheAPartirDeMatriceAdjacente::estOriente() const
{
    return d_oriente;
}

void GrapheAPartirDeMatriceAdjacente::setValue(bool value)
{
    d_value = value;
}

bool GrapheAPartirDeMatriceAdjacente::estValue() const
{
    return d_value;
}

void GrapheAPartirDeMatriceAdjacente::printSommets() const
{
  for (unsigned i = 0; i < d_adj.size(); ++i)
  {
    for (unsigned j = 0; j < d_adj[i].size(); ++j)
    {
        if(d_adj[i][j] == INT_MAX){
            std::cout<<"INF"<<" ";
        }
        else if(d_adj[i][j] == -INT_MAX){
            std::cout<<"-INF"<<" ";
        }
        else{
            std::cout<<d_adj[i][j]<<" ";
        }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void GrapheAPartirDeMatriceAdjacente::ajoutArete(int s1, int s2, double poids)
{
    int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_oriente)
        d_adj[s1-1][s2-1] = poids;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = poids;

}

void GrapheAPartirDeMatriceAdjacente::supprimeArete(int s1, int s2)
{
  int taille = d_adj.size();
    if(s1 > taille || s2 > taille){
        return;
    }
    if(d_oriente)
        d_adj[s1-1][s2-1] = 0;
    else
        d_adj[s1-1][s2-1] = d_adj[s2-1][s1-1] = 0;
}

int GrapheAPartirDeMatriceAdjacente::nombreAretes() const
{
  int n = nombreDeSommets();
  int m = 0;
  for (int i = 1; i < n; ++i)
  {
    for (int j = i+1; j <= n; ++j)
    {
      if (d_adj[i][j] != 0)
        ++m;
    }
  }
  return m;
}

vector<vector<int>>  GrapheAPartirDeMatriceAdjacente::getMatAdj() const
{
    return d_adj;
}
//
void GrapheAPartirDeMatriceAdjacente::prufer(vector<int>& prf) const
{
    vector<vector<int>> mat(d_adj.size(), vector<int>(d_adj.size()+1));

    for(unsigned i = 0; i < d_adj.size(); ++i){
        for(unsigned j = 0; j < d_adj[i].size(); ++j){
            mat[i][j+1] = d_adj[i][j];
        }
    }
    int n = d_adj.size();
    prf.resize(n-1);
    prf[0] = n - 2;
    for(unsigned i = 0; i < mat.size(); i++)
    {
        mat[i][0] = 0;
        for(unsigned j = 1; j < mat[i].size(); j++)
        {
            mat[i][0] += mat[i][j];
        }
    }
    for(int k = 1; k <= n-2; k++)
    {
        int i = 1;
        for(;mat[i][0] != 1; ++i);
        int j = 1;
        for(;mat[i][j] !=1 ; ++j);
        prf[k] = j;
        mat[i][j] = 0;
        mat[j][i] = 0;
        mat[i][0] = 0;
        mat[j][0]--;
    }
}

void GrapheAPartirDeMatriceAdjacente::decoprufer(const vector<int>& t) const
{
    int m = t[0], n = m + 2;
    vector<int> s(n + 1, 0);
    s[0] = n;
    //for (int i = 1; i <= n; i++) s[i] = 0;
    for (int i = 1; i <= m; i++) s[t[i]]++;
    for (int k = 1; k <= m; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            if (s[i] == 0)
            {
                std::cout <<"[ "<<t[k]<<" ,"<<i<<" ]"<<std::endl;
                s[t[k]]--;
                s[i] = -1;
                break;
            }
        }
    }
    std::cout<<"[ ";
    for (int i = 1; i <= n; i++){
        if ( s[i] == 0 )
            std::cout <<i<<" ,";
    }
    std::cout << "]"<<std::endl;
}

bool GrapheAPartirDeMatriceAdjacente::dantzig(vector<vector<int>>& dist) const
{
    int x;
    dist = d_adj;
    int n = dist.size();
    for(int k = 0; k < n; ++k)
    {
        for(int i = 0; i <= k; ++i)
        {
            for(int j = 0; j <= k; ++j)
            {
                if((x = dist[i][j] + dist[j][k+1]) < dist[i][k+1]){
                    dist[i][k+1] = x;
                }
                if((x = dist[k+1][j] + dist[j][i]) < dist[k+1][i]){
                    dist[k+1][i] = x;
                }
            }//j
            //int t = std::min(dist[i][k+1], dist[k+1][i]);
            if((dist[i][k+1]+ dist[k+1][i]) < 0){
                std::cout<<"Presence d'un circuit absorbant passant par "<<i<<" et "<<(k+1)<<std::endl;
                return false;
            }
        }//i
        for(int i = 0; i <= k; ++i)
        {
            for(int j = 0; j <= k; ++j)
            {
                if((x = dist[i][k+1] + dist[k+1][j]) < dist[i][j]){
                    dist[i][j] = x;
                }
            }
        }
    }//k
    return true;
}

void GrapheAPartirDeMatriceAdjacente::tranformationMatAdjEnGrapheKruskal(grapheKruskal& g)
{
    arete a{};
    g.n = nombreDeSommets();
    g.m = nombreAretes();
    for(unsigned i = 0; i < d_adj.size(); ++i)
    {
        for(unsigned j = 0; j < d_adj[i].size(); ++j)
        {
            if(d_adj[i][j] != 0){
                a.s = i+1;
                a.t = j+1;
                a.p = d_adj[i][j];
                g.aretes.push_back(a);
            }
        }
    }
}

void GrapheAPartirDeMatriceAdjacente::triGrapheKruskal(grapheKruskal& g)
{
    for(unsigned i = 0; i < g.aretes.size() - 1; ++i)
    {
        for(unsigned j = i + 1; j < g.aretes.size(); ++j)
        {
           if(g.aretes[j].p < g.aretes[i].p)
           {
                std::swap(g.aretes[j], g.aretes[i]);
           }
           else if(g.aretes[j].p == g.aretes[i].p){
                if(g.aretes[j].s < g.aretes[i].s){
                    std::swap(g.aretes[j], g.aretes[i]);
                }
                else if(g.aretes[j].s == g.aretes[i].s){
                    if(g.aretes[j].t < g.aretes[i].t){
                        std::swap(g.aretes[j], g.aretes[i]);
                    }
                }
           }
        }
    }
}

void GrapheAPartirDeMatriceAdjacente::fusion(int i, int j, vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& nbElem) const
{
    int k = prem[i];
    while(pilch[k] != 0)
        k = pilch[k];
    pilch[k] = prem[j];
    k = prem[j];
    while(k != 0){
        cfc[k] = i;
        k = pilch[k];
    }
}

void GrapheAPartirDeMatriceAdjacente::kruskal()
{
    grapheKruskal g{}, t{};
    tranformationMatAdjEnGrapheKruskal(g);
    triGrapheKruskal(g);
    //INITIALISATION
    t.aretes.resize(g.n-1);
    int n = g.n;
    vector<int> prem(n + 1);
    vector<int> pilch(n + 1, 0);
    vector<int> cfc(n + 1);
    vector<int> nbElem(n + 1, 1);
    prem[0] = pilch[0] = cfc[0] = nbElem[0] = g.n;
    for(int i = 1; i <= n; ++i){
        prem[i] = i;
        cfc[i] = i;
    }
    int x, y;
    int i = 0, j = 0;
    while(j < g.n -1)
    {
        arete ar{};
        ar = g.aretes[i];
        x = cfc[ar.s];
        y = cfc[ar.t];
        if(x != y)
        {
            t.aretes[j++] = g.aretes[i];
            fusion(x, y, prem, pilch, cfc, nbElem);
        }
        ++i;
    }
    t.n = g.n;
    t.m = g.n-1;
    //AFFICHAGE
    for(int i = 0; i < t.m; ++i){
        std::cout<<"Arete No "<<i+1<<" : ("<<t.aretes[i].s<<", ";
        std::cout<<t.aretes[i].t<<") --- "<<t.aretes[i].p<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"prem : ";
    afficher(prem);
    std::cout<<"pilch : ";
    afficher(pilch);
    std::cout<<"cfc : ";
    afficher(cfc);
}

void GrapheAPartirDeMatriceAdjacente::afficher(const vector<int>& tab) const
{
    for(unsigned i = 0; i < tab.size(); ++i)
        std::cout<<tab[i]<<" ";
    std::cout<<std::endl;
}

void GrapheAPartirDeMatriceAdjacente::lireGraphe(std::string nomDuFicher)
{
    std::ifstream grapheMatAdj(nomDuFicher);
    bool oriente;
    int nombreDeSommets;
    grapheMatAdj>>oriente;
    d_oriente=oriente;
    grapheMatAdj>>nombreDeSommets;
    d_adj.clear(); d_adj.resize(nombreDeSommets);
    for(int i = 0; i < nombreDeSommets; ++i)
        d_adj[i].resize(nombreDeSommets);

    for (int i = 0; i < nombreDeSommets; ++i)
    {
        for (int j = 0; j < nombreDeSommets; ++j)
        {
            grapheMatAdj>>d_adj[i][j];
        }
    }
    d_sommets.clear(); d_sommets.resize(nombreDeSommets);
    std::string s;
    for(int i = 0; i < nombreDeSommets; ++i){
        grapheMatAdj>>s;
        d_sommets[i] = Sommet(i, s);
    }
}

void GrapheAPartirDeMatriceAdjacente::ecrireGraphe(std::string nomDuFicher)
{
    std::ofstream grapheMatAdj(nomDuFicher);
    grapheMatAdj<<d_oriente<<std::endl;
    int n = nombreDeSommets();
    grapheMatAdj<<n<<std::endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            grapheMatAdj<<d_adj[i][j]<<" ";
        }
        grapheMatAdj<<std::endl;
    }
    grapheMatAdj<<std::endl;
    for(int i = 0; i < n; ++i){
        grapheMatAdj<<d_sommets[i].getNomSommet()<<" ";
    }
}
