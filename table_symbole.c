#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_symbole.h"

cellule_t *nouvelle_cellule(){
    cellule_t *cel = malloc(sizeof(cellule_t));
    cel->var[0] = '\0';
    cel->valeur = -1;
    cel->suivant = NULL;
    return cel;
}

void init_table(sequence_t *seq){
    seq->tete = NULL;
}

void insert_table(sequence_t *seq,char *idf, int val){
    cellule_t *cel_courant = seq->tete;

    while (cel_courant != NULL){
        if (strcmp(idf, cel_courant->var) == 0){
            cel_courant->valeur = val;
            return;
        }
        cel_courant = cel_courant->suivant;
    }
    cellule_t *cel = nouvelle_cellule();
    cel->valeur = val;
    strcpy(cel->var, idf);
    cel->suivant = seq->tete;
    seq->tete = cel;
    return;
}

int search_table(sequence_t *seq,char *idf, int *val){
    cellule_t *cel_courant = seq->tete;

    while (cel_courant != NULL){
        if (strcmp(idf, cel_courant->var) == 0){
            *val = cel_courant->valeur;
            return 1;
        }
        cel_courant = cel_courant->suivant;
    }
    printf("Variable non existante !!\n");
    return 0;
}

void display_table(sequence_t *seq){
    cellule_t *cel_courant = seq->tete;

    printf("--> Listes variables:\n");
    while (cel_courant != NULL){
        printf("%s = %d;\n", cel_courant->var, cel_courant->valeur);
        cel_courant = cel_courant->suivant;
    }
    return;
}
