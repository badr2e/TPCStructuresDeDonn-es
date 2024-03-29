/*
    Documentation section
    @Project Gestion des horaires de trains
    @Program Description, Programme pour gérer les horaires de trains
*/

// Link section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un horaire de train
typedef struct {
    char ville_depart[50];
    char ville_arrivee[50];
    char heure_depart[10];
    char heure_arrivee[10];
    int distance;
} HoraireTrain;

// Structure pour une liste d'horaires de trains
typedef struct {
    HoraireTrain *horaires;
    int nb_horaires;
} ListeHorairesTrains;

// Function prototype declaration section
void ajouterHoraire(ListeHorairesTrains *liste, char *depart, char *arrivee, char *heure_dep, char *heure_arr, int distance);
void afficherTrainsDepart(ListeHorairesTrains liste, char *ville_depart);
float calculerVitesseMoyenne(HoraireTrain horaire);
void trajetVitesseMax(ListeHorairesTrains liste);
int comparerHeuresDepart(const void *a, const void *b);
void trierHorairesDepart(ListeHorairesTrains *liste);

// Main function
int main() {
    // Initialisation de la liste d'horaires de trains
    ListeHorairesTrains liste = {NULL, 0};

    // Exemple d'ajout de quelques horaires
    ajouterHoraire(&liste, "Lille", "Paris", "08h00", "08h59", 237);
    ajouterHoraire(&liste, "Lille", "Lyon", "07h00", "10h00", 709);
    ajouterHoraire(&liste, "Lille", "Calais", "15h19", "18h34", 110);
    ajouterHoraire(&liste, "Paris", "Marseille", "12h00", "18h00", 900);
    ajouterHoraire(&liste, "Lyon", "Marseille", "10h07", "15h01", 450);
    ajouterHoraire(&liste, "Lyon", "Marseille", "11h50", "17h00", 450);

    // Affichage des trains au départ de Lille
    afficherTrainsDepart(liste, "Lille");

    // Détermination du trajet avec la vitesse moyenne la plus élevée
    trajetVitesseMax(liste);

    // Tri des horaires par ordre croissant de l'heure de départ
    trierHorairesDepart(&liste);

    // Affichage des horaires triées
    printf("\nHoraires triés par ordre croissant de l'heure de départ :\n");
    for (int i = 0; i < liste.nb_horaires; i++) {
        // Copie de l'heure de départ
        char heure_dep_copy[10];
        strcpy(heure_dep_copy, liste.horaires[i].heure_depart);

        // Extraction des heures et des minutes
        int heure_dep = atoi(strtok(heure_dep_copy, "h"));
        int minute_dep = atoi(strtok(NULL, "h"));

        // Affichage des heures et des minutes extraites
        printf("De %s à %s, Départ: %02d:%02d, Arrivée: %s\n", liste.horaires[i].ville_depart,
            liste.horaires[i].ville_arrivee, heure_dep, minute_dep, liste.horaires[i].heure_arrivee);
    }


    // Libération de la mémoire allouée
    free(liste.horaires);

    return 0;
}

// Sub functions
void ajouterHoraire(ListeHorairesTrains *liste, char *depart, char *arrivee, char *heure_dep, char *heure_arr, int distance) {
    // Réallocation dynamique pour augmenter la taille de la liste
    liste->horaires = realloc(liste->horaires, (liste->nb_horaires + 1) * sizeof(HoraireTrain));
    if (liste->horaires == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Ajout des informations du nouvel horaire
    strcpy(liste->horaires[liste->nb_horaires].ville_depart, depart);
    strcpy(liste->horaires[liste->nb_horaires].ville_arrivee, arrivee);
    strcpy(liste->horaires[liste->nb_horaires].heure_depart, heure_dep);
    strcpy(liste->horaires[liste->nb_horaires].heure_arrivee, heure_arr);
    liste->horaires[liste->nb_horaires].distance = distance;

    // Incrément du nombre d'horaires dans la liste
    liste->nb_horaires++;
}

void afficherTrainsDepart(ListeHorairesTrains liste, char *ville_depart) {
    printf("Trains au départ de %s :\n", ville_depart);
    for (int i = 0; i < liste.nb_horaires; ++i) {
        if (strcmp(liste.horaires[i].ville_depart, ville_depart) == 0) {
            printf("Destination: %s, Heure de départ: %s, Heure d'arrivée: %s, Distance: %dkm\n",
                   liste.horaires[i].ville_arrivee, liste.horaires[i].heure_depart,
                   liste.horaires[i].heure_arrivee, liste.horaires[i].distance);
        }
    }
}

float calculerVitesseMoyenne(HoraireTrain horaire) {
    int heure_dep = atoi(strtok(horaire.heure_depart, "h"));
    int minute_dep = atoi(strtok(NULL, "h"));
    int heure_arr = atoi(strtok(horaire.heure_arrivee, "h"));
    int minute_arr = atoi(strtok(NULL, "h"));

    int duree_trajet = (heure_arr - heure_dep) * 60 + (minute_arr - minute_dep);
    float vitesse_moyenne = (float) horaire.distance / (duree_trajet / 60.0);

    return vitesse_moyenne;
}

void trajetVitesseMax(ListeHorairesTrains liste) {
    float vitesse_max = 0;
    int indice_trajet_max = -1;

    for (int i = 0; i < liste.nb_horaires; ++i) {
        float vitesse_actuelle = calculerVitesseMoyenne(liste.horaires[i]);
        if (vitesse_actuelle > vitesse_max) {
            vitesse_max = vitesse_actuelle;
            indice_trajet_max = i;
        }
    }

    if (indice_trajet_max != -1) {
        printf("Trajet avec la vitesse moyenne la plus élevée :\n");
        printf("De %s à %s\n", liste.horaires[indice_trajet_max].ville_depart,
               liste.horaires[indice_trajet_max].ville_arrivee);
        printf("Heure de départ: %s\n", liste.horaires[indice_trajet_max].heure_depart);
        printf("Heure d'arrivée: %s\n", liste.horaires[indice_trajet_max].heure_arrivee);
        printf("Vitesse moyenne: %.2f km/h\n", vitesse_max);
    } else {
        printf("Aucun trajet trouvé.\n");
    }
}

int comparerHeuresDepart(const void *a, const void *b) {
    HoraireTrain *horaireA = (HoraireTrain *) a;
    HoraireTrain *horaireB = (HoraireTrain *) b;

    // Copie des heures de départ pour éviter de modifier les données originales
    char heureDepA[10];
    char heureDepB[10];
    strcpy(heureDepA, horaireA->heure_depart);
    strcpy(heureDepB, horaireB->heure_depart);

    // Extraction des heures et des minutes pour la comparaison
    int heureA = atoi(strtok(heureDepA, "h"));
    int minuteA = atoi(strtok(NULL, "h"));
    int heureB = atoi(strtok(heureDepB, "h"));
    int minuteB = atoi(strtok(NULL, "h"));

    // Comparaison des heures
    if (heureA != heureB) {
        return heureA - heureB;
    } else {
        // Comparaison des minutes si les heures sont égales
        return minuteA - minuteB;
    }
}

void trierHorairesDepart(ListeHorairesTrains *liste) {
    qsort(liste->horaires, liste->nb_horaires, sizeof(HoraireTrain), comparerHeuresDepart);
}

