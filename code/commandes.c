#include "commandes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Commandes createCommandes() {
    Commandes commandes;
    commandes.quitter = "/exit";
    commandes.aide = "/help";
    commandes.naviguerSommet = "/getsommet";
    commandes.appelGraphe = "/callgraph";
    commandes.modifierNB = "/modifynb";
    commandes.infoSommet = "/infoespece";
    commandes.sim = "/sim";
    commandes.startobs = "/startobs";
    commandes.stopobs = "/stopobs";
    commandes.tutorial = "/tuto";
    commandes.detecterEspecesSpeciales = "/detecterespeces";
    commandes.getEspeces = "/getespeces";
    commandes.complexite = "/complexite";
    commandes.print = "/print";
    return commandes;
}

void associerSommetEspeces(Graphe *graphe, espece especes[100], int nbEspeces) {
    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < nbEspeces; j++) {
            if (graphe->sommets[i].id == especes[j].id) {
                graphe->sommets[i].espece = &especes[j];
                printf("Sommet %d associe a l'espece %s\n", i, especes[j].nom);
                break;
            }
        }
    }
}

int interpreterCommande(Commandes commandes, Commande *commande, Programme *programme) {
    Graphe *graphe = &programme->graphe;
    printf("\n");
    if (strcmp(commande->commande, commandes.aide) == 0) { // Si la commande est /help
        commandePrintHelp(commandes);
    } else if (strcmp(commande->commande, commandes.appelGraphe) == 0) { // Si la commande est /callgraph
        commandeCreateGraph(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.quitter) == 0) { // Si la commande est /exit
        return 0;
    } else if (strcmp(commande->commande, commandes.naviguerSommet) == 0) { // Si la commande est /getsommet
        commandeGetSommet(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.modifierNB) == 0) { // Si la commande est /modifynb
        commandeModifNB(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.infoSommet) == 0) { // Si la commande est /infoespece
        return commandInfoSommet(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.sim) == 0) { //
        int nbTours = atoi(commande->argument);
        if (nbTours < 0) {
            printf("\n**Nombre de tours invalide**\n");
            return 1;
        }
        programme->nbTourAFaire = nbTours;
        printf("\n***Simulation de %d tours***\n", nbTours);

    } else if (strcmp(commande->commande, commandes.startobs) == 0) { // Si la commande est /startobs
        commandeStartObs(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.stopobs) == 0) {
        commandeStopObs(commandes, programme, commande->argument);
    } else if (strcmp(commande->commande, commandes.tutorial) == 0) {
        //Ecrit un tutoriel pour charger le graphe et simuler
        printf("**Tutoriel**\n");
        printf("Pour charger un graphe, utilisez la commande /callgraph(nomdufichier) --Pour les test, le nom est graphtest.txt\n");
        // mettre en observation une espèce (/startobs(nom))
        printf("Pour mettre en observation une espece, utilisez la commande /startobs(numero du sommet) --On mettra directement le nom de l'espece quand le programme sera pret\n");
        // simuler un nb de tours donné
        printf("Pour simuler un population de tours, utilisez la commande /sim(nbtours)\n");
        // arreter l'observation et creer le graphique
        printf("Pour arreter l'observation et creer le graphique, utilisez la commande /stopobs\n");


    } else if (strcmp(commande->commande, commandes.getEspeces) == 0) {
        for (int i = 0; i < graphe->ordre; i++) {
            if (programme->graphe.sommets[i].espece != NULL) {
                printf("%s\n", programme->graphe.sommets[i].espece->nom);
            }
        }
    } else if (strcmp(commande->commande, commandes.detecterEspecesSpeciales) == 0) {
        detecterEspecesSpeciales(graphe);
    } else if (strcmp(commande->commande, commandes.complexite) == 0) {
        complexite(programme->graphe);
        importanceTrophique(graphe);
    } else if (strcmp(commande->commande, commandes.print) == 0) {
        printGraph(programme->graphe);
    } else {
        printf("Commande erronee. /help pour de l'aide\n");
    }

    return 1;
}

int getNewCommand(Programme *programme) {
    Commande Commande; // Commande à interpreter
    char commande[100];
    char argument[100];
    char texte[100];
    printf("\n\n--: ");
    scanf("%s", texte); // On récupère la commande de l'utilisateur


    if (texte[0] != '/') { // Si la commande ne commence pas par un "/"
        printf("Commande non reconnue. /help pour de l'aide\n");
        return 1;
    } else {

        // copier le texte dans commande jusqu'au prochain "("
        int i = 0;
        while (texte[i] != '(' && texte[i] != '\0') {
            commande[i] = texte[i];
            i++;
        }
        commande[i] = '\0';
        // copier l'argument entre les parenthèses
        if (texte[i] == '(') {
            i++;
            int j = 0;
            while (texte[i] != ')' && texte[i] != '\0') {
                argument[j] = texte[i];
                i++;
                j++;
            }
            argument[j] = '\0';
        } else {
            argument[0] = '\0';
        }
    }

    Commande.commande = commande;
    Commande.argument = argument;

    return interpreterCommande(programme->commandes, &Commande, programme); // On interprète la commande
}

void commandePrintHelp() {
    printf("\nPour ecrire une commande : /commande(argument) \n");
    printf("***Liste des commandes***\n");
    printf("/help: afficher l'aide\n");
    printf("/exit: quitter le programme\n");
    printf("/tuto: affiche le tutoriel\n");
    printf("/callgraph(nomgraphe.txt): appel un grape a charger\n");
    printf("/print: affiche le graphe\n");
    printf("/detecterespeces: detecte les especes speciales\n");
    printf("/getespeces: affiche les especes presentes dans le graphe\n");
    printf("/getsommet(nomEspece): on se place au niveau d'un sommet specifique\n");
    printf("/modifynb(nb): modifier le population d'individus d'une espece\n");
    printf("/infoespece(Espece): affiche les infos notables de cette especes dans le reseau\n");
    printf("/sim(nb): simuler un population donne de tour\n");
    printf("/startobs(nomEspece): permet de sauvegarder les donnees d'une espece\n");
    printf("/stopobs(nomEspece): permet d'arreter l'observation d'une espece et de sauvegarder le graphique cree\n");
    printf("/complexite: pour afficher la complexite du graphe en cours d'etude\n");
    printf("\n");
}

void commandeLogoTrophique() {
    Color(5, 0);
    printf(" _____                _     _                     \n"
           "|_   _| __ ___  _ __ | |__ (_) ___   _____  _____ \n"
           "  | || '__/ _ \\| '_ \\| '_ \\| |/ __| / _ \\ \\/ / _ \\\n"
           "  | || | | (_) | |_) | | | | | (__ |  __/>  <  __/\n"
           "  |_||_|  \\___/| .__/|_| |_|_|\\___(_)___/_/\\_\\___|\n"
           "               |_|                                ");
    Color(10, 0);
}

int commandeCreateGraph(Commandes commandes, Programme *programme, char *argument) {
    destroyGraphe(&programme->graphe); // On détruit le graphe actuel
    char temp[100] = "../filetxt/";
    strcat(temp, argument); // On concatène le chemin du fichier avec le nom du fichier
    printf("Chargement du graphe %s\n", temp);
    appelGraphe(&programme->graphe, temp); // On charge le graphe
    associerSommetEspeces(&programme->graphe, programme->Especes, 100); // On associe les sommets aux especes
    genererDot("../dot/ReseauProgramme.dot", &programme->graphe); // On génère le dot
    printf("Nouveau fichier .dot genere avec succes\n");
    printGraph(programme->graphe); // On affiche le graphe
    return 1;

}

int commandeGetSommet(Commandes commandes, Programme *programme, char *argument) {
    for (int i = 0; i < programme->graphe.ordre; i++) {
        if (programme->graphe.sommets[i].espece != NULL) {
            if (strcmp(programme->graphe.sommets[i].espece->nom, argument) == 0) {
                printf("Sommet actuel : %s\n", programme->graphe.sommets[i].espece->nom);
                programme->graphe.sommetActuel = i;
                return 1;
            }
        }
    }
}

int commandeModifNB(Commandes commandes, Programme *programme, char *argument) {
    Graphe *graphe = &programme->graphe;
    if (graphe->sommetActuel != -1) {
        int nb = atoi(argument);
        if (nb < -graphe->sommets[graphe->sommetActuel].nombre) {
            printf("sommet : %d", nb);
            printf("\n**Nombre invalide, veuillez reessayer**\n");
            return 1;
        }
        graphe->sommets[graphe->sommetActuel].nombre += nb;
        printf("Nombre d'individus de l'espece %s : %d\n", graphe->sommets[graphe->sommetActuel].espece->nom,
               graphe->sommets[graphe->sommetActuel].nombre);
    } else {
        printf("\n**Sommet actuel indefini** (Utilisez /getsommet(nomEspece)\n");
    }
}

void commandeStartObs(Commandes commandes, Programme *programme, char *argument) {
    if (!programme->graphe.sommets) {
        printf("\n**Aucun graphe charge, veuillez en charger un.**\n");
        return;
    }
    for (int i = 0; i < programme->graphe.ordre; i++) {
        if (programme->graphe.sommets[i].espece != NULL) {
            if (strcmp(programme->graphe.sommets[i].espece->nom, argument) == 0) {
                printf("\n**Observation de l'espece %s commencee**\n", argument);
                programme->sommetObserve = i;
                programme->tab = malloc(1 * sizeof(int));
                programme->obs = 1;
                programme->nbTourActuel = 0;
                return;
            }
        }
    }
}

void commandeStopObs(Commandes commandes, Programme *programme, char *argument) {
    if (!programme->obs) {
        printf("\n**Aucune observation en cours**\n");
        return;
    }
    printf("\n**Observation de l'espece %s arretee**\n", argument);
    programme->obs = 0;

    printf("\n**Creation de la data....**\n");
    FILE *f = fopen("../data.txt", "w");
    if (f == NULL) {
        printf("**Erreur lors de la creation du fichier de data**\n");
        return;
    }

    for (int i = 0; i < programme->nbTourActuel; i++) {
        fprintf(f, "%d %d\n", i, programme->tab[i]);
    }
    programme->nbTourActuel = 0;
    fclose(f);

    printf("\n**Creation du graphique....**\n");
    const char *command = "cd .. && gnuplot graphique.gp";
    int status = system(command);

    if (status == 0) {
        printf("**Graphique cree dans le repertoire**\n");
    } else {
        printf("**Erreur lors de la creation du graphique**\n");
    }
    programme->tab = realloc(programme->tab, 1 * sizeof(int));
}

int commandInfoSommet(Commandes commandes, Programme *programme, char *argument) {
    Graphe *graphe = &programme->graphe;
    int sommet = graphe->sommetActuel;
    if (sommet < 0 || sommet > graphe->ordre - 1) {
        printf("sommet : %d", sommet);
        printf("\n**Sommet indefini ou inexistant**\n");
        return 1;
    } else {
        int listeDep[graphe->ordre]; // liste des sommets enregistrés
        for (int i = 0; i < graphe->ordre; i++) {
            listeDep[i] = 0;
        }
        printf("%s Depend des especes suivantes :\n", graphe->sommets[sommet].espece->nom);
        getDependances(graphe, sommet, listeDep);
        int nbDep = 0;
        for (int i = 0; i < graphe->ordre; i++) {
            if (listeDep[i] == 1) {
                printf("%s\n", graphe->sommets[i].espece->nom);
                nbDep++;
            }
        }
        printf("Nombre d'especes dependantes : %d\n", nbDep);
        printf("\n Niveau trophique de l'espece: %d\n", graphe->sommets[sommet].espece->type);
        printf("Nombre d'individus de l'espece: %d\n", graphe->sommets[sommet].nombre);
    }
}

void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}