#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

#include "type_ast.h"
#include "ast_construction.h"

Ast creer_operation(TypeOperateur opr , Ast opde_gauche , Ast opde_droit) 
{
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = OPERATION;
      expr->operateur = opr;
      if (opde_gauche == NULL || opde_droit == NULL) {
         printf("ERREUR_EXPRESSION\n") ;
	 exit(1) ;
      } else {
         expr->gauche = opde_gauche;
         expr->droite = opde_droit;
      } ;
      return expr ;
}

Ast creer_valeur(int val) { 
      Ast expr ;
      expr = (Ast) malloc (sizeof(NoeudAst));
      expr->nature = VALEUR;
      expr->valeur = val;
      return expr ;
}

Ast creer_seqinst(Ast A1, Ast A2){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_SEPINST;
      expr->gauche = A1;
      expr->droite = A2;
      return expr;
}

Ast creer_idf(char *chaine){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_IDF;
      expr->chaine = malloc(sizeof(char[20]));
      strcpy(expr->chaine, chaine);
      return expr;
}

Ast creer_aff(Ast Ag, Ast Ad){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_AFF;
      expr->gauche = Ag;
      expr->droite = Ad;
      return expr;
}

Ast creer_lire(Ast Ag){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_LIRE;
      expr->gauche = Ag;
      return expr;
}

Ast creer_ecrire(Ast Ag){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_ECRIRE;
      expr->gauche = Ag;
      return expr;
}

Ast creer_si(Ast Acond, Ast Athen, Ast Aelse){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      expr->nature = N_SI;
      expr->gauche = Acond;
      expr->milieu = Athen;
      expr->droite = Aelse;
      return expr;
}

Ast creer_while(Ast Acond, Ast Abody){
    Ast expr;
    expr = (Ast)malloc(sizeof(NoeudAst));
    expr->nature = N_WHILE;
    expr->droite = Abody;
    expr->gauche = Acond;
    return expr;
}
