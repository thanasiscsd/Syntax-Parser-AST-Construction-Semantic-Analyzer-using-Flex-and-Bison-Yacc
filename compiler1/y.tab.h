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
typedef union {
    int   yint;                 /* ακέραια τιμή*/
    char  *ystr;                /* string (ονόματα)*/
    int   nonterm;              /* για ενδιάμεσα*/
    struct AstNode *stnode;     /* δείκτης σε κόμβο AST*/
} YYSTYPE;
extern YYSTYPE yylval;
