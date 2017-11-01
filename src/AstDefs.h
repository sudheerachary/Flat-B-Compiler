#include <bits/stdc++.h>
using namespace std;

class AstNode {
};

union Node {
	int num;
	char *val;
	class Variable *var;
	class Variables *vars;
	class FieldDeclaration *field;
	class FieldDeclarations *fields;
	class Location *loc;
	class Expression *expr;
	class Assignment *assignstmt;
	class ForStatement *forstmt;
	class WhileStatement *whilestmt;
	class IfElseStatement *ifelsestmt;
	class GotoStatement *gotostmt;
	class Statements *stmts;
	class Block *block;
	class Print *print;
	class ReadLine *read;
	class Main *main;
	Node() {
		main = NULL;
		num = 0;
		val= NULL;
		fields = NULL;
		vars = NULL;
		stmts = NULL;
	}
	~Node(){};
};

typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1

class Variable:public AstNode {
	private:
		// length if array type
		unsigned int length;
		// name of the variable
		string identifier;
		// type of variable either array or not
		string type;	
	public:
		// normal variable constructor
		Variable(string, string);
		// array variable constructor
		Variable(string, string, unsigned int);
		// get length if array variable
		int getLength();
		// get type of variable
		string getType();
		// get name of variable
		string getIdentifier();
		//  traverse over tree
		void traverse();
		//	interpret the AST
		void interpret();
};

class Variables:public AstNode {
	private:
		// list of variables in a field declaration
		std::vector<class Variable*> variables;
	public:
		Variables(){}
		// store all variables in a field declaration
		void store(class Variable*);
		// get list of variables
		std::vector<class Variable*> getVariables();
};

class FieldDeclaration:public AstNode {
	private:
		// datatype of a declaration
		string datatype;
		// list of variables in a declaration
		std::vector<class Variable*> variables;
	public:
		FieldDeclaration(string, class Variables *);
		// get datatype of declaration
		string getDataType();
		// get variables in a declaration
		std::vector<class Variable*> getVariables();
		//  traverse over tree
		void traverse();
		//	interpret field declaration
		void interpret();
};

class FieldDeclarations:public AstNode {
	private:
		// list of all declarations
		std::vector<class FieldDeclaration*> field_declarations;
	public:
		FieldDeclarations(){}
		// store all declarations
		void store(class FieldDeclaration*);
		// get declarations
		std::vector<class FieldDeclaration*> getFieldDecls();
		//  traverse over tree
		void traverse();
		//	interpret field declarations
		void interpret();
};

class Statement:public AstNode {
	protected:
		// label for goto
		string label;
		// type of statement
		string stmt_type;
	public:
		Statement(){}
		// setters & getters of type
		void setType(string);
		string getType();
		// setters & getters of label
		void setLabel(string);
		string getLabel();
		//  traverse over tree
		virtual void traverse(){}
		//	interpret statement
		virtual int interpret(){}
};

class Location:public AstNode {
	private:
		// Location of storage 
		string identifier, index;
		// number 
		unsigned int value;
		// type of variable
		string type;
	public:
		Location(unsigned int);
		Location(string);
		Location(string, unsigned int);
		Location(string, string);
		//	type of storage Location
		string getType();
		//	get identifier
		string getIdentifier();
		//	get index
		string getIndex();
		//	get value
		int getValue();
		//  traverse over tree
		void traverse();
		//	interpret Location
		int interpret();
};

class Expression:public Statement {
	private:
		// lhs of expression
		class Expression *lhs;
		// rhs of expression
		class Expression *rhs;
		// single values for assignment
		unsigned int value;
		class Location *loc;
		// operator
		string operand;
	public:
		Expression(class Expression *, string, class Expression *);
		Expression(class Location *);
		//  traverse over tree
		void traverse();
		//	interpret expression
		int interpret();
};

class Assignment:public Statement {
	private:
		// rhs expression 
		class Expression *expr;
		// location to be assigned
		class Location *loc;
	public:
		Assignment(class Location *, class Expression *);
		//  traverse over tree
		void traverse();
		//	interpret assignment
		int interpret();
};

class WhileStatement:public Statement {
	private:	
		// conditional Statement
		class Expression *condition;
		// block under while
		class Block *while_block;
	public:
		WhileStatement(class Expression *, class Block *);
		//  traverse over tree
		void traverse();
		//	interpret while block
		int interpret();
};

class ForStatement:public Statement {
	private:
		// looping variable 
		string loop_variable;
		// location of start end step size variables
		class Location *v_start, *v_end, *v_step;
		// block under for
		class Block *for_block;
		// with step or no
		string type;
	public:
		ForStatement(string, class Location *, class Location *, class Block *);
		ForStatement(string, class Location *, class Location *, class Location *, class Block *);
		//  traverse over tree
		void traverse();
		//	interpret for block
		int interpret();
};

class IfElseStatement:public Statement {
	private:
		// conditional Statement
		class Expression *condition;
		// if block Statements
		class Block *if_block;
		// else block Statements
		class Block *else_block;
		// either if or ifelse
		string type;
	public:
		IfElseStatement(class Expression *, class Block *);
		IfElseStatement(class Expression *, class Block *, class Block *);
		//  traverse over tree
		void traverse();
		//	interpret if-else
		int interpret();
};

class GotoStatement:public Statement {
	private:
		// label for goto
		string identifier;
		// conditional goto
		class Expression *condition;
		// either gotoif or goto
		string type;
	public:
		GotoStatement(string);
		GotoStatement(string, class Expression *);
		//  traverse over tree
		void traverse();
};

class Statements:public AstNode {
	private:
		// list of statements
		std::vector<class Statement*> statements;
	public:
		Statements(){}
		// store each statement
		void store(class Statement*);
		// return statements
		std::vector<class Statement*> getStatements();
		//  traverse over tree
		void traverse();
		//	interpret statements
		void interpret();
};

class Block:public AstNode {
	private:
		std::vector<class Statement*> block_statements;
	public:
		Block(class Statements*);
		std::vector<class Statement*> getBlkStatements();
		//  traverse over tree
		void traverse();
		//	interpret block
		void interpret();
};

class Print:public Statement {
	private:
		// text to be displayed
		string text;
		// value to be displayed
		class Location *value;
		// either num or id or array
		string type;
	public:
		Print(class Location *);
		Print(string);
		Print(string, class Location *);
		//  traverse over tree
		void traverse();
		//	interpret print
		int interpret();
};

class ReadLine:public Statement {
	private:
		// value to be read
		class Location *value;
	public:
		ReadLine(class Location *);
		//  traverse over tree
		void traverse();
};

class Main:public AstNode {
	private:
		// all declarations --> { declaration block }
		class FieldDeclarations *field_declarations;
		// all statements --> { code block }
		class Statements *statements;
	public:
		Main(class FieldDeclarations *, class Statements *);
		//  traverse over tree
		void traverse();
		//	interpret main
		void interpret();
};