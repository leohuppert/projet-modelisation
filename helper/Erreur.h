#ifndef PROJET_MODELISATION_ERREUR_H
#define PROJET_MODELISATION_ERREUR_H

#include <string>
#include <iostream>
#include <exception>

class Erreur : public std::exception {
public:
    std::string message;

    Erreur() : message("Erreur !") {}

    explicit Erreur(const std::string &messageErreur) : Erreur() { this->message += " " + messageErreur; }

    explicit Erreur(const char *messageErreur) : Erreur((std::string) messageErreur) {}
};

std::ostream &operator<<(std::ostream &os, const Erreur &e);

#endif //PROJET_MODELISATION_ERREUR_H
