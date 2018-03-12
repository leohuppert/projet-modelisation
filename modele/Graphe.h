#ifndef PROJET_MODELISATION_GRAPHE_H
#define PROJET_MODELISATION_GRAPHE_H

#include <utility>
#include <vector>
#include <algorithm>
#include "PElement.h"
#include "Sommet.h"
#include "Arc.h"

template<typename S, typename T>
class Graphe {
protected:
    int prochaineClef;

public:
    PElement<Sommet<T>> *lSommets;
    PElement<Arc<S, T>> *lArcs;

    std::string nom;

    std::vector<Sommet<T> *> sources;
    std::vector<Sommet<T> *> puits;

private:
    Sommet<T> *creeSommet1(const int clef, const T &info, bool source, bool puits);

    void majProchaineClef(const int clef) { prochaineClef = std::max(1 + clef, prochaineClef); }

    Sommet<T> *creeSommet(const int clef, const T &info, bool source, bool puits) {
        majProchaineClef(clef);
        return creeSommet1(clef, info, source, puits);
    }

public:
    Sommet<T> *creeSommet(const T &info, bool source = false, bool puits = false) {
        return creeSommet1(prochaineClef++, info, source, puits);
    }

private:
    Arc<S, T> *creeArete1(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin);

    Arc<S, T> *creeArete(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin) {
        majProchaineClef(clef);
        return creeArete1(clef, info, debut, fin);
    }

public:
    Arc<S, T> *creeArete(const S &info, Sommet<T> *debut, Sommet<T> *fin) {
        return creeArete1(prochaineClef++, info, debut, fin);
    }

private:
    void copie(const Graphe<S, T> &graphe);

    void effaceTout();

public:
    Graphe(const std::string &nom = "graphe") : prochaineClef(0), lSommets(nullptr), lArcs(nullptr), nom(nom) {}

    Graphe(const Graphe<S, T> &graphe) : Graphe() { this->copie(graphe); }

    const Graphe<S, T> &operator=(const Graphe<S, T> &graphe) {
        this->effaceTout();
        this->copie(graphe);
        return *this;
    }

    ~Graphe() { this->effaceTout(); }

    int nombreSommets() const { return PElement<Sommet<T> >::taille(lSommets); }

    int nombreAretes() const { return PElement<Arc<S, T> >::taille(lArcs); }

    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *adjacences(const Sommet<T> *sommet) const;

    PElement<Arc<S, T> > *aretesAdjacentes(const Sommet<T> *sommet) const;

    PElement<Sommet<T> > *voisins(const Sommet<T> *sommet) const;

    Arc<S, T> *getAreteParSommets(const Sommet<T> *s1, const Sommet<T> *s2) const;

    explicit operator std::string() const;

    template<typename FENETRE>
    bool dessineToutesAretes(FENETRE &fenetre) const;

    template<typename FENETRE>
    bool dessineTousSommets(FENETRE &fenetre) const;

    template<typename FENETRE>
    bool dessine(FENETRE &fenetre) const;
};

template<typename S, typename T>
Sommet<T> *Graphe<S, T>::creeSommet1(const int clef, const T &info, bool source, bool puits) {
    auto *sommetCree = new Sommet<T>(clef, info);
    lSommets = new PElement<Sommet<T> >(sommetCree, lSommets);

    if (source)
        this->sources.push_back(sommetCree);
    else if (puits)
        this->puits.push_back(sommetCree);

    return sommetCree;
}

template<typename S, typename T>
Arc<S, T> *Graphe<S, T>::creeArete1(const int clef, const S &info, Sommet<T> *debut, Sommet<T> *fin) {
    // ici tester que les 2 sommets sont bien existants dans le graphe
    if (!PElement<Sommet<T> >::appartient(debut, lSommets)) throw Erreur("début d'arête non défini");
    if (!PElement<Sommet<T> >::appartient(fin, lSommets)) throw Erreur("fin d'arête non définie");

    auto nouvelleArete = new Arc<S, T>(clef, info, debut, fin);

    lArcs = new PElement<Arc<S, T> >(nouvelleArete, lArcs);

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
        //this->creeSommet(sommet->clef, sommet->v);

        bool source = std::find(graphe.sources.begin(), graphe.sources.end(), sommet) != graphe.sources.end();
        bool puits = std::find(graphe.puits.begin(), graphe.puits.end(), sommet) != graphe.puits.end();

        this->creeSommet(sommet->clef, sommet->v, source, puits);
    }

    const PElement<Arc<S, T>> *pA;
    for (pA = graphe.lArcs; pA; pA = pA->s) {
        const Arc<S, T> *a = pA->v;
        Sommet<T> *d, *f;
        PElement<Sommet<T> > *p;

        SommetDejaPresentDansLaCopie<T> conditionDebut(a->debut);
        p = PElement<Sommet<T> >::appartient(lSommets, conditionDebut);
        d = p->v;

        SommetDejaPresentDansLaCopie<T> conditionFin(a->fin);
        p = PElement<Sommet<T> >::appartient(lSommets, conditionFin);
        f = p->v;

        this->creeArete(a->clef, a->v, d, f);

        // Nom
        this->nom = graphe.nom;
    }
}

template<typename S, typename T>
void Graphe<S, T>::effaceTout() {
    PElement<Arc<S, T>>::efface2(this->lArcs);
    PElement<Sommet<T> >::efface2(this->lSommets);
    this->prochaineClef = 0;
}

template<typename S, typename T>
PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *Graphe<S, T>::adjacences(const Sommet<T> *sommet) const {
    const PElement<Arc<S, T> > *l;

    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *r;

    for (l = lArcs, r = NULL; l; l = l->s)

        if (sommet == l->v->debut)
            r = new PElement<std::pair<Sommet<T> *, Arc<S, T> *> >
                    (new std::pair<Sommet<T> *, Arc<S, T> *>(l->v->fin, l->v), r);
        else if (sommet == l->v->fin)
            r = new PElement<std::pair<Sommet<T> *, Arc<S, T> *> >
                    (new std::pair<Sommet<T> *, Arc<S, T> *>(l->v->debut, l->v), r);

    return r;
}

template<typename S, typename T>
PElement<Arc<S, T> > *Graphe<S, T>::aretesAdjacentes(const Sommet<T> *sommet) const {
    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *ladj = this->adjacences(sommet);
    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *l;

    PElement<Arc<S, T> > *r;

    for (l = ladj, r = NULL; l; l = l->s)
        r = new PElement<Arc<S, T> >(l->v->second, r);

    PElement<std::pair<Sommet<T> *, Arc<S, T> *> >::efface2(ladj);

    return r;
}

template<typename S, typename T>
PElement<Sommet<T> > *Graphe<S, T>::voisins(const Sommet<T> *sommet) const {
    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *ladj = this->adjacences(sommet);
    PElement<std::pair<Sommet<T> *, Arc<S, T> *> > *l;

    PElement<Sommet<T> > *r;

    for (l = ladj, r = NULL; l; l = l->s)
        r = new PElement<Sommet<T> >(l->v->first, r);

    PElement<std::pair<Sommet<T> *, Arc<S, T> *> >::efface2(ladj);

    return r;
}

template<typename S, typename T>
Arc<S, T> *Graphe<S, T>::getAreteParSommets(const Sommet<T> *s1, const Sommet<T> *s2) const {
    PElement<Arc<S, T> > *l;

    for (l = this->lArcs; l; l = l->s)
        if (l->v->estEgal(s1, s2))
            return l->v;

    return NULL;
}

template<typename S, typename T>
Graphe<S, T>::operator std::string() const {
    std::ostringstream oss;
    oss << "Graphe( \n";
    oss << "nom: " << nom << std::endl;

    oss << "Sources : ";
    for (auto const &value: this->sources)
        oss << "Sommet clef " << value->clef << "; ";
    oss << std::endl;

    oss << "Puits : ";
    for (auto const &value: this->puits)
        oss << "Sommet clef " << value->clef << "; ";
    oss << std::endl;

    oss << "prochaine clef = " << this->prochaineClef << std::endl;
    oss << "nombre de sommets = " << this->nombreSommets() << "\n";

    oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "\n");

    oss << "nombre d'arcs = " << this->nombreAretes() << "\n";

    oss << PElement<Arc<S, T> >::toString(lArcs, "", "\n", "\n");
    oss << ")";
    return oss.str();
}

template<typename S, typename T>
template<typename FENETRE>
bool Graphe<S, T>::dessineToutesAretes(FENETRE &fenetre) const {
    // On dessine les arêtes
    PElement<Arc<S, T>> *pA;
    for (pA = this->lArcs; pA; pA = pA->s)
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
