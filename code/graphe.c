#include "graphe.h"

void destroyGraphe(Graphe *graphe) {
    for (int i = 0; i < graphe->ordre; i++) {
        ARC *arc = graphe->sommets[i].arcs;
        while (arc) {
            ARC *temp = arc;
            arc = arc->arcSuivant;
            free(temp);
        }
    }
    free(graphe->sommets);
    free(graphe);
}


void CreerArete(Sommet *sommet, int s1, int s2, int pond) { // Fonction modifiée du TP 3 de théorie des graphes
    if (sommet[s1].arcs == NULL) {
        ARC *Newarc = malloc(sizeof(ARC));
        Newarc->sommetDepart = s1;
        Newarc->sommetArrivee = s2;
        Newarc->valeur = pond;
        Newarc->arcSuivant = NULL;
        sommet[s1].arcs = Newarc;
        return;
    } else {
        ARC *temp = sommet[s1].arcs;
        while (temp->arcSuivant != NULL) {
            temp = temp->arcSuivant;
        }
        ARC *Newarc = malloc(sizeof(ARC));
        Newarc->sommetDepart = s1;
        Newarc->sommetArrivee = s2;
        Newarc->valeur = pond;
        Newarc->arcSuivant = NULL;

        if (temp->sommetArrivee > s2) {
            Newarc->arcSuivant = temp->arcSuivant;
            Newarc->sommetArrivee = temp->sommetArrivee;
            temp->sommetArrivee = s2;
            temp->arcSuivant = Newarc;
            return;
        }

        temp->arcSuivant = Newarc;
        return;
    }
}

void createListeAdjacence(Graphe *graphe) {
    int tailleLocale = 0;
    for (int i = 0; i < graphe->ordre; i++) { // On parcourt tous les sommets
        ARC *arc = graphe->sommets[i].arcs;
        printf("Sommet %d : ", i);
        while (arc) {
            printf("%d(%d) ", arc->sommetArrivee, arc->valeur); // On affiche les arcs
            graphe->aretes[tailleLocale].depart = i; // On ajoute les arcs dans le tableau d'arcs
            graphe->aretes[tailleLocale].arrivee = arc->sommetArrivee; // On ajoute les arcs dans le tableau d'arcs
            graphe->aretes[tailleLocale].poids = arc->valeur; // On ajoute les arcs dans le tableau d'arcs
            tailleLocale++;
            arc = arc->arcSuivant; // On passe à l'arc suivant
        }
        printf("\n");
    }
}

void createGraphe(Graphe *graphe) { // Fonction modifiée du TP 3 de théorie des graphes
    if (graphe == NULL) {
        printf("\n**Erreur de malloc pour le graphe**t\n");
        return;
    }

    graphe->sommets = malloc(graphe->ordre * sizeof(Sommet));
    graphe->aretes = malloc(graphe->taille * sizeof(Arete));

    for (int i = 0; i < graphe->ordre; i++) {
        graphe->sommets[i].id = i;
        graphe->sommets[i].arcs = NULL;
    }
}

void printGraph(Graphe graphe) {
    printf("\n\nGraphe de %d sommets\n\n", graphe.ordre);
    for (int i = 0; i < graphe.ordre; i++) {
        ARC *arc = graphe.sommets[i].arcs;
        printf("Sommet %d, %s : ", i, graphe.sommets[i].espece->nom);
        while (arc) {
            printf("%d (%s,pond :%d%) ", arc->sommetArrivee, graphe.sommets[arc->sommetArrivee].espece->nom,
                   arc->valeur);
            arc = arc->arcSuivant;
        }
        printf("\n");
    }

    //Niveau trophique maximum:
    int max = 0;
    for (int i = 0; i < graphe.ordre; i++) {
        if (graphe.sommets[i].espece->type > max) {
            max = graphe.sommets[i].espece->type;
        }
    }
    printf("Niveau trophique maximum : %d\n", max);
    genererDot("../dot/ReseauProgramme.dot", &graphe); // On génère le dot
}

void appelGraphe(Graphe *graphe, char *argument) {
    printf("Appel du graphe %s\n", argument);

    FILE *ifs = fopen(argument, "r");
    int taille, orientation, ordre, s1, s2, troph, id, espace, etat;
    long pond;

    if (!ifs) {
        printf("\n**Erreur d'allocation graphe**\nVerifiez le nom.txt\n");
        return;
    }

    fscanf(ifs, "%d", &ordre);
    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    graphe->sommetActuel = -1;
    graphe->ordre = ordre;
    graphe->taille = taille;
    graphe->orientation = orientation;
    createGraphe(graphe);

    for (int i = 0; i < taille; ++i) {
        fscanf(ifs, "%d%d%d", &s1, &s2, &pond);
        CreerArete(graphe->sommets, s1, s2, pond);

        if (!orientation)
            CreerArete(graphe->sommets, s2, s1, pond);
    }

    for (int i = 0; i < ordre; ++i) {
        fscanf(ifs, "%d%ld%d", &troph, &pond, &id);
        graphe->sommets[i].etat = troph;
        graphe->sommets[i].nombre = pond;
        graphe->sommets[i].id = id;
    }
    fscanf(ifs, "%d%d", &espace, &etat);
    graphe->espace = espace;
    graphe->etat = etat;

    createListeAdjacence(graphe);
    printf("Graphe cree\n");
}
