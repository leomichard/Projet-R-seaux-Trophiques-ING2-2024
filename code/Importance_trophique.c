#include "code/Importance_trophique.h"

void importanceTrophique(Graphe *graphe) {
    // On initialise les mesures de centralité
    CentralityMeasures *measures = malloc(graphe->ordre * sizeof(CentralityMeasures));
    for (int i = 0; i < graphe->ordre; i++) {
        measures[i].id = i;
        measures[i].degresEntrants = 0;
        measures[i].degresSortants = 0;
        measures[i].centraliteMediane = 0;
    }

    // On calcule la centralité radiale (les arcs entrants et sortants)
    for (int i = 0; i < graphe->ordre; i++) {
        ARC *arc = graphe->sommets[i].arcs;
        while (arc) {
            measures[arc->sommetArrivee].degresEntrants++;
            measures[arc->sommetDepart].degresSortants++;
            arc = arc->arcSuivant;
        }
    }

    // On calcule la centralité médiane
    for (int i = 0; i < graphe->ordre; i++) {
        int *listeDep = malloc(graphe->ordre * sizeof(int));
        for (int j = 0; j < graphe->ordre; j++) {
            listeDep[j] = 0;
        }
        getDependances(graphe, i, listeDep); // On récupère les dépendances de l'espèce i
        int nbDep = 0;
        for (int j = 0; j < graphe->ordre; j++) {
            if (listeDep[j] == 1) {
                nbDep++;
            }
        }
        measures[i].centraliteMediane = (double) nbDep / (graphe->ordre - 1);
        if (measures[i].centraliteMediane < 0.1) {
            strcpy(measures[i].Importance, "Faible");
        } else if (measures[i].centraliteMediane < 0.3) {
            strcpy(measures[i].Importance, "Moyenne");
        } else if (measures[i].centraliteMediane < 0.5) {
            strcpy(measures[i].Importance, "Forte");
        } else if (measures[i].centraliteMediane < 0.7) {
            strcpy(measures[i].Importance, "Forte++");
        } else {
            strcpy(measures[i].Importance, "Indispensable");
        }
        free(listeDep);
    }

    // On affiche les mesures de centralité
    printf("\n\n***Importance trophique***\n");
    printf("Arcs entrants\tArcs sortants\tCentralite Mediane\t Importance \t\t Espece\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%d\t\t%d\t\t%.3f\t\t\t%s\t\t\t%s\n", measures[i].degresEntrants, measures[i].degresSortants,
               measures[i].centraliteMediane, measures[i].Importance, graphe->sommets[i].espece->nom);
    }

    // On libère la mémoire
    free(measures);
}