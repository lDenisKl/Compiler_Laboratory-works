#pragma once
#include "Node.h"
#include "token.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;
class Parser
{
private:
	string lexeme;
	set<string> variables;
	vector<token> ls;
	int i;
	bool isNumber(string s);
	bool isName(string s);
	void getLexeme();
	void Function(Node& n);
	void Begin(Node& n);
	void End(Node& n);
	void FunctionName(Node& n);
	void Descriptions(Node& n);
	void Descriptions1(Node& n);
	void Descr(Node& n);
	void VarList(Node& n);
	void VarList1(Node& n);
	void Type(Node& n);
	void Operators(Node& n);
	void Operators1(Node& n);
	void Op(Node& n);
	void Expr(Node& n);
	void Expr1(Node& n);
	void SimpleExpr(Node& n);
	void Condition(Node& n);
	void RelationOperations(Node& n);
	void Id(Node& n);
	void Const(Node& n);

public:
	Parser(vector<token> ls);
	Node parse();
};

