#include "connexite.h"
#include "graphe.h"

int dfs(Graphe *graphe, int sommet, int *visites) {
    visites[sommet] = 1;
    if (!graphe->sommets[sommet].arcs) {
        return 1;
    }
    ARC *arc = graphe->sommets[sommet].arcs;
    while (arc) {
        if (!visites[arc->sommetArrivee]) {
            dfs(graphe, arc->sommetArrivee, visites);
        }
        arc = arc->arcSuivant;
    }
    return 1;
}

// Fonction pour vérifier la connexité du graphe
int estConnecte(Graphe *graphe) {
    int *visites = (int *) calloc(graphe->ordre, sizeof(int));
    dfs(graphe, 0, visites);  // On commence le DFS à partir du premier sommet

    // Vérification si tous les sommets ont été visités
    for (int i = 0; i < graphe->ordre; i++) {
        if (!visites[i]) {
            free(visites);
            return 0;  // Le graphe n'est pas connecté
        }
    }

    free(visites);
    return 1;  // Le graphe est connecté
}