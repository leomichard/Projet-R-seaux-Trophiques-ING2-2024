#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef REPPROJ_GRAPHE_H
#define REPPROJ_GRAPHE_H

#include "especes.h"

typedef struct mesures_centralite {
    int id;
    int degresEntrants;
    int degresSortants;
    double centraliteMediane;
    char Importance[20];
} CentralityMeasures;

typedef struct {
    int depart;         // Sommet de départ (ID de l'espèce consommée)
    int arrivee;        // Sommet d'arrivée (ID du consommateur)
    int poids;        // Pondération de l'arête (fraction de la consommation, entre 0 et 1)
} Arete;


typedef struct arc {
    int valeur;
    int sommetDepart;
    int sommetArrivee;
    struct arc *arcSuivant;
} ARC;

typedef struct sommet {
    ARC *arcs;
    espece *espece;
    int id;
    long nombre;
    int etat;
} Sommet;

typedef struct graphe {
    Sommet *sommets;
    int ordre;
    int taille;
    int orientation;
    int etat; //qualité de l'endoit ou les betes vivent entre 0 & 10 definit a 5 de base // État du réseau trophique (entre 0 et 10)
    int connexite;      // Connexité (1 = orienté, 0 = non orienté)
    int climat;
    int espace; //en km^2
    int sommetActuel;
    Arete *aretes;      // Tableau dynamique des arêtes
} Graphe;


void genererDot(const char *filename, Graphe *graphe);

void createGraphe(Graphe *graphe);

void appelGraphe(Graphe *graphe, char *argument);

void createListeAdjacence(Graphe *graphe);

void printGraph(Graphe graphe);

void destroyGraphe(Graphe *graphe);




#endif //REPPROJ_GRAPHE_H
