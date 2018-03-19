#ifndef PROJET_MODELISATION_PELEMENT_H
#define PROJET_MODELISATION_PELEMENT_H

#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include "../helper/Erreur.h"

template<typename T>
class PElement {
public:
    T *v; // Valeur
    PElement<T> *s; // Suivant

    PElement(T *v, PElement<T> *s) : v(v), s(s) {}

    static const std::string
    toString(const PElement<T> *p, const char *debut = "( ", const char *separateur = ", ", const char *fin = ")");

    static int taille(const PElement<T> *l);

    static PElement<T> *copie1(PElement<T> *l);

    static PElement<T> *copie2(const PElement<T> *l);

    static PElement<T> *copie3(const PElement<T> *l);

    static void concat(PElement<T> *&l1, PElement<T> *l2);

    static void efface1(PElement<T> *&l);

    static void efface2(PElement<T> *&l);

    static PElement<T> *appartient(const T *a, PElement<T> *l);

    template<class FONCTEUR>
    static PElement<T> *appartient(PElement<T> *l, const FONCTEUR &condition);

    static void insertionOrdonnee(T *a, PElement<T> *&l, bool (*estPlusPetitOuEgal)(const T *a1, const T *a2));

    static bool retire(const T *a, PElement<T> *&l);

    static T *depiler(PElement<T> *&l);
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const PElement<T> *p) {
    return os << PElement<T>::toString(p);
}

template<typename T>
const std::string
PElement<T>::toString(const PElement<T> *p, const char *debut, const char *separateur, const char *fin) {
    PElement<T> *r;
    std::ostringstream oss;

    for (r = (PElement<T> *) p, oss << debut; r; r = r->s)
        oss << *(r->v) << separateur;

    oss << fin;
    return oss.str();
}

template<typename T>
void PElement<T>::concat(PElement<T> *&l1, PElement<T> *l2) {
    if (!l1)
        l1 = l2;

    else
        concat(l1->s, l2);
}

template<typename T>
int PElement<T>::taille(const PElement<T> *l) {
    if (!l) return 0;
    else
        return 1 + PElement<T>::taille(l->s);
}

template<typename T>
PElement<T> *PElement<T>::copie1(PElement<T> *l) {
    if (!l)
        return nullptr;
    else
        return new PElement<T>(l->v, PElement<T>::copie1(l->s));
}

template<typename T>
PElement<T> *PElement<T>::copie2(const PElement<T> *l) {
    if (!l)
        return nullptr;
    else
        return new PElement<T>(new T(*(l->v)), PElement<T>::copie2(l->s));
}

template<typename T>
PElement<T> *PElement<T>::copie3(const PElement<T> *l) {
    if (!l)
        return nullptr;
    else
        return new PElement<T>(l->v->copie(), PElement<T>::copie3(l->s));
}

template<typename T>
void PElement<T>::efface1(PElement<T> *&l) {
    if (l) {
        PElement<T>::efface1(l->s);
        delete l;
        l = nullptr;
    }
}

template<typename T>
void PElement<T>::efface2(PElement<T> *&l) {
    if (l) {
        PElement<T>::efface2(l->s);
        delete l->v;
        delete l;
        l = nullptr;
    }
}

template<typename T>
PElement<T> *PElement<T>::appartient(const T *a, PElement<T> *l) {
    for (; l; l = l->s)
        if (a == l->v)
            return l;

    return l;
}

template<typename T>
template<typename FONCTEUR>
PElement<T> *PElement<T>::appartient(PElement<T> *l, const FONCTEUR &condition) {
    for (; l; l = l->s)
        if (condition(l->v))
            return l;

    return l;
}

template<typename T>
void PElement<T>::insertionOrdonnee(T *a, PElement<T> *&l, bool (*estPlusPetitOuEgal)(const T *a1, const T *a2)) {
    if (!l || estPlusPetitOuEgal(a, l->v))
        l = new PElement<T>(a, l);
    else
        PElement<T>::insertionOrdonnee(a, l->s, estPlusPetitOuEgal);
}

template<typename T>
bool PElement<T>::retire(const T *a, PElement<T> *&l) {
    if (!l)
        return false;
    else if (a == l->v) {
        PElement<T> *r = l;
        l = l->s;
        delete r;
        return true;
    } else
        return PElement<T>::retire(a, l->s);
}

template<typename T>
T *PElement<T>::depiler(PElement<T> *&l) {
    if (!l) throw Erreur("impossible de dépiler une pile vide");
    T *a = l->v;
    PElement<T> *tete = l;

    l = l->s;
    delete tete;
    return a;
}

template<typename T>
PElement<T> *reunion(PElement<T> *l1, PElement<T> *l2) {
    PElement<T> *r = PElement<T>::copie1(l2);
    PElement<T> *pl1;

    for (pl1 = l1; pl1; pl1 = pl1->s)
        if (!PElement<T>::appartient(pl1->v, r))
            r = new PElement<T>(pl1->v, r);

    return r;
}

template<typename T>
void partage(PElement<T> *&p, PElement<T> *&p1) {
    if (p == nullptr || p->s == nullptr)
        p1 = nullptr;
    else {
        PElement<T> *r1, *r2;

        r1 = p->s;
        r2 = r1->s;

        partage(r2, p1);

        r1->s = p1;
        p->s = r2;
        p1 = r1;
    }
}

template<typename T>
void fusion(PElement<T> *&p1, PElement<T> *&p2, bool (*estPlusPetitOuEgal)(const T *a1, const T *a2)) {
    if (!p2) return; // p2 est vide, il n'y a rien à faire

    if (!p1) // p1 est vide et p2 ne l'est pas
    {
        p1 = p2;
        p2 = nullptr;
        return;
    }

    // à présent, p1 et p2 sont non vides
    if (estPlusPetitOuEgal(p1->v, p2->v)) // p1->v <= p2->v
    {
        PElement<T> *r;
        r = p1->s;
        fusion(r, p2, estPlusPetitOuEgal);
        p1->s = r;
    } else // p1->v > p2->v
    {
        PElement<T> *r;
        r = p2->s;
        fusion(p1, r, estPlusPetitOuEgal);
        p2->s = p1;
        p1 = p2;
        p2 = NULL;
    }
}

template<typename T>
void tri(PElement<T> *&p, bool (*estPlusPetitOuEgal)(const T *a1, const T *a2)) {
    if (p != nullptr && p->s != nullptr) {
        PElement<T> *p1;

        partage(p, p1);

        tri(p, estPlusPetitOuEgal);
        tri(p1, estPlusPetitOuEgal);

        fusion(p, p1, estPlusPetitOuEgal);
    }
}

template<typename T>
PElement<T> *inverse(const PElement<T> *pElement) {
    const PElement<T> *pElement1;
    PElement<T> *pElement2 = nullptr;

    for (pElement1 = pElement; pElement1; pElement1 = pElement1->s) {
        pElement2 = new PElement<T>(pElement1->v, pElement2);
    }

    return pElement2;
}

template <typename T>
void insertionFin(T *a, PElement<T> *&l) {
    if(!l)
        l = new PElement<T>(a, l);
        else
        insertionFin(a, l->s);
}

template<typename T>
PElement<T> *getRandomFrom(const PElement<T> *pElement) {
    PElement<T> *pElement1;
    // Seed generator (remplace time(NULL))
    std::random_device rd;

    // Générateur initialisé avec la seed obtenue de rd
    std::mt19937_64 generator{rd()};

    // Génère des nombres aléatoires de 0 à taille - 1
    std::uniform_int_distribution<> dist{0, PElement<T>::taille(pElement) - 1};

    int random = dist(generator);
    pElement1 = const_cast<PElement<T> *>(pElement);

    while (pElement1->s && random > 0) {
        random--;
        pElement1 = pElement1->s;
    }

    return pElement1;
}

#endif //PROJET_MODELISATION_PELEMENT_H
