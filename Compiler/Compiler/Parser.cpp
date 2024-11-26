#include "Parser.h"

bool Parser::isNumber(string s)
{
	int state = 0;
	for (char c : s)
	{
		if (state == 0 && c == '0')
			state = 4;
		else if ((state == 0 || state == 1)
			&& isdigit(c))
			state = 1;
		else if ((state == 1 || state == 4) &&
			c == '.')
			state = 2;
		else if ((state == 2 || state == 3)
			&& isdigit(c))
			state = 3;
		else
			return false;
	}
	return (state == 1 || state == 3 || state == 4);
}
bool Parser::isName(string s)
{
	if(s == "freq" || s == "func")
		return true;
	return false;
}

void Parser::getLexeme()
{
	if (i >= ls.size())
	{
		lexeme = "#";
		return;
	}
	lexeme = ls[i];
	i++;
	
}

void mistake(string msg) {
	cout << msg << '\n';
}

void Parser::Function(Node& n) {
	if (lexeme == "int")
	{
		// Function → Begin Descriptions Operators End
		n.addSon("Begin");
		Begin(n.getSon(0));
		n.addSon("Descriptions");
		Descriptions(n.getSon(1));
		n.addSon("Operators");
		Operators(n.getSon(2));
		n.addSon("End");
		End(n.getSon(3));
	}
	else mistake("'int' expected");
}



void Parser::Begin(Node& n) {
	if (lexeme == "int")
	{
		// Begin → Type FunctionName ( ) {
		n.addSon("Type");
		Type(n.getSon(0));
		n.addSon("FunctionName");
		FunctionName(n.getSon(1));
		n.addSon("(");
		getLexeme();
		n.addSon(")");
		getLexeme();
		n.addSon("{");
		getLexeme();
	}
	else mistake("'int' expected");
}


void Parser::End(Node& n) {
	if (lexeme == "return")
	{
		// End → return Id ; }
		n.addSon("return");
		getLexeme();
		n.addSon("Id");
		Id(n.getSon(1));
		n.addSon(";");
		getLexeme();
		n.addSon("}");
		getLexeme();
	}
	else mistake("'return' expected");
}


void Parser::FunctionName(Node& n) {
	if (isName(lexeme))
	{
		// FunctionName → Id
		n.addSon("Id");
		Id(n.getSon(0));
	}
	else mistake("func name expected");
}

void Parser::Descriptions(Node& n) {
	if (lexeme == "int")
	{
		// Descriptions → Descr Descriptions1
		n.addSon("Descr");
		Descr(n.getSon(0));
		n.addSon("Descriptions1");
		Descriptions1(n.getSon(1));
	}
	else mistake("'int' expected");
}

void Parser::Descriptions1(Node& n) {
	if (lexeme == "int")
	{
		// Descriptions1 → Descriptions
		n.addSon("Descriptions");
		Descriptions1(n.getSon(0));
	}
	else if (lexeme == "for" || isName(lexeme))
	{
		//Descriptions1 → eps
		n.addSon("eps");
	}
	else mistake("'int' or 'for' or id_name expected");
}

void Parser::Descr(Node& n) {
	if (lexeme == "int")
	{
		// Descr → Type VarList ;
		n.addSon("Type");
		Type(n.getSon(0));
		n.addSon("VarList");
		VarList(n.getSon(1));
		n.addSon(";");
		getLexeme();
	}
	else mistake("'int' expected");
}

void Parser::VarList(Node& n) {
	if (isName(lexeme))
	{
		// VarList → Id VarList1
		n.addSon("Id");
		Id(n.getSon(0));
		n.addSon("VarList1");
		VarList1(n.getSon(1));
	}
	else mistake("id_name expected");
}

void Parser::VarList1(Node& n) {
	if (lexeme == ",")
	{
		// VarList1 → , VarList
		n.addSon(",");
		getLexeme();
		n.addSon("VarList");
		VarList(n.getSon(1));
	}
	else if (lexeme == ";") {
		//VarList1 → eps
		n.addSon("eps");
	}
	else mistake("',' or ';' expected");
}

void Parser::Type(Node& n) {
	if (lexeme == "int")
	{
		// Type → int
		n.addSon("int");
		getLexeme();
	}
	else mistake("'int' expected");
}

void Parser::Operators(Node& n) {
	if (lexeme == "for" || isName(lexeme))
	{
		// Operators → Op Operators'
		n.addSon("Op");
		Op(n.getSon(0));
		n.addSon("Operators1");
		Operators1(n.getSon(1));
	}
	else mistake("id_name or 'for' expected");
}

void Parser::Operators1(Node & n) {
	if (isName(lexeme) || lexeme == "for")
	{
		// Operators1 → Operators
		n.addSon("Operators");
		Operators(n.getSon(0));
	}
	else if (lexeme == "}" || lexeme == "return") {
		//Operators1 → eps
		n.addSon("eps");
	}
	else mistake("id_name or '}' or 'return' expected");
}

void Parser::Op(Node& n) {
	if (lexeme == "for")
	{
		// Op → for ( Id = Expr ; Condition ; Expr ) { Operators }
		n.addSon("for");
		getLexeme();
		n.addSon("(");
		getLexeme();
		n.addSon("Id");
		Id(n.getSon(2));
		n.addSon("=");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(4));
		n.addSon(";");
		getLexeme();


		n.addSon("Condition");
		Condition(n.getSon(6));
		n.addSon(";");
		getLexeme();

		n.addSon("Expr");
		Expr(n.getSon(8));
		n.addSon(")");
		getLexeme();


		n.addSon("{");
		getLexeme();
		n.addSon("Operators");
		Operators(n.getSon(11));
		n.addSon("}");
		getLexeme();
	}
	else if (isName(lexeme) ) {
		// Op -> Id = Expr ; 
		n.addSon("Id");
		Id(n.getSon(0));
		n.addSon("=");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(2));
		n.addSon(";");
		getLexeme();
	}
	else mistake("'for' or id_name expected");
}

void Parser::Expr(Node& n) {
	if (isName(lexeme) || isNumber(lexeme) || lexeme == "(")
	{
		// Expr → SimpleExpr Expr1
		n.addSon("SimpleExpr");
		SimpleExpr(n.getSon(0));
		n.addSon("Expr1");
		Expr1(n.getSon(1));
	}
	else mistake("id_name or int_num or '(' expected");
}

void Parser::Expr1(Node& n) {
	if (lexeme == "+")
	{
		// Expr1 → + Expr
		n.addSon("+");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
	}
	else if (lexeme == "-")
	{
		// Expr1 → - Expr
		n.addSon("-");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
	}
	else if (lexeme == ";" || lexeme == ")" ||
		lexeme == "<=" || lexeme == ">=" || 
		lexeme == "==" || lexeme == "!=" || 
		lexeme == "<" || lexeme == ">") {
		//Expr1 → eps
		n.addSon("eps");
	}
	else mistake("';' or ')' or '+' or '-' or RelOp expected");
}


void Parser::SimpleExpr(Node& n) {
	if (lexeme == "(")
	{
		// SimpleExpr → ( Expr )
		n.addSon("(");
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.addSon(")");
		getLexeme();
	}
	else if (isName(lexeme))
	{
		// SimpleExpr → Id
		n.addSon("Id");
		Id(n.getSon(0));
	}
	else if (isNumber(lexeme))
	{
		// SimpleExpr → Const
		n.addSon("Const");
		Const(n.getSon(0));
	}
	else mistake("'(' or Name or Const expected");
}

void Parser::Condition(Node& n) {
	if (lexeme == "(")
	{
		// Condition → Expr RelationOperations Expr
		n.addSon("Expr");
		Expr(n.getSon(0));
		n.addSon("RelationOperations");
		RelationOperations(n.getSon(1));
		n.addSon("Expr");
		Expr(n.getSon(2));
	}
	else mistake("'(' expected");
}


void Parser::RelationOperations(Node& n) {
	if (lexeme == "<=")
	{
		// RelationOperations → <=
		n.addSon("<=");
		getLexeme();
	}
	else if (lexeme == ">=")
	{
		// RelationOperations → >=
		n.addSon(">=");
		getLexeme();
	}
	else if (lexeme == ">")
	{
		// RelationOperations → >
		n.addSon(">");
		getLexeme();
	}
	else if (lexeme == "<")
	{
		// RelationOperations → <
		n.addSon("<");
		getLexeme();
	}
	else if (lexeme == "==")
	{
		// RelationOperations → ==
		n.addSon("==");
		getLexeme();
	}
	else if (lexeme == "!=")
	{
		// RelationOperations → !=
		n.addSon("!=");
		getLexeme();
	}
	else mistake("'RelOp expected");
}


void Parser::Id(Node& n) {
	if (isName(lexeme))
	{
		// Id -> id_name
		n.addSon(lexeme);
		getLexeme();
	}
	else mistake("name expected");
}


void Parser::Const(Node& n) {
	if (isNumber(lexeme))
	{
		// Const -> int_num
		n.addSon(lexeme);
		getLexeme();
	}
	else mistake("const expected");
}

Parser::Parser(std::vector<std::string> lss)
{
	ls = lss;
	i = 0;
}

Node Parser::parse()
{
	Node root("Function");
	getLexeme();
	Function(root);
	if (lexeme != "#")
		throw exception("Wrong input");
	return root;
}
