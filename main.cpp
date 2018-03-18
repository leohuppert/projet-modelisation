#include <iostream>
#include "modele/Graphe.h"
#include "InfoSommet.h"
#include "InfoArc.h"
#include "GprParser.h"
#include "DessinGraphe.h"

int main() {
    Graphe<InfoArc, InfoSommet> *g;
    const char *cheminGPR = "../g4.gpr";

    g = GprParser::genererGraphe(cheminGPR);

    std::cout << *g << std::endl;

    // Dessin
    DessinGraphe::dessineGraphe(*g);

    // PCC entre 1er et dernier sommet
    PElement<Sommet<InfoSommet>> *pcc;
    Sommet<InfoSommet> *depart, *cible;
    depart = OutilsGraphe::getSommetParNom("i_1", g);
    cible = OutilsGraphe::getSommetParNom("i_20", g);

    pcc = OutilsGraphe::plusCourtChemin(g, depart, cible);

    // Dessin PCC
    DessinGraphe::dessineGrapheChemin(*g, pcc);

    return 0;
}

int main1() {
    // Création graphe vide
    Graphe<InfoArc, InfoSommet> g("Graphe1");

    // Création de 3 sommets
    Sommet<InfoSommet> *s0, *s1, *s2, *s3, *s4;

    s0 = g.creeSommet(InfoSommet("s0", 0, 2), true, false);
    s1 = g.creeSommet(InfoSommet("s1", 0, 9));
    s2 = g.creeSommet(InfoSommet("s2", 0, 15));
    s3 = g.creeSommet(InfoSommet("s3", 0, 98));
    s4 = g.creeSommet(InfoSommet("s4", 0, 8), false, true);

    // Création de 2 arcs
    Arc<InfoArc, InfoSommet> *a0, *a1, *a2, *a3, *a4, *a5;

    a0 = g.creeArete(InfoArc("a0", 12, 5), s0, s1);
    a1 = g.creeArete(InfoArc("a1", 6, 2), s1, s2);
    a2 = g.creeArete(InfoArc("a2", 8, 2), s0, s3);
    a3 = g.creeArete(InfoArc("a3", 8, 8), s3, s4);
    a4 = g.creeArete(InfoArc("a4", 1, 3), s2, s3);
    a5 = g.creeArete(InfoArc("a5", 2, 6), s1, s4);

    std::cout << "Graphe créé : " << std::endl;
    std::cout << g << std::endl;

    /*
    // Test Copie
    Graphe<InfoArc, InfoSommet> g2(g);

    std::cout << "Copie de g" << std::endl;
    std::cout << g2 << std::endl;

    std::string res = GprParser::genererInstance(&g);
    std::cout << "Génération .gpr" << std::endl << res << std::endl;

    std::cout << "Lecture fichier gpr" << std::endl;

    Graphe<InfoArc, InfoSommet> *g3;
    g3 = GprParser::genererGraphe("../Graphe1.gpr");
    std::cout << *g3 << std::endl;

    std::cout << "Prédécesseurs : " << std::endl;
    std::cout << OutilsGraphe::getPredecesseurs<InfoArc,InfoSommet>(s1, &g) << std::endl;
    std::cout << "Successeurs : " << std::endl;
    std::cout << OutilsGraphe::getSuccesseurs<InfoArc,InfoSommet>(s1, &g) << std::endl;

    OutilsGraphe::dfs(&g);
     */

    // Meilleur Chemin de s0 à s4
    PElement<Sommet<InfoSommet>> *pcc = OutilsGraphe::plusCourtChemin(&g, s0, s4);

    // Dessin du plus court chemin
    DessinGraphe::dessineGrapheChemin(g, pcc);

    std::cout << "Chemin de s0 à s4" << std::endl;

    for (; pcc; pcc = pcc->s) {
        if (!pcc->s)
            std::cout << pcc->v->v.getNom() << " - Coût : " << pcc->v->v.infoDijkstra.c << std::endl;
        else
            std::cout << pcc->v->v.getNom() << " -> ";
    }

    return 0;
}
