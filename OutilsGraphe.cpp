#include "OutilsGraphe.h"

Sommet<InfoSommet> *OutilsGraphe::getSommetParNom(const std::string &nom, Graphe<InfoArc, InfoSommet> *graphe) {
    PElement<Sommet<InfoSommet>> *l;

    for (l = graphe->lSommets; l; l = l->s) {
        if (l->v->v.getNom() == nom)
            return l->v;
    }

    return nullptr;
}

void OutilsGraphe::dfs(const Graphe<InfoArc, InfoSommet> *graphe) {
    std::vector<std::pair<Sommet<InfoSommet> *, bool>> visite;

    auto sommets = PElement<Sommet<InfoSommet>>::copie1(graphe->lSommets);
    tri(sommets, estOrdonne);
    for (; sommets; sommets = sommets->s)
        visite.emplace_back(sommets->v, false);

    sommets = PElement<Sommet<InfoSommet>>::copie1(graphe->lSommets);
    tri(sommets, estOrdonne);
    for (int i = 0; sommets; i++, sommets = sommets->s)
        if (!visite[i].second)
            dfsUtils(i, visite, graphe);
}

void OutilsGraphe::dfsUtils(int sommet, std::vector<std::pair<Sommet<InfoSommet> *, bool>> &visite,
                            const Graphe<InfoArc, InfoSommet> *graphe) {
    PElement<Sommet<InfoSommet>> *sommets = nullptr;
    PElement<Sommet<InfoSommet>> *voisins;

    PElement<Sommet<InfoSommet>>::insertionOrdonnee(visite[sommet].first, sommets, estOrdonne);

    while (sommets) {
        Sommet<InfoSommet> *s = PElement<Sommet<InfoSommet>>::depiler(sommets);
        Sommet<InfoSommet> *v;
        auto it = std::find_if(visite.begin(), visite.end(), PairPElement<bool, Sommet<InfoSommet>>(s));
        long iteration = it - visite.begin();
        voisins = getSuccesseurs(s, graphe);
        tri(voisins, estOrdonne);

        if (!visite[iteration].second)
            visite[iteration].second = true;

        while (voisins) {
            v = PElement<Sommet<InfoSommet>>::depiler(voisins);
            auto it1 = std::find_if(visite.begin(), visite.end(), PairPElement<bool, Sommet<InfoSommet>>(v));
            long i = it1 - visite.begin();
            if (!visite[i].second) {
                if (PElement<Sommet<InfoSommet>>::appartient(v, sommets))
                    PElement<Sommet<InfoSommet>>::retire(v, sommets);
                v->v.infoDijkstra.etat = OUVERT;
                v->v.infoDijkstra.pere = s;
                PElement<Sommet<InfoSommet>>::insertionOrdonnee(v, sommets, estOrdonneParents);
            }
        }
        s->v.infoDijkstra.etat = FERME;
    }
}

void OutilsGraphe::dijkstra(const Graphe<InfoArc, InfoSommet> *graphe, Sommet<InfoSommet> *depart) {
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

        std::cout << "Sommet : " << s->v.getNom() << std::endl;

        for (l = successeurs; l; l = l->s) {
            Sommet<InfoSommet> *v = l->v;

            std::cout << "voisin : " << v->v.getNom() << std::endl;

            double nouveauCout = s->v.infoDijkstra.c + graphe->getAreteParSommets(s, v)->v.getCout();

            std::cout << "cout de l'arete " << graphe->getAreteParSommets(s, v)->v.getNom() << " : "
                      << graphe->getAreteParSommets(s, v)->v.getCout() << std::endl;

            std::cout << "nv coût : " << nouveauCout << std::endl;

            if (v->v.infoDijkstra.etat == LIBRE) {
                std::cout << v->v.getNom() << " est libre" << std::endl;

                v->v.infoDijkstra.pere = s;
                v->v.infoDijkstra.c = nouveauCout;
                PElement<Sommet<InfoSommet>>::insertionOrdonnee(v, ouverts, estPlusPetitOuEgal);
                v->v.infoDijkstra.etat = OUVERT;
            } else {
                if (nouveauCout < v->v.infoDijkstra.c) {
                    std::cout << v->v.getNom() << " pas libre et nouveau cout meilleur : " << nouveauCout << " < "
                              << v->v.infoDijkstra.c << std::endl;

                    if (v->v.infoDijkstra.etat == OUVERT)
                        PElement<Sommet<InfoSommet>>::retire(v, ouverts);

                    v->v.infoDijkstra.pere = s;
                    v->v.infoDijkstra.c = nouveauCout;
                    PElement<Sommet<InfoSommet>>::insertionOrdonnee(v, ouverts, estPlusPetitOuEgal);
                    v->v.infoDijkstra.etat = OUVERT;
                }
            }

            std::cout << std::endl;
        }
    }
}

PElement<Sommet<InfoSommet>> *
OutilsGraphe::plusCourtChemin(const Graphe<InfoArc, InfoSommet> *g, const Sommet<InfoSommet> *depart,
                              const Sommet<InfoSommet> *cible) {
    PElement<Sommet<InfoSommet>> *l;

    dijkstra(g, const_cast<Sommet<InfoSommet> *>(depart));
    chemin(const_cast<Sommet<InfoSommet> *>(cible), l);

    return l;
}
