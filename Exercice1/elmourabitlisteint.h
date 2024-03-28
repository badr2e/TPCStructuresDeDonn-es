#ifndef ELMOURABITLISTEINT_H
#define ELMOURABITLISTEINT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

// Déclaration de la structure maillon_int
typedef struct maillon {
    int val;                // Champ représentant la valeur de l'élément dans la liste
    struct maillon* p_suiv; // Pointeur vers le prochain élément dans la liste
} maillon_int;

// Déclaration des fonctions
maillon_int* init_elt();
void ajout_tete_v2(maillon_int** p_p_tete, maillon_int* p_nv_elt);
void parcourir(maillon_int* p_tete);
maillon_int* inserer1(maillon_int* p_tete, maillon_int* p_nv_elt);
void inserer2(maillon_int** prem, maillon_int* e);
void supprimer_debut(maillon_int** prem);
maillon_int* critere_supp_un1(maillon_int* prem, int val);
void critere_supp_un2(maillon_int** prem, int val);
void detruire_liste(maillon_int** prem);
void detruire_liste2(maillon_int** prem);
void sauver_liste(maillon_int* prem);
maillon_int* load_liste();

#endif
