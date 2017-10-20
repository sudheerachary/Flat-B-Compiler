%{
#include <bits/stdc++.h>
#include "AstDefs.h"
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
extern union Node yylval;
using namespace std;
%}

%%
"int"					{ return INT; }
"print"					{ return PRINT; }
"println"				{ return PRINTLN; }
"read"					{ return READ; }
"for"					{ return FOR; }
"if"					{ return IF; }
"else"					{ return ELSE; }
"got"					{ return GOT; }
"goto"					{ return GOTO; }
[0-9][0-9]*				{ return NUMBER; }
[a-zA-Z][a-zA-Z0-9]* 	{ yylval.val = strdup(yytext); return IDENTIFIER; }
";"						{ return SC; } 
","						{ return COMMA; }
"+"						{ yylval.val = strdup(yytext); return ADD; }
"-"						{ yylval.val = strdup(yytext); return SUB; }
"*"						{ yylval.val = strdup(yytext); return MUL; }
"&&"					{ yylval.val = strdup(yytext); return AND;}	
"||"					{ yylval.val = strdup(yytext); return OR;}
"!="					{ yylval.val = strdup(yytext); return NOTEQUALS;}
"!"						{ yylval.val = strdup(yytext); return NOT; }
"/"						{ yylval.val = strdup(yytext); return DIV; }
"%"						{ yylval.val = strdup(yytext); return MOD; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
"["						{ return '['; }
"]"						{ return ']'; }
"=="					{ return EQUALS; }
"="						{ return EQ; }
">"						{ return G; }
"<"						{ return L; }
":"						{ return COL; }
L?\"(\\.|[^\\"])*\"		{ yylval.val = strdup(yytext); return STRING; }
([ \t]|[ \n])			{ /* Do nothing */ }
.						{ return ETOK; }
%%