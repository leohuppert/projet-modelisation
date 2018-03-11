#ifndef PROJET_MODELISATION_GELEMENT_H
#define PROJET_MODELISATION_GELEMENT_H

#include "AElement.h"

template<typename T>
class GElement : public AElement {
public:
    T v;

    GElement(const int clef, const T &v) : AElement(clef), v(v) {}

    explicit operator std::string() const override;

    friend std::ostream &operator<<(std::ostream &os, const GElement<T> &gElement) {
        return os << (std::string) gElement;
    }
};

template<typename T>
GElement<T>::operator std::string() const {
    std::ostringstream o;
    o << this->AElement::operator std::string() << ", v = " << v;
    return o.str();
}

#endif //PROJET_MODELISATION_GELEMENT_H
