#include "code/programme.h"
#include "code/dot.h"



int main() {
    commandeLogoTrophique(); // Affiche le logo
    commandePrintHelp(); // Affiche le tuto
    Color(15, 0);

    Programme programme = {0};
    createProgramme(&programme); // On initialise le programme
    int varBoucle = 1;


    while (varBoucle) {

        varBoucle = getNewCommand(&programme); // On récupère la commande de l'utilisateur

        while (programme.nbTourAFaire > 0) { // Si ya une simulation à faire
            simulateTurn(&programme); // On simule un tour
        }
    }

    //on libère la mémoire
    free(programme.tab);
    destroyGraphe(&programme.graphe);
    return 0;
}
