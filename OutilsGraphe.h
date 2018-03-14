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
     * @tparam T
     * @param sommet
     * @return PElement<Sommet<T>>
     */
    template<typename T>
    static PElement<Sommet<T>> getSuccesseurs(const Sommet<T> *sommet);

    /**
     * DFS (Depth-first Search)
     * Réalise un parcours en profondeur d'abord du graphe donné
     * @param graphe
     */
    static void dfs(const Graphe<InfoArc, InfoSommet> *graphe);
};

#endif //PROJET_MODELISATION_OUTILSGRAPHE_H
