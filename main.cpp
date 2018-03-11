#include <iostream>
#include "modele/Graphe.h"

int main() {
    // Création graphe vide
    Graphe<std::string, std::string> g;

    // Création de 3 sommets
    Sommet<std::string> *s0, *s1, *s2;

    s0 = g.creeSommet("Sommet 0");
    s1 = g.creeSommet("Sommet 1");
    s2 = g.creeSommet("Sommet 2");

    // Création de 2 Arêtes
    Arete<std::string, std::string> *a0, *a1;

    a0 = g.creeArete("Arete 0", s0, s1);
    a1 = g.creeArete("Arete 1", s1, s2);

    std::cout << "Graphe créé : " << std::endl;
    std::cout << g << std::endl;
    return 0;
}
