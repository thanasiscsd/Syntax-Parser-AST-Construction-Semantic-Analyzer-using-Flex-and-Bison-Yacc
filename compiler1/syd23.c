#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "y.tab.h"

int yyparse();
extern AstNode *TreeRoot;

/* ----------------------------------------------------------- */
/* ---------------------- FUNCTIONS -------------------------- */
/* ----------------------------------------------------------- */


/*Η συνάρτηση traverse είναι υπεύθυνη για την αναδρομική εκτύπωση του Abstract Syntax Tree (AST). Κάθε κόμβος 
του AST αντιπροσωπεύει μια δομική μονάδα του προγράμματος (π.χ. μέθοδος, δήλωση μεταβλητής, έκφραση). Η συνάρτηση 
προσθέτει κατάλληλες εσοχές για να φαίνεται η ιεραρχία των κόμβων και εμφανίζει επιπλέον πληροφορίες όπως το όνομα 
και η τιμή των μεταβλητών ή παραμέτρων όταν υπάρχουν. Αναδρομικά επισκέπτεται όλα τα παιδιά κάθε κόμβου για να 
εκτυπώσει όλο το δέντρο.
*/

void traverse(AstNode *p, int n) {
    int i;

    // Αν ο κόμβος είναι NULL, δεν έχουμε τίποτα να εμφανίσουμε
    if (!p) return;

    // Εκτύπωση εσοχών για να φαίνεται η ιεραρχία των κόμβων
    for (i = 0; i < n; i++)
        printf(" ");

    // Εμφάνιση του τύπου του κόμβου και πιθανών πληροφοριών (όνομα/τιμή)
    switch(p->NodeType) {
        case N_PROGRAM:       printf("PROGRAM\n"); break;
        case N_METHLIST:      printf("METHLIST\n"); break;
        case N_METH:          printf("METH\n"); break;
        case N_PARAMS:        printf("PARAMS\n"); break;
        case N_FORMALS:       printf("FORMALS\n"); break;
        case N_TYPE:          printf("TYPE : int\n"); break;
        case N_BODY:          printf("BODY\n"); break;
        case N_DECLS:         printf("DECLS\n"); break;
        case N_DECLLIST:      printf("DECLLIST\n"); break;

        case N_DECL:
            // Αν ο κόμβος έχει συνδεδεμένο σύμβολο (SymbolNode), εμφανίζουμε όνομα και τιμή
            if (p->SymbolNode)
                printf("DECL: %s = %d\n", p->SymbolNode->name, p->SymbolNode->timi);
            else
                printf("DECL\n");
            break;

        case N_VARS:
            // Αν υπάρχει SymbolNode, εμφανίζουμε όνομα μεταβλητής και πιθανή τιμή
            if (p->SymbolNode && p->SymbolNode->name) {
                printf("VARS: %s", p->SymbolNode->name);
                if (p->SymbolNode->timi != -1)
                    printf(" = %d", p->SymbolNode->timi);
                printf("\n");
            } else {
                printf("VARS\n");
            }
            break;

        case N_STMTS:         printf("STMTS\n"); break;
        case N_STMT:          printf("STMT\n"); break;
        case N_ASSIGN:        printf("ASSIGN\n"); break;
        case N_LOCATION:      printf("LOCATION\n"); break;
        case N_EXPR:          printf("EXPR\n"); break;
        case N_RELOP:         printf("RELOP\n"); break;
        case N_ADDEXPR:       printf("ADDEXPR\n"); break;
        case N_ADDOP:         printf("ADDOP\n"); break;
        case N_TERM:          printf("TERM\n"); break;
        case N_MULOP:         printf("MULOP\n"); break;
        case N_FACTOR:        printf("FACTOR\n"); break;
        case N_METHOD:        printf("METHOD\n"); break;
        case N_CALL:          printf("CALL\n"); break;
        case N_ARGS:          printf("ARGS\n"); break;

        case N_CONST:
            printf("CONST: %d\n", p->value); // Εκτύπωση τιμής σταθεράς
            break;

        case N_PLUS:          printf("PLUS\n"); break;
        case N_MINUS:         printf("MINUS\n"); break;
        case N_MUL:           printf("MUL\n"); break;
        case N_DIV:           printf("DIV\n"); break;
        case N_LT:            printf("LT\n"); break;
        case N_GT:            printf("GT\n"); break;
        case N_LE:            printf("LE\n"); break;
        case N_GE:            printf("GE\n"); break;
        case N_EQ:            printf("EQ\n"); break;
        case N_NE:            printf("NE\n"); break;
        case N_BLOCK:         printf("BLOCK\n"); break;
        case N_RETURN:        printf("RETURN\n"); break;
        case N_IF:            printf("IF\n"); break;
        case N_WHILE:         printf("WHILE\n"); break;
        case N_BREAK:         printf("BREAK\n"); break;
        case N_BOOL:
    	    if (p->SymbolNode) {
        	printf("BOOL: %s (value = %d)\n", p->SymbolNode->name, p->SymbolNode->timi);
    	    } else {
        	printf("BOOL\n");
    	    }
    	    break;

        case N_PARAM:
            if (p->SymbolNode)
                printf("PARAM: %s = %d\n", p->SymbolNode->name, p->SymbolNode->timi);
            else
                printf("PARAM\n");
            break;

        case N_ID:
            if (p->SymbolNode && p->SymbolNode->name) {
                if (p->SymbolNode->timi == -1)
                    printf("ID: %s\n", p->SymbolNode->name);  // Όνομα μεθόδου
                else
                    printf("ID: %s \n", p->SymbolNode->name); // Όνομα μεταβλητής ή παραμέτρου
            } else
                printf("ID\n");
            break;
    }

    // Αναδρομικά επισκεπτόμαστε όλα τα παιδιά του κόμβου
    for (i = 0; i < 4; i++)
        traverse(p->pAstNode[i], n + 2); // Αυξάνουμε εσοχή κατά 2
}