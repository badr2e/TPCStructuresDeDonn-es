#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "elmourabitlisteint.h"

int menu()
{
    int choix = 0;
    printf("1 Creer une liste d'entiers compris entre 0 et 20 de taille aleatoire comprise entre 1 et 20\n"
        "2 Ajouter un élément entier aléatoire (compris entre 0 et 20) en tête de liste\n"
        "3 Inserer un élément entier aléatoire dans sa place dans la liste suivant l'ordre croissant des premiers éléments\n"
        "4 Supprimer l'élément de tête\n"
        "5 Supprimer tous les maillons d'une valeur donnee\n"
        "6 Detruire liste\n"
        "7 Sauver la liste courante en binaire dans le fichier \"saveliste.bin\"\n"
        "8 Charger une liste depuis le fichier \"savelist.bin\"\n");

    scanf("%d", &choix);
    rewind(stdin);

    return choix;
}


int main()
{
    maillon_int* premier = NULL;
    maillon_int* nouveau;
    int fin = 0;
    int i, nb;

    srand((unsigned)time(NULL));
    while (!fin) {
        i = menu();
        switch (i) {

        case 1: // Creer une liste de taille aleatoire
            detruire_liste(&premier); // On détuit la liste existante avant de créer une nouvelle
            nb = rand() % 20 + 1; // Taille aléatoire entre 1 et 20
            for (int j = 0; j < nb; j++) {
                nouveau = init_elt();
                ajout_tete_v2(&premier, nouveau);
            }
            parcourir(premier); // Afficher la nouvelle liste
            break;

        case 2: // Ajouter
            nouveau = init_elt(); // Créer un nouveau maillon
            ajout_tete_v2(&premier, nouveau);
            parcourir(premier);
            break;

        case 3: // Inserer (ordre croissant)
            nouveau = init_elt(); 
            inserer2(&premier, nouveau);
            parcourir(premier);
            break;

        case 4: // Supprimer debut
            supprimer_debut(&premier);
            parcourir(premier);
            break;

        case 5: // Supprimer un maillon d'une valeur donnee
            printf("Entrez la valeur à supprimer : ");
            scanf("%d", &nb);
            critere_supp_un2(&premier, nb);
            parcourir(premier);
            break;

        case 6: // Detruire liste
            detruire_liste2(&premier);
            parcourir(premier);
            break;

        case 7: // Sauver liste
            sauver_liste(premier);
            break;

        case 8: // Charger liste
            detruire_liste(&premier); // Détruire la liste existante avant de charger la nouvelle
            premier = load_liste();
            parcourir(premier);
            break;

        default:
            fin = 1; // Quitter le programme si un choix invalide est entré
            break;
        }
    }

    return 0;
}