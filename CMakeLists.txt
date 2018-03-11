cmake_minimum_required(VERSION 3.9)
project(projet_modelisation)

set(CMAKE_CXX_STANDARD 11)

add_executable(projet_modelisation main.cpp modele/PElement.h helper/Erreur.h helper/Erreur.cpp modele/AElement.h modele/GElement.h modele/Sommet.h modele/Arete.h modele/Graphe.h GprParser.h)