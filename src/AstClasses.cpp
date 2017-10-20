#include <bits/stdc++.h>
#include "AstDefs.h"
using namespace std;

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
	this->loop_variable = id;
	this->v_start = start;
	this->v_step = NULL;
	this->v_end = end;
	this->for_block = blk;
}

ForStatement::ForStatement(string id, class Location *start, class Location *end, class Location *step, class Block *blk) {
	this->loop_variable = id;
	this->v_start = start;
	this->v_step = step;
	this->v_end = end;
	this->for_block = blk;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *blk) {
	this->condition = expr;
	this->if_block = blk;
	this->else_block = NULL;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *iblk, class Block *eblk) {
	this->condition = expr;
	this->if_block = iblk;
	this->else_block = eblk; 
}

GotoStatement::GotoStatement(string id) {
	this->identifier = id;
}

GotoStatement::GotoStatement(string id, class Expression *cond) {
	this->identifier = id;
	this->condition = cond;
}

Print::Print(class Location *value) {
	this->value = value;
}

Print::Print(string text) {
	this->text = text;
}

Print::Print(string text, class Location *value) {
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