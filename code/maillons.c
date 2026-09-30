#include "maillons.h"
#include "graphe.h"

int dfsCycle(Graphe *graphe, int sommet, int *visites, int *pileRecursion) {
    if (pileRecursion[sommet]) return 1;  // Cycle détecté
    if (visites[sommet]) return 0;   // Déjà visité, pas de cycle

    visites[sommet] = 1;
    pileRecursion[sommet] = 1;

    ARC *arc = graphe->sommets[sommet].arcs;
    while (arc) {
        if (dfsCycle(graphe, arc->sommetArrivee, visites, pileRecursion)) {
            return 1;  // Cycle trouvé
        }
        arc = arc->arcSuivant;
    }

    pileRecursion[sommet] = 0;  // Retour en arrière
    return 0;
}

// Fonction pour vérifier si le graphe contient un cycle
int contientCycle(Graphe *graphe) {
    int *visites = (int *) calloc(graphe->ordre, sizeof(int));
    int *pileRecursion = (int *) calloc(graphe->ordre, sizeof(int));  // Pile de récursion

    for (int i = 0; i < graphe->ordre; i++) {
        if (!visites[i] && dfsCycle(graphe, i, visites, pileRecursion)) {
            free(visites);
            free(pileRecursion);
            return 1;  // Le graphe contient un cycle
        }
    }

    free(visites);
    free(pileRecursion);
    return 0;  // Pas de cycle
}
