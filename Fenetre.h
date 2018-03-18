#ifndef PROJET_MODELISATION_FENETRE_H
#define PROJET_MODELISATION_FENETRE_H


#include <QtCore/QArgument>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include "InfoArc.h"
#include "InfoSommet.h"
#include "modele/Graphe.h"

class Fenetre : public QWidget {
    Q_OBJECT

public:
    Fenetre(Graphe<InfoArc, InfoSommet> *g);

public slots:
    void handleButton();

private:
    Graphe<InfoArc, InfoSommet> *graphe;

    QPushButton *bouton;

    QLabel *lblDepart;
    QComboBox *listeDepart;
    QLabel *lblCible;
    QComboBox *listeCible;

    QHBoxLayout *qhBoxLayout;
    QLabel *image;
    QGridLayout *gridLayout;
};


#endif //PROJET_MODELISATION_FENETRE_H