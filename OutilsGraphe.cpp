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

void OutilsGraphe::dijkstra(const Graphe<InfoArc, InfoSommet> *graphe, Sommet<InfoSommet> *depart) {
    std::cout << "ALGORITHME DIJKSTRA" << std::endl;

    PElement<Sommet<InfoSommet>> *l;
    PElement<Sommet<InfoSommet>> *ouverts;

    // Parcours de tous les sommets du graphe => Etat: LIBRE, Père: null
    for (l = graphe->lSommets; l; l = l->s) {
        l->v->v.infoDijkstra.etat = LIBRE;
        l->v->v.infoDijkstra.pere = nullptr;
    }

    depart->v.infoDijkstra.c = 0;
    depart->v.infoDijkstra.pere = nullptr;

    ouverts = new PElement<Sommet<InfoSommet>>(depart, nullptr);
    depart->v.infoDijkstra.etat = OUVERT;

    while (ouverts) {
        Sommet<InfoSommet> *s = PElement<Sommet<InfoSommet>>::depiler(ouverts);
        s->v.infoDijkstra.etat = FERME;

        // Successeurs TODO: liste pair<Sommet, double> double => coût de l'arc s->v
        PElement<Sommet<InfoSommet>> *successeurs = OutilsGraphe::getSuccesseurs(s, graphe);
        PElement<Sommet<InfoSommet>> *l;

        for (l = successeurs; l; l = l->s) {
            Sommet<InfoSommet> *v = l->v;

            double nouveauCout = l->v->v.infoDijkstra.c + graphe->getAreteParSommets(s, v)->v.getCout();

            if (v->v.infoDijkstra.etat == LIBRE) {
                v->v.infoDijkstra.pere = s;
                v->v.infoDijkstra.c = nouveauCout;
                PElement<Sommet<InfoSommet>>::insertionOrdonnee(v, ouverts, estPlusPetitOuEgal);
                v->v.infoDijkstra.etat = OUVERT;
            } else {
                if (nouveauCout < v->v.infoDijkstra.c) {
                    if (v->v.infoDijkstra.etat == OUVERT)
                        PElement<Sommet<InfoSommet>>::retire(v, ouverts);

                    v->v.infoDijkstra.pere = s;
                    v->v.infoDijkstra.c = nouveauCout;
                    PElement<Sommet<InfoSommet>>::insertionOrdonnee(v, ouverts, estPlusPetitOuEgal);
                    v->v.infoDijkstra.etat = OUVERT;
                }
            }
        }
    }
}
