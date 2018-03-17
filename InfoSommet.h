#ifndef PROJET_MODELISATION_INFOSOMMET_H
#define PROJET_MODELISATION_INFOSOMMET_H

#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include "InfoDijkstra.h"

class InfoSommet {
private:
    std::string nom;
    int borneInferieure, borneSuperieure;

public:
    /**
     * Infos relatives à l'algorithme de Dijkstra
     */
    InfoDijkstra infoDijkstra;

    InfoSommet(std::string nom, int bInf, int bSup, InfoDijkstra infoDijkstra1 = InfoDijkstra()) :
            nom(std::move(nom)), borneInferieure(bInf), borneSuperieure(bSup), infoDijkstra(infoDijkstra1) {}

    std::string getNom() const { return nom; }

    int getBorneInferieure() const { return borneInferieure; }

    int getBorneSuperieure() const { return borneSuperieure; }

    friend std::ostream &operator<<(std::ostream &os, const InfoSommet &infoSommet) {
        os << "InfoSommet [ ";
        os << "nom: " << infoSommet.nom << "; borne inférieure: " << infoSommet.borneInferieure;
        os << "; borne supérieure: " << infoSommet.borneSuperieure;
        os << " InfoDijkstra [ " << infoSommet.infoDijkstra << " ]";
        os << " ]";

        return os;
    }
};

#endif //PROJET_MODELISATION_INFOSOMMET_H
