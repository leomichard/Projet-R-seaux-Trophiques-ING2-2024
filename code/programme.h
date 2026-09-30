#ifndef REPPROJ_PROGRAMME_H
#define REPPROJ_PROGRAMME_H

#include "commandes.h"

void createProgramme(Programme *programme);

void initialisationDesEspeces(Programme *programme);

void simulateTurn(Programme *programme);

void simulationEspece(Graphe *graphe, int steps);
void prompt_natural_disaster(Graphe *graphe);

#endif // REPPROJ_PROGRAMME_H
