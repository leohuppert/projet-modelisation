#include <iostream>
#include "modele/Graphe.h"
#include "InfoSommet.h"
#include "InfoArc.h"
#include "GprParser.h"

int main() {
    // Création graphe vide
    Graphe<InfoArc, InfoSommet> g("Graphe1");

    // Création de 3 sommets
    Sommet<InfoSommet> *s0, *s1, *s2;

    s0 = g.creeSommet(InfoSommet("s0", 0, 2));
    s1 = g.creeSommet(InfoSommet("s1", 0, 9));
    s2 = g.creeSommet(InfoSommet("s2", 0, 15));

    // Création de 2 arcs
    Arc<InfoArc, InfoSommet> *a0, *a1;

    a0 = g.creeArete(InfoArc("a0", 12, 5), s0, s1);
    a1 = g.creeArete(InfoArc("a1", 6, 23), s1, s2);

    std::cout << "Graphe créé : " << std::endl;
    std::cout << g << std::endl;

    // Test Copie
    Graphe<InfoArc, InfoSommet> g2(g);

    std::cout << "Copie de g" << std::endl;
    std::cout << g2 << std::endl;

    std::string res = GprParser::genererInstance(&g);
    std::cout << "Génération .gpr" << std::endl << res << std::endl;

    return 0;
}
