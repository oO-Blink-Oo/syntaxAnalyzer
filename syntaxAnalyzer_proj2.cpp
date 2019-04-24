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
bool E();
bool T();
bool Q();
bool R();
bool F();
bool Eps();

string test() {
	string userInput;
	cout << "Please input a string to be tested for syntax analysis.\n";
	getline(cin, userInput);
	return userInput;
}

bool E() {
	bool flag = false;
	if (T()) {
		if (Q()) {
			cout << "E -> TQ\n";
			flag = true;
		}
	}
}

bool Q() {
	char currentChar = ' ';
	bool flag = false;
	//currentChar = token;
	if (currentChar == '+') {
		if (T()) {
			if (Q()) {
				cout << "Q -> +TQ\n";
				flag = false;
			}
		}
		else
			if (currentChar == ')' || currentChar == '$') {
				//backup;
				cout << "Q -> eps\n";
				flag = true;
			}
	}
}

bool T() {
	bool flag = false;
	if (F()) {
		if (R()) {
			cout << "T -> FR'\n";
			flag = false;
		}
	}
}

bool R() {
	char currentChar = ' ';
	bool flag = false;
	//currentChar = token;
	if (currentChar == '*') {
		if(F())
			if (R()) {
				cout << "R -> *FR\n";
				flag = false;
			}
	}
	else
		if (currentChar == '+' || currentChar == ')' || currentChar == '$') {
			cout << "R -> eps\n";
			//backup;
			flag = true;
		}

}

bool F() {
	char currentChar = ' ';
	bool flag = false;
	//currentChar = token;
	if (/*currentChar == 'a' to 'z'*/) {
		cout << "F -> id'\n";
		flag = true;
	}else
		if (currentChar = ')') {
			if (E()) {
				//currentChar = token;
			}
			if (currentChar = ')') {
				cout << "F -> (E)'\n";
				flag = true;
			}
		}
}

int main() {
	//variables needed
	string userString = test(); // get a string input to be analyzed 
	vector<tokenType> tokens = lexer(userString);    //vector to hold tokens as they are being inputted

	int tokenIndex = 0;  //Index used to step through token vector

	bool printSwitch = true;

	vector<tokenType> tokenList; //vector that holds all tokens once they have been read in initially
	tokenType currentToken;

	//emter root node now

	return 0;
}

//int main() {
//
//	//outputting to a file
//	string outName = "out.txt";
//	ofstream outFile(outName);
//	
//	//strings to be tested
//	string a = "a = b + c";
//	string b = "a = b + c;";
//	string c = "a = b + c ;"; //perfect case
//	string d = "a=b+c";
//	string e = "a=b+c;";
//
//	//string stringExp = test(); // string that is being tested for syntax
//	vector<tokenType> tokens; // holds the lexed stringExp
//
//	tokens = lexer(e); // replace with stringExp after testing is done
//
//	for (size_t i = 0; i < tokens.size(); ++i) {
//		if (tokens[i].lexemeName != "COMMENT") {
//			cout << setw(15) << left << tokens[i].lexemeName << " =" << setw(15) << right << tokens[i].token << endl; // use outFile when done testing
//		}
//
//	}
//
//	return 0;
//}
