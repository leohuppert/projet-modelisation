#include "Erreur.h"

std::ostream &operator<<(std::ostream &os, const Erreur &e) {
    os << e.message;
    return os;
}
