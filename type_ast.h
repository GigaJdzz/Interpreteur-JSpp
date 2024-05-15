
#ifndef __TYPE_AST__
#define __TYPE_AST__ 

typedef enum {OPERATION, VALEUR, N_SEPINST, N_IDF, N_AFF, N_LIRE, N_ECRIRE, N_SI, N_EQ, N_NE, N_GT, N_GE, N_LT, N_LE, N_WHILE} TypeAst ;
typedef enum {N_PLUS, N_MUL, N_MOINS, N_DIV} TypeOperateur ;

typedef struct noeud { 
	TypeAst nature ;
	TypeOperateur operateur ;
	struct noeud *gauche, *droite, *milieu;
	int valeur;
	char *chaine;
} NoeudAst;

typedef NoeudAst *Ast ;

#endif  
