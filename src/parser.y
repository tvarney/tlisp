
%{
    #include <stdint.h>
    #include <stdio.h>
    #include "parser.h"
    #include "UnaryNodes.h"
    #include "BinaryNodes.h"
    int yylex(void);
    void yyerror(char const *msg);
%}

%defines

%token T_VALUE
%token T_SYMBOL
%token T_SPACE

%%

node:
  "'" subnode                 { $$ = $2; }
| "(" "+" subnode subnode ")" { $$ = (struct Node *)AddNode_new($3, $4); }
| "(" "-" subnode subnode ")" { $$ = (struct Node *)SubNode_new($3, $4); }
| "(" "*" subnode subnode ")" { $$ = (struct Node *)MulNode_new($3, $4); }
| "(" "/" subnode subnode ")" { $$ = (struct Node *)DivNode_new($3, $4); }
| "(" "%" subnode subnode ")" { $$ = (struct Node *)ModNode_new($3, $4); }
| "(" "-" subnode ")"         { $$ = (struct Node *)NumNegNode_new($3); }
| "(" "!" subnode ")"         { $$ = (struct Node *)BoolNegNode_new($3); }
| "(" "not" subnode ")"       { $$ = (struct Node *)BoolNegNode_new($3); }
| "(" "~" subnode ")"         { $$ = (struct Node *)ComplementNode_new($3); }
| "(" "abs" subnode ")"       { $$ = (struct Node *)AbsNode_new($3); }
  ;

subnode:
  T_VALUE
| node
  ;

%%

void yyerror(char const *msg) {
    fprintf(stderr, "error: %s\n", msg);
}
