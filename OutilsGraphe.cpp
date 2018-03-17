#include "OutilsGraphe.h"

Sommet<InfoSommet> *OutilsGraphe::getSommetParNom(const std::string &nom, Graphe<InfoArc, InfoSommet> *graphe) {
    PElement<Sommet<InfoSommet>> *l;

    for (l = graphe->lSommets; l; l = l->s) {
        if (l->v->v.getNom() == nom)
            return l->v;
    }

    return nullptr;
}

// TODO: getSuccesseurs / graphe->adjacences ? orienté / non-orienté ? Voir dans dfs et dfsUtils
void OutilsGraphe::dfs(const Graphe<InfoArc, InfoSommet> *graphe) {
    // TODO: structure à revoir
    std::vector<std::pair<Sommet<InfoSommet> *, bool>> visite;

    auto sommets = graphe->lSommets;
    for (; sommets; sommets = sommets->s)
        visite.emplace_back(sommets->v, false);

    sommets = graphe->lSommets;
    for (int i = 0; sommets; i++, sommets = sommets->s)
        if (!visite[i].second)
            dfsUtils(i, visite, graphe);
}

void OutilsGraphe::dfsUtils(int sommet, std::vector<std::pair<Sommet<InfoSommet> *, bool>> &visite,
                            const Graphe<InfoArc, InfoSommet> *graphe) {
    PElement<Sommet<InfoSommet>> *sommets = nullptr;
    PElement<Sommet<InfoSommet>> *voisins;

    sommets = new PElement<Sommet<InfoSommet>>(visite[sommet].first, sommets);

    for (; sommets; sommets = sommets->s) {
        auto it = std::find_if(visite.begin(), visite.end(), PairPElement<bool, Sommet<InfoSommet>>(sommets->v));
        long iteration = it - visite.begin();
        voisins = getSuccesseurs(visite[iteration].first, graphe);

        if (!visite[sommet].second) {
            std::cout << visite[sommet].first->clef << " ";
            visite[sommet].second = true;
        }

        for (auto v = voisins; v; v = v->s) {
            auto it1 = std::find_if(visite.begin(), visite.end(), PairPElement<bool, Sommet<InfoSommet>>(v->v));
            long i = it1 - visite.begin();
            if (!visite[i].second) {
                sommets = new PElement<Sommet<InfoSommet>>(visite[i].first, sommets);
            }
        }
    }
}
