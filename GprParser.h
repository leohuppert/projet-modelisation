#ifndef PROJET_MODELISATION_GPRPARSER_H
#define PROJET_MODELISATION_GPRPARSER_H

#include <iostream>
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

    oss << "#Instance " << input->nom << " à " << input->nombreSommets() << " sommets et " << input->nombreAretes() << " arcs" << std::endl;
    oss << "Ressource 1" << std::endl;
    oss << std::endl;

    oss << "sectionSommets" << std::endl;

    PElement<Sommet<InfoSommet>> *ls;

    for (ls = input->lSommets; ls; ls = ls->s) {
        oss << ls->v->v.getNom() << " " << ls->v->v.getBorneInferieure() << " " << ls->v->v.getBorneSuperieure()
             << std::endl;
    }

    oss << std::endl;

    // Sources
    oss << "sources" << std::endl;
    for (auto const &value : input->sources)
        oss << value->v.getNom() << std::endl;
    oss << std::endl;

    // Puits
    oss << "puits" << std::endl;
    for (auto const &value : input->puits)
        oss << value->v.getNom() << " " << value->v.getBorneInferieure() << " " << value->v.getBorneSuperieure() << std::endl;
    oss << std::endl;

    oss << "sectionArcs" << std::endl;

    PElement<Arc<InfoArc, InfoSommet>> *la;

    for (la = input->lArcs; la; la = la->s) {
        oss << la->v->v.getNom() << " " << la->v->debut->v.getNom() << " " << la->v->fin->v.getNom() << " "
             << la->v->v.getCout() << " " << la->v->v.getTemps() << std::endl;
    }

    oss << std::endl;

    oss << "sectionGraphe" << std::endl;
    oss << input->nom << " " << input->sources.front()->v.getNom() << " " << input->puits.front()->v.getNom() << std::endl;

    // Création du fichier
    std::ofstream file;

    std::ostringstream nomFichier;
    nomFichier << "../" << input->nom << ".gpr";

    file.open(nomFichier.str());
    file << oss.str();


    return oss.str();
}

#endif //PROJET_MODELISATION_GPRPARSER_H
