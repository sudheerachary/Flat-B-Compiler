%{
#include "AstDefs.h"
#include "parser.tab.h"

#include <bits/stdc++.h>

#define YY_DECL extern "C" int yylex()

extern union Node yylval;
using namespace std;
%}

%%
"int"					{ printf("<int> "); yylval.val = strdup(yytext); return INT; }
"print"					{ printf("<PRINT> "); return PRINT; }
"println"				{ printf("<PRINTLN> "); return PRINTLN; }
"read"					{ printf("<READ> "); return READ; }
"for"					{ printf("<FOR> "); return FOR; }
"if"					{ printf("<IF> "); return IF; }
"else"					{ printf("<ELSE> "); return ELSE; }
"got"					{ printf("<GOT> "); return GOT; }
"goto"					{ printf("<GOTO> "); return GOTO; }
"while"					{ printf("<WHILE> "); return WHILE; }
[0-9][0-9]*				{ printf("<NUMBER> "); yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* 	{ printf("<IDENTIFIER> "); yylval.val = strdup(yytext); return IDENTIFIER; }
";"						{ printf(";"); return SC; } 
","						{ printf("<,> "); return COMMA; }
"+"						{ printf("<+> "); yylval.val = strdup(yytext); return ADD; }
"-"						{ printf("<-> "); yylval.val = strdup(yytext); return SUB; }
"*"						{ printf("<*> "); yylval.val = strdup(yytext); return MUL; }
"&&"					{ printf("<&&> "); yylval.val = strdup(yytext); return AND;}	
"||"					{ printf("<||> "); yylval.val = strdup(yytext); return OR;}
"!="					{ printf("<!=> "); yylval.val = strdup(yytext); return NOTEQUALS;}
"!"						{ printf("<!> "); yylval.val = strdup(yytext); return NOT; }
"/"						{ printf("</> "); yylval.val = strdup(yytext); return DIV; }
"%"						{ printf("<MOD> "); yylval.val = strdup(yytext); return MOD; }
"{"						{ printf("<{> "); return OP; }
"}"						{ printf("<}> "); return CP; }
"["						{ printf("<[> "); return OSB; }
"]"						{ printf("<]> "); return CSB; }
"=="					{ printf("<==> "); yylval.val = strdup(yytext); return EQUALS; }
"="						{ printf("<=> "); return EQ; }
">"						{ printf("<'>'> "); return G; }
"<"						{ printf("<'<'> "); return L; }
":"						{ printf("<:> "); return COL; }
L?\"(\\.|[^\\"])*\"		{ printf("<%s> ", yytext); yylval.val = strdup(yytext); return STRING; }
([ \t]|[ \n])			{ /* Do nothing */ }
.						{ return ETOK; }
%%