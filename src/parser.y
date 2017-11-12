%{
  #include <bits/stdc++.h>
  #include "AstDefs.h"
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern "C" int errors;
  extern union Node yylval;
  void yyerror (char const *s);
  class Main *root = NULL;
  int errors = 0;
%}

%start program
%token <val> IDENTIFIER STRING
%token <num> NUMBER
%token WHILE GOT IF ELSE 
%token PRINT PRINTLN READ
%token ETOK GOTO FOR
%token SC COMMA COL 
%token OP CP OSB CSB
%token <val> AND OR NOT INT
%token <val> ADD SUB MUL DIV MOD
%token <val> G L
%token <val> EQ NOTEQUALS
%token <val> EQUALS

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
program:	OP declarations CP OP statements CP 
	{
		$$ = new Main($2, $5);
		root = $$;
	}
	;

declarations:	{	$$ = new FieldDeclarations();	}
			|	declarations declaration SC
			{	$$->store($2);	}
			;

declaration:	INT variables
			{	$$ = new FieldDeclaration(string($1), $2);	}
			;


variables:		variable
	{	$$ = new Variables();
		$$->store($1);	}
	|	variables COMMA variable
	{	$$->store($3);	}
	;

variable:	IDENTIFIER
		{	$$ = new Variable(string($1));	}
		|	IDENTIFIER OSB NUMBER CSB
		{	$$ = new Variable(string($1), $3);	}
		;

statements:	{	$$ = new Statements();	}
		|	statements assignment SC
		{	$$->store($2);	}
		|	statements IDENTIFIER COL assignment SC
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
		|	statements IDENTIFIER COL goto_block SC
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

assignment:	value EQ expression
		{	$$ = new Assignment($1, $3);	}
		;

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
	|	IDENTIFIER OSB expression CSB	
	{	$$ = new Location(string($1), $3);	}
	|	NUMBER
	{	$$ = new Location($1);	}
	;

for_block:	FOR IDENTIFIER EQ expression COMMA expression block
		{	$$ = new ForStatement(string($2), $4, $6, $7);	}
		|	FOR IDENTIFIER EQ expression COMMA expression COMMA expression block
		{	$$ = new ForStatement(string($2), $4, $6, $8, $9);	}
		;

if_block:	IF expression block
		{	$$ = new IfElseStatement($2, $3);	}
		|	IF expression block ELSE block
		{	$$ = new IfElseStatement($2, $3, $5);	}
		;

while_block:	WHILE expression block
			{	$$ = new WhileStatement($2, $3);	}
			;

goto_block:	GOTO IDENTIFIER IF expression
		{	$$ = new GotoStatement(string($2), $4);	}
		|	GOT IDENTIFIER
		{	$$ = new GotoStatement(string($2));	}
		;

block:	OP statements CP
		{	$$ = new Block($2);	}
		;

print_line:	PRINT STRING COMMA value
		{	$$ = new Print($2, $4);	}
		|	PRINT STRING
		{	$$ = new Print($2);	}
		|	PRINT value
		{	$$ = new Print($2);	}
		|	PRINTLN STRING
		{	$$ = new Print($2);	}
		;

read_line:	READ value
		{	$$ = new ReadLine($2);	}
		;

%%

void yyerror (char const *s) 
{	
	errors++;
	printf("Error: %s\n", s);
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

	if (yyin == NULL){
		printf("Can't open the given file!\n");
		exit(-1);
	}
	do {
		yyparse();
	} while (!feof(yyin));

	if (root) {
		// AST Generation
		// root->traverse();
		// AST Interpretation
		// root->interpret();
		// Code Generation
		root->codegen();
	}
	return 0;
}
