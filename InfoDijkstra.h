#ifndef PROJET_MODELISATION_INFODIJKSTRA_H
#define PROJET_MODELISATION_INFODIJKSTRA_H

#include "modele/AElement.h"

constexpr int LIBRE = 0;
constexpr int OUVERT = 1;
constexpr int FERME = 2;

class InfoDijkstra {
public:
    const static char *ETATS[];

    // pointeur sur un Sommet<?>. où ? est une classe composée ou dérivée de InfoStar
    AElement *pere;

    int etat;        // LIBRE, OUVERT ou FERMé
    double c;        // coût déjà calculé. cf. A* ou Dijkstra

    InfoDijkstra(AElement *pere = nullptr, const int etat = LIBRE, const double &c = 0) : pere(pere), etat(etat),
                                                                                          c(c) {}

    explicit operator std::string() const {
        std::ostringstream oss;

        oss << "clef pere = ";
        if (pere)
            oss << pere->clef;
        else
            oss << "non définie";

        oss << ", état = " << ETATS[etat] << ", coût = " << c;

        return oss.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const InfoDijkstra &infoDijkstra) {
        return os << (std::string) infoDijkstra;
    }
};

#endif //PROJET_MODELISATION_INFODIJKSTRA_H
