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
    std::ostringstream oss;

    oss << "#Instance " << input->nom << " à " << input->nombreSommets() << " sommets et " << input->nombreAretes() << " arcs\n";
    oss << "Ressource 1\n";
    oss << "\n";

    oss << "sectionSommets\n";

    PElement<Sommet<InfoSommet>> *ls;

    for (ls = input->lSommets; ls; ls = ls->s) {
        oss << ls->v->v.getNom() << " " << ls->v->v.getBorneInferieure() << " " << ls->v->v.getBorneSuperieure()
             << "\n";
    }

    oss << "\n";
    oss << "sectionArcs\n";

    PElement<Arc<InfoArc, InfoSommet>> *la;

    for (la = input->lArcs; la; la = la->s) {
        oss << la->v->v.getNom() << " " << la->v->debut->v.getNom() << " " << la->v->fin->v.getNom() << " "
             << la->v->v.getCout() << " " << la->v->v.getTemps() << "\n";
    }

    oss << "\n";

    oss << "sectionGraphe\n";
    oss << input->nom;

    std::ofstream file;

    std::ostringstream nomFichier;
    nomFichier << "../" << input->nom << ".gpr";

    file.open(nomFichier.str());
    file << oss.str();


    return oss.str();
}

#endif //PROJET_MODELISATION_GPRPARSER_H
