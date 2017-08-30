%{
  #include <stdio.h>
  #include <stdlib.h>
  FILE *yyin;
  int yylex (void);
  void yyerror (char const *s);
%}

%token NUMBER
%token IDENTIFIER
%token EQUALS
%token STRING
%token WHILE
%token GOT
%token IF
%token ELSE
%token FOR
%token INT
%token GOTO
%token PRINT
%token READ
%token ETOK
%left '+'
%left '*'

%%
program:	decl_block code_block

decl_block:  '{' declarations '}'

code_block:  '{' statements '}'

declarations:	INT decl ';'
			|	INT decl ';' declarations
			;

decl:	IDENTIFIER
	|	IDENTIFIER '[' NUMBER ']'
	|	IDENTIFIER ',' decl
	|	IDENTIFIER '[' NUMBER ']' ',' decl	
	;

statements:		assignment
		|		assignment statements
		|		IDENTIFIER ':' assignment
		|		IDENTIFIER ':' assignment statements
		|		for_block
		|		for_block statements
		|		IDENTIFIER ':' for_block
		|		IDENTIFIER ':' for_block statements
		|		if_block
		|		if_block statements
		|		IDENTIFIER ':' if_block
		|		IDENTIFIER ':' if_block statements
		| 		while_block
		|		while_block statements
		| 		IDENTIFIER ':' while_block
		|		IDENTIFIER ':' while_block statements
		|		goto_block
		|		goto_block statements
		|		IDENTIFIER ':' goto_block
		|		IDENTIFIER ':' goto_block statements
		|		read_line
		|		read_line statements
		|		IDENTIFIER ':' read_line
		|		IDENTIFIER ':' read_line statements
		|		print_line
		|		print_line statements
		|		IDENTIFIER ':' print_line
		|		IDENTIFIER ':' print_line statements
		;

assignment:		value '=' expression

for_block:		FOR IDENTIFIER '=' value ',' value '{' statements '}'
		|		FOR IDENTIFIER '=' value ',' value ',' value '{' statements '}'
		|		FOR IDENTIFIER '=' NUMBER ',' NUMBER '{' statements '}'
		|		FOR IDENTIFIER '=' NUMBER ',' NUMBER ',' NUMBER '{' statements '}'
		;

if_block:	IF conditional '{' statements '}'
		|	IF conditional '{' statements '}' ELSE '{' statements '}'
		;

while_block:	WHILE conditional '{' statements '}'

goto_block:		GOTO IDENTIFIER IF conditional
		|		GOT IDENTIFIER
		;

print_line:		PRINT STRING ',' value
		|		PRINT STRING
		|		PRINT value
		;

read_line:		READ value

conditional:	expression '<' expression
		|		expression '>' expression
		|		expression EQUALS expression	
		;

expression: 	expression '+' expression 
		|		expression '*' expression 
		| 		value
		|		NUMBER
		;

value:	IDENTIFIER
	|	IDENTIFIER'['NUMBER']'
	|	IDENTIFIER'['IDENTIFIER']'	
	;
%%

void yyerror (char const *s)
{
       fprintf (stderr, "%s\n", s);
}

int main(int argc, char *argv[])
{
	if (argc == 1 ) {
		fprintf(stderr, "Correct usage: bcc filename\n");
		exit(1);
	}

	if (argc > 2) {
		fprintf(stderr, "Passing more arguments than necessary.\n");
		fprintf(stderr, "Correct usage: bcc filename\n");
	}

	yyin = fopen(argv[1], "r");
	yyparse();
}
