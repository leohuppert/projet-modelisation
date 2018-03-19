#ifndef PROJET_MODELISATION_FENETRE_H
#define PROJET_MODELISATION_FENETRE_H


#include <QtCore/QArgument>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include "InfoArc.h"
#include "InfoSommet.h"
#include "modele/Graphe.h"

class Fenetre : public QWidget {
    Q_OBJECT

public:
    explicit Fenetre(Graphe<InfoArc, InfoSommet> *g = nullptr);

public slots:
    void handleButton();
    void handleEvent();
    void choixFichier();
    void creerUnGraphe();

private:
    void init();

    Graphe<InfoArc, InfoSommet> *graphe;

    QPushButton *bouton;

    QLabel *lblAlgorithmes;
    QComboBox *listeAlgorithmes;

    QLabel *lblDepart;
    QComboBox *listeDepart;
    QLabel *lblCible;
    QComboBox *listeCible;

    QHBoxLayout *qhBoxLayout;
    QHBoxLayout *topLayout;
    QPushButton *boutonGpr;
    QPushButton *boutonCreer;

    QLabel *lblNom;
    QLineEdit *nomFichier;

    QLabel *lblSommets;
    QLineEdit *nombreSommets;

    QLabel *lblValeurMin;
    QLineEdit *valeurMin;

    QLabel *lblValeurMax;
    QLineEdit *valeurMax;

    QLabel *image;
    QGridLayout *gridLayout;

    QLabel *texte;

    QVBoxLayout *baseLayout;
};


#endif //PROJET_MODELISATION_FENETRE_H
