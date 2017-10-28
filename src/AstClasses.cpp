#include <bits/stdc++.h>
#include "AstDefs.h"
using namespace std;
#define TBS print_tabs()
int tabs = 0;
const int width = 4;

void print_tabs() {
	for (int i = 0; i < tabs; i++)
		for (int j = 0; j < width; j++)
			cout<<" ";
}

Variable::Variable(string type, string identifier) {
	this->type = type;
	this->identifier = identifier; 
}

Variable::Variable(string type, string identifier, unsigned int len) {
	this->type = type;
	this->identifier = identifier;
	this->length = len;
}

FieldDeclaration::FieldDeclaration(string datatype, class Variables *variables) {
	this->datatype = datatype; 
	this->variables = variables->getVariables();
}

Assignment::Assignment(class Location *loc, class Expression *expr) {
	this->stmt_type = string("assignment");
	this->loc = loc;
	this->expr = expr;
}

Expression::Expression(class Expression *lhs, string operand, class Expression *rhs) {
	this->stmt_type = string("binary_expression");
	this->lhs = lhs;
	this->rhs = rhs;
	this->operand = operand;
}

Expression::Expression(class Location *loc) {
	this->stmt_type = string("unary_expression");
	this->loc = loc;
}

Location::Location(unsigned int value) {
	this->type = string("number");
	this->value = value;
}

Location::Location(string identifier) {
	this->type = string("variable");
	this->identifier = identifier;
}

Location::Location(string identifier, unsigned int index) {
	this->type = string("array_const_index");
	this->identifier = identifier;
	this->value = index;
}

Location::Location(string identifier, string index) {
	this->type = string("array_var_index");
	this->identifier = identifier;
	this->index = index;
}

Block::Block(class Statements *statements) {
	this->block_statements = statements->getStatements();
}

WhileStatement::WhileStatement(class Expression *cond, class Block *blk) {
	this->condition = cond;
	this->while_block = blk;
}

ForStatement::ForStatement(string id, class Location *start, class Location *end, class Block *blk) {
	this->type = string("no step");
	this->loop_variable = id;
	this->v_start = start;
	this->v_end = end;
	this->for_block = blk;
}

ForStatement::ForStatement(string id, class Location *start, class Location *end, class Location *step, class Block *blk) {
	this->type = string("step");
	this->loop_variable = id;
	this->v_start = start;
	this->v_step = step;
	this->v_end = end;
	this->for_block = blk;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *blk) {
	this->type = string("if");
	this->condition = expr;
	this->if_block = blk;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *iblk, class Block *eblk) {
	this->type = string("ifelse");
	this->condition = expr;
	this->if_block = iblk;
	this->else_block = eblk; 
}

GotoStatement::GotoStatement(string id) {
	this->type = string("goto");
	this->identifier = id;
}

GotoStatement::GotoStatement(string id, class Expression *cond) {
	this->type = string("gotoif");
	this->identifier = id;
	this->condition = cond;
}

Print::Print(class Location *value) {
	this->type = string("loc");
	this->value = value;
}

Print::Print(string text) {
	this->type = string("str");
	this->text = text;
}

Print::Print(string text, class Location *value) {
	this->type = string("locstr");
	this->text = text;
	this->value = value;
}

ReadLine::ReadLine(class Location *value) {
	this->value = value;
}

Main::Main(class FieldDeclarations *decls, class Statements *stmts) {
	this->field_declarations = decls;
	this->statements = stmts;
}

int Variable::getLength() {
	return this->length;
}

string Variable::getType() {
	return this->type;
}

string Variable::getIdentifier() {
	return this->identifier;
}

void Variables::store(class Variable *variable) {
	this->variables.push_back(variable);
}

std::vector<class Variable*> Variables::getVariables() {
	return this->variables;
}

string FieldDeclaration::getDataType() {
	return this->datatype;
}

std::vector<class Variable *> FieldDeclaration::getVariables() {
	return this->variables;
}

void FieldDeclarations::store(class FieldDeclaration *declaration) {
	return this->field_declarations.push_back(declaration);
}

std::vector<class FieldDeclaration *> FieldDeclarations::getFieldDecls() {
	return this->field_declarations;
}	

string Statement::getType() {
	return this->stmt_type;
}

void Statement::setType(string type) {
	this->stmt_type = type;
}

string Statement::getLabel() {
	return this->label;
}

void Statement::setLabel(string label) {
	this->label = label;
}

std::vector<class Statement *> Block::getBlkStatements() {
	return this->block_statements;
}

void Statements::store(class Statement *statement) {
	this->statements.push_back(statement);
}

std::vector<class Statement *> Statements::getStatements() {
	return this->statements;
}

void Main::traverse() {
	TBS;
	cout<<"<Main>"<<endl;
		tabs++;
		field_declarations->traverse();
		statements->traverse();
		tabs--;
	TBS;
	cout<<"</Main>"<<endl;
}

void FieldDeclarations::traverse() {
	TBS;
	cout<<"<Declarations>"<<endl;
		tabs++;
		for (int i = 0; i < field_declarations.size(); ++i)
			field_declarations[i]->traverse();
		tabs--;
	TBS;
	cout<<"</Declarations>"<<endl;
}

void FieldDeclaration::traverse() {
	TBS;
	cout<<"<Declaration>"<<endl;
		tabs++;
		TBS;
		cout<<"DataType: "<<endl;
		for (int i = 0; i < variables.size(); i++)
			variables[i]->traverse();
		tabs--;
	TBS;
	cout<<"</Declaration>"<<endl;
}

void Variable::traverse() {
	TBS;
	cout<<"<Variable ";
	cout<<"declaration: "<<identifier;
	if (type.compare("Array") == 0)
		cout<<", length: "<<length;
	cout<<" />"<<endl;
}

void Location::traverse() {
	TBS;
	cout<<"<Location ";
	if (type.compare("number") == 0)
		cout<<"number: "<<value;
	else if (type.compare("variable") == 0)
		cout<<"variable: "<<identifier;
	else if (type.compare("array_const_index") == 0)
		cout<<"identifier: "<<identifier<<" index: "<<value;
	else
		cout<<"identifier: "<<identifier<<" index: "<<index;	
	cout<<" />"<<endl;
}

void Block::traverse() {
	TBS;
	cout<<"<Block>"<<endl;
		tabs++;
		for (int i = 0; i < block_statements.size(); i++)
			block_statements[i]->traverse();
		tabs--;
	TBS;
	cout<<"</Block>"<<endl;
}

void Statements::traverse() {
	TBS;
	cout<<"<Statements>"<<endl;
		tabs++;
		for (int i = 0; i < statements.size(); i++)
			statements[i]->traverse();
		tabs--;
	TBS;
	cout<<"</Statements>"<<endl;
}

void Expression::traverse() {
	TBS;
	cout<<"<Binary Expression Operator: "<<operand<<" >"<<endl;
		tabs++;
		lhs->traverse();
		rhs->traverse();
		tabs--;
	TBS;
	cout<<"</Binary Expression>"<<endl;
}

void Assignment::traverse() {
	TBS;
	cout<<"<Assignment Expression>"<<endl;
		tabs++;
		loc->traverse();
		expr->traverse();
		tabs--;
	TBS;
	cout<<"</Assignment Expression>"<<endl;
}

void WhileStatement::traverse() {
	TBS;
	cout<<"<While Block>"<<endl;
		tabs++;
		condition->traverse();
		while_block->traverse();
		tabs--;
	TBS;
	cout<<"</While Block>"<<endl;
}

void ForStatement::traverse() {
	TBS;
	cout<<"<For Block>"<<endl;
	TBS;
	cout<<"<start: ";v_start->traverse();cout<<"/>"<<endl;
	TBS;
	cout<<"<end: ";v_end->traverse();cout<<"/>"<<endl;
	if (type.compare("step") == 0) {
		TBS;
		cout<<"<step: ";
		v_step->traverse();
		cout<<"/>"<<endl;
	}
		tabs++;
			for_block->traverse();
		tabs--;
	TBS;
	cout<<"</For Block>"<<endl;
}

void IfElseStatement::traverse() {
	TBS;
	cout<<"<If Block>"<<endl;
		tabs++;
		if_block->traverse();
		tabs--;
	TBS;
	cout<<"</If Block>"<<endl;
	if (type.compare("ifelse") == 0) {
		TBS;
		cout<<"<Else Block>"<<endl;
			tabs++;
			else_block->traverse();
			tabs--;
		TBS;
		cout<<"</Else Block>"<<endl;
	}
}

void GotoStatement::traverse() {
	TBS;
	cout<<"<Goto label: "<<identifier<<endl;
	if (type.compare("gotoif") == 0) {
		tabs++;
		condition->traverse();
		tabs--;
	}
	TBS;
	cout<<" />"<<endl;
}

void Print::traverse() {
	TBS;
	cout<<"<Print ";
	if (type.compare("str") == 0) {
		cout<<"string: "<<text;
	}
	else if (type.compare("loc") == 0) {
		tabs ++;
		value->traverse();
		tabs--;
	}
	else {
		cout<<"string: "<<text;
		tabs++;
		value->traverse();
		tabs--;
	}
	cout<<" />";
}

void ReadLine::traverse() {
	TBS;
	cout<<"<Read ";
		tabs++;
		value->traverse();
		tabs--;
	cout<<" />";
}