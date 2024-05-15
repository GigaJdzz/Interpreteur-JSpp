#include <stdio.h>
#include <stdlib.h>

#include "analyse_lexicale.h"
#include "analyse_syntaxique.h"
#include "type_ast.h"
#include "ast_construction.h"
#include "ast_parcours.h"

int main (int argc, char *argv[]) {
   switch (argc) {
        case 1:
        // demarre l'analyse syntaxique sur stdin
               demarrer ("") ; 
                break ;
        case 2:
        // demarre l'analyse syntaxique sur le fichier transmis en argument
               demarrer (argv[1]) ; 
                break ;
        default:
                printf("nombre d'arguments incorrects !\n");
                exit(1) ;
   } ;
   
//    while (! fin_de_sequence()) { 
//                 afficher_lex(lexeme_courant()) ;
//                 printf("\n") ;
//                 avancer() ;
//         } ;
//         arreter();

   Ast A;
   sequence_t table_symbole;
   init_table(&table_symbole);
   printf("---------- debut du programme ----------\n");
   analyser(argv[1], &A, &table_symbole);
   interpreter(A, &table_symbole);
   printf("----------- Fin du programme -----------\n");
   display_table(&table_symbole);

   arreter() ; // termine l'analyse syntaxique
   return 0 ;
}