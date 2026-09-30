#include "programme.h"


void initialisationDesEspeces(Programme *programme) {
    FILE *ifs = fopen("../filetxt/especes.txt", "r");
    if (!ifs) {
        printf("\n**Erreur d'allocation graphe**\nVerifiez le nom.txt\n");
        return;
    }
    //scan nombre d'especes
    int nbEspeces;
    fscanf(ifs, "%d", &nbEspeces);
    char temp[50];
    //scan id, nom, type, valeur nutritive, nb de portées par ans, nb d'individus par portée, domaine vital nécéssaire, besoin nutritif
    for (int i = 0; i < nbEspeces; ++i) {
        fscanf(ifs, "%d", &programme->Especes[i].id);
        fscanf(ifs, "%s", temp);
        strcpy(programme->Especes[i].nom, temp);
        fscanf(ifs, "%d", &programme->Especes[i].type);
        if (programme->Especes[i].type == 1) {
            strcpy(programme->Especes[i].couleur, "limegreen");
        } else if (programme->Especes[i].type == 2) {
            strcpy(programme->Especes[i].couleur, "darkcyan");
        } else if (programme->Especes[i].type == 3) {
            strcpy(programme->Especes[i].couleur, "saddlebrown");
        } else if (programme->Especes[i].type == 5) {
            strcpy(programme->Especes[i].couleur, "orangered");
        } else if (programme->Especes[i].type == 4) {
            strcpy(programme->Especes[i].couleur, "red4");
        } else if (programme->Especes[i].type == 6) {
            strcpy(programme->Especes[i].couleur, "orange1");
        }
        //scan valeur nutritive puis nb de portées par ans puis nb d'individus par portée puis domaine vital nécéssaire puis besoin nutritif
        fscanf(ifs, "%lf", &programme->Especes[i].valeurNutri);
        fscanf(ifs, "%f", &programme->Especes[i].TempsGest);
        fscanf(ifs, "%d", &programme->Especes[i].CapaciteGest);
        fscanf(ifs, "%f", &programme->Especes[i].domaineVital);
        fscanf(ifs, "%lf", &programme->Especes[i].besoinNutri);
    }
    fclose(ifs);
}


void createProgramme(Programme *programme) {
    programme->commandes = createCommandes();
    programme->graphe;
    programme->nbTourAFaire = 0;
    programme->nbTourActuel = 0;
    initialisationDesEspeces(programme); // On initialise les especes depuis le fichier especes.txt
}

void simulateTurn(Programme *programme) {
    printf("\n***Tour %d***\n", programme->nbTourActuel);
    //prompt_natural_disaster(&programme-> graphe);
    simulationEspece(&programme->graphe, programme->nbTourAFaire);
    if (programme->obs == 1) {
        programme->tab = realloc(programme->tab, (programme->nbTourActuel + 1) * sizeof(int));
        programme->tab[programme->nbTourActuel] = programme->graphe.sommets[programme->sommetObserve].nombre;
        printf("Nombre d'individus de l'espèce observée: %d\n", programme->tab[programme->nbTourActuel]);
    }

    programme->nbTourActuel++;
    programme->nbTourAFaire--;
}
