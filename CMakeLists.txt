cmake_minimum_required(VERSION 3.9)
project(projet_modelisation)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

add_executable(projet_modelisation main.cpp modele/PElement.h helper/Erreur.h helper/Erreur.cpp modele/AElement.h modele/GElement.h modele/Sommet.h modele/Arc.h modele/Graphe.h GprParser.h InfoSommet.h InfoArc.h OutilsGraphe.h OutilsGraphe.cpp InfoDijkstra.h InfoDijkstra.cpp DessinGraphe.h Fenetre.cpp Fenetre.h)

find_package(Qt5Widgets)
target_link_libraries(projet_modelisation Qt5::Widgets)