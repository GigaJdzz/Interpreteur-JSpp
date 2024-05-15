// Made by Jad Fawaz & Sam Hajj Assaf
#ifndef ___TABLE_SYMBOLE_H___
#define ___TABLE_SYMBOLE_H___


struct cellule {
    char var[256];
    int valeur;
    struct cellule *suivant;
};
typedef struct cellule cellule_t;

struct sequence {
    cellule_t *tete;
};
typedef struct sequence sequence_t;


// creer nouvelle cellule
cellule_t *nouvelle_cellule();

// initialiser la table
void init_table(sequence_t *seq);

// inseret dans la table
void insert_table(sequence_t *seq,char *idf, int val);

// chercher dans la table
int search_table(sequence_t *seq,char *idf, int *val);

// afficher la table
void display_table(sequence_t *seq);


#endif // ___TABLE_SYMBOLE_H___
