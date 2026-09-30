

#ifndef REPPROJ_ESPECES_H
#define REPPROJ_ESPECES_H

typedef struct espece {
    char nom[25];
    char couleur[30];
    int id;
    int type;
    float TempsGest;
    int CapaciteGest;
    double valeurNutri;
    double besoinNutri;
    float domaineVital;
} espece;

#endif //REPPROJ_ESPECES_H
