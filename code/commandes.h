
#ifndef REPPROJ_COMMANDES_H
#define REPPROJ_COMMANDES_H

#include "windows.h"
#include "Importance_trophique.h"
#include "dot.h"
#include "connexite.h"
#include "symbiose.h"
#include "especes_speciales.h"
#include "simulation.h"
#include "complexite.h"

typedef struct Commande {
    char *commande;
    char *argument;
} Commande;

typedef struct Commandes {
    char *quitter; //fait
    char *aide; //fait
    char *naviguerSommet; // permet de naviguer à un sommet du graphe
    char *infoSommet; // permet d'afficher les informations d'un sommet
    char *appelGraphe; // permet d'appeler un graphe
    char *sim; // simuler un nombre donne de tour
    char *startobs; // permet de sauvegarder les donnees d'une espèce
    char *stopobs; // permet d'arreter l'observation d'une espèce et de sauvegarder le graphique creer
    char *modifierNB; // permet de modifier le nombre d'individus d'une espèce
    char *tutorial; // affiche le tutoriel
    char *detecterEspecesSpeciales; // detecte la presence d'especes speciales
    char *getEspeces; // affiche les especes présentes dans le graphe
    char *complexite; // affiche la complexite du graphe
    char *print; // affiche le graphe
} Commandes;

typedef struct Prog {
    Commandes commandes;
    Graphe graphe;
    espece Especes[100];
    int *tab; // tableau du nombre d'une espece sauvegarde à chaque tour
    int sommetObserve; // sommet qu'on observe et dont ont sauvegarde les donnees
    int obs;
    int nbTourActuel;
    int nbTourAFaire;
} Programme;

Commandes createCommandes();

void commandePrintHelp();

int commandeCreateGraph(Commandes commandes, Programme *programme, char *argument);

int commandeGetSommet(Commandes commandes, Programme *programme, char *argument);

int commandInfoSommet(Commandes commandes, Programme *programme, char *argument);

int commandeModifNB(Commandes commandes, Programme *programme, char *argument);

void commandeStartObs(Commandes commandes, Programme *programme, char *argument);

void commandeStopObs(Commandes commandes, Programme *programme, char *argument);

void commandGetInfosGraphe(Commandes commandes, Programme *programme);

int interpretCommand(Commandes commandes, Commande *commande, Programme *po);

int getNewCommand(Programme *programme);

void associerSommetEspeces(Graphe *graphe, espece especes[100], int nbEspeces);

void Color(int couleurDuTexte, int couleurDeFond);

void commandeLogoTrophique();

void calculate_and_print_centrality_measures(Graphe *graphe);

#endif //REPPROJ_COMMANDES_H
