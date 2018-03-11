#ifndef PROJET_MODELISATION_INFOARC_H
#define PROJET_MODELISATION_INFOARC_H

#include <iostream>
#include <string>
#include <utility>

class InfoArc {
private:
    std::string nom;
    int cout, temps;

public:
    InfoArc(std::string nom, int cout, int temps) : nom(std::move(nom)), cout(cout), temps(temps) {}

    std::string getNom() const { return nom; }

    int getCout() const { return cout; }

    int getTemps() const { return temps; }

    friend std::ostream &operator<<(std::ostream &os, const InfoArc &infoArc) {
        os << "InfoArc [ ";
        os << "nom: " << infoArc.nom;
        os << "; coût: " << infoArc.cout << "; temps: " << infoArc.temps;
        os << " ]";

        return os;
    }
};

#endif //PROJET_MODELISATION_INFOARC_H
