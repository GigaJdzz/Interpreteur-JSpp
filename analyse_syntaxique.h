/* ------------------------------------------------------------------------
-- analyse syntaxique d'une expression arithmetique
--
-- J. FAWAZ & S. HAJJ ASSAF - 22/01/24
------------------------------------------------------------------------ */

#include "type_ast.h"
#include "table_symbole.h"

void analyser (char *fichier, Ast *A, sequence_t *table_symbole);

// e.i : indifferent
// e.f : une Expression Arithmetique a ete lue dans fichier
// si elle ne contient pas d’erreur de syntaxe un message est affiche
// sinon le pgm termine sur un message d’erreur
void rec_pgm(Ast *A, sequence_t *table_symbole);

void rec_seq_inst(Ast *A, sequence_t *table_symbole);

void rec_suite_seq_inst(Ast *A1, Ast *A, sequence_t *table_symbole);

void rec_seq_inst(Ast *A, sequence_t *table_symbole);

void rec_inst(Ast *A, sequence_t *table_symbole);

void rec_seq_aff(sequence_t *table_symbole);

void rec_aff(sequence_t *table_symbole);

void rec_eag(Ast *A, sequence_t *table_symbole);

void rec_seq_terme(Ast *A, sequence_t *table_symbole);

void rec_suite_seq_terme(Ast *Ag, Ast *A, sequence_t *table_symbole);

void rec_terme(Ast *A, sequence_t *table_symbole);

void rec_seq_facteur(Ast *A, sequence_t *table_symbole);

void rec_suite_seq_facteur(Ast *Ag, Ast *A, sequence_t *table_symbole);

void rec_facteur(Ast *A, sequence_t *table_symbole);

void rec_op1(TypeOperateur *op);

void rec_op2(TypeOperateur *op);

void interpreter(Ast A, sequence_t *table_symbole);

void interpreter_aff(Ast A, sequence_t *table_symbole);

void interpreter_lire(Ast A,sequence_t *table_symbole);

void interpreter_ecrire(Ast A,sequence_t *table_symbole);

void interpreter_si_alors_sinon(Ast A, sequence_t *table_symbole);

void interpreter_while(Ast A, sequence_t *table_symbole);