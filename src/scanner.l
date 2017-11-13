%{
#include "AstDefs.h"
#include "parser.tab.h"
#include <bits/stdc++.h>

#define YY_DECL extern "C" int yylex()

extern union Node yylval;
using namespace std;
%}

%%
"int"					{ yylval.val = strdup(yytext); return INT; }
"print"					{ return PRINT; }
"println"				{ return PRINTLN; }
"read"					{ return READ; }
"for"					{ return FOR; }
"if"					{ return IF; }
"else"					{ return ELSE; }
"got"					{ return GOT; }
"goto"					{ return GOTO; }
"while"					{ return WHILE; }
[0-9][0-9]*				{ yylval.num = atoi(yytext); return NUMBER; }
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
"{"						{ return OP; }
"}"						{ return CP; }
"["						{ return OSB; }
"]"						{ return CSB; }
"=="					{ yylval.val = strdup(yytext); return EQUALS; }
"="						{ return EQ; }
">"						{ yylval.val = strdup(yytext); return G;	}
"<"						{ yylval.val = strdup(yytext); return L; }
":"						{ return COL; }
\"(\\n|\\t|\\'|\\\\|\\\"|[^\\"'])*\"	{ yylval.val = strdup(yytext); return STRING; }
([ \t]|[ \n])			{ /* Do nothing */ }
.						{ return ETOK; }
%%