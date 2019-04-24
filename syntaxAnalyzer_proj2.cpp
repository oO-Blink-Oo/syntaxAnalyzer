/*
G={N,T,S,R}

PRODUCTION RULES FOR 1ST ITERATION: p. 116_3.9
G={
	N = {E, T, F}					//Set of Nonterminals
	T = {+, -, *, /, (, ), i}		//Set of Terminals
	S = E							//Starting point
	R = {							//Set of production rules
			E -> E + T | E - T | T
			T -> T * F | T / F | F
			F -> (E) | i
	}
}



PRODUCTION RULES FOR 2ND ITERATION: p. 117_3.13
N = {S, E, T, Q, F, R}
T = {i, =, +, -, *, /, (, ), ep}
S = S
R = {
	// Q is like E'
	// R is like T'
		S -> i = E
		E -> TQ       // E -> TE'
		Q -> +TQ | -TQ | ep
		T -> FR		 // T -> FT'
		R -> *FR | /FR | ep
		F -> (E) | i
}
*/


#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"

using namespace std;
/*
variables needed:
currChar
*/
string test();
void E();
void T();
void Q();
void R();
void F();
void Eps();

string test() {
	string userInput;
	cout << "Please input a string to be tested for syntax analysis.\n";
	cin >> userInput;
	return userInput;
}

int main() {

	//outputting to a file
	string outName = "out.txt";
	ofstream outFile(outName);
	
	string stringExp = test(); // string that is being tested for syntax
	vector<tokenType> tokens; // holds the lexed stringExp

	tokens = lexer(stringExp);

	for (size_t i = 0; i < tokens.size(); ++i) {
		if (tokens[i].lexemeName != "COMMENT") {
			cout << setw(15) << left << tokens[i].lexemeName << " =" << setw(15) << right << tokens[i].token << endl; // use outFile when done testing
		}

	}

	system("pause");
	return 0;
}
