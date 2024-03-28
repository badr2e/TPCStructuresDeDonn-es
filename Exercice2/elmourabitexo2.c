/*
    Section de documentation
    @Projet Structure de pile en C
    @Program Description, Programme pour inverser une liste à l'aide d'une pile
*/

#include <stdio.h>
#include <stdlib.h>

// Structure de nœud pour la liste chaînée
typedef struct Noeud {
    int donnee;
    struct Noeud* suivant;
} Noeud;

// Structure pour la pile basée sur une liste chaînée
typedef struct {
    Noeud* sommet; // Pointeur vers le nœud du sommet de la pile
} Pile;


int estVide(Pile* pile);
void empiler(Pile* pile, int valeur);
int sommet(Pile* pile);
int depiler(Pile* pile);


int main() {
    // Création d'une pile vide
    Pile* maPile = (Pile*)malloc(sizeof(Pile));
    maPile->sommet = NULL;

    // Empile des valeurs dans la pile
    empiler(maPile, 10);
    empiler(maPile, 20);
    empiler(maPile, 30);

    // Affiche la valeur au sommet de la pile
    printf("Sommet de la pile : %d\n", sommet(maPile));

    // Dépile et affiche les valeurs de la pile
    printf("Valeurs dépilées : ");
    while (!estVide(maPile)) {
        printf("%d ", depiler(maPile));
    }
    printf("\n");

    // Libère la mémoire allouée pour la pile
    free(maPile);

    return 0;
}

// Fonction pour tester si la pile est vide
int estVide(Pile* pile) {
    return pile->sommet == NULL;
}

// Fonction pour empiler un élément sur la pile
void empiler(Pile* pile, int valeur) {
    Noeud* nouveauNoeud = (Noeud*)malloc(sizeof(Noeud));
    if (nouveauNoeud) {
        nouveauNoeud->donnee = valeur;
        nouveauNoeud->suivant = pile->sommet;
        pile->sommet = nouveauNoeud;
    }
}

// Fonction pour récupérer la valeur de l'élément de sommet de pile
int sommet(Pile* pile) {
    if (!estVide(pile)) {
        return pile->sommet->donnee;
    }
    return -1; // Valeur par défaut pour indiquer une pile vide
}

// Fonction pour récupérer la valeur et enlever l'élément de sommet de pile
int depiler(Pile* pile) {
    if (!estVide(pile)) {
        Noeud* temp = pile->sommet;
        int valeur = temp->donnee;
        pile->sommet = temp->suivant;
        free(temp);
        return valeur;
    }
    return -1; // Valeur par défaut pour indiquer une pile vide
}

