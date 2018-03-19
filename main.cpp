#include <iostream>
#include <QtWidgets/QApplication>
#include "modele/Graphe.h"
#include "InfoSommet.h"
#include "InfoArc.h"
#include "GprParser.h"
#include "Fenetre.h"

int main(int argc, char *argv[]) {
    try {
        Graphe<InfoArc, InfoSommet> *g;
        const char *cheminGPR = "../g1.gpr";

        g = GprParser::genererGraphe(cheminGPR);

        QApplication app(argc, argv);
        app.setApplicationName("Projet Modélisation");

        Fenetre f(g);
        f.show();

        return app.exec();
    } catch (const Erreur &e) {
         std::cerr << e << std::endl;
    }
}
