#include "lexicalAnalyzer.h"
#include "Parser.h"
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	std::ifstream fin("sourceCode.txt");
	std::ofstream fout("tokens.txt");
	std::ofstream Sout("tree.txt");
	std::string line;
	std::string code;
	while (getline(fin, line)) {
		code +=line + ' ';
	}
	lexicalAnalyzer lA;
	HashTable<std::string, token>* h = new HashTable<std::string, token>;
	std::vector<std::string> wrongLexems;
	std::vector<std::string> lexems;
	lA.process(h,wrongLexems,code,lexems);
	std::string g = h->display();
	fout << g;
	fout << '\n';
	for (auto x : wrongLexems) {
		fout << x<< " | MISTAKE\n";
	}

	Parser p(lexems);
	Node root = p.parse();
	root.print(0);
}