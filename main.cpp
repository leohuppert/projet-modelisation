#include <iostream>
#include <QtWidgets/QApplication>
#include "modele/Graphe.h"
#include "InfoSommet.h"
#include "InfoArc.h"
#include "Fenetre.h"

int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);
        app.setApplicationName("Projet Modélisation");

        Fenetre f;
        f.show();

        return app.exec();
    } catch (const Erreur &e) {
         std::cerr << e << std::endl;
    }
}
