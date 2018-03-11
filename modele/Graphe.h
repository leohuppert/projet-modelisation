#ifndef PROJET_MODELISATION_GRAPHE_H
#define PROJET_MODELISATION_GRAPHE_H

#include <utility>
#include "PElement.h"
#include "Sommet.h"
#include "Arete.h"

template<typename S, typename T>
class Graphe {
protected:
    int prochaineClef;

public:
    PElement<Sommet<T>> *lSommets;
    PElement<Arete<S, T>> *lAretes;

private:
    Sommet<T> *creeSommet1(const int clef, const T &info);

    void majProchaineClef(const int clef) { prochaineClef = std::max(1 + clef, prochaineClef); }

    Sommet<T> *creeSommet(const int clef, const T &info) {
        majProchaineClef(clef);
        return creeSommet1(clef, info);
    }

public:
    Sommet<T> *creeSommet(const T &info) { return creeSommet1(prochaineClef++, info); }

private:
    Arete<S, T> *creeArete1(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin);

    Arete<S, T> *creeArete(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin) {
        majProchaineClef(clef);
        return creeArete1(clef, info, debut, fin);
    }

public:
    Arete<S, T> *creeArete(const S &info, Sommet<T> *debut, Sommet<T> *fin) {
        return creeArete1(prochaineClef++, info, debut, fin);
    }

private:
    void copie(const Graphe<S, T> &graphe);

    void effaceTout();

public:
    Graphe() : prochaineClef(0), lSommets(nullptr), lAretes(nullptr) {}

    Graphe(const Graphe<S, T> &graphe) : Graphe() { this->copie(graphe); }

    const Graphe<S, T> &operator=(const Graphe<S, T> &graphe) {
        this->effaceTout();
        this->copie(graphe);
        return *this;
    }

    ~Graphe() { this->effaceTout(); }

    int nombreSommets() const { return PElement<Sommet<T> >::taille(lSommets); }

    int nombreAretes() const { return PElement<Arete<S, T> >::taille(lAretes); }

    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *adjacences(const Sommet<T> *sommet) const;

    PElement<Arete<S, T> > *aretesAdjacentes(const Sommet<T> *sommet) const;

    PElement<Sommet<T> > *voisins(const Sommet<T> *sommet) const;

    Arete<S, T> *getAreteParSommets(const Sommet<T> *s1, const Sommet<T> *s2) const;

    explicit operator std::string() const;

    template<typename FENETRE>
    bool dessineToutesAretes(FENETRE &fenetre) const;

    template<typename FENETRE>
    bool dessineTousSommets(FENETRE &fenetre) const;

    template<typename FENETRE>
    bool dessine(FENETRE &fenetre) const;
};

template<typename S, typename T>
Sommet<T> *Graphe<S, T>::creeSommet1(const int clef, const T &info) {
    auto *sommetCree = new Sommet<T>(clef, info);
    lSommets = new PElement<Sommet<T> >(sommetCree, lSommets);

    return sommetCree;
}

template<typename S, typename T>
Arete<S, T> *Graphe<S, T>::creeArete1(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin) {
    // ici tester que les 2 sommets sont bien existants dans le graphe
    if (!PElement<Sommet<T> >::appartient(debut, lSommets)) throw Erreur("début d'arête non défini");
    if (!PElement<Sommet<T> >::appartient(fin, lSommets)) throw Erreur("fin d'arête non définie");

    auto nouvelleArete = new Arete<S, T>(clef, info, debut, fin);

    lAretes = new PElement<Arete<S, T> >(nouvelleArete, lAretes);

    return nouvelleArete;
}

template<typename T>
class SommetDejaPresentDansLaCopie {
public:
    const Sommet<T> *s;

    explicit SommetDejaPresentDansLaCopie(const Sommet<T> *s) : s(s) {}

    bool operator()(const Sommet<T> *sommet) const { return sommet->clef == s->clef; }
};

template<typename S, typename T>
void Graphe<S, T>::copie(const Graphe<S, T> &graphe) {
    const PElement<Sommet<T>> *pS;

    for (pS = graphe.lSommets; pS; pS = pS->s) {
        const Sommet<T> *sommet = pS->v;
        this->creeSommet(sommet->clef, sommet->v);
    }

    const PElement<Arete<S, T>> *pA;
    for (pA = graphe.lAretes; pA; pA = pA->s) {
        const Arete<S, T> *a = pA->v;
        Sommet<T> *d, *f;
        PElement<Sommet<T> > *p;

        SommetDejaPresentDansLaCopie<T> conditionDebut(a->debut);
        p = PElement<Sommet<T> >::appartient(lSommets, conditionDebut);
        d = p->v;

        SommetDejaPresentDansLaCopie<T> conditionFin(a->fin);
        p = PElement<Sommet<T> >::appartient(lSommets, conditionFin);
        f = p->v;

        this->creeArete(a->clef, a->v, d, f);
    }
}

template<typename S, typename T>
void Graphe<S, T>::effaceTout() {
    PElement<Arete<S, T>>::efface2(this->lAretes);
    PElement<Sommet<T> >::efface2(this->lSommets);
    this->prochaineClef = 0;
}

template<typename S, typename T>
PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *Graphe<S, T>::adjacences(const Sommet<T> *sommet) const {
    const PElement<Arete<S, T> > *l;

    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *r;

    for (l = lAretes, r = NULL; l; l = l->s)

        if (sommet == l->v->debut)
            r = new PElement<std::pair<Sommet<T> *, Arete<S, T> *> >
                    (new std::pair<Sommet<T> *, Arete<S, T> *>(l->v->fin, l->v), r);
        else if (sommet == l->v->fin)
            r = new PElement<std::pair<Sommet<T> *, Arete<S, T> *> >
                    (new std::pair<Sommet<T> *, Arete<S, T> *>(l->v->debut, l->v), r);

    return r;
}

template<typename S, typename T>
PElement<Arete<S, T> > *Graphe<S, T>::aretesAdjacentes(const Sommet<T> *sommet) const {
    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *ladj = this->adjacences(sommet);
    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *l;

    PElement<Arete<S, T> > *r;

    for (l = ladj, r = NULL; l; l = l->s)
        r = new PElement<Arete<S, T> >(l->v->second, r);

    PElement<std::pair<Sommet<T> *, Arete<S, T> *> >::efface2(ladj);

    return r;
}

template<typename S, typename T>
PElement<Sommet<T> > *Graphe<S, T>::voisins(const Sommet<T> *sommet) const {
    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *ladj = this->adjacences(sommet);
    PElement<std::pair<Sommet<T> *, Arete<S, T> *> > *l;

    PElement<Sommet<T> > *r;

    for (l = ladj, r = NULL; l; l = l->s)
        r = new PElement<Sommet<T> >(l->v->first, r);

    PElement<std::pair<Sommet<T> *, Arete<S, T> *> >::efface2(ladj);

    return r;
}

template<typename S, typename T>
Arete<S, T> *Graphe<S, T>::getAreteParSommets(const Sommet<T> *s1, const Sommet<T> *s2) const {
    PElement<Arete<S, T> > *l;

    for (l = this->lAretes; l; l = l->s)
        if (l->v->estEgal(s1, s2))
            return l->v;

    return NULL;
}

template<typename S, typename T>
Graphe<S, T>::operator std::string() const {
    std::ostringstream oss;
    oss << "Graphe( \n";
    oss << "prochaine clef = " << this->prochaineClef << std::endl;
    oss << "nombre de sommets = " << this->nombreSommets() << "\n";

    oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "\n");

    oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";

    oss << PElement<Arete<S, T> >::toString(lAretes, "", "\n", "\n");
    oss << ")";
    return oss.str();
}

template<typename S, typename T>
template<typename FENETRE>
bool Graphe<S, T>::dessineToutesAretes(FENETRE &fenetre) const {
    // On dessine les arêtes
    PElement<Arete<S, T>> *pA;
    for (pA = this->lAretes; pA; pA = pA->s)
        if (!fenetre.dessine(pA->v)) return false;

    return true;
}

template<typename S, typename T>
template<typename FENETRE>
bool Graphe<S, T>::dessineTousSommets(FENETRE &fenetre) const {
    // On dessine les sommets
    PElement<Sommet<T>> *pS;
    for (pS = this->lSommets; pS; pS = pS->s)
        if (!fenetre.dessine(pS->v)) return false;

    return true;
}

template<typename S, typename T>
template<typename FENETRE>
bool Graphe<S, T>::dessine(FENETRE &fenetre) const {
    if (!this->dessineToutesAretes(fenetre)) return false;
    return this->dessineTousSommets(fenetre);
}

template<typename S, typename T>
std::ostream &operator<<(std::ostream &os, const Graphe<S, T> &gr) {
    return os << (std::string) gr;
}

template<typename T, typename FENETRE>
bool dessine(const PElement<Sommet<T>> *chemin, FENETRE &fenetre, const unsigned int couleur) {
    if (!(chemin && chemin->s))
        return true;

    else {
        fenetre.dessine(chemin->v, chemin->s->v, couleur);
        return dessine(chemin->s, fenetre, couleur);
    }
}

#endif //PROJET_MODELISATION_GRAPHE_H
