
#ifndef REPPROJ_COMPLEXITE_H
#define REPPROJ_COMPLEXITE_H

#include "code/graphe.h"

void complexite(Graphe graphe);

float calculerDegreMoyen(Graphe *graphe);

float calculerDensite(Graphe *graphe);

void afficherPredecesseurs(Graphe *graphe);

void afficherSuccesseurs(Graphe *graphe);

//void afficherPredecesseurs(Graphe* graphe, int idSommetCible, FILE* fichierSortie);
#endif //REPPROJ_COMPLEXITE_H
