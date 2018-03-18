#ifndef PROJET_MODELISATION_DESSINGRAPHE_H
#define PROJET_MODELISATION_DESSINGRAPHE_H

#include <string>
#include <fstream>
#include <a.out.h>
#include "modele/Graphe.h"
#include "modele/Arc.h"
#include "InfoArc.h"
#include "InfoSommet.h"

class DessinGraphe {
public:
    /**
     * Génère un fichier .dot utilisé par graphviz
     * @param Graphe g
     * @return std::string le chemin du fichier .dot créé
     */
    static const std::string genereDot(const Graphe<InfoArc, InfoSommet> &g);

    /**
     * Génère un fichier .dot utilisé par graphviz
     * Met en couleur le chemin passé
     * @param Graphe g
     * @return std::string le chemin du fichier .dot créé
     */
    static const std::string
    genereDotChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin);

    /**
     * Crée une image PNG à l'aide de Graphviz
     * @param g
     * @return std::string le chemin de l'image créée
     */
    static const std::string dessineGraphe(const Graphe<InfoArc, InfoSommet> &g);

    /**
     * Crée une image PNG à l'aide de Graphviz et met en évidence un chemin
     * @param g
     * @return std::string le chemin de l'image créée
     */
    static const std::string
    dessineGrapheChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin);
};

const std::string DessinGraphe::genereDot(const Graphe<InfoArc, InfoSommet> &g) {
    std::ostringstream oss, contenu;
    std::string cheminFichier;

    PElement<Arc<InfoArc, InfoSommet>> *arcs = g.lArcs;

    // Chemin du fichier .dot
    oss << "../dot/" << g.nom << ".dot";
    cheminFichier = oss.str();

    contenu << "digraph " << g.nom << " {" << std::endl;

    for (; arcs; arcs = arcs->s) {
        contenu << "  " << arcs->v->debut->v.getNom() << " -> " << arcs->v->fin->v.getNom() << " [label="
                << arcs->v->v.getCout()
                << "]" << std::endl;
    }

    contenu << "}";

    // Création du fichier
    std::ofstream file;
    file.open(cheminFichier);
    file << contenu.str();

    return cheminFichier;
}

const std::string DessinGraphe::dessineGraphe(const Graphe<InfoArc, InfoSommet> &g) {
    std::string cheminDot;
    std::ostringstream cmd;

    cheminDot = genereDot(g);
    cmd << "dot -Tpng -O " << cheminDot;

    system(cmd.str().c_str());

    return cheminDot.append(".png");
}

const std::string
DessinGraphe::genereDotChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin) {
    std::ostringstream oss, contenu;
    std::string cheminFichier;

    PElement<Arc<InfoArc, InfoSommet>> *arcs = g.lArcs;

    // Chemin du fichier .dot
    oss << "../dot/" << g.nom << "_pcc.dot";
    cheminFichier = oss.str();

    contenu << "digraph " << g.nom << " {" << std::endl;

    for (; arcs; arcs = arcs->s) {
        PElement<Sommet<InfoSommet>> *app;
        app = PElement<Sommet<InfoSommet>>::appartient(arcs->v->debut, chemin);

        if (app && app->s && (arcs->v->debut == app->v && arcs->v->fin == app->s->v)) {
            contenu << "  " << arcs->v->debut->v.getNom() << " -> " << arcs->v->fin->v.getNom() << " [label="
                    << arcs->v->v.getCout() << " color=red fontcolor=red];" << std::endl;
        } else {
            contenu << "  " << arcs->v->debut->v.getNom() << " -> " << arcs->v->fin->v.getNom() << " [label="
                    << arcs->v->v.getCout() << "];" << std::endl;
        }
    }

    for (; chemin; chemin = chemin->s)
        contenu << "  " << chemin->v->v.getNom() << " [color=red];" << std::endl;

    contenu << "}";

    // Création du fichier
    std::ofstream file;
    file.open(cheminFichier);
    file << contenu.str();

    return cheminFichier;
}

const std::string
DessinGraphe::dessineGrapheChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin) {
    std::string cheminDot;
    std::ostringstream cmd;

    cheminDot = genereDotChemin(g, chemin);
    cmd << "dot -Tpng -O " << cheminDot;

    system(cmd.str().c_str());

    return cheminDot.append(".png");
}

#endif //PROJET_MODELISATION_DESSINGRAPHE_H
