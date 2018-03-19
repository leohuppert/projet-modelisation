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
    static constexpr int PNG = 0;
    static constexpr int SVG = 1;

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
     * Génère un fichier .dot utilisé par graphviz
     * Met en couleur l'arbre passé
     * @param g
     * @param arbre
     * @return
     */
    static const std::string
    genereDotArbre(const Graphe<InfoArc, InfoSommet> &g, PElement<Arc<InfoArc, InfoSommet>> *arbre);

    /**
     * Crée une image PNG à l'aide de Graphviz
     * @param g
     * @return std::string le chemin de l'image créée
     */
    static const std::string dessineGraphe(const Graphe<InfoArc, InfoSommet> &g, const int format);

    /**
     * Crée une image PNG à l'aide de Graphviz et met en évidence un chemin
     * @param g
     * @return std::string le chemin de l'image créée
     */
    static const std::string
    dessineGrapheChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin, const int format);

    /**
     * Crée une image PNG à l'aide de Graphviz et met en évidence un arbre
     * @param g
     * @param arbre
     * @param format
     * @return
     */
    static const std::string
    dessineGrapheArbre(const Graphe<InfoArc, InfoSommet> &g, PElement<Arc<InfoArc, InfoSommet>> *arbre,
                       const int format);

private:
    static const std::string genereSortie(const std::string &chemin, const int format) {
        std::ostringstream cmd;
        std::string out = chemin;

        if (format == PNG) {
            cmd << "dot -Tpng -O " << chemin;
            out.append(".png");
        } else if (format == SVG) {
            cmd << "dot -Tsvg -O " << chemin;
            out.append(".svg");
        }

        system(cmd.str().c_str());

        return out;
    }
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

const std::string DessinGraphe::dessineGraphe(const Graphe<InfoArc, InfoSommet> &g, const int format = PNG) {
    std::string cheminDot;

    cheminDot = genereDot(g);

    return genereSortie(cheminDot, format);
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
        contenu << "  " << chemin->v->v.getNom() << " [color=red fontcolor=red];" << std::endl;

    contenu << "}";

    // Création du fichier
    std::ofstream file;
    file.open(cheminFichier);
    file << contenu.str();

    return cheminFichier;
}

const std::string
DessinGraphe::genereDotArbre(const Graphe<InfoArc, InfoSommet> &g, PElement<Arc<InfoArc, InfoSommet>> *arbre) {
    std::ostringstream oss, contenu;
    std::string cheminFichier;

    PElement<Sommet<InfoSommet>> *sommetsArbre = nullptr;
    PElement<Arc<InfoArc, InfoSommet>> *arcs = g.lArcs;

    // Chemin du fichier .dot
    oss << "../dot/" << g.nom << "_dfs.dot";
    cheminFichier = oss.str();

    contenu << "digraph " << g.nom << " {" << std::endl;

    for (; arcs; arcs = arcs->s) {
        if (arcs->appartient(arcs->v, arbre)) {
            if (!PElement<Sommet<InfoSommet>>::appartient(arcs->v->debut, sommetsArbre)) {
                contenu << "  " << arcs->v->debut->v.getNom() << " [color=blue fontcolor=blue];" << std::endl;
                sommetsArbre = new PElement<Sommet<InfoSommet>>(arcs->v->debut, sommetsArbre);
            }

            if (!PElement<Sommet<InfoSommet>>::appartient(arcs->v->fin, sommetsArbre)) {
                contenu << "  " << arcs->v->fin->v.getNom() << " [color=blue fontcolor=blue];" << std::endl;
                sommetsArbre = new PElement<Sommet<InfoSommet>>(arcs->v->fin, sommetsArbre);
            }

            contenu << "  " << arcs->v->debut->v.getNom() << " -> " << arcs->v->fin->v.getNom() << " [label="
                    << arcs->v->v.getCout() << " color=blue fontcolor=blue];" << std::endl;
        } else {
            contenu << "  " << arcs->v->debut->v.getNom() << " -> " << arcs->v->fin->v.getNom() << " [label="
                    << arcs->v->v.getCout() << "];" << std::endl;
        }
    }


    contenu << "}";

    // Création du fichier
    std::ofstream file;
    file.open(cheminFichier);
    file << contenu.str();

    return cheminFichier;
}

const std::string
DessinGraphe::dessineGrapheChemin(const Graphe<InfoArc, InfoSommet> &g, PElement<Sommet<InfoSommet>> *chemin,
                                  const int format = PNG) {
    std::string cheminDot;

    cheminDot = genereDotChemin(g, chemin);

    return genereSortie(cheminDot, format);
}

const std::string
DessinGraphe::dessineGrapheArbre(const Graphe<InfoArc, InfoSommet> &g, PElement<Arc<InfoArc, InfoSommet>> *arbre,
                                 const int format = PNG) {
    std::string arbreDot;

    arbreDot = genereDotArbre(g, arbre);

    return genereSortie(arbreDot, format);
}

#endif //PROJET_MODELISATION_DESSINGRAPHE_H
