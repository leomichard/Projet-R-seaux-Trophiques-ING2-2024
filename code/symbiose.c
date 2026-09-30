#include "symbiose.h"
#include "commandes.h"
#include "graphe.h"

void detecterSymbiose(Graphe *graphe) {

    for (int i = 0; i < graphe->ordre; i++) {

        if (graphe->sommets[i].espece == NULL) {
            continue;
        }
        ARC *arc = graphe->sommets[i].arcs;

        while (arc) {

            // Verification de l'existence d'un arc inverse du predateur vers la proie

            ARC *arcInverse = graphe->sommets[arc->sommetArrivee].arcs;

            while (arcInverse) {

                if (arcInverse->sommetArrivee == i) {

                    printf("Symbiose detectee entre les espèces %d et %d\n", i, arc->sommetArrivee);

                    break;

                }

                arcInverse = arcInverse->arcSuivant;

            }

            arc = arc->arcSuivant;

        }

    }

}
