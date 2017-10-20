%{
  #include <bits/stdc++.h>
  #include "AstDefs.h"
  extern "C" int yylex();
  extern "C" int yyparse();
  extern union Node yylval;
  void yyerror (char const *s);
  class Main *root = NULL;
%}

%token <num> NUMBER
%token <val> IDENTIFIER
%token <val> EQUALS
%token <val> STRING
%token WHILE
%token GOT
%token IF
%token ELSE
%token FOR
%token <val> INT
%token GOTO
%token <val> PRINT
%token <val> PRINTLN
%token READ
%token ETOK
%token <val> DIV
%token <val> MOD
%token <val> AND
%token <val> OR
%token <val> NOT
%token <val> SC
%token <val> NOTEQUALS
%token <val> COMMA
%token <val> ADD
%token <val> MUL
%token <val> SUB
%token <val> G
%token <val> L
%token <val> EQ
%token <val> COL

%left EQUALS NOTEQUALS
%left AND OR
%left L G
%left ADD SUB
%left MUL DIV MOD
%nonassoc NOT

%type <main> program
%type <fields> declarations
%type <field> declaration
%type <vars> variables
%type <var> variable
%type <stmts> statements
%type <loc> value
%type <expr> expression
%type <assignstmt> assignment
%type <forstmt> for_block
%type <ifelsestmt> if_block
%type <whilestmt> while_block
%type <gotostmt> goto_block
%type <print> print_line
%type <read> read_line
%type <block> block

%%
program:	'{' declarations '}' '{' statements '}' 
{
	$$ = new Main($2, $5);
	root = $$;
}

declarations:	{	$$ = new FieldDeclarations();	}
			|	declarations declaration SC
			{	$$->store($2);	}

declaration:	INT variables
			{	$$ = new FieldDeclaration(string($1), $2);	}


variables:	{	$$ = new Variables();	}
	|	variables COMMA variable
	{	$$->store($3);	}
	;

variable:	IDENTIFIER
		{	$$ = new Variable(string("Not Array"), string($1));	}
		|	IDENTIFIER '[' NUMBER ']'
		{	$$ = new Variable(string("Array"), string($1), $3);	}

statements:	{	$$ = new Statements();	}
		|	statements assignment 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL assignment 
		{	$4->setLabel(string($2));
			$$->store($4);	}
		|	statements for_block 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL for_block 
		{	$4->setLabel($2);	
			$$->store($4);	}
		|	statements if_block 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL if_block 
		{	$4->setLabel($2);	
			$$->store($4);	}
		|	statements while_block 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL while_block 
		{	$4->setLabel($2);	
			$$->store($4);	}
		|	statements goto_block SC 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL goto_block 
		{	$4->setLabel($2);	
			$$->store($4);	}
		|	statements read_line SC 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL read_line 
		{	$4->setLabel($2);	
			$$->store($4);	}
		|	statements print_line SC 
		{	$$->store($2);	}
		|	statements IDENTIFIER COL print_line SC 
		{	$4->setLabel($2);	
			$$->store($4);	}
		;

assignment:	value EQ expression SC
		{	$$ = new Assignment($1, $3);	}

expression: 	expression SUB expression
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression ADD expression 
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression MUL expression 
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression DIV expression 
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression MOD expression 
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression L expression
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression G expression
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression EQUALS expression	
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression NOTEQUALS expression
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression AND expression
		{	$$ = new Expression($1, string($2), $3);	}
		|		expression OR expression
		{	$$ = new Expression($1, string($2), $3);	}
		| 		value
		{	$$ = new Expression($1);	}
		;

value:	IDENTIFIER
	{	$$ = new Location(string($1));	}
	|	IDENTIFIER '[' NUMBER ']'
	{	$$ = new Location(string($1), $3);	}
	|	IDENTIFIER '[' IDENTIFIER ']'	
	{	$$ = new Location(string($1), string($3));	}
	|	NUMBER
	{	$$ = new Location($1);	}
	;

for_block:	FOR IDENTIFIER EQ value COMMA value block
		{	$$ = new ForStatement(string($2), $4, $6, $7);	}
		|	FOR IDENTIFIER EQ value COMMA value COMMA value block
		{	$$ = new ForStatement(string($2), $4, $6, $8, $9);	}
		;

if_block:	IF expression block
		{	$$ = new IfElseStatement($2, $3);	}
		|	IF expression block ELSE block
		{	$$ = new IfElseStatement($2, $3, $5);	}
		;

while_block:	WHILE expression block
			{	$$ = new WhileStatement($2, $3);	}

goto_block:	GOTO IDENTIFIER IF expression
		{	$$ = new GotoStatement(string($2), $4);	}
		|	GOT IDENTIFIER
		{	$$ = new GotoStatement(string($2));	}
		;

block:	'{' statements '}'
		{	$$ = new Block($2);	}
		;

print_line:	PRINT STRING COMMA value SC
		{	$$ = new Print($2, $4);	}
		|	PRINT STRING SC
		{	$$ = new Print($2);	}
		|	PRINT value SC
		{	$$ = new Print($2);	}
		|	PRINTLN STRING SC
		{	$$ = new Print($2);	}
		;

read_line:	READ value SC
		{	$$ = new ReadLine($2);	}

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

	FILE *yyin = fopen(argv[1], "r");

	if (yyin == NULL){
		printf("Can't open the given file!\n");
		exit(-1);
	}
	do {
		yyparse();
	} while (!feof(yyin));
	if (root)
		// AST Generation
		root->traverse();
	return 0;
}
