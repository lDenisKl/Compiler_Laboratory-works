#pragma once
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
class Parser
{
private:
	string lexeme;
	vector<string> ls; // список лексем по порядку
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
	Parser(vector<string> ls);
	Node parse();
};

