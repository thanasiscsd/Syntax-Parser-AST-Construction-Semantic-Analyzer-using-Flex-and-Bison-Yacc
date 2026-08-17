#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "syd2"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "defs.h"
#define DEBUG 0

#define SYM_TABLE_SIZE 41   /* μέγεθος πίνακα κατακερματισμού για σύμβολα*/
#define NAME_MAX  32        /* μέγιστο μήκος ονόματος μεταβλητής/μεθόδου*/
#define MAX_LOCAL_VARS 100  /* μέγιστος αριθμός τοπικών μεταβλητών*/

/* Δημιουργία κόμβου στο AST*/
AstNode *MkNode(int tipos, symbol *sn, AstNode *z0, AstNode *z1, AstNode *z2, AstNode *z3);
void yyerror(char *s);
/* Συνάρτηση για την εκτύπωση του AST*/
void traverse(AstNode *p, int n); 

/* Ορισμός πίνακα κατακερματισμού για το Symbol Table*/
typedef struct hash_tab {
   int numbsymbols;
   symbol *table[SYM_TABLE_SIZE];
} HASH_TAB;

AstNode* TreeRoot;       /* Ρίζα του AST (πρόγραμμα)*/
symbol *SymbolTable = NULL;
symbol *p;

int yyparse();           /* parser (δημιουργείται από bison/yacc)*/
int yylex();             /* lexer (δημιουργείται από flex)*/

#define STACKSIZE 200

symbol *vs[STACKSIZE];
int TopOfStack = -1;

void push_vs(symbol *p) {
    if (TopOfStack >= STACKSIZE - 1) {
       
        exit(1);
    }
    vs[++TopOfStack] = p;
}

symbol *pop_vs(void) {
    if (TopOfStack < 0) {
       
        exit(1);
    }
    return vs[TopOfStack--];
}

symbol *top_vs(void) {
    if (TopOfStack < 0) return NULL;
    return vs[TopOfStack];
}

/* Αντιγραφή περιεχομένων συμβόλου (χωρίς τα links)*/
void copy_symbol(symbol *dest, symbol *src) {
    if (!dest || !src) return;

    strcpy((char *)dest->name, (char *)src->name);
    strcpy(dest->scope_name, src->scope_name);

    dest->timi       = src->timi;
    dest->disposable = src->disposable;
    dest->lvalue     = src->lvalue;
    dest->typos      = src->typos;

    /* Δεν αντιγράφουμε τους pointers που συνδέουν λίστες συμβόλων*/
    dest->Next_in_Cross_Link = NULL;
    dest->NextSymbol         = NULL;
    dest->PrevSymbol         = NULL;
}

/* Διαγραφή συμβόλου (μόνο αν είναι disposable)*/
void discard_symbol(symbol *s) {
    if (!s) return;
    if (s->disposable) {
        free(s);
    }
}
#line 86 "syd2"
typedef union {
    int   yint;                 /* ακέραια τιμή*/
    char  *ystr;                /* string (ονόματα)*/
    int   nonterm;              /* για ενδιάμεσα*/
    struct AstNode *stnode;     /* δείκτης σε κόμβο AST*/
} YYSTYPE;
#line 101 "y.tab.c"
#define AND 257
#define ELSE 258
#define IF 259
#define INT 260
#define NOT 261
#define OR 262
#define PRINT 263
#define READ 264
#define WHILE 265
#define MAIN 266
#define DEC_CONST 267
#define ID 268
#define RETURN 269
#define BREAK 270
#define GE 271
#define LE 272
#define EQ 273
#define NE 274
#define TRUE 275
#define FALSE 276
#define VOID 277
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    1,    1,    2,    4,    4,    6,    6,    3,
    5,    7,    7,    8,    8,    9,    9,   13,   13,   13,
   10,   10,   11,   11,   11,   11,   11,   11,   11,   15,
   14,   16,   12,   12,   23,   23,   23,   23,   23,   23,
   18,   18,   24,   24,   19,   19,   25,   25,   20,   20,
   20,   20,   20,   20,   17,   21,   21,   22,   22,
};
short yylen[] = {                                         2,
    0,    1,    2,    1,    6,    0,    3,    4,    0,    1,
    4,    2,    0,    2,    0,    4,    6,    3,    5,    0,
    2,    0,    2,    3,    7,    5,    2,    1,    1,    3,
    3,    1,    3,    1,    1,    1,    1,    1,    1,    1,
    3,    1,    1,    1,    3,    1,    1,    1,    3,    1,
    1,    4,    1,    1,    1,    2,    0,    3,    0,
};
short yydefred[] = {                                      0,
   10,    0,    2,    0,    0,    3,    0,    0,    0,    0,
    0,    0,    0,    5,    0,   22,    0,    8,    0,    0,
    0,   22,   11,   29,    0,    0,   32,    0,    0,   21,
    0,   28,    0,    0,    0,    0,    0,    0,   51,    0,
   53,   54,    0,   50,    0,    0,    0,   46,   27,   23,
    0,    0,    0,    0,   30,    0,    0,    0,   24,    0,
   38,   35,   39,   40,   36,   37,   43,   44,    0,    0,
   47,   48,    0,   31,    0,    0,   16,    0,    0,   49,
    0,    0,    0,    0,   45,    0,   18,    0,    0,   26,
   52,    0,    0,   17,    0,   58,   19,   25,
};
short yydgoto[] = {                                       2,
    3,    4,    5,    9,   14,   10,   16,   17,   21,   19,
   30,   43,   54,   31,   32,   44,   45,   46,   47,   48,
   81,   82,   69,   70,   73,
};
short yysindex[] = {                                   -255,
    0,    0,    0, -255, -243,    0,   -1,    0,  -15, -255,
  -74, -216,    0,    0,   20,    0, -255,    0,    3, -202,
    0,    0,    0,    0,   34,   35,    0,  -38,   19,    0,
   22,    0,   23,  -10,   11,  -38,  -38,  -38,    0,    0,
    0,    0,   24,    0,   42,  -14,   21,    0,    0,    0,
  -38, -183,  -38,   27,    0,   47,   48,   49,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -38,  -38,
    0,    0,  -38,    0,   15,   50,    0,   18,   18,    0,
   51,  -38,   28,   21,    0,  -38,    0,   36, -165,    0,
    0,   53,   50,    0,   18,    0,    0,    0,
};
short yyrindex[] = {                                     98,
    0,    0,    0,   99,    0,    0,    0,  -37,    0,    0,
    0,    0,  -56,    0,   59,    0,    0,    0,    0,    0,
   -4,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   44,    0,    0,    0,    0,    0,  -32,
    0,    0,    0,    0,    0,    6,  -27,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -40,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   44,   44,    0,    0,    0,    0,
    0,    0,   13,  -22,    0,    0,    0,    0,    0,    0,
    0,   60,   44,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
  100,    0,   43,    0,    0,    0,    0,    0,    0,   80,
  -34,    5,  -69,    0,    0,    1,    0,   37,   38,   32,
    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 288
short yytable[] = {                                      59,
   57,   38,   13,    6,    1,   87,   88,   55,   32,   32,
   32,   32,   32,   42,   32,   42,   42,   42,   41,   33,
   41,   41,   41,   97,    7,   11,   32,   32,   67,   32,
   68,   42,   42,   52,   42,   33,   41,   41,    8,   41,
   56,   57,   58,   89,   90,   65,   34,   66,   13,   34,
   53,   15,   12,   33,   12,   74,   33,   76,   52,   20,
   98,   24,   71,   18,   34,   34,   13,   72,   13,   24,
   67,   33,   68,   36,   37,   86,   24,   49,   33,   33,
   50,   60,   59,   51,   75,   77,   92,   78,   79,   80,
   93,   91,   95,   52,   94,   33,   96,    1,    4,    7,
   56,   35,   20,    6,   85,   83,    0,   84,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   12,    0,
   12,    0,    0,    0,    0,   22,    0,   23,    0,    0,
    0,    0,    0,   22,    0,   55,    0,    0,    0,    0,
   22,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   13,   15,    0,    0,    0,    0,   13,    0,
    0,   13,   13,   13,    0,    0,    0,    0,    0,    0,
    0,    0,    9,    0,    0,    0,   59,   59,   39,   40,
    0,    0,    0,    0,   59,   59,   41,   42,   32,   32,
   32,   32,    0,   42,   42,   42,   42,    0,   41,   41,
   41,   41,    0,    0,   12,   14,   61,   62,   63,   64,
   12,   25,    0,   12,   12,   12,    0,   26,    0,   25,
   27,   28,   29,    0,    0,   26,   25,    0,   27,   28,
   29,    0,   26,    0,    0,   27,   28,   29,
};
short yycheck[] = {                                      40,
   41,   40,   59,   41,  260,   75,   76,   40,   41,   42,
   43,   44,   45,   41,   47,   43,   44,   45,   41,   19,
   43,   44,   45,   93,  268,   41,   59,   60,   43,   62,
   45,   59,   60,   44,   62,   35,   59,   60,   40,   62,
   36,   37,   38,   78,   79,   60,   41,   62,  123,   44,
   61,  268,   10,   41,   59,   51,   44,   53,   44,   17,
   95,   59,   42,   44,   59,  268,  123,   47,  125,   59,
   43,   59,   45,   40,   40,   61,   59,   59,   78,   79,
   59,   40,   59,   61,  268,   59,   82,   41,   41,   41,
   86,   41,  258,   44,   59,   95,   44,    0,    0,   41,
   41,   22,   59,    4,   73,   69,   -1,   70,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,
  125,   -1,   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,
   -1,   -1,   -1,  123,   -1,  125,   -1,   -1,   -1,   -1,
  123,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,  265,   -1,
   -1,  268,  269,  270,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  260,   -1,   -1,   -1,  267,  268,  267,  268,
   -1,   -1,   -1,   -1,  275,  276,  275,  276,  271,  272,
  273,  274,   -1,  271,  272,  273,  274,   -1,  271,  272,
  273,  274,   -1,   -1,  259,  260,  271,  272,  273,  274,
  265,  259,   -1,  268,  269,  270,   -1,  265,   -1,  259,
  268,  269,  270,   -1,   -1,  265,  259,   -1,  268,  269,
  270,   -1,  265,   -1,   -1,  268,  269,  270,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 277
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"AND","ELSE","IF","INT","NOT","OR","PRINT","READ","WHILE",
"MAIN","DEC_CONST","ID","RETURN","BREAK","GE","LE","EQ","NE","TRUE","FALSE",
"VOID",
};
char *yyrule[] = {
"$accept : Program",
"Program :",
"Program : MethList",
"MethList : METH MethList",
"MethList : METH",
"METH : TYPE ID '(' Params ')' Body",
"Params :",
"Params : FORMALS TYPE ID",
"FORMALS : FORMALS TYPE ID ','",
"FORMALS :",
"TYPE : INT",
"Body : '{' Decls Stmts '}'",
"Decls : DeclList Decl",
"Decls :",
"DeclList : DeclList Decl",
"DeclList :",
"Decl : TYPE ID Vars ';'",
"Decl : TYPE ID '=' Expr Vars ';'",
"Vars : ',' ID Vars",
"Vars : ',' ID '=' Expr Vars",
"Vars :",
"Stmts : Stmts Stmt",
"Stmts :",
"Stmt : Assign ';'",
"Stmt : RETURN Expr ';'",
"Stmt : IF '(' Expr ')' Stmt ELSE Stmt",
"Stmt : WHILE '(' Expr ')' Stmt",
"Stmt : BREAK ';'",
"Stmt : Block",
"Stmt : ';'",
"Block : '{' Stmts '}'",
"Assign : Location '=' Expr",
"Location : ID",
"Expr : AddExpr Relop AddExpr",
"Expr : AddExpr",
"Relop : LE",
"Relop : '<'",
"Relop : '>'",
"Relop : GE",
"Relop : EQ",
"Relop : NE",
"AddExpr : AddExpr Addop Term",
"AddExpr : Term",
"Addop : '+'",
"Addop : '-'",
"Term : Term Mulop Factor",
"Term : Factor",
"Mulop : '*'",
"Mulop : '/'",
"Factor : '(' Expr ')'",
"Factor : Location",
"Factor : DEC_CONST",
"Factor : METHOD '(' Actuals ')'",
"Factor : TRUE",
"Factor : FALSE",
"METHOD : ID",
"Actuals : Args Expr",
"Actuals :",
"Args : Args Expr ','",
"Args :",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 358 "syd2"


/*Η MkNode δημιουργεί δυναμικά έναν κόμβο AST, αρχικοποιεί τον τύπο του κόμβου (NodeType), συνδέει το 
συμβολικό δείκτη (SymbolNode) και αντιγράφει τους τέσσερις δείκτες παιδιών που της δίνονται (z0..z3). Επίσης 
αρχικοποιεί την value στο 0. Χρησιμοποιείται παντού στον parser για να χτίσει το δέντρο σύνταξης.
*/
AstNode *MkNode(int tipos,symbol *sn,AstNode *z0,AstNode *z1,AstNode *z2,AstNode *z3) {
   /* Δημιουργεί και επιστρέφει ένα νέο AstNode.
      Παραλαμβάνει:
        - tipos: ο κωδικός/τύπος κόμβου (π.χ. N_METH, N_ID ...)
        - sn: δείκτης σε symbol (π.χ. για N_ID ή N_METHOD)
        - z0..z3: δείκτες σε έως τέσσερα παιδιά (μπορεί να είναι NULL)
   */
   AstNode *p=(AstNode *)malloc(sizeof(AstNode)); // Δέσμευση μνήμης
   p->NodeType=tipos;           // Θέτουμε τον τύπο του κόμβου
   p->SymbolNode=sn;           // Θέτουμε το σχετικό symbol (αν υπάρχει)
   p->pAstNode[0]=z0;          // Συνδέουμε το 1ο παιδί
   p->pAstNode[1]=z1;          // Συνδέουμε το 2ο παιδί
   p->pAstNode[2]=z2;          // Συνδέουμε το 3ο παιδί
   p->pAstNode[3]=z3;          // Συνδέουμε το 4ο παιδί
   p->value=0;                 // Προεπιλεγμένη τιμή (χρήσιμο για σταθερές)
   return(p);                  // Επιστρέφουμε τον νέο κόμβο
}


/*Η new_symbol δημιουργεί και αρχικοποιεί ένα νέο symbol δομής για ένα όνομα (π.χ. μεταβλητής ή μεθόδου). 
Αντιγράφει το όνομα μέσα στο πεδίο name (με όριο NAME_MAX), αρχικοποιεί timi, lvalue, typos, καθαρίζει το 
scope_name και τις συνδέσεις NextSymbol/PrevSymbol. Επιστρέφει τον καινούριο συμβολισμό.
*/
symbol* new_symbol(const char* name) {
    /* Δημιουργεί ένα νέο symbol με αρχικές προδιαγραφές.
       Χρησιμοποιείται σε δηλώσεις ID, σε δημιουργία const temporaries κ.λπ.
    */
    symbol* s = (symbol*)malloc(sizeof(symbol));   // Δέσμευση μνήμης για το symbol
    // Αντιγραφή ονόματος με όριο NAME_MAX και τερματισμό '\0'
    strncpy((char*)s->name, name, NAME_MAX);
    s->name[NAME_MAX-1] = 0;

    // Αρχικές τιμές
    s->timi = 0;           // τιμή/αρχικοποίηση = 0 (προεπιλογή)
    s->lvalue = 1;         // προεπιλεγμένο ότι είναι lvalue (μπορεί να αλλάξει)
    s->typos = 0;          // τύπος άγνωστος/προεπιλογή
    s->scope_name[0] = '\0'; // δεν έχει scope ακόμα
    s->NextSymbol = NULL;  // δεν είναι συνδεδεμένο στη λίστα
    s->PrevSymbol = NULL;
    return s;              // επιστρέφει το νέο symbol
}

/*Η addsymb προσθέτει ένα symbol στην global (σύνδετη) λίστα SymbolTable. 
Αν το SymbolTable είναι κενό, το νέο symbol γίνεται η αρχή της λίστας. Αλλιώς 
προστίθεται στο τέλος της συνδεδεμένης λίστας
*/
void addsymb(symbol* s) {
    if (!s) return; // Αν δεν υπάρχει symbol, τίποτα να κάνουμε

    if (!SymbolTable) {
        // Αν ο πίνακας είναι κενός, το s γίνεται η πρώτη εγγραφή
        SymbolTable = s;
    } else {
        // Διασχίζουμε μέχρι το τέλος της λίστας και προσθέτουμε το s
        symbol* p = SymbolTable;
        while (p->NextSymbol) p = p->NextSymbol; // πηγαίνουμε στο τελευταίο
        p->NextSymbol = s;       // συνδέουμε το νέο στο τέλος
        s->PrevSymbol = p;       // οπισθιοσύνδεσμος
    }
}

/*Η findsymb ψάχνει τη συνδεδεμένη λίστα SymbolTable για συμβολο με συγκεκριμένο 
name και συγκεκριμένο scope. Επιστρέφει τον δείκτη στο symbol αν βρεθεί, αλλιώς NULL. 
Χρησιμοποιείται για να αποφευχθούν διπλές δηλώσεις στο ίδιο scope και για να εντοπιστούν 
μεταβλητές/μέθοδοι κατά τον έλεγχο.
*/
symbol* findsymb(const char* name, const char* scope) {
    // Ξεκινάμε από την αρχή της λίστας και ψάχνουμε για ίδιο όνομα ΚΑΙ ίδιο scope
    symbol* p = SymbolTable;
    while (p) {
        if (strcmp(p->name, name) == 0 && strcmp(p->scope_name, scope) == 0) {
            return p; // βρέθηκε ίδια μεταβλητή στο ίδιο scope
        }
        p = p->NextSymbol; // πηγαίνουμε στον επόμενο symbol
    }
    return NULL; // δεν βρέθηκε
}

/*Η βοηθητική type_to_string μετατρέπει τον ακέραιο κωδικό τύπου (INT, VOID κ.λπ.) σε 
ανθρώπινη αναγνωρίσιμη συμβολοσειρά. Χρησιμοποιείται για εμφάνιση στον πίνακα συμβόλων 
(print_symbol_table).
*/
const char* type_to_string(int t) {
    switch(t) {
        case INT: return "int";
        case VOID: return "void";
        default: return "unknown"; // αν δεν αναγνωρίσουμε τον κωδικό
    }
}

/*Η συνάρτηση build_symbol_table είναι υπεύθυνη για τη δημιουργία του πίνακα συμβόλων (symbol table) 
με βάση το Abstract Syntax Tree (AST). Ο πίνακας συμβόλων κρατάει πληροφορίες για όλες τις δηλώσεις 
μεταβλητών και μεθόδων, όπως το όνομα, το scope και την αρχική τιμή. Η συνάρτηση δουλεύει αναδρομικά: ξεκινάει από 
έναν κόμβο του AST και ανάλογα με τον τύπο του (μέθοδος, παράμετρος, δήλωση μεταβλητής, λίστα μεταβλητών, κλπ.) 
ενημερώνει τον πίνακα συμβόλων και μετά συνεχίζει στους υποκόμβους. Επίσης, κάνει έλεγχο για διπλές δηλώσεις μέσα 
στο ίδιο scope και τερματίζει το πρόγραμμα αν εντοπιστεί σφάλμα. Με αυτόν τον τρόπο εξασφαλίζεται ότι το πρόγραμμα 
έχει σωστά scopes και μοναδικές δηλώσεις.
*/
void build_symbol_table(AstNode* node, const char* current_scope) {
    // Αν ο κόμβος είναι NULL (δηλ. δεν υπάρχει), σταματάμε
    if (!node) return;

    switch (node->NodeType) {
        case N_METH: {
            // --- Μέθοδος ---
            // Παίρνουμε το σύμβολο της μεθόδου (το ID της)
            symbol* method_sym = node->pAstNode[1]->SymbolNode;
            // Οι μέθοδοι ανήκουν πάντα στο global scope
            strncpy(method_sym->scope_name, "global", NAME_MAX);
            // Προσθήκη της μεθόδου στον πίνακα συμβόλων
            addsymb(method_sym);

            // Επεξεργασία παραμέτρων και σώματος με το όνομα της μεθόδου ως νέο scope
            build_symbol_table(node->pAstNode[2], method_sym->name); // Params
            build_symbol_table(node->pAstNode[3], method_sym->name); // Body
            break;
        }

        case N_PARAM:
        case N_FORMALS: {
            // --- Παράμετροι μεθόδου ---
            // Έλεγχος αν υπάρχει ID στη δήλωση
            if (node->pAstNode[2] && node->pAstNode[2]->NodeType == N_ID) {
                symbol* s = node->pAstNode[2]->SymbolNode;
                // Αν η παράμετρος δεν έχει ήδη δηλωθεί στο ίδιο scope, την προσθέτουμε
                if (!findsymb(s->name, current_scope)) {
                    strncpy(s->scope_name, current_scope, NAME_MAX);
                    addsymb(s);
                }
            }
            // Συνεχίζουμε αναδρομικά και με τις άλλες παραμέτρους
            build_symbol_table(node->pAstNode[0], current_scope);
            build_symbol_table(node->pAstNode[1], current_scope);
            break;
        }
        

        case N_DECL: {
    // --- Δήλωση μεταβλητής ---
    if (node->pAstNode[1] && node->pAstNode[1]->NodeType == N_ID) {
        symbol* s = node->pAstNode[1]->SymbolNode;

        if (!findsymb(s->name, current_scope)) {
            strncpy(s->scope_name, current_scope, NAME_MAX);

            // Έλεγχος αρχικοποίησης (προσοχή στο NodeType)
            if (node->pAstNode[2]) {
                if (node->pAstNode[2]->NodeType == N_CONST || node->pAstNode[2]->NodeType == N_BOOL) {
                    s->timi = node->pAstNode[2]->value;
                } 
                else {
                    // Δεν είναι σταθερά, μάλλον είναι VARS ή expression -> default 0
                    s->timi = 0;
                }
            } else {
                s->timi = 0;
            }

            addsymb(s);
        } else {
            fprintf(stderr, "Error: Double declaration of variable '%s' in scope '%s'\n",
                    s->name, current_scope);
            fflush(stderr);
            exit(1);
        }
    }

    // Πολύ σημαντικό: πρέπει ΠΑΝΤΑ να συνεχίσουμε την αναδρομή
    build_symbol_table(node->pAstNode[2], current_scope); 
    break;
}

        case N_VARS: {
            // --- Λίστα μεταβλητών ---
            AstNode* current = node;
            // Διατρέχουμε όλη τη λίστα μεταβλητών (comma-separated)
            while (current && current->NodeType == N_VARS) {
                // Παίρνουμε το ID της τρέχουσας μεταβλητής
                AstNode* idNode = current->pAstNode[0];
                if (idNode && idNode->NodeType == N_ID) {
                    symbol* s = idNode->SymbolNode;
                    // Αν δεν υπάρχει ήδη στο scope, την προσθέτουμε
                    if (!findsymb(s->name, current_scope)) {
                        strncpy(s->scope_name, current_scope, NAME_MAX);
                        // Έλεγχος αν έχει αρχικοποίηση
                        AstNode* maybeExpr = current->pAstNode[1];
                        if (maybeExpr && maybeExpr->NodeType == N_CONST)
                            s->timi = maybeExpr->value;
                        else
                            s->timi = 0;
                        addsymb(s);
                    } else {
                        // Σφάλμα: διπλή δήλωση
                        fprintf(stderr, "Error: Double declaration of variable '%s' in scope '%s'\n",
                                s->name, current_scope);
                        fflush(stderr);
                        exit(1);
                    }
                }
                // Προχωράμε στην επόμενη μεταβλητή της λίστας
                if (current->pAstNode[2] && current->pAstNode[2]->NodeType == N_VARS)
                    current = current->pAstNode[2];
                else if (current->pAstNode[1] && current->pAstNode[1]->NodeType == N_VARS)
                    current = current->pAstNode[1];
                else
                    break;
            }
            break;
        }

        default: {
            // --- Γενική περίπτωση ---
            // Για όλους τους άλλους κόμβους, κάνουμε αναδρομή σε όλα τα παιδιά
            for (int i = 0; i < 4; i++)
                build_symbol_table(node->pAstNode[i], current_scope);
            break;
        }
    }
}

/*Εκτυπώνει την τρέχουσα λίστα SymbolTable σε απλό πίνακα (scope, όνομα, τύπος, τιμή). 
Χρησιμοποιεί την type_to_string για να εμφανίσει τον τύπο σαν string.
*/
void print_symbol_table() {
    printf("\n--- Symbol Table ---\n");
    symbol* p = SymbolTable;
    while (p) {
        printf("Scope: %-10s | Name: %-10s | Type: %-4s | Value: %d\n ",
               p->scope_name, p->name, type_to_string(p->typos), p->timi);
        p = p->NextSymbol; 
    }
}

//Απλή συνάρτηση παροχής σφαλμάτων για τον parser
void yyerror(char *s)
{
   fputs(s,stderr); putc('\n',stderr);
}

/*Ελέγχει αν ένα όνομα είναι δεσμευμένη λέξη της γλώσσας (π.χ. int, if, main κ.λπ.). 
Επιστρέφει 1 αν είναι reserved, αλλιώς 0.
*/
int is_reserved_word(const char* name) {
    const char* reserved[] = {"int","void","return","if","else","while","break","main","print","read","true","false", NULL};
    for(int i=0; reserved[i]; i++)
        if(strcmp(reserved[i], name)==0) return 1; // βρέθηκε στο πίνακα
    return 0; // όχι reserved
}

/*Ελέγχει διαίρεση κατά το στάδιο κατασκευής εκφράσεων: παίρνει δύο operands (σύμβολα) και αν ο δεύτερος 
έχει τιμή 0 τερματίζει με error (division by zero). Διαφορετικά δημιουργεί ένα προσωρινό symbol (tmp_div) 
που αντιγράφει τα χαρακτηριστικά του πρώτου operand, το επισημαίνει ως disposable και επιστρέφει το νέο σύμβολο. 
Απελευθερώνει (discard) τα input operands αν χρειάζεται.
*/
symbol *check_divop(symbol *opnd1, symbol *opnd2) {
    if (!opnd1 || !opnd2) return NULL; // έλεγχος εγκυρότητας

    // Έλεγχος διαίρεσης με 0
    if (opnd2->timi == 0) {
         fprintf(stderr, "\nDivision by zero!\n");
         exit(1); // τερματίζουμε το πρόγραμμα
    }

    // Δημιουργία προσωρινού αποτελέσματος ως νέο symbol
    symbol *res = new_symbol("tmp_div");
    copy_symbol(res, opnd1);    // αντιγράφουμε εκείνα που χρειάζεται από opnd1
    res->disposable = 1;        // θα απελευθερωθεί αργότερα
    res->lvalue = 0;            // αποτέλεσμα έκφρασης => όχι lvalue

    // Απελευθερώνουμε τα αρχικά operands αν ήταν disposable
    discard_symbol(opnd1);
    discard_symbol(opnd2);

    return res; // επιστρέφουμε το προσωρινό σύμβολο ως αποτέλεσμα
}

/*Αναδρομικά διασχίζει το AST και ελέγχει ότι κάθε μεταβλητή (N_ID) που χρησιμοποιείται 
υπάρχει δηλωμένη στο αντίστοιχο scope (βασιζόμενο στο current_scope). Αν βρει ID χωρίς 
αντίστοιχο σύμβολο στο symbol table, εκτυπώνει προειδοποίηση/σφάλμα και τερματίζει. Επιπλέον 
ελέγχει ότι δεν χρησιμοποιείται κάποιο reserved word ως όνομα μεταβλητής.
*/
void check_undeclared_variables(AstNode* node, const char* current_scope) {
    if (!node) return;

    switch (node->NodeType) {
        case N_METH: {
            // Όταν βλέπουμε μέθοδο, η μέθοδος έχει δικό της scope (το όνομά της)
            symbol* method_sym = node->pAstNode[1]->SymbolNode;
            const char* method_scope = method_sym->name;

            // Έλεγχος του σώματος της μεθόδου στο scope της μεθόδου
            check_undeclared_variables(node->pAstNode[3], method_scope);
            break;
        }
        case N_ID: {
            // Ελέγχουμε αν το ID υπάρχει στο symbol table για το τρέχον scope
            symbol* s = node->SymbolNode;
            if (s && !findsymb(s->name, current_scope)) {
                fprintf(stderr, "Warning: Variable '%s' used but not declared in scope '%s'\n", s->name, current_scope);
                exit(1); // απλό παράδειγμα: εδώ κάνουμε exit (μπορεί να θέλεις μόνο warning)
            }
            // Έλεγχος αν χρησιμοποιείται δεσμευμένη λέξη ως μεταβλητή
            if (s && is_reserved_word(s->name)) {
                fprintf(stderr, "Error: Reserved word '%s' used as variable in scope '%s'\n", s->name, current_scope);
                exit(1);
            }
            break;
        }
        default: {
            // Γενική αναδρομή σε όλα τα παιδιά
            for (int i = 0; i < 4; i++) {
                check_undeclared_variables(node->pAstNode[i], current_scope);
            }
            break;
        }
    }
}


/*Ελέγχει αν υπάρχει στη ρίζα/στο δέντρο κάποια συνάρτηση με όνομα "main". 
Επιστρέφει 1 αν βρεθεί, αλλιώς 0. Κάνει αναδρομή σε όλα τα παιδιά.
*/
int find_main(AstNode* node) {
    if (!node) return 0;

    // Εάν είναι κόμβος μεθόδου, έλεγξε το όνομα της μεθόδου
    if (node->NodeType == N_METH) {
        AstNode* idNode = node->pAstNode[1]; // το ID της μεθόδου
        if (idNode && idNode->NodeType == N_ID && idNode->SymbolNode) {
            if (strcmp(idNode->SymbolNode->name, "main") == 0) {
                return 1; // Βρήκαμε main
            }
        }
    }

    // Αναδρομικός έλεγχος σε όλα τα παιδιά
    for (int i = 0; i < 4; i++) {
        if (find_main(node->pAstNode[i])) return 1;
    }

    return 0; // δεν βρέθηκε main πουθενά
}


/*Μετράει αναδρομικά τον αριθμό των ορισμάτων (arguments) που δίνονται σε μια κλήση 
με βάση τη δομή κόμβου N_ARGS. Επιστρέφει 0 αν δεν υπάρχουν ορίσματα.
*/
int count_arguments(AstNode *args_node) {
    if (!args_node) return 0;

    switch (args_node->NodeType) {
        case N_ARGS:
            // Προσθέτουμε 1 για το τρέχον argument και επαναλαμβάνουμε για τα προηγούμενα
            return 1 + count_arguments(args_node->pAstNode[0]);
        default:
            return 0;
    }
}

/*Η συνάρτηση count_parameters μετράει πόσες παραμέτρους έχει μια μέθοδος, με βάση τον κόμβο του AST. 
Δουλεύει αναδρομικά: ξεκινά από τον κόμβο της πρώτης παραμέτρου και προχωράει προς τα πίσω (μέσω των παιδιών του AST), 
μετρώντας κάθε φορά που βρίσκει κόμβο τύπου N_PARAM ή N_FORMALS. Επιστρέφει έναν ακέραιο με το πλήθος των παραμέτρων. 
Αν ο κόμβος είναι NULL ή δεν έχει άλλες παραμέτρους, επιστρέφει 0.
*/
int count_parameters(AstNode *params_node) {
    // Αν δεν υπάρχει καθόλου κόμβος (δηλ. δεν υπάρχουν παράμετροι)
    if (!params_node) return 0;

    // Ελέγχουμε αν ο κόμβος είναι παράμετρος (N_PARAM) ή λίστα παραμέτρων (N_FORMALS)
    if (params_node->NodeType == N_PARAM || params_node->NodeType == N_FORMALS) {
        
        // Αν υπάρχει τρίτο παιδί (δηλ. το ID της παραμέτρου υπάρχει)
        // τότε μετράμε +1 για αυτήν την παράμετρο και συνεχίζουμε αναδρομικά
        if (params_node->pAstNode[2] != NULL){ 
            return count_parameters(params_node->pAstNode[0]) + 1;
        }
    }

    // Σε κάθε άλλη περίπτωση δεν υπάρχουν παράμετροι
    return 0;  
}

/*Ελέγχει ότι κάθε κλήση μεθόδου (N_CALL) αναφέρεται σε ορισμένη μέθοδο που υπάρχει 
στο SymbolTable (στο global scope). Επίσης συγκρίνει τον αριθμό των παραμέτρων που 
δόθηκαν με τον αριθμό που δηλώθηκε (p->num_params) και πετά σφάλμα αν δεν ταιριάζουν.
Καλεί αναδρομικά για όλα τα παιδιά.
*/
void check_method_calls(AstNode* node) {
    if (!node) return;

    if (node->NodeType == N_CALL) {
        AstNode* methodNode = node->pAstNode[0]; // METHOD
        if (methodNode && methodNode->NodeType == N_METHOD) {
            symbol* s = methodNode->SymbolNode; // όνομα μεθόδου
            if (s && !findsymb(s->name, "global")) {
                fprintf(stderr, "Error: Call to undefined method '%s'\n", s->name);
                fflush(stderr);
                exit(1);
            }
            // Βρίσκουμε την δήλωση της μεθόδου στο global symbol table
            symbol* p = findsymb(s->name, "global");
            AstNode* argsNode   = node->pAstNode[1]; // Actuals
            int given_args = count_arguments(argsNode);

            // Έλεγχος αριθμού παραμέτρων
            if (p->num_params != given_args) {
                fprintf(stderr,
                    "Error: Method '%s' expects %d parameters but got %d\n",
                    p->name, p->num_params, given_args);
                fflush(stderr);
                exit(1);
            }
        }
    }

    // Αναδρομική επίσκεψη όλων των παιδιών
    for (int i = 0; i < 4; i++)
        check_method_calls(node->pAstNode[i]);
}


/*Ελέγχει ότι κάθε break στο πρόγραμμα βρίσκεται εντός ενός while. Η συνάρτηση παίρνει 
ένα flag insideWhile που μεταδίδεται στην αναδρομή — όταν βρεθεί break και το flag είναι 0, 
θεωρείται λάθος. Όταν δει N_WHILE, καλεί τα παιδιά με insideWhile = 1.
*/
void check_breaks(AstNode* node, int insideWhile) {
    if (!node) return;

    // Εάν είναι κόμβος while, τότε το περιβάλλον για τα παιδιά του είναι "μέσα σε while"
    if (node->NodeType == N_WHILE) {
        for (int i = 0; i < 4; i++) {
            check_breaks(node->pAstNode[i], 1); // είμαστε μέσα σε while τώρα
        }
        return;
    }

    // Αν είναι break και δεν είμαστε μέσα σε while -> λάθος
    if (node->NodeType == N_BREAK) {
        if (!insideWhile) {
            fprintf(stderr, "Error: 'break' outside of while!\n");
            exit(EXIT_FAILURE);
        }
    }

    // Αναδρομή στα παιδιά με το ίδιο insideWhile flag
    for (int i = 0; i < 4; i++) {
        check_breaks(node->pAstNode[i], insideWhile);
    }
}

//Κάνει χρήση της find_main για να βεβαιωθεί ότι υπάρχει συνάρτηση main στο AST. Αν δεν βρεθεί, τερματίζει με error.
void check_main_exists(AstNode* root) {
    if (!find_main(root)) {
        fprintf(stderr, "Error: no 'main' function found!\n");
        exit(EXIT_FAILURE);
    }
}


/*Εκτελεί τη διαδικασία parsing (yyparse()), ελέγχει αν το AST δημιουργήθηκε, 
χτίζει τον πίνακα συμβόλων (build_symbol_table), εκτελεί σειρά από static checks 
(ύπαρξη main, σωστή χρήση break, έλεγχος μη δηλωμένων μεταβλητών, έλεγχος κλήσεων μεθόδων), 
τρέχει traverse για εμφάνιση AST και τυπώνει τον πίνακα συμβόλων.
*/
int main(void) {
    yyparse(); // Εκτελούμε τον parser (ο parser γεμίζει το TreeRoot)
    if(TreeRoot == NULL) {
        
    } else {
        
    // 1) Κατασκευή του symbol table ξεκινώντας από το global scope
    build_symbol_table(TreeRoot, "global");

    // 2) Έλεγχος ότι υπάρχει main
    check_main_exists(TreeRoot);

    // 3) Έλεγχος σωστής χρήσης του break
    check_breaks(TreeRoot, 0);

    // 4) Έλεγχος για μη δηλωμένες μεταβλητές (global scope)
    check_undeclared_variables(TreeRoot, "global");

    // 5) Έλεγχος κλήσεων μεθόδων (ύπαρξη + αριθμός παραμέτρων)
    check_method_calls(TreeRoot);

    // 6) Traversal / προβολή AST
    traverse(TreeRoot, 0);

    // 7) Εκτύπωση symbol table 
    print_symbol_table();
    }

    
}
#line 853 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 113 "syd2"
{ yyval.stnode = NULL; }
break;
case 2:
#line 114 "syd2"
{ yyval.stnode = MkNode(N_PROGRAM, NULL, yyvsp[0].stnode, NULL, NULL, NULL); TreeRoot = yyval.stnode; }
break;
case 3:
#line 118 "syd2"
{ yyval.stnode = MkNode(N_METHLIST, NULL, yyvsp[-1].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 4:
#line 119 "syd2"
{ yyval.stnode = yyvsp[0].stnode; }
break;
case 5:
#line 123 "syd2"
{
          symbol *s = new_symbol(yyvsp[-4].ystr);   /* δημιουργία συμβόλου για τη μέθοδο*/
          s->typos = INT;
          s->timi = -1;
          s->num_params = count_parameters(yyvsp[-2].stnode); /* υπολογισμός παραμέτρων*/

          yyval.stnode = MkNode(N_METH, NULL, yyvsp[-5].stnode,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL),
                      yyvsp[-2].stnode, yyvsp[0].stnode);
      }
break;
case 6:
#line 136 "syd2"
{ yyval.stnode = NULL; }
break;
case 7:
#line 137 "syd2"
{
          symbol *s = new_symbol(yyvsp[0].ystr); /* νέα παράμετρος*/
          s->typos = INT;
          s->timi = 0;
          yyval.stnode = MkNode(N_PARAM, NULL, yyvsp[-2].stnode, yyvsp[-1].stnode,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL), NULL);
      }
break;
case 8:
#line 148 "syd2"
{
          symbol *s = new_symbol(yyvsp[-1].ystr);
          s->typos = INT;
          s->timi = 0;
          yyval.stnode = MkNode(N_FORMALS, NULL, yyvsp[-3].stnode, yyvsp[-2].stnode,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL), NULL);
      }
break;
case 9:
#line 155 "syd2"
{ yyval.stnode = NULL; }
break;
case 10:
#line 160 "syd2"
{ yyval.stnode = MkNode(N_TYPE, NULL, NULL, NULL, NULL, NULL); }
break;
case 11:
#line 165 "syd2"
{ yyval.stnode = MkNode(N_BODY, NULL, yyvsp[-2].stnode, yyvsp[-1].stnode, NULL, NULL); }
break;
case 12:
#line 169 "syd2"
{ yyval.stnode = MkNode(N_DECLS, NULL, yyvsp[-1].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 13:
#line 170 "syd2"
{ yyval.stnode = NULL; }
break;
case 14:
#line 175 "syd2"
{ yyval.stnode = MkNode(N_DECLLIST, NULL, yyvsp[-1].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 15:
#line 176 "syd2"
{ yyval.stnode = NULL; }
break;
case 16:
#line 181 "syd2"
{
          symbol *s = new_symbol(yyvsp[-2].ystr);  /* νέο σύμβολο για μεταβλητή*/
          s->typos = INT;
          s->timi = 0;
          strncpy(s->scope_name, "current_scope", NAME_MAX);

          yyval.stnode = MkNode(N_DECL, NULL, yyvsp[-3].stnode,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL), yyvsp[-1].stnode, NULL);
      }
break;
case 17:
#line 190 "syd2"
{
          symbol *s = new_symbol(yyvsp[-4].ystr);
          s->typos = INT;
          s->timi = yyvsp[-2].stnode->value; /* αρχικοποίηση με έκφραση*/
          yyval.stnode = MkNode(N_DECL, NULL, yyvsp[-5].stnode,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL), yyvsp[-2].stnode, yyvsp[-1].stnode);
      }
break;
case 18:
#line 201 "syd2"
{
          symbol *s = new_symbol(yyvsp[-1].ystr);
          s->typos= INT; s->timi=0;
          yyval.stnode = MkNode(N_VARS, NULL,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL),
                      yyvsp[0].stnode, NULL, NULL);
      }
break;
case 19:
#line 208 "syd2"
{
          symbol *s = new_symbol(yyvsp[-3].ystr);
          s->typos= INT; s->timi = yyvsp[-1].stnode->value;
          yyval.stnode = MkNode(N_VARS, NULL,
                      MkNode(N_ID, s, NULL, NULL, NULL, NULL),
                      yyvsp[-1].stnode, yyvsp[0].stnode, NULL);
      }
break;
case 20:
#line 215 "syd2"
{ yyval.stnode = NULL; }
break;
case 21:
#line 220 "syd2"
{ yyval.stnode = MkNode(N_STMTS, NULL, yyvsp[-1].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 22:
#line 221 "syd2"
{ yyval.stnode = NULL; }
break;
case 23:
#line 226 "syd2"
{ yyval.stnode = MkNode(N_ASSIGN, NULL, yyvsp[-1].stnode, NULL, NULL, NULL); }
break;
case 24:
#line 227 "syd2"
{ yyval.stnode = MkNode(N_RETURN, NULL, yyvsp[-1].stnode, NULL, NULL, NULL); }
break;
case 25:
#line 228 "syd2"
{ yyval.stnode = MkNode(N_IF, NULL, yyvsp[-4].stnode, yyvsp[-2].stnode, yyvsp[0].stnode, NULL); }
break;
case 26:
#line 229 "syd2"
{ yyval.stnode = MkNode(N_WHILE, NULL, yyvsp[-2].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 27:
#line 230 "syd2"
{ yyval.stnode = MkNode(N_BREAK, NULL, NULL, NULL, NULL, NULL); }
break;
case 28:
#line 231 "syd2"
{ yyval.stnode = yyvsp[0].stnode; }
break;
case 29:
#line 232 "syd2"
{ yyval.stnode = NULL; }
break;
case 30:
#line 237 "syd2"
{ yyval.stnode = MkNode(N_BLOCK, NULL, yyvsp[-1].stnode, NULL, NULL, NULL); }
break;
case 31:
#line 242 "syd2"
{
          yyval.stnode = MkNode(N_ASSIGN, NULL, yyvsp[-2].stnode, yyvsp[0].stnode, NULL, NULL);
          if (yyvsp[-2].stnode->SymbolNode && yyvsp[0].stnode) yyvsp[-2].stnode->SymbolNode->timi = yyvsp[0].stnode->value; /* ενημέρωση τιμής*/
      }
break;
case 32:
#line 250 "syd2"
{ 
          symbol *s = new_symbol(yyvsp[0].ystr); 
          s->typos = INT; 
          s->timi = 0; 
          yyval.stnode = MkNode(N_ID, s, NULL, NULL, NULL, NULL); 
      }
break;
case 33:
#line 260 "syd2"
{ yyval.stnode = MkNode(N_RELOP, NULL, yyvsp[-2].stnode, yyvsp[-1].stnode, yyvsp[0].stnode, NULL); }
break;
case 34:
#line 261 "syd2"
{ yyval.stnode = yyvsp[0].stnode; }
break;
case 35:
#line 266 "syd2"
{ yyval.stnode = MkNode(N_LE, NULL, NULL, NULL, NULL, NULL); }
break;
case 36:
#line 267 "syd2"
{ yyval.stnode = MkNode(N_LT, NULL, NULL, NULL, NULL, NULL); }
break;
case 37:
#line 268 "syd2"
{ yyval.stnode = MkNode(N_GT, NULL, NULL, NULL, NULL, NULL); }
break;
case 38:
#line 269 "syd2"
{ yyval.stnode = MkNode(N_GE, NULL, NULL, NULL, NULL, NULL); }
break;
case 39:
#line 270 "syd2"
{ yyval.stnode = MkNode(N_EQ, NULL, NULL, NULL, NULL, NULL); }
break;
case 40:
#line 271 "syd2"
{ yyval.stnode = MkNode(N_NE, NULL, NULL, NULL, NULL, NULL); }
break;
case 41:
#line 276 "syd2"
{ yyval.stnode = MkNode(N_ADDOP, NULL, yyvsp[-2].stnode, yyvsp[-1].stnode, yyvsp[0].stnode, NULL); }
break;
case 42:
#line 277 "syd2"
{ yyval.stnode = yyvsp[0].stnode; }
break;
case 43:
#line 281 "syd2"
{ yyval.stnode = MkNode(N_PLUS, NULL, NULL, NULL, NULL, NULL); }
break;
case 44:
#line 282 "syd2"
{ yyval.stnode = MkNode(N_MINUS, NULL, NULL, NULL, NULL, NULL); }
break;
case 45:
#line 287 "syd2"
{
          symbol *op2 = pop_vs();
          symbol *op1 = pop_vs();

          if (yyvsp[-1].stnode->NodeType == N_DIV) {
              yyval.stnode = MkNode(N_DIV, NULL, yyvsp[-2].stnode, yyvsp[0].stnode, NULL, NULL);
              push_vs(check_divop(op1, op2)); /* έλεγχος διαίρεσης*/
          } else if (yyvsp[-1].stnode->NodeType == N_MUL) {
              yyval.stnode = MkNode(N_MUL, NULL, yyvsp[-2].stnode, yyvsp[0].stnode, NULL, NULL);
              /*push_vs(check_multop(op1, op2)); // έλεγχος πολλαπλασιασμού (προαιρετικός)*/
          }
      }
break;
case 46:
#line 299 "syd2"
{ yyval.stnode = yyvsp[0].stnode; }
break;
case 47:
#line 303 "syd2"
{ yyval.stnode = MkNode(N_MUL, NULL, NULL, NULL, NULL, NULL); }
break;
case 48:
#line 304 "syd2"
{ yyval.stnode = MkNode(N_DIV, NULL, NULL, NULL, NULL, NULL); }
break;
case 49:
#line 308 "syd2"
{ yyval.stnode = yyvsp[-1].stnode; }
break;
case 50:
#line 309 "syd2"
{ 
          yyval.stnode = yyvsp[0].stnode; 
          if (yyvsp[0].stnode && yyvsp[0].stnode->SymbolNode) {
              push_vs(yyvsp[0].stnode->SymbolNode);   /* βάζει το symbol της μεταβλητής στη στοίβα*/
          }
      }
break;
case 51:
#line 315 "syd2"
{ 
          /* Δημιουργία προσωρινού συμβόλου για σταθερά*/
          symbol *s = new_symbol("const");
          s->timi = yyvsp[0].yint;        
          s->disposable = 1;   /* να απελευθερωθεί μετά*/
          s->lvalue = 0;       /* δεν είναι lvalue*/
          push_vs(s);          

          yyval.stnode = MkNode(N_CONST, NULL, NULL, NULL, NULL, NULL);
          yyval.stnode->value = yyvsp[0].yint;
      }
break;
case 52:
#line 326 "syd2"
{ yyval.stnode = MkNode(N_CALL, NULL, yyvsp[-3].stnode, yyvsp[-1].stnode, NULL, NULL); }
break;
case 53:
#line 327 "syd2"
{ symbol *s = new_symbol("true");
             s->typos= INT; s->timi=1;
             yyval.stnode=MkNode(N_BOOL,s,NULL,NULL,NULL,NULL);
             yyval.stnode->value = 1; }
break;
case 54:
#line 332 "syd2"
{ symbol *s = new_symbol("false");
              s->typos= INT; s->timi=0;
              yyval.stnode=MkNode(N_BOOL,s,NULL,NULL,NULL,NULL);
              yyval.stnode->value = 0; }
break;
case 55:
#line 340 "syd2"
{ 
          symbol* s = new_symbol(yyvsp[0].ystr);  /* νέο σύμβολο για μέθοδο*/
          yyval.stnode = MkNode(N_METHOD, s, NULL, NULL, NULL, NULL); 
      }
break;
case 56:
#line 348 "syd2"
{ yyval.stnode = MkNode(N_ARGS, NULL, yyvsp[-1].stnode, yyvsp[0].stnode, NULL, NULL); }
break;
case 57:
#line 349 "syd2"
{ yyval.stnode = NULL; }
break;
case 58:
#line 354 "syd2"
{ yyval.stnode = MkNode(N_ARGS, NULL, yyvsp[-2].stnode, yyvsp[-1].stnode, NULL, NULL); }
break;
case 59:
#line 355 "syd2"
{ yyval.stnode = NULL; }
break;
#line 1320 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
