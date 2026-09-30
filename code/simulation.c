#include "simulation.h"

// Fonction pour calculer la population à l'etape suivante en utilisant la methode RK2
float calculate_next_population_rk2(float Nt, float r, float K) {
    float k1 = r * Nt * (1 - Nt / K);
    float k2 = r * (Nt + 0.5 * k1) * (1 - (Nt + 0.5 * k1) / K);
    return Nt + k2;
}

//pas utiliser car RK2 trop complexe avec n'aux txt de nombre population
void update_population_calcs(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        espece *current_species = graphe->sommets[i].espece;
        float Nt = graphe->sommets[i].nombre; // en gr
        float r = current_species->valeurNutri; // en gr
        float K = current_species->domaineVital; // en gr

        // Mettre à jour les calculs de population en utilisant la methode RK2
        float new_population = calculate_next_population_rk2(Nt, r, K);
        graphe->sommets[i].nombre = new_population > 0 ? new_population : 0;
    }
}

void apply_natural_disaster(Graphe *graphe) {
    srand(time(NULL));

    for (int i = 0; i < graphe->ordre; i++) {

        double reduction_percentage =
                (rand() % 16 + 5) / 100.0; //hasard avec time entre 0 a 16 puis +5 pour que minimum soit 5

        graphe->sommets[i].nombre *= (1 - reduction_percentage);

        if (graphe->sommets[i].nombre < 0) {
            graphe->sommets[i].nombre = 0;
        }
    }
}

void apply_human_disaster(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        espece *current_species = graphe->sommets[i].espece;

        current_species->domaineVital *= 0.95; //-5%
        current_species->valeurNutri *= 0.90; //-10%
        graphe->sommets[i].nombre *= 0.92; //-8%

        if (graphe->sommets[i].nombre < 0) {
            graphe->sommets[i].nombre = 0;
        }
    }
    graphe->etat -= 2; //-2
}

void prompt_natural_disaster(Graphe *graphe) {
    char response;
    printf("Voulez-vous creer une catastrophe naturelle ? (Y/N) : ");
    scanf(" %c", &response);

    if (response == 'y' || response == 'Y') {
        apply_natural_disaster(graphe);
        printf("Effet catastrophe naturel mis en etat. La population a etait reduit entre 5 et 20%. \n"); //sans accent car console aime pas
    } else {
        printf("Aucune catastrophe naturelle appliquee.\n");
    }
}

void prompt_human_disaster(Graphe *graphe) {
    char response;
    printf("Voulez-vous creer une catastrophe humaine ? (Y/N) : ");
    scanf(" %c", &response);

    if (response == 'y' || response == 'Y') {
        apply_human_disaster(graphe);
        printf("Effet catastrophe humaine mis en etat. La population a etait reduit de 8%, le nombre total de chaque espece possible sur le territoire reduit de 5%, \n "
               "et la valeur nutritionel apporter par chaque reduit de 10%. Finalement le niveau du territoire est diminue de 2.\n"); //sans accent car console aime pas
    } else {
        printf("Aucune catastrophe humaine appliquee.\n");
    }
}

void disaster_rapport_etat(Graphe *graphe) { // avec mauvais etat d'environnement alors consequences régulières
    srand(time(NULL));
    for (int i = 0; i < graphe->ordre; i++) {

        if (graphe->etat < 2) {
            if (rand() % 2 == 0) {
                apply_natural_disaster(graphe);
            } else {
                apply_human_disaster(graphe);
            }
        } else if (graphe->etat < 4) {
            apply_natural_disaster(graphe);
        }
    }
}


void majPopulation(Graphe *graphe, int species_index) {
    espece *current_species = graphe->sommets[species_index].espece;
    Sommet *current_sommet = &graphe->sommets[species_index];

    current_sommet->nombre += current_species->CapaciteGest * current_species->TempsGest;

    if (current_sommet->nombre > current_species->domaineVital) {
        current_sommet->nombre = current_species->domaineVital;
    }
    if (current_sommet->nombre < 0) {
        current_sommet->nombre = 0;
    }
}

void processChaineAlim(Graphe *graphe, int species_index) {
    espece *predateur = graphe->sommets[species_index].espece;
    Sommet *sommetPredateur = &graphe->sommets[species_index];

    for (ARC *arc = sommetPredateur->arcs; arc != NULL; arc = arc->arcSuivant) {
        int prey_index = arc->sommetArrivee;
        espece *prey = graphe->sommets[prey_index].espece;
        Sommet *prey_sommet = &graphe->sommets[prey_index];

        float amount_needed = predateur->besoinNutri * (arc->valeur / 100.0); // pourcentage necessaire
        float amount_available = prey->valeurNutri * prey_sommet->nombre;

        if (amount_available >= amount_needed) {
            prey_sommet->nombre -= amount_needed / prey->valeurNutri;
            sommetPredateur->nombre += amount_needed / predateur->valeurNutri;
        } else {
            sommetPredateur->nombre -= (amount_needed - amount_available) / predateur->valeurNutri;
            prey_sommet->nombre = 0;
        }

        if (prey_sommet->nombre == 0) {
            sommetPredateur->nombre -= predateur->besoinNutri * (arc->valeur / 100.0) / predateur->valeurNutri;
            //perte vie predateur si prey a 0
        }

        if (sommetPredateur->nombre > predateur->domaineVital) {
            sommetPredateur->nombre = predateur->domaineVital;
        }
        if (sommetPredateur->nombre < 0) {
            sommetPredateur->nombre = 0;
        }
    }
}

// BFS traversal to simulate birth and eating
void bfs_tranversal(Graphe *graphe) {
    bool *visited = (bool *) malloc(graphe->ordre * sizeof(bool));
    for (int i = 0; i < graphe->ordre; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < graphe->ordre; i++) {
        if (!visited[i]) {
            // BFS queue
            int queue[graphe->ordre];
            int front = 0, rear = 0;
            queue[rear++] = i;
            visited[i] = true;

            while (front < rear) {
                int current = queue[front++];
                majPopulation(graphe, current);
                processChaineAlim(graphe, current);

                for (ARC *arc = graphe->sommets[current].arcs; arc != NULL; arc = arc->arcSuivant) {
                    int neighbor = arc->sommetArrivee;
                    if (!visited[neighbor]) {
                        queue[rear++] = neighbor;
                        visited[neighbor] = true;
                    }
                }
            }
        }
    }

    free(visited);
}

void simulationEspece(Graphe *graphe, int steps) {
    for (int t = 0; t < steps; t++) {
        printf("***Tour %d***\n", t);
        bfs_tranversal(graphe);

        prompt_natural_disaster(graphe);
        prompt_human_disaster(graphe);
        disaster_rapport_etat(graphe);

        for (int i = 0; i < graphe->ordre; i++) {
            printf("Species %s population e l'etape %d: %ld\n %d \n", graphe->sommets[i].espece->nom, t, graphe->sommets[i].nombre, graphe->etat);
        }
    }
}