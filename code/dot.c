#include <code/dot.h>
#include "code/graphe.h"

void genererDot(const char *filename, Graphe *graphe) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de la création du fichier .dot");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "digraph Graphe {\n");
    fprintf(file, "graph [rankdir=TB]; // Orientation de haut en bas\n");


    // Ajouter les sommets avec leurs couleurs et populations
    for (int i = 0; i < graphe->ordre; i++) {
        fprintf(file, "    %d [label=\"%s\\nPopulation: %d\", color=%s, style=filled];\n",
                i, graphe->sommets[i].espece->nom, graphe->sommets[i].nombre, graphe->sommets[i].espece->couleur);
    }

    // Ajouter les arêtes avec les pondérations
    for (int i = 0; i < graphe->taille; i++) {
        fprintf(file, "    %d -> %d [label=\"%d%%\"];\n",
                graphe->aretes[i].depart, graphe->aretes[i].arrivee, graphe->aretes[i].poids);
    }
    fprintf(file, "// nœud pour la legende\n"
                  "    legend [\n"
                  "    label=\"Couleurs :\n"
                  "    Producteurs primaires       vert\n"
                  "    Consommateurs primaires     bleu\n"
                  "    Predateurs primaires        orange\n"
                  "    Predateurs intermediaires   rouge/orange\n"
                  "    Predateurs finaux           rouge\n"
                  "    Consommateurs/proies        marron\t\",\n"
                  "    shape=note,\n"
                  "    color=grey,\n"
                  "    fontsize=10,\n"
                  "    fontname =\"Helvetica-Bold\""

                  "\n"
                  "    width=0.1, // Largeur \n"
                  "    height=0.1, // Hauteur \n"
                  "    margin=0.14 // Marges internes (reduction)\n"
                  "    ];\n");

    fprintf(file, "}\n");
    fclose(file);

}



