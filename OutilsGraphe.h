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

    /**
     * Algorithme de Dijkstra
     * @param graphe
     * @param depart
     */
    static void dijkstra(const Graphe<InfoArc, InfoSommet> *graphe, Sommet<InfoSommet> *depart);

    /**
     * Utilise Dijkstra et renvoie un plus court chemin
     * @param depart
     * @param cible
     * @return
     */
    static PElement<Sommet<InfoSommet>> *
    plusCourtChemin(const Graphe<InfoArc, InfoSommet> *g, const Sommet<InfoSommet> *depart,
                    const Sommet<InfoSommet> *cible);

private:

    /**
     * Fonction récursive qui réalise le parcours en profondeur et met à jour les sommets visités
     * @param sommet
     * @param visite
     */
    static void dfsUtils(int sommet, std::vector<std::pair<Sommet<InfoSommet> *, bool>> &visite,
                         const Graphe<InfoArc, InfoSommet> *graphe);

    static bool estPlusPetitOuEgal(const Sommet<InfoSommet> *s1, const Sommet<InfoSommet> *s2) {
        return s1->v.infoDijkstra.c <= s2->v.infoDijkstra.c;
    }

    /**
     * Construit un chemin
     * @param cible
     * @param debut
     * @return
     */
    static PElement<Sommet<InfoSommet>> *chemin(Sommet<InfoSommet> *cible, PElement<Sommet<InfoSommet>> *&debut) {
        if (!cible) {
            debut = nullptr;

            return nullptr;
        } else if (!cible->v.infoDijkstra.pere) {
            debut = new PElement<Sommet<InfoSommet>>(cible, nullptr);

            return debut;
        } else {
            PElement<Sommet<InfoSommet>> *d = chemin((Sommet<InfoSommet> *&)
                                                             cible->v.infoDijkstra.pere, debut);
            d->s = new PElement<Sommet<InfoSommet>>(cible, nullptr);

            return d->s;
        }
    }
};

template<typename S, typename T>
class PairPElement {
private:
    // TODO: T ou PElement<T> ?
    T *t;
public:
    explicit PairPElement(T *t) : t(t) {}

    bool operator()(std::pair<S, T *> pair) {
        return (pair.second == t);
    }

    bool operator()(std::pair<T *, S> pair) {
        return (pair.first == t);
    }
};

#endif //PROJET_MODELISATION_OUTILSGRAPHE_H
