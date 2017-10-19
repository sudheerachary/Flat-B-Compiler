#include <bits/stdc++.h>
using namespace std;

class AstNode {
};

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
};

class Variables:public AstNode {
	private:
		// list of variables in a field declaration
		std::vector<class Variable*> variables;
	public:
		Variables();
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
};

class FieldDeclarations:public AstNode {
	private:
		// list of all declarations
		std::vector<class FieldDeclaration*> field_declarations;
	public:
		FieldDeclarations();
		// store all declarations
		void store(class FieldDeclaration*);
		// get declarations
		std::vector<class FieldDeclaration*> getFieldDecls();
};

class Statement:public AstNode {
	private:
		string stmt_type;
	public:
		Statement(string);
		string getType();
};

class Expression:public Statement {
	private:
		string expr_type;
	public:
		Expression(string, string);
		string getType();
};

class Assignment:public Statement {
	private:
		class Expression *expr;
		string variable;
	public:
		Assignment(string, class Expression *);
}

class WhileStatement:public Statement {
	private:	
		class Expression *condition;
		class Block *while_block;
	public:
		WhileStatement(class Expression *, class Block *);
};

class ForStatement:public Statement {
	private:
		string loop_variable;
		class Expression *intialisation;
		class Expression *condition;
		class Expression *increment
		class Block *for_block;
	public:
		ForStatement(string, class Expression *, class Expression *, class Expression *);
};

class IfElseStatement:public Statement {
	private:
		class Expression *condition;
		class Block *if_block;
		class Block *else_block;
	public:
		IfElseStatement(class Expression *, class Block *, class Block *);
};

class Block:public AstNode {
	private:
		std::vector<class Statement*> block_statements;
	public:
		Block(class Statements*);
		std::vector<class Statement*> getBlkStatements();
};

class Statements:public AstNode {
	private:
		std::vector<class Statement*> statements;
	public:
		Statements();
		void push(class Statement*);
		std::vector<class Statement*> getStatements();
};

class Main:public AstNode {
	private:
		// all declarations --> { declaration block }
		class FieldDeclarations *field_declarations;
		// all statements --> { code block }
		class Statements *statements;
	public:
		Main(class FieldDeclarations *, class Statements *);

};