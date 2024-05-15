
#include <stdio.h>
#include <stdlib.h>
#include "type_ast.h"
#include "table_symbole.h"	

void aff_operateur(TypeOperateur op){
	switch (op) {
		case N_PLUS:
			printf("+") ;
			break;
		case N_MOINS:
			printf("-") ;
			break;
		case N_MUL:
			printf("*") ;
			break;
		case N_DIV:
			printf("/");
			break;
	} 
}

void afficher(Ast expr) {
	switch (expr->nature) {
		case OPERATION:
			printf("(");
			afficher(expr->gauche);
			aff_operateur(expr->operateur) ;
			afficher(expr->droite);
			printf(")");
			break ;
		case VALEUR:
			printf("%d", expr->valeur);
			break ;
		case N_SEPINST:
			printf(";");
			break;
		case N_IDF:
			printf("%s", expr->chaine);
			break;
		case N_AFF:
			printf("=");
			break;
		case N_LIRE:
			printf("N_LIRE");
			break;
		case N_ECRIRE:
			printf("N_ECRIRE");
			break;
		case N_SI:
			printf("N_SI");
			break;
		case N_EQ:
			printf("N_EQ");
			break;
		case N_NE:
			printf("N_EQ");
			break;
		case N_GT:
			printf("N_GT");
			break;
		case N_GE:
			printf("N_GE");
			break;
		case N_LT:
			printf("N_LT");
			break;
		case N_LE:
			printf("N_LE");
			break;
		case N_WHILE:
			printf("N_WHILE");
			break;
		}
}

int evaluation(Ast expr, sequence_t *table_symbole) {
	// calcule la valeur de l'expression arithmetique expr
	int v;
	int g,d;
	switch (expr->nature)
	{
	case N_IDF:
		if (search_table(table_symbole, expr->chaine, &v) == 1){
			return v;
		}
		printf("Erreur!");
		exit(1);
	case VALEUR:
		return expr->valeur;
		break;
	case OPERATION:
		g = evaluation(expr->gauche, table_symbole);
		d = evaluation(expr->droite, table_symbole);
		switch (expr->operateur)
		{
		case N_PLUS:
			return g + d;
			break;
		case N_MOINS:
			return g - d;
			break;
		case N_MUL:
			return g * d;
			break;
		case N_DIV:
			if (d==0){
				printf("\nZeroDivisionError\n");
                exit(0);
			}
			return g / d;
			break;
		default:
			break;
		}
	default:
		break;
	}
	return -1 ;
}
