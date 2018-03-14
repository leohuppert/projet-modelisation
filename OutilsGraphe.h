#ifndef PROJET_MODELISATION_OUTILSGRAPHE_H
#define PROJET_MODELISATION_OUTILSGRAPHE_H

#include "InfoSommet.h"
#include "modele/Sommet.h"
#include "InfoArc.h"
#include "modele/Graphe.h"

class OutilsGraphe {
public:

    /**
     * Retourne un pointeur sur le sommet ayant le nom donné
     * @param nom
     * @param graphe
     * @return Sommet *
     */
    static Sommet<InfoSommet> *getSommetParNom(const std::string &nom, Graphe<InfoArc, InfoSommet> *graphe);

    /**
     * Retourne une liste des successeurs du sommet donné
     * @tparam S
     * @tparam T
     * @param sommet
     * @param graphe
     * @return PElement<Sommet<T>> *
     */
    template<typename S,typename T>
    static PElement<Sommet<T>> *getSuccesseurs(const Sommet<T> *sommet, const Graphe<S, T> *graphe) {
        const PElement<Arc<S, T> > *l;
        PElement<Sommet<T>> *s;

        for (l = graphe->lArcs, s = NULL; l; l = l->s)
            if (sommet == l->v->debut)
                s = new PElement<Sommet<T>>(l->v->fin, s);

        return s;
    }

    /**
     * Retourne une liste des prédécesseurs du sommet donné
     * @tparam S
     * @tparam T
     * @param sommet
     * @param graphe
     * @return PElement<Sommet<T>> *
     */
    template<typename S,typename T>
    static PElement<Sommet<T>> *getPredecesseurs(const Sommet<T> *sommet, const Graphe<S, T> *graphe) {
        const PElement<Arc<S, T> > *l;
        PElement<Sommet<T>> *s;

        for (l = graphe->lArcs, s = NULL; l; l = l->s)
            if (sommet == l->v->fin)
                s = new PElement<Sommet<T>>(l->v->debut, s);

        return s;
    }

    /**
     * DFS (Depth-first Search)
     * Réalise un parcours en profondeur d'abord du graphe donné
     * @param graphe
     */
    static void dfs(const Graphe<InfoArc, InfoSommet> *graphe);
};

#endif //PROJET_MODELISATION_OUTILSGRAPHE_H
