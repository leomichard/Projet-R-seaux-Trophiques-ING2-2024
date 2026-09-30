#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "especes.h"
#include "graphe.h"

float calculate_next_population_rk2(float Nt, float r, float K);

void update_population_calcs(Graphe *graphe);

void apply_natural_disaster(Graphe *graphe);

void prompt_natural_disaster(Graphe *graphe);

void prompt_human_disaster(Graphe *graphe);

void apply_human_disaster(Graphe *graphe);

void majPopulation(Graphe *graphe, int species_index);

void processChaineAlim(Graphe *graphe, int species_index);

void bfs_tranversal(Graphe *graphe);

void simulationEspece(Graphe *graphe, int steps);

void disaster_rapport_etat(Graphe *graphe);

#endif // SIMULATION_H
