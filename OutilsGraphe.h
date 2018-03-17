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
    template<typename S, typename T>
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
    template<typename S, typename T>
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

private:

    /**
     * Fonction récursive qui réalise le parcours en profondeur et met à jour les sommets visités
     * @param sommet
     * @param visite
     */
    static void dfsUtils(int sommet, std::vector<std::pair<Sommet<InfoSommet> *, bool>> &visite,
                         const Graphe<InfoArc, InfoSommet> *graphe);
};

template<typename S, typename T>
class PairPElement {
private:
    // TODO: T ou PElement<T> ?
    T *t;
public:
    explicit PairPElement(T *t) : t(t) {}

    bool operator()(std::pair<S, T*> pair) {
        return (pair.second == t);
    }

    bool operator()(std::pair<T*, S> pair) {
        return (pair.first == t);
    }
};

#endif //PROJET_MODELISATION_OUTILSGRAPHE_H
