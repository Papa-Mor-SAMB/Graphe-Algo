#ifndef GRAPHEAPARTIRDEMATRICEADJACENTE_H_INCLUDED
#define GRAPHEAPARTIRDEMATRICEADJACENTE_H_INCLUDED
#include "Graphe.h"
#include "Sommet.h"
#include <vector>

using std::vector;
class GrapheAPartirDeFsAps;

class GrapheAPartirDeMatriceAdjacente : public Graphe
{
public:
    GrapheAPartirDeMatriceAdjacente(bool oriente = false, bool value = true);
    GrapheAPartirDeMatriceAdjacente(const GrapheAPartirDeFsAps g);
    void fsAps2matAdj(const GrapheAPartirDeFsAps g);
    virtual void ajouterSommet(const Sommet& s) override;
    virtual void supprimerSommet(int s) override;
    virtual Sommet getSommet(int s) const override;
    virtual int nombreDeSommets() const override;
    virtual void printSommets() const override;
    virtual void setOriente(bool oriente) override;
    virtual bool estOriente() const override;
    virtual void setValue(bool value) override;
    virtual bool estValue() const override;
    void ajoutArete(int s1, int s2, double poids = 1);
    void supprimeArete(int s1, int s2);
    int nombreAretes() const;
    vector<vector<int>> getMatAdj() const;
    //
    void prufer(vector<int>& prf) const;
    void decoprufer(const vector<int>& t) const;
    bool dantzig(vector<vector<int>>& dist) const;
    void kruskal();

    virtual void afficher(const vector<int>& tab) const override;
    virtual void lireGraphe(std::string nomDuFicher) override;
    virtual void ecrireGraphe(std::string nomDuFicher
                              ) override;

private:
    vector<std::vector<int>> d_adj;
    vector<Sommet> d_sommets;
    bool d_oriente;
    bool d_value;
    //Structure kruskal
    struct  arete{
        int s, t;
        double p;
    };
    struct grapheKruskal{
        int n, m;
        vector<arete> aretes;
    };
    void tranformationMatAdjEnGrapheKruskal(grapheKruskal& g);
    void triGrapheKruskal(grapheKruskal& g);
    void fusion(int i, int j, vector<int>& prem, vector<int>& pilch, vector<int>& cfc, vector<int>& nbElem) const;
};


#endif // GRAPHEAPARTIRDEMATRICEADJACENTE_H_INCLUDED
