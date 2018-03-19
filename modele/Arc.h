#ifndef PROJET_MODELISATION_ARETE_H
#define PROJET_MODELISATION_ARETE_H

#include "GElement.h"
#include "Sommet.h"

template<typename S, typename T>
class Arc : public GElement<S> {
public:
    Sommet<T> *debut, *fin;

    Arc(const int clef, const S &v, Sommet<T> *debut, Sommet<T> *fin) : GElement<S>(clef, v), debut(debut), fin(fin) {
        debut->degre++;
        fin->degre++;
    }

    ~Arc() {
        debut->degre--;
        fin->degre--;
    }

    operator std::string() const;

    bool estEgal(const Sommet<T> *s1, const Sommet<T> *s2) const;
};

template<typename S, typename T>
Arc<S, T>::operator std::string() const {
    std::ostringstream oss;

    oss << "Arc  (" << std::endl;
    oss << GElement<S>::operator std::string() << std::endl;
    oss << "clef début = " << debut->clef << std::endl;
    oss << "clef fin = " << fin->clef << std::endl;
    oss << ")";
    return oss.str();
}

template<class S, class T>
std::ostream &operator<<(std::ostream &os, const Arc<S, T> &arete) {
    return os << (std::string) arete;
}

template<typename S, typename T>
bool Arc<S, T>::estEgal(const Sommet<T> *s1, const Sommet<T> *s2) const {
    return s1 == debut && s2 == fin;
}

#endif //PROJET_MODELISATION_ARETE_H
