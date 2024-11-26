#pragma once
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
class Parser
{
private:
	string input, lexeme;
	int i;
	bool isNumber(string s);
	void getLexeme();
	void S(Node& n);
	void S1(Node& n);
	void T(Node& n);
	void T1(Node& n);
	void F(Node& n);
	void F1(Node& n);
	void A(Node& n);
public:
	Parser(string inp);
	Node parse();
};

