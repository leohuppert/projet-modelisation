#include <iostream>
#include "Fenetre.h"
#include "DessinGraphe.h"
#include "OutilsGraphe.h"

Fenetre::Fenetre(Graphe<InfoArc, InfoSommet> *g) : QWidget() {
    setBaseSize(800, 600);

    graphe = g;

    lblDepart = new QLabel("Sommet départ");
    lblCible = new QLabel("Sommet cible");
    listeDepart = new QComboBox();
    listeCible = new QComboBox();
    bouton = new QPushButton("Lancer");

    PElement<Sommet<InfoSommet>> *listeSommets = inverse(graphe->lSommets);

    for (; listeSommets; listeSommets = listeSommets->s) {
        listeDepart->addItem(listeSommets->v->v.getNom().c_str());
        listeCible->addItem(listeSommets->v->v.getNom().c_str());
    }

    texte = new QLabel("Recherche de plus court chemin");
    texte->setFont(QFont("Liberation", 12));

    qhBoxLayout = new QHBoxLayout();
    qhBoxLayout->addWidget(lblDepart);
    qhBoxLayout->addWidget(listeDepart);
    qhBoxLayout->addWidget(lblCible);
    qhBoxLayout->addWidget(listeCible);
    qhBoxLayout->addWidget(bouton);

    image = new QLabel();
    std::string cheminImage = DessinGraphe::dessineGraphe(*graphe, DessinGraphe::PNG);
    image->setPixmap(QPixmap(cheminImage.c_str()));
    image->setAlignment(Qt::AlignCenter);

    gridLayout = new QGridLayout();
    gridLayout->addWidget(texte, 0, 1);
    gridLayout->addWidget(image, 1, 1);
    gridLayout->addLayout(qhBoxLayout, 2, 1);

    setLayout(gridLayout);

    QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(handleButton()));
}

void Fenetre::handleButton() {
    std::string s1, s2, imageG;

    s1 = listeDepart->currentText().toStdString();
    s2 = listeCible->currentText().toStdString();

    // On lance Dijkstra
    Sommet<InfoSommet> *depart = OutilsGraphe::getSommetParNom(s1, graphe);
    Sommet<InfoSommet> *cible = OutilsGraphe::getSommetParNom(s2, graphe);

    PElement<Sommet<InfoSommet>> *pcc;
    pcc = OutilsGraphe::plusCourtChemin(graphe, depart, cible);

    imageG = DessinGraphe::dessineGrapheChemin(*graphe, pcc, DessinGraphe::PNG);

    image->setPixmap(QPixmap(imageG.c_str()));

    std::ostringstream oss;
    oss << "Recherche de plus court chemin : ";

    for (; pcc; pcc = pcc->s) {
        if (!pcc->s)
            oss << pcc->v->v.getNom() << " - Coût : " << pcc->v->v.infoDijkstra.c;
        else
            oss << pcc->v->v.getNom() << " -> ";
    }

    texte->setText(oss.str().c_str());
}
