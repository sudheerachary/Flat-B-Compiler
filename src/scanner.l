%{
#include "parser.tab.h"
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
";"						{ return ';'; } 
","						{ return ','; }
"+"						{ return '+'; }
"-"						{ return '-'; }
"*"						{ return '*'; }
("{"|"<%")				{ return '{'; }
("}"|"%>")				{ return '}'; }
"["						{ return '['; }
"]"						{ return ']'; }
"=="					{ return EQUALS; }
"="						{ return '='; }
">"						{ return '>'; }
"<"						{ return '<'; }
":"						{ return ':'; }
L?\"(\\.|[^\\"])*\"		{ return STRING; }
([ \t]|[ \n])			{ /* Do nothing */ }
.						{ return ETOK; }

