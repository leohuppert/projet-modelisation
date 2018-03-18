#ifndef PROJET_MODELISATION_GPRPARSER_H
#define PROJET_MODELISATION_GPRPARSER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "modele/Graphe.h"
#include "InfoArc.h"
#include "InfoSommet.h"
#include "OutilsGraphe.h"

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

    for (ls = inverse(input->lSommets); ls; ls = ls->s) {
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

    for (la = inverse(input->lArcs); la; la = la->s) {
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
    Graphe<InfoArc, InfoSommet> *graphe = new Graphe<InfoArc, InfoSommet>();

    // Ouverture du fichier
    std::ifstream ifs(input);
    std::string line;
    std::stringstream in;

    if (ifs.is_open()) {
        while (getline(ifs, line)) {

            // Partie sommets
            if (line == "sectionSommets") {
                // Lecture de tous les sommets
                std::cout << "Lecture des sommets" << std::endl;

                std::string nomSommet;
                int borneInf = 0, borneSup = 0;

                while (getline(ifs, line) && (!line.empty())) {
                    in = std::stringstream(line);
                    in >> nomSommet >> borneInf >> borneSup;

                    graphe->creeSommet(InfoSommet(nomSommet, borneInf, borneSup));
                }
            } else if (line == "sources" || line == "source") {
                // Ajout de la/des source(s)
                std::string nomSommet;

                while (getline(ifs, line) && (!line.empty())) {
                    in = std::stringstream(line);
                    in >> nomSommet;

                    graphe->sources.push_back(OutilsGraphe::getSommetParNom(nomSommet, graphe));
                }
            } else if (line == "puits") {
                // Ajout du/des puits
                std::string nomSommet;

                while (getline(ifs, line) && (!line.empty())) {
                    in = std::stringstream(line);
                    in >> nomSommet;

                    graphe->puits.push_back(OutilsGraphe::getSommetParNom(nomSommet, graphe));
                }
            } else if (line == "sectionArcs") {
                // Ajout des arcs

                std::string nomArc, nomSommetDeb, nomSommetFin;
                int cout, temps;

                while (getline(ifs, line) && (!line.empty())) {
                    in = std::stringstream(line);
                    in >> nomArc >> nomSommetDeb >> nomSommetFin >> cout >> temps;

                    graphe->creeArete(InfoArc(nomArc, cout, temps), OutilsGraphe::getSommetParNom(nomSommetDeb, graphe),
                                      OutilsGraphe::getSommetParNom(nomSommetFin, graphe));
                }
            } else if (line == "sectionGraphe" || line == "sectionGraphes") {

                // On lit le nom du graphe
                std::string nom;

                while (getline(ifs, line)) {
                    if (!line.empty()) {
                        in = std::stringstream(line);
                        in >> nom;

                        graphe->nom = nom;
                    }
                }
            }
        }

        ifs.close();
    } else {
        throw Erreur("Impossible d'ouvrir le fichier");
    }

    return graphe;
}

#endif //PROJET_MODELISATION_GPRPARSER_H
