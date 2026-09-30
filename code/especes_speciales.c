#include "especes_speciales.h"
#include "graphe.h"

void detecterEspecesSpeciales(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        int aPredateur = 0;
        int sourcesNourriture = 0;
        int estAutosuffisante = 0;

        // Vérifier si l'espèce a des prédateurs (arcs entrants)
        for (int j = 0; j < graphe->ordre; j++) {
            ARC *arc = graphe->sommets[j].arcs;
            while (arc) {
                if (arc->sommetArrivee == i) {
                    aPredateur = 1;
                }
                if (arc->sommetDepart == i && arc->sommetArrivee == i) {
                    estAutosuffisante = 1;
                }
                arc = arc->arcSuivant;
            }
        }

        // Compter combien d'espèces l'espèce actuelle nourrit (arcs sortants)
        ARC *arc = graphe->sommets[i].arcs;
        while (arc) {
            sourcesNourriture++;
            arc = arc->arcSuivant;
        }

        // Vérifier si l'espèce est sans prédateurs
        if (!aPredateur) {
            printf("Espece sans predateurs detectee : %s\n", graphe->sommets[i].espece->nom);
        }

        // Vérifier si l'espèce est autosuffisante
        if (estAutosuffisante) {
            printf("Espece autosuffisante detectee : %s\n", graphe->sommets[i].espece->nom);
        }

        // Vérifier si l'espèce a une seule source d'alimentation
        if (sourcesNourriture == 1) {
            printf("Espece avec une seule source d'alimentation detectee : %s\n",  graphe->sommets[i].espece->nom);
            printf("Qui se nourrie de : %s\n\n", graphe->sommets[graphe->sommets[i].arcs->sommetArrivee].espece->nom);
        }
    }
}
