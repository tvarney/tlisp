%top{
#include "parser.h"
#include "parser.tab.h"
#include "Node.h"
#include "UnaryNodes.h"
}

%option noyywrap nounput

INT     [+-]?[0-9]+
UINT    [0-9]+
FLOAT   [+-]?
CHAR    \'([[:print:]]|\\[[:print:]])\'
STRING \"([[:print:]]|\\[[:print:]])*\"

%%

;[^\n\r]*[\n\r]+  /* Consume comments */
[:space:]*        /* return TOKEN_SPACE to ensure things are spaced out? */

"Nil" {
    yylval = (struct Node *)NilNode;
    return T_VALUE;
}
"true" {
    yylval = (struct Node *)TrueNode;
    return T_VALUE;
}
"false" {
    yylval = (struct Node *)FalseNode;
    return T_VALUE;
}
{INT} {
    yylval = (struct Node *)ValueNode_new(VALUE_INT,
                                          (union ValueData)atoi(yytext));
    return T_VALUE;
}
{FLOAT}[fF] {
    yylval = (struct Node *)ValueNode_new(VALUE_FLOAT,
                                          (union ValueData)strtof(yytext,
                                                                  NULL));
    return T_VALUE;
}
{FLOAT} {
    yylval = (struct Node *)ValueNode_new(VALUE_DOUBLE,
                                          (union ValueData)strtod(yytext,
                                                                  NULL));
    return T_VALUE;
}

. { return yytext[0]; }

%%
