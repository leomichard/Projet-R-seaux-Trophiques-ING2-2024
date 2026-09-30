#include "code/complexite.h"

float calculerDensite(Graphe *graphe) {
    int maxAretes = graphe->ordre * (graphe->ordre - 1); // Pour graphe oriente
    return (float) graphe->taille / maxAretes;
}

float calculerDegreMoyen(Graphe *graphe) {
    return (float) (graphe->taille) * 2 / graphe->ordre;
}

void afficherSuccesseurs(Graphe *graphe) {
    printf("\n\nListe des successeurs pour chaque sommet :\n\n");

    // Parcourir tous les sommets
    for (int i = 0; i < graphe->ordre; i++) {
        Sommet *sommet = &graphe->sommets[i];
        printf("Sommet %d (%s) : ", sommet->id, sommet->espece->nom);

        ARC *arc = sommet->arcs;
        int successeur = 0;

        // Parcourir tous les arcs sortants de ce sommet
        while (arc != NULL) {
            printf("%s ", graphe->sommets[arc->sommetArrivee].espece->nom);
            successeur = 1;
            arc = arc->arcSuivant;
        }

        if (!successeur) {
            printf("Aucun successeur");
        }

        printf("\n\n");
    }
}

void afficherPredecesseurs(Graphe *graphe) {
    printf("\nListe des predecesseurs pour chaque sommet :\n\n");

    // Parcourir tous les sommets du graphe (cibles des arcs)
    for (int i = 0; i < graphe->ordre; i++) {
        Sommet *sommet = &graphe->sommets[i];
        printf("Sommet %d (%s) : ", sommet->id, sommet->espece->nom); // Affichage avec ID 1-based

        int predecesseur = 0;

        // Parcourir tous les arcs de chaque sommet pour identifier les predecesseurs
        for (int j = 0; j < graphe->ordre; j++) {
            Sommet *autreSommet = &graphe->sommets[j];
            ARC *arc = autreSommet->arcs;

            // Parcourir la liste chaînee des arcs sortants du sommet j
            while (arc != NULL) {
                if (arc->sommetArrivee == sommet->id) {
                    printf("%s ", autreSommet->espece->nom); // Ajouter le nom du predecesseur
                    predecesseur = 1;
                }
                arc = arc->arcSuivant;
            }
        }

        if (!predecesseur) {
            printf("Aucun predecesseur");
        }

        printf("\n\n");
    }
}


void complexite(Graphe graphe) {


    // Calculer la densite
    float densite = calculerDensite(&graphe);
    printf("\nDensite du graphe (oriente) : %.2f\n", densite);

    // Calculer le degre moyen
    float degre_moyen = calculerDegreMoyen(&graphe);
    printf("\nDegre moyen du graphe : %.2f\n", degre_moyen);

    //ordre du graphe
    printf("\nNombre de sommets du graphe : %d\n", graphe.ordre);

    //la taille du graphe
    printf("\nTaille du graphe : %d\n", graphe.taille);


    // Calculer et afficher les predecesseurs
    afficherPredecesseurs(&graphe);

    // Calculer et afficher les successeurs
    afficherSuccesseurs(&graphe);

    // Liberer la memoire
    free(graphe.aretes);
}

