#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	ofstream fout("tokens.txt");
	ifstream fin("sourceCode.txt");
	string code;
	string line;
	while (getline(fin, line))
	{
		code += line + '\n';
	}
	// -----
	vector<int> tokens;
	fout << tokens[0];
}