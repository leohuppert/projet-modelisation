#include <iostream>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include "Fenetre.h"
#include "DessinGraphe.h"
#include "OutilsGraphe.h"
#include "GprParser.h"

Fenetre::Fenetre(Graphe<InfoArc, InfoSommet> *g) : QWidget() {
    setBaseSize(800, 600);
    setMaximumSize(800, 600);

    graphe = g;

    lblAlgorithmes = new QLabel("Choix d'algorithme à appliquer");
    listeAlgorithmes = new QComboBox();
    listeAlgorithmes->addItem("Dijkstra");
    listeAlgorithmes->addItem("DFS");

    lblDepart = new QLabel("Sommet départ");
    lblCible = new QLabel("Sommet cible");
    listeDepart = new QComboBox();
    listeCible = new QComboBox();
    bouton = new QPushButton("Lancer");

    /*PElement<Sommet<InfoSommet>> *listeSommets = inverse(graphe->lSommets);

    for (; listeSommets; listeSommets = listeSommets->s) {
        listeDepart->addItem(listeSommets->v->v.getNom().c_str());
        listeCible->addItem(listeSommets->v->v.getNom().c_str());
    }*/

    texte = new QLabel();
    texte->setFont(QFont("Liberation", 12));

    qhBoxLayout = new QHBoxLayout();
    qhBoxLayout->addWidget(lblAlgorithmes);
    qhBoxLayout->addWidget(listeAlgorithmes);
    qhBoxLayout->addWidget(lblDepart);
    qhBoxLayout->addWidget(listeDepart);
    qhBoxLayout->addWidget(lblCible);
    qhBoxLayout->addWidget(listeCible);
    qhBoxLayout->addWidget(bouton);

    lblNom = new QLabel("Nom Fichier :");
    lblNom->setVisible(false);

    nomFichier = new QLineEdit();
    nomFichier->setMaximumSize(150, 30);
    nomFichier->setVisible(false);

    lblSommets = new QLabel("Nombre de sommets :");
    lblSommets->setVisible(false);

    nombreSommets = new QLineEdit();
    nombreSommets->setMaximumSize(150, 30);
    nombreSommets->setVisible(false);

    lblValeurMax = new QLabel("Valuation Max :");
    lblValeurMax->setVisible(false);

    valeurMax = new QLineEdit();
    valeurMax->setMaximumSize(150, 30);
    valeurMax->setVisible(false);

    lblValeurMin = new QLabel("Valuation Min :");
    lblValeurMin->setVisible(false);

    valeurMin = new QLineEdit();
    valeurMin->setMaximumSize(150, 30);
    valeurMin->setVisible(false);

    boutonGpr = new QPushButton("Choisir fichier ...");
    boutonGpr->setMaximumSize(150, 30);

    boutonCreer = new QPushButton("Valider");
    boutonCreer->setMaximumSize(150, 30);
    boutonCreer->setVisible(false);

    boutonAfficher = new QPushButton("Créer un graphe");
    boutonAfficher->setMaximumSize(150, 30);

    topLayout = new QHBoxLayout();
    topLayout->addWidget(texte);

    topLayout->addWidget(lblNom, Qt::AlignRight);
    topLayout->addWidget(nomFichier, Qt::AlignRight);

    topLayout->addWidget(lblSommets, Qt::AlignRight);
    topLayout->addWidget(nombreSommets, Qt::AlignRight);

    topLayout->addWidget(lblValeurMax, Qt::AlignRight);
    topLayout->addWidget(valeurMax, Qt::AlignRight);

    topLayout->addWidget(lblValeurMin, Qt::AlignRight);
    topLayout->addWidget(valeurMin, Qt::AlignRight);

    topLayout->addWidget(boutonAfficher, Qt::AlignRight);
    topLayout->addWidget(boutonCreer, Qt::AlignRight);
    topLayout->addWidget(boutonGpr, Qt::AlignRight);

    image = new QLabel();
    /*std::string cheminImage = DessinGraphe::dessineGraphe(*graphe, DessinGraphe::PNG);

    image->setMaximumSize(1000, 900);
    image->setPixmap(QPixmap(cheminImage.c_str()));
    image->setAlignment(Qt::AlignCenter);

    if (image->pixmap()->width() > 1000)
        image->setScaledContents(true);*/

    listeAlgorithmes->setEnabled(false);
    listeDepart->setEnabled(false);
    listeCible->setEnabled(false);
    bouton->setEnabled(false);

    gridLayout = new QGridLayout();
    gridLayout->addLayout(topLayout, 0, 1);
    gridLayout->addWidget(image, 1, 1);
    gridLayout->addLayout(qhBoxLayout, 2, 1);

    setLayout(gridLayout);

    QObject::connect(listeAlgorithmes, SIGNAL(currentIndexChanged(int)), this, SLOT(handleEvent()));
    QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(handleButton()));
    QObject::connect(boutonGpr, SIGNAL(clicked()), this, SLOT(choixFichier()));
    QObject::connect(boutonCreer, SIGNAL(clicked()), this, SLOT(creerUnGraphe()));
    QObject::connect(boutonAfficher, SIGNAL(clicked()), this, SLOT(afficherBoutonsGraphe()));
}


void Fenetre::handleButton() {
    std::string algo, s1, s2, imageG;
    std::ostringstream oss;

    algo = listeAlgorithmes->currentText().toStdString();

    s1 = listeDepart->currentText().toStdString();
    s2 = listeCible->currentText().toStdString();

    if (algo == "Dijkstra") {
        // On lance Dijkstra
        Sommet<InfoSommet> *depart = OutilsGraphe::getSommetParNom(s1, graphe);
        Sommet<InfoSommet> *cible = OutilsGraphe::getSommetParNom(s2, graphe);

        PElement<Sommet<InfoSommet>> *pcc;
        pcc = OutilsGraphe::plusCourtChemin(graphe, depart, cible);

        imageG = DessinGraphe::dessineGrapheChemin(*graphe, pcc, DessinGraphe::PNG);

        oss << "Recherche de plus court chemin : ";
        for (; pcc; pcc = pcc->s) {
            if (!pcc->s)
                oss << pcc->v->v.getNom() << " - Coût : " << pcc->v->v.infoDijkstra.c;
            else
                oss << pcc->v->v.getNom() << " -> ";
        }
    } else if (algo == "DFS") {
        // Test dfs
        PElement<Arc<InfoArc, InfoSommet>> *dfs;
        OutilsGraphe::dfs(graphe);
        OutilsGraphe::arbreCouvrant(graphe, dfs);

        imageG = DessinGraphe::dessineGrapheArbre(*graphe, dfs, DessinGraphe::PNG);

        oss << "Affichage d'un arbre couvrant : ";
    }

    image->setPixmap(QPixmap(imageG.c_str()));

    texte->setText(oss.str().c_str());
}

void Fenetre::handleEvent() {
    std::string algo = listeAlgorithmes->currentText().toStdString();
    texte->clear();
    if (algo == "Dijkstra") {
        lblDepart->setVisible(true);
        listeDepart->setVisible(true);
        lblCible->setVisible(true);
        listeCible->setVisible(true);

    } else if (algo == "DFS") {
        lblDepart->setVisible(false);
        listeDepart->setVisible(false);
        lblCible->setVisible(false);
        listeCible->setVisible(false);
    }
}

void Fenetre::choixFichier() {
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichier GPR (*.gpr)");

    if (fichier != "") {
        // On récupère le graphe à partir du fichier gpr
        Graphe<InfoArc, InfoSommet> *g;
        g = GprParser::genererGraphe(fichier.toStdString().c_str());

        graphe = g;

        this->init();
    }
}

void Fenetre::afficherBoutonsGraphe(){
    boutonAfficher->setVisible(false);
    boutonCreer->setVisible(true);
    valeurMax->setVisible(true);
    valeurMin->setVisible(true);
    nomFichier->setVisible(true);
    nombreSommets->setVisible(true);
    lblValeurMax->setVisible(true);
    lblValeurMin->setVisible(true);
    lblNom->setVisible(true);
    lblSommets->setVisible(true);
}

void Fenetre::masquerBoutonsGraphe(){
    boutonAfficher->setVisible(true);
    boutonCreer->setVisible(false);
    valeurMax->setVisible(false);
    valeurMin->setVisible(false);
    nomFichier->setVisible(false);
    nombreSommets->setVisible(false);
    lblValeurMax->setVisible(false);
    lblValeurMin->setVisible(false);
    lblNom->setVisible(false);
    lblSommets->setVisible(false);
}

void Fenetre::creerUnGraphe() {
    std::string nom = nomFichier->text().toStdString();
    if (nom == "")
        nom = "Graphe";
    int nbSommets = nombreSommets->text().toInt();
    if (nbSommets <= 0)
        nbSommets = rand() % 8 + 2;
    int vMax = valeurMax->text().toInt();
    if (vMax <= 0)
        vMax = 100;

    int vMin = valeurMin->text().toInt();
    if (vMin <= 0)
        vMin = 0;

    Graphe<InfoArc, InfoSommet> *g = new Graphe<InfoArc, InfoSommet>(nom);
    graphe = Graphe<InfoArc, InfoSommet>::genererGraphe(nbSommets, g, vMax, vMin);
    GprParser::genererInstance(graphe);
    this->masquerBoutonsGraphe();
    this->init();
}

void Fenetre::init() {
    // On vide les listes de sommets
    listeDepart->clear();
    listeCible->clear();
    texte->clear();

    PElement<Sommet<InfoSommet>> *listeSommets = inverse(graphe->lSommets);

    for (; listeSommets; listeSommets = listeSommets->s) {
        listeDepart->addItem(listeSommets->v->v.getNom().c_str());
        listeCible->addItem(listeSommets->v->v.getNom().c_str());
    }

    listeAlgorithmes->setEnabled(true);
    listeDepart->setEnabled(true);
    listeCible->setEnabled(true);
    bouton->setEnabled(true);

    std::string cheminImage = DessinGraphe::dessineGraphe(*graphe, DessinGraphe::PNG);

    image->setMaximumSize(1000, 900);
    image->setPixmap(QPixmap(cheminImage.c_str()));
    image->setAlignment(Qt::AlignCenter);

    image->setScaledContents(image->pixmap()->width() > 800 || image->pixmap()->height() > 600);
}
