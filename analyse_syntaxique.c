#include <string.h>
#include <stdlib.h> 
#include <stdio.h> 

#include "lecture_caracteres.h"
#include "analyse_lexicale.h"

#include "analyse_syntaxique.h"

#include "type_ast.h"
#include "ast_construction.h"

#include "table_symbole.h"
#include "ast_parcours.h"


void analyser (char *fichier, Ast *A, sequence_t *table_symbole){
    demarrer(fichier);
    // sequence_t *table_symbole = malloc(sizeof(sequence_t));
    // init_table(table_symbole);
    rec_pgm(A, table_symbole);
    //display_table(table_symbole);
    //interpreter(A, table_symbole);
    return;
}

void rec_pgm(Ast *A, sequence_t *table_symbole){
    rec_seq_inst(A, table_symbole);
}

void rec_seq_inst(Ast *A, sequence_t *table_symbole){
    Ast A1;
    rec_inst(&A1, table_symbole);
    rec_suite_seq_inst(&A1, A, table_symbole);
}

void rec_suite_seq_inst(Ast *A1, Ast *A, sequence_t *table_symbole){
    Ast A2;
    switch (lexeme_courant().nature){
    case SEPAFF:
        avancer();
        rec_seq_inst(&A2, table_symbole);
        *A = creer_seqinst(*A1, A2);
        break;

    default:
        *A = *A1;
        break;
    }
}

Ast creer_cond(Ast A1, Ast A2, Nature_Lexeme nature){
      Ast expr;
      expr = (Ast)malloc(sizeof(NoeudAst));
      switch (nature){
            case EQ:
                  expr->nature = N_EQ;
                  break;
            case NE:
                  expr->nature = N_NE;
                  break;
            case GT:
                  expr->nature = N_GT;
                  break;
            case GE:
                  expr->nature = N_GE;
                  break;
            case LT:
                  expr->nature = N_LT;
                  break;
            case LE:
                  expr->nature = N_LE;
                  break;
            default:
                  printf("Erreur_construction_arbre_creer_cond\n");
                  exit(0);
      }
      expr->gauche = A1;
      expr->droite = A2;
      return expr;
}



void rec_condition(Ast *Acond, sequence_t *table_symbole){
    Ast A1, A2;
    rec_eag(&A1, table_symbole);
    switch (lexeme_courant().nature){
        case EQ:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, EQ);
            break;
        case NE:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, NE);
            break;
        case GT:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, GT);
            break;
        case GE:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, GE);
            break;
        case LT:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, LT);
            break;
        case LE:
            avancer();
            rec_eag(&A2, table_symbole);
            *Acond = creer_cond(A1, A2, LE);
            break;

        default:
            printf("ERREUR: condition, à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
    }

}

void rec_inst(Ast *A, sequence_t *table_symbole){
    Ast Ag, Ad;
    Ast Acond, Athen, Aelse;
    Ast Abody;
    switch (lexeme_courant().nature)
    {
    case IDF:
        Ag = creer_idf(lexeme_courant().chaine);
        avancer();
        if (lexeme_courant().nature != AFF){
            printf("\033[0;31mERREUR\033[0m: affectation à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        rec_eag(&Ad, table_symbole);
        if (lexeme_courant().nature != SEPAFF ){
            //&& lexeme_courant().nature != SINON && lexeme_courant().nature != FSI && lexeme_courant().nature != FAIT
            printf("\033[0;31mERREUR\033[0m: manque un ';' à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        *A = creer_aff(Ag, Ad);
        break;

    case LIRE:
        avancer();
        if (lexeme_courant().nature != PARO){
            printf("\033[0;31mERREUR\033[0m: manque parenthese à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        if (lexeme_courant().nature != IDF){
            printf("\033[0;31mERREUR\033[0m: manque expresseion à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        Ag = creer_idf(lexeme_courant().chaine);
        avancer();
        *A = creer_lire(Ag);
        if (lexeme_courant().nature != PARF)
        {
            printf("\033[0;31mERREUR\033[0m: manque parenthese à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        if (lexeme_courant().nature != SEPAFF ){
            //&& lexeme_courant().nature != SINON && lexeme_courant().nature != FSI && lexeme_courant().nature != FAIT
            printf("\033[0;31mERREUR\033[0m: manque un ';' à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        break;
    
    case ECRIRE:
        avancer();
        if (lexeme_courant().nature != PARO){
            printf("\033[0;31mERREUR\033[0m: manque parenthese à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        rec_eag(&Ag, table_symbole);
        *A = creer_ecrire(Ag);
        if (lexeme_courant().nature != PARF)
        {
            printf("\033[0;31mERREUR\033[0m: manque parenthese à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        if (lexeme_courant().nature != SEPAFF ){
            //&& lexeme_courant().nature != SINON && lexeme_courant().nature != FSI && lexeme_courant().nature != FAIT
            printf("\033[0;31mERREUR\033[0m: manque un ';' à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        break;

    case SI:
        avancer();
        rec_condition(&Acond, table_symbole);
        if (lexeme_courant().nature != ALORS){
            printf("\033[0;31mERREUR\033[0m: Mot clé 'alors', ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();

        rec_seq_inst(&Athen, table_symbole);
        if (lexeme_courant().nature != SINON){
            printf("\033[0;31mERREUR\033[0m: Mot clé 'sinon', ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();

        rec_seq_inst(&Aelse, table_symbole);
        if (lexeme_courant().nature != FSI){
            printf("\033[0;31mERREUR\033[0m: Mot clé 'fsi', ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();

        if (lexeme_courant().nature != SEPAFF){
            printf("\033[0;31mERREUR\033[0m: manque un ';' à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        //&& lexeme_courant().nature != SI && lexeme_courant().nature != TANTQUE && lexeme_courant().nature != LIRE && lexeme_courant().nature != ECRIRE

        *A = creer_si(Acond, Athen, Aelse);
        break;

    case TANTQUE:
        avancer();
        rec_condition(&Acond, table_symbole);
        if (lexeme_courant().nature != FAIRE){
            printf("\033[0;31mERREUR\033[0m: Mot clé 'faire', ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        rec_seq_inst(&Abody, table_symbole);
        if (lexeme_courant().nature != FAIT){
            printf("\033[0;31mERREUR\033[0m: Mot clé 'fait', ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        avancer();
        if (lexeme_courant().nature != SEPAFF){
            printf("\033[0;31mERREUR\033[0m: manque un ';' à la ligne %d\n", lexeme_courant().ligne);
            exit(0);
        }
        *A = creer_while(Acond, Abody);
        break;

    default:
        break;
    }

}

void rec_seq_aff(sequence_t *table_symbole){
    
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
        case IDF:
            rec_aff(table_symbole);
            rec_seq_aff(table_symbole);
            break;
        default:
            break;
        }
        return;
}

void rec_aff(sequence_t *table_symbole){
    Ast A;
    int v;
    char idf[256];
    strcpy(idf, lexeme_courant().chaine);
    if (lexeme_courant().nature == IDF)
        avancer();
    else {
        printf("\033[0;31mERREUR\033[0m: Identificateur attendue, ligne %d\n", lexeme_courant().ligne);
        exit(0);
    }
    if (lexeme_courant().nature == AFF)
        avancer();
    else{
        printf("\033[0;31mERREUR\033[0m: '=' attendue, ligne %d\n", lexeme_courant().ligne);
        exit(0);
    }
    rec_eag(&A, table_symbole);
    v = evaluation(A, table_symbole);
    insert_table(table_symbole, idf, v);
    if (lexeme_courant().nature == SEPAFF)
        avancer();
    else{
        printf("\033[0;31mERREUR\033[0m: ';' attendue, ligne %d\n", lexeme_courant().ligne);
        exit(0);
    }
    return;
}

void rec_eag(Ast *A, sequence_t *table_symbole){
    rec_seq_terme(A, table_symbole);
}

void rec_seq_terme(Ast *A, sequence_t *table_symbole){
    Ast A1;
    rec_terme(&A1, table_symbole);
    rec_suite_seq_terme(&A1,A, table_symbole);
}

void rec_suite_seq_terme(Ast *Ag, Ast *A,sequence_t *table_symbole){
    Ast Ad;
    Ast A1;
    TypeOperateur op;
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
        case PLUS:
        case MOINS:
            rec_op1(&op);
            rec_terme(&Ad, table_symbole);
            A1 = creer_operation(op, *Ag, Ad);
            rec_suite_seq_terme(&A1,A, table_symbole);
            break;
        default:
            *A = *Ag;
            break;
    }
}

void rec_terme(Ast *A, sequence_t *table_symbole){
    rec_seq_facteur(A, table_symbole);
}

void rec_seq_facteur(Ast *A, sequence_t *table_symbole){
    Ast A1;
    rec_facteur(&A1, table_symbole);
    rec_suite_seq_facteur(&A1, A, table_symbole);
}

void rec_suite_seq_facteur(Ast *Ag, Ast *A, sequence_t *table_symbole){
    Ast Ad;
    Ast A1;
    TypeOperateur op;
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
        case MUL:
        case DIV:
            rec_op2(&op);
            rec_facteur(&Ad, table_symbole);
            A1 = creer_operation(op, *Ag, Ad);
            rec_suite_seq_facteur(&A1,A, table_symbole);
            break;
        default:
            *A = *Ag;
            break;
    }
}

void rec_facteur(Ast *A, sequence_t *table_symbole){
    // int v;
    // int trouve; // drapeau
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
        case ENTIER:
            *A = creer_valeur(lc.valeur);
            avancer();
            break;
        case PARO:
            avancer(); 
            rec_eag(A, table_symbole);
            lc = lexeme_courant();
            if (lc.nature == PARF){
                avancer();
            }
            else{
                printf("\033[0;31mERREUR\033[0m : Parenthèse ouvrante à la ligne %d est manqué\n", lc.ligne);
                exit(0);
            }
            break;
        case IDF:
            *A = creer_idf(lexeme_courant().chaine);
            avancer();
            break;
        default:
            printf("\033[0;31mERREUR\033[0m: n'est pas un facteur, ligne %d\n", lc.ligne);
            exit(0);
            break;
    }
}

void rec_op1(TypeOperateur *op){
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
    case PLUS:
        *op = N_PLUS;
        avancer();
        break;
    case MOINS:
        *op = N_MOINS;
        avancer();
        break;
    default:
        printf("\033[0;31mERREUR\033[0m: op1 à la ligne %d", lc.ligne);
        exit(0);
    }
}

void rec_op2(TypeOperateur *op){
    Lexeme lc = lexeme_courant();
    switch (lc.nature){
    case MUL:
        *op = N_MUL;
        avancer();
        break;
    case DIV:
        *op = N_DIV;
        avancer();
        break;
    default:
        printf("\033[0;31mERREUR:\033[0m op2 à la ligne %d", lc.ligne);
        exit(0);
    }
}

//INTERPRETATION

void interpreter(Ast A, sequence_t *table_symbole){
    switch (A->nature){
    case N_SEPINST:
        interpreter(A->gauche, table_symbole);
        interpreter(A->droite, table_symbole);
        break;
    case N_AFF:
        interpreter_aff(A, table_symbole);
        break;
    case N_LIRE:
        interpreter_lire(A, table_symbole);
        break;
    case N_ECRIRE:
        interpreter_ecrire(A, table_symbole);    
        break;
    case N_SI:
        interpreter_si_alors_sinon(A, table_symbole);
        break;
    case N_WHILE:
        interpreter_while(A, table_symbole);
        break;
    default:
        //printf("Erreur d'interpretation\n");
        break;
    }
}

void interpreter_aff(Ast A, sequence_t *table_symbole){
    char *idf = A->gauche->chaine;
    int v = evaluation(A->droite, table_symbole);
    insert_table(table_symbole, idf, v);
}

void interpreter_lire(Ast A,sequence_t *table_symbole){
    int v;
    scanf("%d",&v);
    insert_table(table_symbole, A->gauche->chaine, v);
}

void interpreter_ecrire(Ast A,sequence_t *table_symbole){
    int v = evaluation(A->gauche, table_symbole);
    printf("%d\n", v);
}

int valeur_booleene(Ast A, sequence_t *table_symbole){
    int valeurg, valeurd;
    valeurg = evaluation(A->gauche, table_symbole);
    valeurd = evaluation(A->droite, table_symbole);
    switch (A->nature){
        case N_EQ:
            return (valeurg == valeurd);
        case N_NE:
            return (valeurg != valeurd);
        case N_GT:
            return (valeurg > valeurd);
        case N_GE:
            return (valeurg >= valeurd);
        case N_LT:
            return (valeurg < valeurd);
        case N_LE:
            return (valeurg <= valeurd);
        default:
            break;
    }
    return 0;
}

void interpreter_si_alors_sinon(Ast A, sequence_t *table_symbole){
    int condition = valeur_booleene(A->gauche, table_symbole);
    if (condition)
        interpreter(A->milieu, table_symbole);
    else
        interpreter(A->droite, table_symbole);
}

void interpreter_while(Ast A, sequence_t *table_symbole){
    while (valeur_booleene(A->gauche, table_symbole)){
        interpreter(A->droite, table_symbole);
    }
    return;
}