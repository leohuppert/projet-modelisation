#ifndef PROJET_MODELISATION_SOMMET_H
#define PROJET_MODELISATION_SOMMET_H

#include "GElement.h"

template<typename T>
class Sommet : public GElement<T> {
public:
    int degre;

    Sommet(const int clef, const T &v) : GElement<T>(clef, v), degre(0) {}

    explicit operator std::string() const;
};

template<typename T>
Sommet<T>::operator std::string() const {
    std::ostringstream oss;

    oss << "Sommet(" << std::endl;
    oss << GElement<T>::operator std::string() << std::endl;
    oss << "degré = " << degre << std::endl;
    oss << ")";

    return oss.str();
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const Sommet<T> &sommet) {
    return os << (std::string) sommet;
}

#endif //PROJET_MODELISATION_SOMMET_H
