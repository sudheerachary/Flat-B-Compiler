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
[a-zA-Z][a-zA-Z0-9]* 	{ return IDENTIFIER; }
";"						{ return SC; } 
","						{ return COMMA; }
"+"						{ return ADD; }
"-"						{ return SUB; }
"*"						{ return MUL; }
"&&"					{ return AND;}	
"||"					{ return OR;}
"!="					{ return NOTEQUALS;}
"!"						{ return NOT; }
"/"						{ return DIV; }
"%"						{ return MOD; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
"["						{ return '['; }
"]"						{ return ']'; }
"=="					{ return EQUALS; }
"="						{ return EQ; }
">"						{ return G; }
"<"						{ return L; }
":"						{ return COL; }
L?\"(\\.|[^\\"])*\"		{ return STRING; }
([ \t]|[ \n])			{ /* Do nothing */ }
.						{ return ETOK; }
%%