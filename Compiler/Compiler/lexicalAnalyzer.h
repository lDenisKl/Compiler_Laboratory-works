#pragma once
#include "HashTable.h"
#include "token.h"
#include "dfa.h"
#include "nfa.h"
#include <vector>

class lexicalAnalyzer
{
private:
	nfa n;
	dfa d;
	std::string source="";
	long currentPos = 0;
	token next();
	long charpos(std::string str1, char c);
public:
	lexicalAnalyzer();
	void  process(HashTable<std::string, token>*& hash, std::vector<std::string>& wrongLexems, std::string source);
};



long lexicalAnalyzer::charpos(std::string str1, char c)
{
	char* str = &str1[0];
	for (char* ptr = str; *ptr; ptr++)
		if (*ptr == c) return (long)(ptr - str);
	return -1;
}

lexicalAnalyzer::lexicalAnalyzer() {
	int statesCount = 15;
	std::string alphabetString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789=!-+<>;,(){}";
	std::vector<char> alphabet;
	for (int i = 0; i < alphabetString.size(); ++i) {
		alphabet.push_back(alphabetString[i]);
	}
	std::vector<int> finalStates = { 1,2,3,4,7 };
	std::vector<std::vector<std::vector<int>>> transitFunction;
	transitFunction.resize(statesCount);
	for (int i = 0; i < statesCount; ++i) {
		transitFunction[i].resize(alphabetString.size());
	}

	// const values: 0....9
	std::string constStr = "0123456789";
	for (auto ch : constStr) {
		int index = charpos(alphabetString, ch);
		transitFunction[0][index] = { 1 };
		transitFunction[1][index] = { 1 };
	}

	// sep (){};,
	std::string separatorsStr = "(){};,";
	for (auto ch : separatorsStr) {
		int index = charpos(alphabetString, ch);
		transitFunction[0][index] = { 4 };
	}

	// ID values : a...Z
	std::string idStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	for (auto ch : idStr) {
		int index = charpos(alphabetString, ch);
		transitFunction[2][index] = { 2 };
		if (ch == 'i') {
			std::vector<int> tmp;
			tmp.push_back(2);
			tmp.push_back(5);
			transitFunction[0][index] =tmp;
		}
		else if (ch == 'r') {

			std::vector<int> tmp;
			tmp.push_back(2);
			tmp.push_back(8);
			transitFunction[0][index] = tmp;
		}
		else if(ch == 'f'){
			std::vector<int> tmp;
			tmp.push_back(2);
			tmp.push_back(13);
			transitFunction[0][index] = tmp;
		}
		else {
			transitFunction[0][index] = { 2 };
		}
	}
	//int
	transitFunction[5][charpos(alphabetString, 'n')] = { 6 };
	transitFunction[6][charpos(alphabetString, 't')] = { 7 };
	//for
	transitFunction[13][charpos(alphabetString, 'o')] = { 14 };
	transitFunction[14][charpos(alphabetString, 'r')] = { 7 };
	//return
	transitFunction[8][charpos(alphabetString, 'e')] = { 9 };
	transitFunction[9][charpos(alphabetString, 't')] = { 10 };
	transitFunction[10][charpos(alphabetString, 'u')] = { 11 };
	transitFunction[11][charpos(alphabetString, 'r')] = { 12 };
	transitFunction[12][charpos(alphabetString, 'n')] = { 7 };

	////KEYWORDS
	//std::string keywordStr = "neturo";
	//for (auto ch : keywordStr) {
	//	int index = charpos(alphabetString, ch);
	//	transitFunction[5][index] = { 5 };
	//}



	// Operators 
	transitFunction[3][charpos(alphabetString, '=')] = { 3 };
	transitFunction[0][charpos(alphabetString, '=')] = { 3 };
	transitFunction[0][charpos(alphabetString, '<')] = { 3 };
	transitFunction[0][charpos(alphabetString, '>')] = { 3 };
	transitFunction[0][charpos(alphabetString, '+')] = { 3 };
	transitFunction[0][charpos(alphabetString, '-')] = { 3 };
	transitFunction[0][charpos(alphabetString, '!')] = { 3 };

	for (int i = 0; i < transitFunction.size(); ++i) {
		for (int j = 0; j < transitFunction[i].size(); ++j) {
			if (transitFunction[i][j].size() == 0) {
				transitFunction[i][j].push_back(-1);
			}
		}
	}
	nfa nfa1(statesCount, alphabet, finalStates, transitFunction);
	dfa dfa1 = nfa1.createDFA();

	d = dfa1;
	n = nfa1;
}


token lexicalAnalyzer::next() {
	token t;
	std::string lexem="";
	while (source[currentPos]!=' ')
	{
		lexem += source[currentPos];
		currentPos++;
	}
	currentPos++;
	t.lexem = lexem;
	t.type = d.isAccept(lexem);
	return t;
}

void lexicalAnalyzer::process(HashTable<std::string,token>*& hash,std::vector<std::string>& wrongLexems, std::string sourc1e) {
	source = sourc1e;
	while (currentPos != source.size()) {
		token t = next();
		if (t.type == LexemType::ERROR) {
			wrongLexems.push_back(t.lexem);
		}
		else{
			hash->insertNode(t.lexem, t);
		}
	}

}