#include "OutilsGraphe.h"

Sommet<InfoSommet> *OutilsGraphe::getSommetParNom(const std::string &nom, Graphe<InfoArc, InfoSommet> *graphe) {
    PElement<Sommet<InfoSommet>> *l;

    for (l = graphe->lSommets; l; l = l->s) {
        if (l->v->v.getNom() == nom)
            return l->v;
    }

    return nullptr;
}

template<typename T>
PElement<Sommet<T>> OutilsGraphe::getSuccesseurs(const Sommet<T> *sommet) {
    return PElement<Sommet<T>>(nullptr, nullptr);
}
