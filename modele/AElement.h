#ifndef PROJET_MODELISATION_AELEMENT_H
#define PROJET_MODELISATION_AELEMENT_H

#include <string>
#include <iostream>
#include <sstream>

class AElement {
public:
    int clef;

    explicit AElement(const int clef) : clef(clef) {}

    virtual explicit operator std::string() const {
        std::ostringstream oss;
        oss << "Clef = " << clef;
        return oss.str();
    }

    friend std::ostream &operator<<(std::ostream &os, const AElement &aElement) {
        return os << (std::string) aElement;
    }
};

#endif //PROJET_MODELISATION_AELEMENT_H
