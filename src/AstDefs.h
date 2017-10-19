#include <bits/stdc++.h>
using namespace std;

class AstNode {
};

class Variable:public AstNode {
	private:
		string identifier;
		string datatype;
		string type;	
		unsigned int length;
	public:
		Variable(string, string);
		Variable(string, string, unsigned int);
		int getLength();
		string getDataType();
		string getIdentifier();
};

class Variables:public AstNode {
	private:
		std::vector<class Variable*> variables;
	public:
		Variables();
		void push(class Variable*);
		std::vector<class Variable*> getVariabList();
};

class FieldDeclaration:public AstNode {
	private:
		string datatype;
		std::vector<class Variable*> field_declaration;
	public:
		FieldDeclaration(string, class Variables*);
		string getDataType();
		std::vector<class Variable*> getFieldVarbs();
};

class FieldDeclarations:public AstNode {
	private:
		std::vector<class FieldDeclaration*> field_declarations;
	public:
		FieldDeclarations();
		void push(class FieldDeclaration*);
		std::vector<class FieldDeclaration*> getFieldDecls();
};

class Expression:public AstNode {
	private:
		string expr_type;
	public:
		Expression(string);
		string getType();
};

class Statement:public AstNode {
	private:
		string stat_type;
	public:
		Statement(string);
		string getType();
};

class Statements:public AstNode {
	private:
		std::vector<class Statement*> statements;
	public:
		Statements();
		void push(class Statement*);
		std::vector<class Statement*> getStatements();
};

class Block:public AstNode {
	private:
		std::vector<class Statement*> block_statements;
	public:
		Block(class Statements*);
		std::vector<class Statement*> getBlkStatements();
};