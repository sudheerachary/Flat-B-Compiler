%{
  #include <bits/stdc++.h>
  #include "AstDefs.h"
  extern "C" int yylex();
  extern "C" int yyparse();
  extern "C" FILE *yyin;
  extern union Node yylval;
  void yyerror (char const *s);
  class Main *root = NULL;
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

declarations:	{	$$ = new FieldDeclarations();
					std::cout<<"creating DECLS"<<std::endl;	}
			|	declarations declaration SC
			{	$$->store($2);
				std::cout<<"Storing DECLS"<<std::endl;	}
			;

declaration:	INT variables
			{	$$ = new FieldDeclaration(string($1), $2);
				std::cout<<"creating DECL"<<std::endl;	}
			;


variables:		variable
	{	$$ = new Variables();
		$$->store($1);
		std::cout<<"Storing Variable"<<std::endl;	}
	|	variables COMMA variable
	{	$$->store($3);	}
	;

variable:	IDENTIFIER
		{	std::cout<<IDENTIFIER<<std::endl;
		$$ = new Variable(string("Not Array"), string($1));	}
		|	IDENTIFIER OSB NUMBER CSB
		{	std::cout<<IDENTIFIER<<NUMBER<<std::endl;
		$$ = new Variable(string("Array"), string($1), $3);	}
		;

statements:	{	$$ = new Statements();	
				std::cout<<"STATEMENT CREATION"<<std::endl;	}
		|	statements assignment SC
		{	$$->store($2);
			std::cout<<"ASSIGNEMNT STORE"<<std::endl;	}
		|	statements IDENTIFIER COL assignment SC
		{	$4->setLabel(string($2));
			$$->store($4);
			std::cout<<"ASSIGNEMNT STORE"<<std::endl;	}
		|	statements for_block 
		{	$$->store($2);
			std::cout<<"FOR STORE"<<std::endl;	}
		|	statements IDENTIFIER COL for_block 
		{	$4->setLabel($2);	
			$$->store($4);	
			std::cout<<"FOR STORE"<<std::endl;	}
		|	statements if_block 
		{	$$->store($2);
			std::cout<<"IF STORE"<<std::endl;	}
		|	statements IDENTIFIER COL if_block 
		{	$4->setLabel($2);	
			$$->store($4);
			std::cout<<"IF STORE"<<std::endl;	}
		|	statements while_block 
		{	$$->store($2);
			std::cout<<"WHILE STORE"<<std::endl;	}
		|	statements IDENTIFIER COL while_block 
		{	$4->setLabel($2);	
			$$->store($4);	
			std::cout<<"WHILE STORE"<<std::endl;	}
		|	statements goto_block SC 
		{	$$->store($2);	
			std::cout<<"GOTO STORE"<<std::endl;	}
		|	statements IDENTIFIER COL goto_block SC
		{	$4->setLabel($2);	
			$$->store($4);	
			std::cout<<"GOTO STORE"<<std::endl;	}
		|	statements read_line SC 
		{	$$->store($2);	
			std::cout<<"READ STORE"<<std::endl;	}
		|	statements IDENTIFIER COL read_line 
		{	$4->setLabel($2);	
			$$->store($4);	
			std::cout<<"READ STORE"<<std::endl;	}
		|	statements print_line SC 
		{	$$->store($2);	
			std::cout<<"PRINT STORE"<<std::endl;	}
		|	statements IDENTIFIER COL print_line SC 
		{	$4->setLabel($2);	
			$$->store($4);	
			std::cout<<"PRINT STORE"<<std::endl;	}
		;

assignment:	value EQ expression
		{	$$ = new Assignment($1, $3);
			std::cout<<"ASSIGNEMNT CREATION"<<std::endl;	}
		;

expression: 	expression SUB expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"SUB"<<std::endl;	}
		|		expression ADD expression 
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"ADD"<<std::endl;	}
		|		expression MUL expression 
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"MUL"<<std::endl;	}
		|		expression DIV expression 
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"DIV"<<std::endl;	}
		|		expression MOD expression 
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"MOD"<<std::endl;	}
		|		expression L expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"LESS"<<std::endl;	}
		|		expression G expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"GREATER"<<std::endl;	}
		|		expression EQUALS expression	
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"EQUALS"<<std::endl;	}
		|		expression NOTEQUALS expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"NOTEQUALS"<<std::endl;	}
		|		expression AND expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"AND"<<std::endl;	}
		|		expression OR expression
		{	$$ = new Expression($1, string($2), $3);
			std::cout<<"OR"<<std::endl;	}
		| 		value
		{	$$ = new Expression($1);
			std::cout<<"VALUE CREATION"<<std::endl;	}
		;

value:	IDENTIFIER
	{	$$ = new Location(string($1));
		std::cout<<"VALUE CREATION"<<std::endl;	}
	|	IDENTIFIER OSB NUMBER CSB
	{	$$ = new Location(string($1), $3);
		std::cout<<"VALUE CREATION"<<std::endl;	}
	|	IDENTIFIER OSB IDENTIFIER CSB	
	{	$$ = new Location(string($1), string($3));
		std::cout<<"VALUE CREATION"<<std::endl;	}
	|	NUMBER
	{	$$ = new Location($1);
		std::cout<<"VALUE CREATION"<<std::endl;	}
	;

for_block:	FOR IDENTIFIER EQ value COMMA value block
		{	$$ = new ForStatement(string($2), $4, $6, $7);
			std::cout<<"FOR CREATION"<<std::endl;	}
		|	FOR IDENTIFIER EQ value COMMA value COMMA value block
		{	$$ = new ForStatement(string($2), $4, $6, $8, $9);
			std::cout<<"FOR CREATION"<<std::endl;	}
		;

if_block:	IF expression block
		{	$$ = new IfElseStatement($2, $3);
			std::cout<<"IF CREATION"<<std::endl;	}
		|	IF expression block ELSE block
		{	$$ = new IfElseStatement($2, $3, $5);
			std::cout<<"IF-ELSE CREATION"<<std::endl;	}
		;

while_block:	WHILE expression block
			{	$$ = new WhileStatement($2, $3);
				std::cout<<"WHILE CREATION"<<std::endl;	}
			;

goto_block:	GOTO IDENTIFIER IF expression
		{	$$ = new GotoStatement(string($2), $4);
			std::cout<<"GOTO CREATION"<<std::endl;	}
		|	GOT IDENTIFIER
		{	$$ = new GotoStatement(string($2));
			std::cout<<"GOTO CREATION"<<std::endl;	}
		;

block:	OP statements CP
		{	$$ = new Block($2);
			std::cout<<"BLOCK CREATION"<<std::endl;	}
		;

print_line:	PRINT STRING COMMA value
		{	$$ = new Print($2, $4);
			std::cout<<"PRINT CREATION"<<std::endl;	}
		|	PRINT STRING
		{	$$ = new Print($2);	
			std::cout<<"PRINT CREATION"<<std::endl;	}
		|	PRINT value
		{	$$ = new Print($2);
			std::cout<<"PRINT CREATION"<<std::endl;	}
		|	PRINTLN STRING
		{	$$ = new Print($2);
			std::cout<<"PRINT CREATION"<<std::endl;	}
		;

read_line:	READ value
		{	$$ = new ReadLine($2);
			std::cout<<"READ CREATION"<<std::endl;	}
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

	if (yyin == NULL){
		printf("Can't open the given file!\n");
		exit(-1);
	}
	do {
		yyparse();
	} while (!feof(yyin));

	if (root) {
		// AST Generation
		printf("---------Entered Root-------\n");
		root->traverse();
		}
	return 0;
}
