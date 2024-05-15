#ifndef __AST_PARCOURS__
#define __AST_PARCOURS__

void afficher(Ast expr) ;
// affiche l'arbre abstrait de l'expression arithmetique expr

int evaluation(Ast expr, sequence_t *table_symbole) ;
// calcule la valeur de l'expression arithmetique expr
// FONCTION A COMPLETER !

#endif

