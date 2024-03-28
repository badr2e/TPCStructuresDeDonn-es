#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

typedef struct maillon {
    int val;                // Champ représentant la valeur de l'élément dans la liste
    struct maillon* p_suiv; // Pointeur vers le prochain élément dans la liste
} maillon_int;              


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


/* Initialise un nouvel élément de liste avec une valeur entière aléatoire entre 0 et 20
@output : maillon_int*, pointeur vers le nouvel élément initialisé
@precondition : aucune
@postcondition : le nouvel élément est initialisé avec une valeur aléatoire entre 0 et 20 et son pointeur suivant est NULL
*/
maillon_int* init_elt()
{
    maillon_int* p_nv_elt = malloc(sizeof(maillon_int));
    p_nv_elt->val = rand() % 21;
    p_nv_elt->p_suiv = NULL;
    return p_nv_elt;
}


/* Ajoute un nouvel élément en tête de la liste (version 1)
@input : maillon_int* p_tete, pointeur sur le premier élément de la liste
         maillon_int* p_nv_elt, pointeur vers le nouvel élément à ajouter en tête
@output : maillon_int*, pointeur vers le nouveau premier élément de la liste
@precondition : aucune
@postcondition : le nouvel élément est ajouté en tête de la liste et devient le premier élément
*/
maillon_int* ajout_tete_v1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = p_tete;
    p_tete = p_nv_elt;
    return p_tete;
}


/* Ajoute un nouvel élément en tête de la liste (version 2)
@input : maillon_int** p_p_tete, pointeur sur le pointeur du premier élément de la liste
         maillon_int* p_nv_elt, pointeur vers le nouvel élément à ajouter en tête
@output : void
@precondition : aucune
@postcondition : le nouvel élément est ajouté en tête de la liste et devient le premier élément
*/
void ajout_tete_v2(maillon_int** p_p_tete, maillon_int* p_nv_elt)
{
    p_nv_elt->p_suiv = *p_p_tete;
    *p_p_tete = p_nv_elt;
}


/* Parcourt la liste et affiche ses éléments séparés par des tirets
@input : maillon_int* p_tete, pointeur sur le premier élément de la liste à parcourir
@output : void
@precondition : aucune
@postcondition : les éléments de la liste sont affichés à l'écran séparés par des tirets
*/
void parcourir(maillon_int* p_tete)
{
    if (p_tete == NULL)
        printf("liste vide");
    else
        while (p_tete != NULL) {
            printf("%d--", p_tete->val);
            p_tete = p_tete->p_suiv;
        }
    putchar('\n');
}


/* Insère un nouvel élément dans la liste en conservant l'ordre croissant des éléments (version 1)
@input : maillon_int* p_tete, pointeur sur le premier élément de la liste
         maillon_int* p_nv_elt, pointeur vers le nouvel élément à insérer
@output : maillon_int*, pointeur vers le premier élément de la liste après insertion
@precondition : aucune
@postcondition : le nouvel élément est inséré dans la liste tout en conservant l'ordre croissant des éléments
*/
maillon_int* inserer1(maillon_int* p_tete, maillon_int* p_nv_elt)
{
    maillon_int* n, * prec;
    
    if (p_tete == NULL || p_nv_elt->val <= p_tete->val) {  
        p_nv_elt->p_suiv = p_tete;
        p_tete = p_nv_elt;
    }
    else {  
        n = prec = p_tete;
        while (n != NULL && p_nv_elt->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        p_nv_elt->p_suiv = n;
        prec->p_suiv = p_nv_elt;
    }
    return p_tete;
}


/* Insère un nouvel élément dans la liste en conservant l'ordre croissant des éléments (version 2)
@input : maillon_int** prem, pointeur sur le pointeur du premier élément de la liste
         maillon_int* e, pointeur vers le nouvel élément à insérer
@output : void
@precondition : aucune
@postcondition : le nouvel élément est inséré dans la liste tout en conservant l'ordre croissant des éléments
*/
void inserer2(maillon_int** prem, maillon_int* e)
{
    maillon_int* n, * prec;
    if (*prem == NULL || e->val <= (*prem)->val){ 
        e->p_suiv = *prem;
        *prem = e;
    }
    else {  
        n = prec = *prem;
        while (n != NULL && e->val > n->val) {
            prec = n;
            n = n->p_suiv;
        }
        e->p_suiv = n;
        prec->p_suiv = e;
    }
}


/* Supprime le premier élément de la liste
@input : maillon_int** prem, pointeur sur le pointeur du premier élément de la liste
@output : void
@precondition : aucune
@postcondition : le premier élément de la liste est supprimé et la mémoire est libérée
*/
void supprimer_debut(maillon_int** prem)
{
    maillon_int* n;
    if (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}


/* Supprime tous les éléments de la liste ayant une valeur donnée
@input : maillon_int* prem, pointeur sur le premier élément de la liste
         int val, valeur à supprimer de la liste
@output : maillon_int*, pointeur vers le premier élément de la liste après suppression
@precondition : aucune
@postcondition : tous les éléments ayant la valeur spécifiée sont supprimés de la liste
*/
maillon_int* critere_supp_un1(maillon_int* prem, int val)
{
    maillon_int* e = prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
    return prem;
}


/* Supprime tous les éléments de la liste ayant une valeur donnée (version 2)
@input : maillon_int** prem, pointeur sur le pointeur du premier élément de la liste
         int val, valeur à supprimer de la liste
@output : void
@precondition : aucune
@postcondition : tous les éléments ayant la valeur spécifiée sont supprimés de la liste
*/
void critere_supp_un2(maillon_int** prem, int val)
{
    maillon_int* e = *prem, * prec = NULL, * n;

    while (e != NULL) {
        n = NULL;
        if (e->val == val) {
            n = e;
            if (prec == NULL)
                *prem = e->p_suiv;
            else
                prec->p_suiv = e->p_suiv;
        }
        else
            prec = e;
        e = e->p_suiv;
        if (n != NULL)
            free(n);
    }
}


/* Détruit tous les éléments de la liste et libère la mémoire
@input : maillon_int** prem, pointeur sur le pointeur du premier élément de la liste
@output : void
@precondition : aucune
@postcondition : tous les éléments de la liste sont supprimés et la mémoire est libérée
*/
void detruire_liste(maillon_int** prem)
{
    maillon_int* n;
    while (*prem != NULL) {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}


/* Détruit tous les éléments de la liste et libère la mémoire (version 2)
@input : maillon_int** prem, pointeur sur le pointeur du premier élément de la liste
@output : void
@precondition : aucune
@postcondition : tous les éléments de la liste sont supprimés et la mémoire est libérée
*/
void detruire_liste2(maillon_int** prem)
{
    while (*prem != NULL)
        supprimer_debut(prem);
}


/* Permet la sérialisation format binaire dans le fichier
"saveliste.bin" de la liste d'entier (maillon_int) dont
le pointeur sur le premier élément est passé en paramètre
@input : maillon_int * prem, pointeur sur l'élément de tête de la liste à sérialiser
@output : void
@precondition : le répertoire courant et le processus père permettent l'écriture 
                le pointeur prem, est soit NULL (aucune action) soit pointe sur
                le premier élément d'une liste d'entiers
@postcondition : le fichier saveliste.bin contient les éléments de la liste 
                dont le premier élément est pointé par prem. 
                Nota : il n'y a pas de libération de la mémoire occupée par la 
                liste. Il faut donc la détruire avant d'éventuellement la recharger.
*/
void sauver_liste(maillon_int* prem)
{
    //ouvrir un fichier binaire en écriture : suffixe b
    FILE* f=fopen("saveliste.bin", "wb");
    printf("Ouvertude du fichier %p\n",f);
    // si liste non vide
    if (prem != NULL) {
        if (f==NULL)
            fprintf(stderr,"erreur création fichier :%i\n",errno);
        else // parcourir la liste jusque fin
            while (prem != NULL) {
                // écrire chaque maillon en binaire
                if (1 !=fwrite(prem, sizeof(maillon_int), 1, f))
                    fprintf(stderr,"Erreur d'écriture du maillon %p\n",prem);
                else 
                // passer au maillon suivant
                prem = prem->p_suiv;
            }
            fclose(f);	// fermer le fichier
    }
    else
        fprintf(stderr,"pas de sauvegarde pour une liste vide\n");
}


/* Charge une liste depuis un fichier binaire "saveliste.bin"
@output : maillon_int*, pointeur vers le premier élément de la liste chargée depuis le fichier
@precondition : le fichier "saveliste.bin" existe et est accessible en lecture
@postcondition : si le fichier est valide, la liste est chargée depuis le fichier et le pointeur vers son premier élément est renvoyé
                 sinon, NULL est renvoyé et un message d'erreur est affiché
*/
maillon_int* load_liste()
{
    FILE* f;
    maillon_int* prem = NULL, * p, e;
    if ((f= fopen("saveliste.bin", "rb")) != NULL) {
        prem = malloc(sizeof(maillon_int));
        fread(prem, sizeof(maillon_int), 1, f);
        p = prem;
        while (fread(&e, sizeof(maillon_int), 1, f)) {
            p->p_suiv = malloc(sizeof(maillon_int));
            p = p->p_suiv;
            *p = e;
            p->p_suiv = NULL;
        }
        fclose(f);
    }
    else
        printf("erreur ou fichier inexistant");
    return prem;
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