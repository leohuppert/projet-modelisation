#ifndef PROJET_MODELISATION_GPRPARSER_H
#define PROJET_MODELISATION_GPRPARSER_H

#include <string>
#include "modele/Graphe.h"

class GprParser {
public:
    template<typename S, typename T>
    static const std::string *genererInstance(const Graphe<S, T> *input);

    template<typename S, typename T>
    static Graphe<S, T> *genererGraphe(const char *input);
};

#endif //PROJET_MODELISATION_GPRPARSER_H
