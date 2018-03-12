#ifndef PROJET_MODELISATION_GPRPARSER_H
#define PROJET_MODELISATION_GPRPARSER_H

#include <fstream>
#include <string>
#include "modele/Graphe.h"
#include "InfoArc.h"
#include "InfoSommet.h"

class GprParser {
public:
    template<typename S, typename T>
    static const std::string genererInstance(Graphe<S, T> *input);

    template<typename S, typename T>
    static Graphe<S, T> *genererGraphe(const char *input);
};

template<>
const std::string GprParser::genererInstance(Graphe<InfoArc, InfoSommet> *input) {
    std::ofstream file;

    file.open("../graphe.gpr");

    file << "#Instance Graphe à " << input->nombreSommets() << " sommets et " << input->nombreAretes() << " arcs\n";
    file << "Ressource 1\n";
    file << "\n";

    file << "sectionSommets\n";

    PElement<Sommet<InfoSommet>> *ls;

    for (ls = input->lSommets; ls; ls = ls->s) {
        file << ls->v->v.getNom() << " " << ls->v->v.getBorneInferieure() << " " << ls->v->v.getBorneSuperieure() << "\n";
    }

    return "ok";
}

#endif //PROJET_MODELISATION_GPRPARSER_H
