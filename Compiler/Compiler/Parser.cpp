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
	if(ls[i-1].type == LexemType::ID)
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
	lexeme = ls[i].lexem;
	i++;
	
}

void mistake(string msg) {
	cout << msg << '\n';
	exit(1);
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
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr+" "+ n.getSon(2).tr + " " + n.getSon(3).tr;
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
		if (lexeme == "(") {
			n.addSon("(");
			getLexeme();
		}
		else {
			mistake("'(' excepted");
		}
		if (lexeme == ")") {
			n.addSon(")");
			getLexeme();
		}
		else {
			mistake("')' excepted");
		}
		if (lexeme == "{") {
			n.addSon("{");
			getLexeme();
		}
		else {
			mistake("'{' excepted");
		}
		n.tr = n.getSon(1).tr + " CALL";
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
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			mistake("';' expected");
		}
		if (lexeme == "}") {
			n.addSon("}");
			getLexeme();
		}
		else {
			mistake("'}' expected");
		}
		n.tr = n.getSon(1).tr + " RETURN";
	}
	else mistake("'return' expected");
}


void Parser::FunctionName(Node& n) {
	if (isName(lexeme))
	{
		// FunctionName → Id
		n.addSon("Id");
		Id(n.getSon(0)); 
		n.tr = n.getSon(0).tr;
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
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr;
	}
	else mistake("'int' expected");
}

void Parser::Descriptions1(Node& n) {
	if (lexeme == "int")
	{
		// Descriptions1 → Descriptions
		n.addSon("Descriptions");
		Descriptions1(n.getSon(0));
		n.tr = n.getSon(0).tr;
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
		if (lexeme == ";") {
			n.addSon(";");
			getLexeme();
		}
		else {
			mistake("';' expected");
		}
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr+ to_string(n.getSon(1).count) + " DECL";

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
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr;
		n.count = n.getSon(1).count + 1;
	}
	else mistake("id_name expected");
}

void Parser::VarList1(Node& n) {
	if (lexeme == ",")
	{
		// VarList1 → , VarList
		n.addSon(","); 
		n.getSon(0).tr = lexeme;
		getLexeme();
		n.addSon("VarList");
		VarList(n.getSon(1));

		n.tr = " " + n.getSon(1).tr;
		n.count = n.getSon(1).count;
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
		n.getSon(0).tr = lexeme;
		getLexeme();
		n.tr = n.getSon(0).tr;
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
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr;
	}
	else mistake("id_name or 'for' expected");
}

void Parser::Operators1(Node & n) {
	if (isName(lexeme) || lexeme == "for")
	{
		// Operators1 → Operators
		n.addSon("Operators");
		Operators(n.getSon(0));
		n.tr = n.getSon(0).tr;
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
		n.getSon(0).tr = lexeme;
		getLexeme();

		if (lexeme == "(") {
			n.addSon("(");
			n.getSon(1).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("'(' expected");
		}
		n.addSon("Id");
		Id(n.getSon(2));
		if (lexeme == "=") {
			n.addSon("=");
			n.getSon(3).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("'=' expected");
		}
		n.addSon("Expr");
		Expr(n.getSon(4));
		if (lexeme == ";") {
			n.addSon(";");
			n.getSon(5).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("';' expected");
		}

		n.addSon("Condition");
		Condition(n.getSon(6));
		if (lexeme == ";") {
			n.addSon(";");
			n.getSon(7).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("';' expected");
		}

		n.addSon("Expr");
		Expr(n.getSon(8));
		if (lexeme == ")") {
			n.addSon(")");
			n.getSon(9).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("')' expected");
		}

		if (lexeme == "{") {
			n.addSon("{");
			n.getSon(10).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("'{' expected");
		}
		n.addSon("Operators");
		Operators(n.getSon(11));
		if (lexeme == "}") {
			n.addSon("}");
			n.getSon(12).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("'}' expected");
		}

		// n.tr = lexeme; ????
	}
	else if (isName(lexeme) ) {
		// Op -> Id = Expr ; 
		n.addSon("Id");
		Id(n.getSon(0));
		if (lexeme == "=") {
			n.addSon("=");
			n.getSon(1).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("'=' expected");
		}
		n.addSon("Expr");
		Expr(n.getSon(2));
		if (lexeme == ";") {
			n.addSon(";");
			n.getSon(3).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("';' expected");
		}

		n.tr = n.getSon(0).tr + " " + n.getSon(2).tr+"=";
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
		n.tr = n.getSon(0).tr + " " + n.getSon(1).tr;
	}
	else mistake("id_name or int_num or '(' expected");
}

void Parser::Expr1(Node& n) {
	if (lexeme == "+")
	{
		// Expr1 → + Expr
		n.addSon("+"); 
		n.getSon(0).tr = lexeme;
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.tr = n.getSon(1).tr + " " + n.getSon(0).tr;
	
	}
	else if (lexeme == "-")
	{
		// Expr1 → - Expr
		n.addSon("-");
		n.getSon(0).tr = lexeme;
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1)); 
		n.tr = n.getSon(1).tr + " " + n.getSon(0).tr;
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
		n.getSon(0).tr = "(";
		getLexeme();
		n.addSon("Expr");
		Expr(n.getSon(1));
		if (lexeme == ")") {
			n.addSon(")");
			n.getSon(2).tr = ")";
			getLexeme();
		}
		else {
			mistake("')' expected");
		}

		n.tr = n.getSon(1).tr+" ";
	}
	else if (isName(lexeme))
	{
		// SimpleExpr → Id
		n.addSon("Id");
		Id(n.getSon(0));
		n.tr = n.getSon(0).tr;

	}
	else if (isNumber(lexeme))
	{
		// SimpleExpr → Const
		n.addSon("Const");
		Const(n.getSon(0)); 
		n.tr = n.getSon(0).tr;
	}
	else mistake("'(' or Name or Const expected");
}

void Parser::Condition(Node& n) {
	if (lexeme == "(" || isNumber(lexeme) || isName(lexeme))
	{
		// Condition → Expr RelationOperations Expr
		n.addSon("Expr");
		Expr(n.getSon(0));
		n.addSon("RelationOperations");
		RelationOperations(n.getSon(1));
		n.addSon("Expr");
		Expr(n.getSon(2));

		n.tr = n.getSon(0).tr + " " + n.getSon(2).tr + " " + n.getSon(1).tr;
	}
	else mistake("'(' expected");
}


void Parser::RelationOperations(Node& n) {
	if (lexeme == "<=")
	{
		// RelationOperations → <=
		n.addSon("<=");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else if (lexeme == ">=")
	{
		// RelationOperations → >=
		n.addSon(">=");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else if (lexeme == ">")
	{
		// RelationOperations → >
		n.addSon(">");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else if (lexeme == "<")
	{
		// RelationOperations → <
		n.addSon("<");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else if (lexeme == "==")
	{
		// RelationOperations → ==
		n.addSon("==");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else if (lexeme == "!=")
	{
		// RelationOperations → !=
		n.addSon("!=");
		n.getSon(0).tr = lexeme;
		getLexeme();
	}
	else mistake("'RelOp expected");
}


void Parser::Id(Node& n) {
	if (isName(lexeme))
	{
		// Id -> id_name
		bool isAlreadyDeclared = variables.find(lexeme) != variables.end();
		if (!isAlreadyDeclared) {
			n.addSon(lexeme);
			n.getSon(0).tr = lexeme;
			getLexeme();
		}
		else {
			mistake("already declared : " + lexeme);
		}

		n.tr = n.getSon(0).tr;
	}
	else mistake("name expected");
}


void Parser::Const(Node& n) {
	if (isNumber(lexeme))
	{
		// Const -> int_num
		n.addSon(lexeme);
		n.getSon(0).tr = lexeme;
		getLexeme();
		n.tr = n.getSon(0).tr;
	}
	else mistake("const expected");
}

Parser::Parser(std::vector<token> lss)
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
		mistake("chto-to poshlo ne tak");
	return root;
}
