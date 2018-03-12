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
    static const std::string genererInstance(Graphe<InfoArc, InfoSommet> *input);

    static Graphe<InfoArc, InfoSommet> *genererGraphe(const char *input);
};

const std::string GprParser::genererInstance(Graphe<InfoArc, InfoSommet> *input) {
    std::ostringstream oss;

    oss << "#Instance " << input->nom << " à " << input->nombreSommets() << " sommets et " << input->nombreAretes()
        << " arcs" << std::endl;
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
        oss << value->v.getNom() << " " << value->v.getBorneInferieure() << " " << value->v.getBorneSuperieure()
            << std::endl;
    oss << std::endl;

    oss << "sectionArcs" << std::endl;

    PElement<Arc<InfoArc, InfoSommet>> *la;

    for (la = input->lArcs; la; la = la->s) {
        oss << la->v->v.getNom() << " " << la->v->debut->v.getNom() << " " << la->v->fin->v.getNom() << " "
            << la->v->v.getCout() << " " << la->v->v.getTemps() << std::endl;
    }

    oss << std::endl;

    oss << "sectionGraphe" << std::endl;
    oss << input->nom << " " << input->sources.front()->v.getNom() << " " << input->puits.front()->v.getNom()
        << std::endl;

    // Création du fichier
    std::ofstream file;

    std::ostringstream nomFichier;
    nomFichier << "../" << input->nom << ".gpr";

    file.open(nomFichier.str());
    file << oss.str();


    return oss.str();
}

Graphe<InfoArc, InfoSommet> *GprParser::genererGraphe(const char *input) {
    // Ouverture du fichier
    std::ifstream ifs(input);
    std::string line;

    if (ifs.is_open()) {
        while (getline(ifs, line)) {
            // Partie sommets
            if (line == "sectionSommets") {
                // Lecture de tous les sommets
                std::cout << "Lecture des sommets" << std::endl;

                char *nomSommet = nullptr;
                int borneInf, borneSup;

                while (getline(ifs, line) && (!line.empty())) {
                    // fonctionne pas
                    sscanf(line.c_str(), "%s %d %d", nomSommet, &borneInf, &borneSup);
                    std::cout << "nomSommet = " << static_cast <const void *> (nomSommet) << " binf = " << borneInf << " bsup = " << borneSup << std::endl;
                }
            }
        }

        ifs.close();
    } else {
        throw Erreur("Impossible d'ouvrir le fichier");
    }

    return nullptr;
}

#endif //PROJET_MODELISATION_GPRPARSER_H
