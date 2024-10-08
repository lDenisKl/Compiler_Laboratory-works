#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "HashTable.h"

using namespace std;
//
//int main() {
//	ofstream fout("tokens.txt");
//	ifstream fin("sourceCode.txt");
//	string code;
//	string line;
//	while (getline(fin, line))
//	{
//		code += line + '\n';
//	}
//	// -----
//	vector<int> tokens;
//	fout << tokens[0];
//}


int main()
{
	HashTable<string, string>* h = new HashTable<string, string>;
	h->insertNode("int", "type | 1");
	h->insertNode("dbl", "err | 2 ");
	h->insertNode("float", "type | 3");
	h->display();
	cout << h->getSize() << endl;
	cout << h->deleteNode("dbl") << endl;
	cout << h->getSize() << endl;
	cout << h->isEmpty() << endl;
	cout << h->get("float");
}