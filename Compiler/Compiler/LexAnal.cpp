#include "lexicalAnalyzer.h"
#include <fstream>

int main()
{	
	std::ofstream fout("tokens.txt");
	std::ifstream fin("sourceCode.txt");
	std::string line;
	std::string code;
	while (getline(fin, line)) {
		code +=line + ' ';
	}
	lexicalAnalyzer lA;
	HashTable<std::string, token>* h = new HashTable<std::string, token>;
	std::vector<std::string> wl;
	lA.process(h,wl,code);
	std::string g = h->display();
	fout << g;
	fout << '\n';
	for (auto x : wl) {
		fout << x<< " | MISTAKE\n";
	}
}