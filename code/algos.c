#include "algos.h"
#include "string.h"

void getDependances(Graphe *graphe, int sommet, int *listeDep) {
    // On parcourt tous les sommets et arcs du graphes pour trouver les especes qui dépendent directement et indirectement du sommet
    listeDep[sommet] = 1;
    for (int i = 0; i < graphe->ordre; i++) {
        if (listeDep[i] == 0) {
            ARC *arc = graphe->sommets[i].arcs;
            while (arc != NULL) {
                if (arc->sommetArrivee == sommet) {
                    listeDep[arc->sommetDepart] = 1;
                    getDependances(graphe, arc->sommetDepart, listeDep);
                }
                arc = arc->arcSuivant;
            }
        }
    }
}
