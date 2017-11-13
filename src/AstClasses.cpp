#include <bits/stdc++.h>
#include "AstDefs.h"

using namespace std;
using namespace llvm;
#define TBS print_tabs()

int tabs = 0;
Function *fooFunc;
extern int errors;
const int width = 4;
static LLVMContext Context;
std::map<string, int> var_table;
static IRBuilder<> Builder(Context);
std::map<string, std::vector<int>> array_table;
static Module *ModuleOb = new Module("Flat-B Compiler", Context);

Function *createFunc(IRBuilder <> &Builder, string Name) {
	FunctionType *functype = FunctionType::get(Builder.getInt32Ty(), false);
	Function *foofunc = Function::Create(
		functype, Function::ExternalLinkage, Name, ModuleOb);
	return foofunc;
}

BasicBlock *createBB(Function *foofunc, string Name) {
	return BasicBlock::Create(Context, Name, foofunc);
}

void BasicBuildLLVM(Module * TheModule)
{
    fooFunc = createFunc(Builder,"main");
    BasicBlock  *entry = createBB(fooFunc,"entry");
    Builder.SetInsertPoint(entry);
}

void print_tabs() {
	for (int i = 0; i < tabs; i++)
		for (int j = 0; j < width; j++)
			cout<<" ";
}

int evaluate(int lhs, string operand, int rhs) {
	if (operand.compare("+") == 0)
		return (lhs + rhs);
	if (operand.compare("-") == 0)
		return (lhs - rhs);
	if (operand.compare("*") == 0)
		return (lhs * rhs);
	if (operand.compare("/") == 0)
		return (lhs / rhs);
	if (operand.compare("%") == 0)
		return (lhs % rhs);
	if (operand.compare(">") == 0)
		return (lhs > rhs);
	if (operand.compare("<") == 0)
		return (lhs < rhs);
	if (operand.compare("==") == 0)
		return (lhs == rhs);
	if (operand.compare("!=") == 0)
		return (lhs != rhs);
	if (operand.compare("&&") == 0)
		return (lhs && rhs);
	if (operand.compare("||") == 0)
		return (lhs || rhs);
}

Variable::Variable(string identifier) {
	this->type = string("variable");
	this->identifier = identifier; 
}

Variable::Variable(string identifier, int len) {
	this->type = string("array");
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

Location::Location(int value) {
	this->type = string("number");
	this->value = value;
}

Location::Location(string identifier) {
	this->type = string("variable");
	this->identifier = identifier;
}

Location::Location(string identifier, class Expression *index) {
	this->type = string("array");
	this->identifier = identifier;
	this->index = index;
}

Block::Block(class Statements *statements) {
	this->block_statements = statements->getStatements();
}

WhileStatement::WhileStatement(class Expression *cond, class Block *blk) {
	this->stmt_type = string("while");
	this->condition = cond;
	this->while_block = blk;
}

ForStatement::ForStatement(string id, class Expression *start, class Expression *end, class Block *blk) {
	this->stmt_type = string("for");
	this->type = string("no_step");
	this->loop_variable = id;
	this->v_start = start;
	this->v_end = end;
	this->for_block = blk;
}

ForStatement::ForStatement(string id, class Expression *start, class Expression *end, class Expression *step, class Block *blk) {
	this->stmt_type = string("for");
	this->type = string("step");
	this->loop_variable = id;
	this->v_start = start;
	this->v_step = step;
	this->v_end = end;
	this->for_block = blk;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *blk) {
	this->stmt_type = string("if");
	this->type = string("if");
	this->condition = expr;
	this->if_block = blk;
}

IfElseStatement::IfElseStatement(class Expression *expr, class Block *iblk, class Block *eblk) {
	this->stmt_type = string("ifelse");
	this->type = string("ifelse");
	this->condition = expr;
	this->if_block = iblk;
	this->else_block = eblk; 
}

GotoStatement::GotoStatement(string id) {
	this->stmt_type = string("goto");
	this->type = string("goto");
	this->identifier = id;
}

GotoStatement::GotoStatement(string id, class Expression *cond) {
	this->stmt_type = string("gotoif");
	this->type = string("gotoif");
	this->identifier = id;
	this->condition = cond;
}

Print::Print(class Location *value) {
	this->stmt_type = string("print");
	this->type = string("loc");
	this->value = value;
}

Print::Print(string text) {
	this->stmt_type = string("print");
	this->type = string("str");
	this->text = text;
}

Print::Print(string text, class Location *value) {
	this->stmt_type = string("print");
	this->type = string("locstr");
	this->text = text;
	this->value = value;
}

ReadLine::ReadLine(class Location *value) {
	this->stmt_type = string("read");
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

string Location::getType() {
	return this->type; 
}

string Location::getIdentifier() {
	return this->identifier;
}

class Expression *Location::getIndex() {
	return this->index;
}

int Location::getValue() {
	return this->value;
}

string Expression::getType() {
	return this->stmt_type;
}

int Main::interpret() {
	cout<<"---------AST Interpreter-----"<<endl;
	field_declarations->interpret();
	statements->interpret();
	return 0;
}

void Main::traverse() {
	cout<<"---------AST Traversal-------"<<endl;
	TBS;
	cout<<"<Main>"<<endl;
		tabs++;
		field_declarations->traverse();
		statements->traverse();
		tabs--;
	TBS;
	cout<<"</Main>"<<endl;
}

void FieldDeclarations::interpret() {
	for (int i = 0; i < field_declarations.size(); ++i)
		field_declarations[i]->interpret();
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

void FieldDeclaration::interpret() {
	for (int i = 0; i < variables.size(); i++)
		variables[i]->interpret();
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

void Variable::interpret() {
	if (type.compare("array") == 0)
		array_table[identifier] = std::vector<int> (length, 0);
	else 
		var_table[identifier] = 0;
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
	if (type.compare("number") == 0) {
		TBS;
		cout<<"number: "<<value;
	}
	else if (type.compare("variable") == 0) {
		TBS;
		cout<<"variable: "<<identifier;
	}
	else if (type.compare("array") == 0)  {
		TBS;
		cout<<"identifier: "<<identifier;
		TBS;
		cout<<"index: ";
		tabs++;
		index->traverse();
		tabs--;
	}
	TBS;
	cout<<" />"<<endl;
}

int Location::interpret() {
	if (type.compare("number") == 0) {
		return value;
	}
	else if (type.compare("variable") == 0) {
		return var_table[identifier];
	}
	else if (type.compare("array") == 0) {
		return array_table[identifier][index->interpret()];
	}
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

void Block::interpret() {
	for (int i = 0; i < block_statements.size(); i++)
		block_statements[i]->interpret();
}

void Statements::traverse() {
	TBS;
	cout<<"<Statements>"<<endl;
		tabs++;
		for (int i = 0; i < statements.size(); i++) {
			TBS;
			cout<<"<Label: "<<statements[i]->getLabel()<<">"<<endl;
			statements[i]->traverse();
		}
		tabs--;
	TBS;
	cout<<"</Statements>"<<endl;
}

void Statements::interpret() {
	for (int i = 0; i < statements.size(); i++)
		statements[i]->interpret();
}

void Expression::traverse() {
	if (stmt_type.compare("unary_expression") == 0) {
		TBS;
		cout<<"<Value>"<<endl;
		tabs++;
		loc->traverse();
		tabs--;
		TBS;
		cout<<"</Value>"<<endl;
	}
	else { 
		TBS;
		cout<<"<Binary Expression Operator: "<<operand<<" >"<<endl;
		tabs++;
		lhs->traverse();
		rhs->traverse();
		tabs--;
		TBS;
		cout<<"</Binary Expression>"<<endl;
	}
}

int Expression::interpret() {
	int value;
	if (stmt_type.compare("unary_expression") == 0)
		value = loc->interpret();
	else 
		value = evaluate(lhs->interpret(), operand, rhs->interpret());
	return value;
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

int Assignment::interpret() {
	if (loc->getType().compare("variable") == 0) {
		var_table[loc->getIdentifier()] = expr->interpret();
	}
	if (loc->getType().compare("array") == 0) { 
		array_table[string(loc->getIdentifier())][loc->getIndex()->interpret()] = expr->interpret();
	}
	return 0;
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

int WhileStatement::interpret() {
	while (condition->interpret())
		while_block->interpret();
	return 0;
}

void ForStatement::traverse() {
	TBS;
	cout<<"<For Block>"<<endl;
	TBS;cout<<"<loop variable: "<<loop_variable<<">"<<endl;
	TBS;cout<<"<start: ";
	v_start->traverse();
	TBS;cout<<"/>"<<endl;
	TBS;cout<<"<end: ";
	v_end->traverse();
	TBS;cout<<"/>"<<endl;
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

int ForStatement::interpret() {
	if (type.compare("step") == 0) {
		var_table.insert(pair <string, int> (loop_variable, 0));
		for (int i = v_start->interpret(); i < v_end->interpret(); i+v_step->interpret()) {
			var_table[loop_variable] = i;
			for_block->interpret();			
		}
	}
	else {
		var_table.insert(pair <string, int> (loop_variable, 0));
		for (int i = v_start->interpret(); i < v_end->interpret(); i++) {
			var_table[loop_variable] = i;
			for_block->interpret();	
		}
	}
	return 0;
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

int IfElseStatement::interpret() {
	if (type.compare("ifelse") == 0) {
		if (condition->interpret())
			if_block->interpret();
		else
			else_block->interpret();
	}
	else {
		if (condition->interpret())
			if_block->interpret();
	}
	return 0;
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

int GotoStatement::interpret() {

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
	TBS;
	cout<<" />";
}

int Print::interpret() {
	if (type.compare("loc") == 0)
		cout<<value->interpret()<<endl;
	else if (type.compare("locstr") == 0)
		cout<<text<<value->interpret()<<endl;
	else
		cout<<text<<endl;
	return 0;
}

void ReadLine::traverse() {
	TBS;
	cout<<"<Read ";
		tabs++;
		value->traverse();
		tabs--;
	TBS;
	cout<<" />";
}

int ReadLine::interpret() {
	if (value->getType().compare("array") == 0)
		cin>>array_table[value->getIdentifier()][value->getIndex()->interpret()];
	else 
		cin>>var_table[value->getIdentifier()];
	return 0;
}	

Value *Variable::codegen() {
	Value *V = ConstantInt::get(Context, APInt(32, 0));
	return V;
}

Value *FieldDeclaration::codegen() {
	for (int i = 0; i < variables.size(); i++) {
		class Variable *variable = variables[i];
		if (variable->getType().compare("array") == 0) {
			llvm::Type *type;
			type = Type::getInt32Ty(Context);
			ArrayType* arrType = ArrayType::get(type, variable->getLength());
			PointerType* PointerTy_1 = PointerType::get(ArrayType::get(type, variable->getLength()), 0);
			GlobalVariable* gv = new GlobalVariable(*ModuleOb, arrType, false, GlobalValue::ExternalLinkage, 0, variable->getIdentifier());
			gv->setInitializer(ConstantAggregateZero::get(arrType));
		}
		else {
			ModuleOb->getOrInsertGlobal(variable->getIdentifier(), Builder.getInt32Ty());
			GlobalVariable *gvar = ModuleOb->getNamedGlobal(variable->getIdentifier());
			gvar->setLinkage(GlobalValue::CommonLinkage);
			gvar->setAlignment(4);
			ConstantInt* const_int_val = ConstantInt::get(Context, APInt(32,0));
			gvar->setInitializer(const_int_val);
		}
	}
	Value *v = ConstantInt::get(Context, APInt(32, 1));
	return v;
}

Value *FieldDeclarations::codegen() {
	for (int i = 0; i < field_declarations.size(); i++)
		field_declarations[i]->codegen();
	Value *v = ConstantInt::get(Context, APInt(32, 1));
	return v;
}

Value *Expression::codegen() {
	if (this->getType().compare("unary_expression") == 0) {
		Value *v = loc->codegen();
		if(loc->getType().compare("number") != 0)
			v = Builder.CreateLoad(v);
		return v;
	}
	if (this->getType().compare("binary_expression") == 0) {
		Value *left = lhs->codegen();
		Value *right = rhs->codegen();
		if (left == 0) 
			return reportError::ErrorV("Error in left operand of " + operand);
		if (right == 0)
			return reportError::ErrorV("Error in right operand of " + operand);
		Value *v;
		if (operand.compare("+") == 0)
			v = Builder.CreateAdd(left, right, "addtmp");
		else if (operand.compare("-") == 0)
			v = Builder.CreateSub(left, right, "subtmp");
		else if (operand.compare("*") == 0)
			v = Builder.CreateMul(left, right, "multmp");
		else if (operand.compare("/") == 0)
			v = Builder.CreateUDiv(left, right, "divtmp");
		else if (operand.compare("%") == 0)
			v = Builder.CreateURem(left, right, "modtmp");
		else if (operand.compare("<") == 0)
			v = Builder.CreateICmpULT(left, right, "ltcomparetmp");
		else if (operand.compare(">") == 0)
			v = Builder.CreateICmpUGT(left, right, "gtcomparetmp");
		else if (operand.compare("==") == 0)
			v = Builder.CreateICmpEQ(left, right, "equalcomparetmp");
		else if (operand.compare("!=") == 0)
			v = Builder.CreateICmpNE(left, right, "notequalcomparetmp");
		return v;
	}
}

Value *Statements::codegen() {
	Value *v = ConstantInt::get(Context, APInt(32, 1));
	for (int i = 0; i < statements.size(); i++)
		v = statements[i]->codegen();
	return v;
}

Value *Main::codegen() {
	cout<<"------Code Generation------"<<endl;
	Value *v = ConstantInt::get(Context, APInt(32, 0));
	BasicBuildLLVM(ModuleOb);
	field_declarations->codegen();
	statements->codegen();
	Builder.CreateRet(Builder.getInt32(0));
	if (errors == 0)
		ModuleOb->dump();
	else
		cout<<"Program has Error: "<<errors<<endl;
	return v;
}

Value *Block::codegen() {
	Value *v = ConstantInt::get(Context, APInt(32, 0));
	for (int i = 0; i < block_statements.size(); i++)
		block_statements[i]->codegen();
	return v;
}

Value *Location::codegen() {
	if (this->getType().compare("number") == 0) {
		Value *v = ConstantInt::get(Context, APInt(32, value));
		return v;
	}
	else {
		Value* v = ModuleOb->getNamedGlobal(identifier);
		if (v == 0) {
			errors++;
			return reportError::ErrorV("Unknown Variable name "+identifier);
		}
		if (type.compare("array") != 0) {
			return v;
		}
		else {
			Value *index = this->index->codegen();
			if (index == 0) {
				errors ++;
				return reportError::ErrorV("Invalid Index");
			}
			vector <Value *> array_index;
			array_index.push_back(Builder.getInt32(0));
			array_index.push_back(index);
			v = Builder.CreateGEP(v, array_index, identifier+"_Index");
			return v;
		}
	}
}

Value *Assignment::codegen() {
	Value *lhs = ModuleOb->getGlobalVariable(loc->getIdentifier());
	if (lhs == 0) {
		errors++;
	 	return reportError::ErrorV("Unknown Variable Name "+loc->getIdentifier());
	}
	Value *rhs = expr->codegen();
	if (rhs == 0) {
		errors++;
	 	return reportError::ErrorV("Error in right hand side of Assignment");
	}
	lhs = loc->codegen();
	Value *v = Builder.CreateStore(rhs, lhs);
	return v;
}

Value *IfElseStatement::codegen() {
	Value* v = ConstantInt::get(Context, APInt(32,0));
	Value* condition = this->condition->codegen();
	BasicBlock* ifblock = createBB(fooFunc,"if");
	BasicBlock* elseblock = createBB(fooFunc,"else");
	BasicBlock* mergeblock = createBB(fooFunc,"ifmerge");
	Builder.CreateCondBr(condition, ifblock, elseblock);
	Builder.SetInsertPoint(ifblock);
	Value *ifval  = if_block->codegen();
	Builder.CreateBr(mergeblock);
	ifblock = Builder.GetInsertBlock();
	Builder.SetInsertPoint(elseblock);
	Value* elseval;
	if (this->type.compare("ifelse") == 0) {
        elseval = else_block->codegen();
	}
    Builder.CreateBr(mergeblock);
    elseblock = Builder.GetInsertBlock();
    Builder.SetInsertPoint(mergeblock);
    return v;
}

Value *ForStatement::codegen() {
	Value* intial = v_start->codegen();
    BasicBlock *loop = createBB(fooFunc, "loop");
    BasicBlock *after = createBB(fooFunc, "afterloop");
    Value* loop_variable = ModuleOb->getGlobalVariable(this->loop_variable);
    if (loop_variable == 0) {
    	errors++;
    	reportError::ErrorV("loop variable not found: "+this->loop_variable);
    }
    Value* v3 = v_end->codegen();
    Value *v34 = Builder.CreateStore(intial, loop_variable);
    Value *v45 = Builder.CreateLoad(loop_variable);
    if (v45 == 0) {
    	reportError::ErrorV("Unknown loop variable: "+this->loop_variable);
    }
    Value *end1 = Builder.CreateICmpULT(intial,v3,"condi");
    Builder.CreateCondBr(end1, loop, after);
    Builder.SetInsertPoint(loop);
    Value *v = for_block->codegen();
    Value* inc;
    if (this->type.compare("no_step") == 0) {
        inc = Builder.getInt32(1);
    }
    else {
        inc = v_step->codegen();
    }
    Value *ty = Builder.CreateLoad(loop_variable);
    Value *re = Builder.CreateAdd(ty, inc, "next");
    Builder.CreateStore(re, loop_variable);
    Value *end = Builder.CreateICmpULT(re, v3, "loopcond");
    Builder.CreateCondBr(end, loop, after);
    Builder.SetInsertPoint(after);
}

Value *WhileStatement::codegen() {
	BasicBlock *loop = createBB(fooFunc, "loop");
    BasicBlock *after = createBB(fooFunc, "afterloop");
    Value *cond_gen = condition->codegen();
    Value *loop_condition = Builder.CreateICmpNE(cond_gen, Builder.getInt1(0),"whilecon");
    Builder.CreateCondBr(loop_condition, loop, after);
    Builder.SetInsertPoint(loop);
    Value *v = while_block->codegen();
    cond_gen = condition->codegen();
    Value *after_loop_condition = Builder.CreateICmpNE(cond_gen, Builder.getInt1(0),"whilecon");
    Builder.CreateCondBr(after_loop_condition, loop, after);
    Builder.SetInsertPoint(after);
}

Value *GotoStatement::codegen() {

}

Value *ReadLine::codegen() {
	Value* v;
	vector <Value *> args;
	vector <Type *> type;
	string s = "%d";
	Value* x = Builder.CreateGlobalStringPtr(s);
	args.push_back(x);
	type.push_back(x->getType());
	v = value->codegen();
	args.push_back(v);
	type.push_back(v->getType());
	llvm::ArrayRef <Type *> typeargs(type);
	llvm::ArrayRef <Value *> refargs(args);
	llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), typeargs, false);
	Constant* readfunc = ModuleOb->getOrInsertFunction("scanf", FType);
	return Builder.CreateCall(readfunc,refargs);
}

Value *Print::codegen() {
	Value* v;
	vector <Value *> args;
	vector <Type *> type;
	string s;
	if (this->type.compare("str")==0) {
		s = text+"\n";
		Value* x = Builder.CreateGlobalStringPtr(s);
		args.push_back(x);
		type.push_back(x->getType());
	}
	else if (this->type.compare("loc")==0) {
		s = "%d\n";
		Value* x = Builder.CreateGlobalStringPtr(s);
		args.push_back(x);
		type.push_back(x->getType());
		v = value->codegen();
		v = Builder.CreateLoad(v);
		if (v == 0) {
			errors++;
			reportError::ErrorV("Unknown Variable in PRINT");
		}
		args.push_back(v);
		type.push_back(v->getType());
	}
	else {
		s = text+"%d\n";
		Value* x = Builder.CreateGlobalStringPtr(s);
		args.push_back(x);
		type.push_back(x->getType());
		v = value->codegen();
		v = Builder.CreateLoad(v);
		if (v == 0) {
			errors++;
			reportError::ErrorV("Unknown Variable in PRINT");
		}
		args.push_back(v);
		type.push_back(v->getType());
	}
	llvm::ArrayRef <Type *> typeargs(type);
	llvm::ArrayRef <Value *> refargs(args);
	llvm::FunctionType *FType = FunctionType::get(Type::getInt32Ty(Context), typeargs, false);
	Constant* printfunc = ModuleOb->getOrInsertFunction("printf", FType);
	return Builder.CreateCall(printfunc, refargs);
}