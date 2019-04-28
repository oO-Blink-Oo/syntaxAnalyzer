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

stack holds the reverse order of production rules
a is incoming token

*/

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "Lexer.h"
#include <fstream>
#include <algorithm>

//PRODUCTION RULES FOR 2ND ITERATION : p. 117_3.13
//N = { S, E, T, Q, F, R }
//T = { i, =, +, -, *, / , (,), ep }
//S = S
//R = {
//	// Q is like E'
//	// R is like T'
//		S->i = E
//		E->TQ       // E -> TE'
//		Q -> + TQ | -TQ | ep
//		T->FR		 // T -> FT'
//		R -> *FR | /FR | ep
//		F -> (E) | i
//}

//FUNCTION PROTOTYPES:
string test();
string ruleString(int i);
char ruleNickName(string s);



enum Symbols {
	//TERMINAL SYMBOLS:
	T_PLUS,			// +			0
	T_MINUS,		// -			1
	T_ASTER,		// *			2
	T_DIVI,			// /			3
	T_L_PARENS,		// (			4
	T_R_PARENS,		// )			5
	T_I,			// i			6
	T_EOS,			// $			7
	T_ERROR,		//				8

	//NONTERMINAL SYMBOLS:
	N_E,			//				9			
	N_Q,			//				10
	N_T,			//				11
	N_R,			//				12
	N_F				//				13
};

Symbols translateSymbol(char c) {
	switch (c)
	{
	case '+': return T_PLUS;
	case '-': return T_MINUS;
	case '*': return T_ASTER;
	case '/': return T_DIVI;
	case '(': return T_L_PARENS;
	case ')': return T_R_PARENS;
	case 'i': return T_I;
	case '\0': return T_EOS;

	default:
		return T_ERROR;
		break;
	}
}

char numToChar(Symbols n);

string test() {
	string userInput;
	cout << "Please input a string to be tested for syntax analysis.\n";
	getline(cin, userInput);
	return userInput;
}

string ruleString(int i) {

	string rule = "";
	switch (i)
	{
	case 0:
		rule = "E -> TQ";
		return rule;
		break;
	case 1:
		rule = "E -> TQ";
		return rule;
		break;
	case 2:
		rule = "Q -> +TQ";
		return rule;
		break;
	case 3:
		rule = "Q -> -TQ";
		return rule;
		break;
	case 4:
		rule = "Q -> Eps";
		return rule;
		break;
	case 5:
		rule = "T -> FR";
		return rule;
		break;
	case 6:
		rule = "R -> *FR";
		return rule;
		break;
	case 7:
		rule = "R -> /FR";
		return rule;
		break;
	case 8:
		rule = "R -> Eps";
		return rule;
		break;
	case 9:
		rule = "F -> (E)";
		return rule;
		break;
	case 10:
		rule = "F -> i";
		return rule;
		break;
	default:
		rule = "ERROR NO SUCH RULE FOR THAT GRAMMAR";
		return rule;
		break;
	}
}

char ruleNickName(string s) {
	if (s == "IDENTIFIER") {
		return 'i';
	}
}

char numToChar(Symbols n) {
	char conversion = ' ';
	switch (n){
	case T_PLUS:
		conversion = '+';
		return conversion;
		break;
	case T_MINUS:
		conversion = '-';
		return conversion;
		break;
	case T_ASTER:
		conversion = '*';
		return conversion;
		break;
	case T_DIVI:
		conversion = '/';
		return conversion;
		break;
	case T_L_PARENS:
		conversion = '(';
		return conversion;
		break;
	case T_R_PARENS:
		conversion = ')';
		return conversion;
		break;
	case T_I:
		conversion = 'i';
		return conversion;
		break;
	case T_EOS:
		conversion = '\0';
		return conversion;
		break;
	case T_ERROR:
		conversion = 'X';
		return conversion;
		break;
	case N_E:
		conversion = 'E';
		return conversion;
		break;
	case N_Q:
		conversion = 'Q';
		return conversion;
		break;
	case N_T:
		conversion = 'T';
		return conversion;
		break;
	case N_R:
		conversion = 'R';
		return conversion;
		break;
		conversion = '+';
		return conversion;
	case N_F:
		conversion = 'F';
		return conversion;
		break;
	default:
		conversion = '^';
		return conversion;
		break;
	}

} 
using namespace std;

int main() {
	map <Symbols, map<Symbols, int>> table;
	stack<Symbols> ss;	// symbol
	//string userString = test();
	char userString [] = "a + c ";
	vector<tokenType> tokens = lexer(userString); // holds the lexed stringExp tokens[i].lexeme

	int stringSize = tokens.size() - 1; //this will change if we are testing a different string

	//userString[7] = T_EOS;
	//userString.push_back(T_EOS);

	char *charPointer = userString;			// input buffer
	int tokenTrack = 0;
	// initialize the symbols stack
	ss.push(T_EOS); //initialize the stack with a $
	ss.push(N_E);		//push the starting node in the stack 

	//set up the parsing table
	table[N_E][T_L_PARENS] = 1; // TQ			9 4
	table[N_E][T_I] = 1;		// TQ			9 6
	table[N_Q][T_PLUS] = 2;		// +TQ			10 0
	table[N_Q][T_MINUS] = 3;	// -TQ			10 1
	table[N_Q][T_R_PARENS] = 4; // EPSILON		10 5
	table[N_Q][T_EOS] = 4;		// EPSILON		10 7
	table[N_T][T_L_PARENS] = 5; // FR			11 4
	table[N_T][T_I] = 5;		// FR			11 6
	table[N_R][T_PLUS] = 8;		// EPSILON		12 0
	table[N_R][T_MINUS] = 8;	// EPSILON		12 1
	table[N_R][T_ASTER] = 6;	// *FR			12 2
	table[N_R][T_DIVI] = 7;		// /FR			12 3
	table[N_R][T_R_PARENS] = 8; // EPSILON		12 5
	table[N_R][T_EOS] = 8;		// EPSILON		12 7
	table[N_F][T_L_PARENS] = 9; // (E)			13 4
	table[N_F][T_I] = 10;		// i			13 6

	   

	while (ss.size() > 0) {
		
		tokenType currentToken = tokens[tokenTrack];

		//if (translateSymbol(*charPointer) == ss.top()) { //if both are terminal
		//	cout << "Token: " << currentToken.lexemeName << "Lexeme: " << currentToken.token << endl;

		//	tokenTrack++;
		//	charPointer++;
		//	ss.pop();
		//}

		if (translateSymbol(*charPointer) == ss.top() || translateSymbol(ruleNickName(currentToken.lexemeName)) == ss.top()) { //if both are terminal

			if (*charPointer != '\0') {
				cout << "Token: " << currentToken.lexemeName << "\tLexeme: " << currentToken.token << endl;
			}

			if (tokenTrack < stringSize) {
				tokenTrack++;
			}
			else {
				tokenTrack -= 1;
			}
			
			charPointer++;
			if (*charPointer == ' ') {
				charPointer++;
			}
			
			ss.pop();
		}
		else {
			//switch for when the token is an identifier
			if (currentToken.lexemeName == "IDENTIFIER") {
				cout << ruleString(table[ss.top()][translateSymbol('i')]) << endl;
				switch (table[ss.top()][translateSymbol('i')]) { //problem here is that *charPointer can point to an identifier such as 'a' or 'c' but those are not in our cases in translateSymbol

				case 1:		// 0. E -> TQ
					ss.pop();
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					break;
				case 2:		// 1. Q -> +TQ
					ss.pop();
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					ss.push(T_PLUS); //+
					break;
				case 3:		// 2. Q -> -TQ
					ss.pop();
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					ss.push(T_MINUS); //-
					break;
				case 4:		// 3. Q -> Eps
					ss.pop();
					break;
				case 5:		// 4. T -> FR
					ss.pop();
					ss.push(N_R);	// R
					ss.push(N_F);	// F
					break;
				case 6:		// 5. R -> *FR
					ss.pop();
					ss.push(N_R);	 // R
					ss.push(N_F);	 // F
					ss.push(T_ASTER);// *
					break;
				case 7:		// 6. R -> /FR
					ss.pop();
					ss.push(N_R);	// R
					ss.push(N_F);	// F
					ss.push(T_DIVI); // /
					break;
				case 8:		// 7. R -> Eps
					ss.pop();
					break;
				case 9:		// 8. F -> (E)
					ss.pop();
					ss.push(T_R_PARENS);	// )
					ss.push(N_E);			// E
					ss.push(T_L_PARENS);	// (
					break;
				case 10:		// 9. F -> i
					ss.pop();
					ss.push(T_I);
					break;

				default:
					cout << "You can't do that mate!" << endl;
					//return 0;
					break;
				}

			} else { //switch for regualr characters
				cout << ruleString(table[ss.top()][translateSymbol(*charPointer)]) << endl; //problem here is that *charPointer can point to an identifier such as 'a' or 'c' but those are not in our cases in translateSymbol
				
				switch (table[ss.top()][translateSymbol(*charPointer)]) { //problem here is that *charPointer can point to an identifier such as 'a' or 'c' but those are not in our cases in translateSymbol

				case 1:		// 0. E -> TQ
					ss.pop();
					ss.push(N_E); //E
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					break;
				case 2:		// 1. Q -> +TQ
					ss.pop();
					ss.push(N_Q); //Q
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					ss.push(T_PLUS); //+
					break;
				case 3:		// 2. Q -> -TQ
					ss.pop();
					ss.push(N_Q); //Q
					ss.push(N_Q); //Q
					ss.push(N_T); //T
					ss.push(T_MINUS); //-
					break;
				case 4:		// 3. Q -> Eps
					ss.pop();
					break;
				case 5:		// 4. T -> FR
					ss.pop();
					ss.push(N_R);	// R
					ss.push(N_F);	// F
					break;
				case 6:		// 5. R -> *FR
					ss.pop();
					ss.push(N_R);	 // R
					ss.push(N_F);	 // F
					ss.push(T_ASTER);// *
					break;
				case 7:		// 6. R -> /FR
					ss.pop();
					ss.push(N_R);	// R
					ss.push(N_F);	// F
					ss.push(T_DIVI); // /
					break;
				case 8:		// 7. R -> Eps
					ss.pop();
					break;
				case 9:		// 8. F -> (E)
					ss.pop();
					ss.push(T_R_PARENS);	// )
					ss.push(N_E);			// E
					ss.push(T_L_PARENS);	// (
					break;
				case 10:		// 9. F -> i
					ss.pop();
					ss.push(T_I);
					break;

				default:
					cout << "You can't do that mate!" << endl;
					//return 0;
					break;
				}
			}
		}
	}

	cout << "\n\nThis was to only test the arithmetic operations. We hard coded the string that was being tested which was \"a + c \". \n " << "\n\nSyntax Analysis Team:\nIan Michael Jesu Alvarez\nFrancis Nguyen\nFrank Young (Section 4, MW 5:30, ID: 889546446)" << endl;
	cout << "\nEverything should be working accordingly to the specifications except for one problem where the syntax analyzer would print out extra rules after the end of the analysis" << endl;
	cout << "The extra rules that are printing out at the end are the epsilon cases  Q -> Eps, R -> Eps" << endl;
	return 0;
}

//while (ss.size() > 0) {
//	//check if the top of the stack and the current character are equal to each other
//	//if so, increment the characterPointer and pop the stack
//
//	tokenType currentToken = tokens[tokenTrack];
//	//pass the lexeme name to a function to convert identifiers to i char instead that way we can use translateSymbol()
//
//	//translateSymbol(ruleNickName(currentToken.token))
//	if (currentToken.lexemeName == "IDENTIFIER") {
//		if (translateSymbol('i') == ss.top()) {	//meaning the top of the stack is a terminal as well
//					// output the production rule
//			cout << ruleString(table[ss.top()][translateSymbol(*charPointer)]) << endl;
//
//			cout << "TOKENS: " << currentToken.lexemeName << "LEXME: " << currentToken.token << endl;
//			//output lexemename and tokenname
//
//			tokenTrack++;
//			charPointer++;
//			ss.pop();
//		}
//	}
//	if (translateSymbol(*charPointer) == ss.top()) {	//meaning the top of the stack is a terminal as well // return error because of default
//		// output the production rule
//		cout << ruleString(table[ss.top()][translateSymbol(*charPointer)]) << endl;
//
//		cout << "TOKENS: " << currentToken.lexemeName << "LEXME: " << currentToken.token << endl;
//		//output lexemename and tokenname
//		tokenTrack++;
//		charPointer++;
//		ss.pop();
//	}
//	else {
//		//output the production rule
//		if (currentToken.lexemeName == "IDENTIFIER") {
//			cout << ruleString(table[ss.top()][translateSymbol('i')]) << endl;
//		}
//		cout << ruleString(table[ss.top()][translateSymbol(*charPointer)]) << endl; //////////PROBLEM
//
//		switch (table[ss.top()][translateSymbol(*charPointer)])
//		{
//
//
//		case 0:		// 0. E -> TQ
//			ss.pop();
//			ss.push(N_E); //E
//			ss.push(N_Q); //Q
//			ss.push(N_T); //T
//			break;
//		case 1:		// 1. Q -> +TQ
//			ss.pop();
//			ss.push(N_Q); //Q
//			ss.push(N_Q); //Q
//			ss.push(N_T); //T
//			ss.push(T_PLUS); //+
//			break;
//		case 2:		// 2. Q -> -TQ
//			ss.pop();
//			ss.push(N_Q); //Q
//			ss.push(N_Q); //Q
//			ss.push(N_T); //T
//			ss.push(T_MINUS); //-
//			break;
//		case 3:		// 3. Q -> Eps
//			break;
//		case 4:		// 4. T -> FR
//			ss.pop();
//			ss.push(N_R);	// R
//			ss.push(N_F);	// F
//			break;
//		case 5:		// 5. R -> *FR
//			ss.pop();
//			ss.push(N_R);	 // R
//			ss.push(N_F);	 // F
//			ss.push(T_ASTER);// *
//			break;
//		case 6:		// 6. R -> /FR
//			ss.pop();
//			ss.push(N_R);	// R
//			ss.push(N_F);	// F
//			ss.push(T_DIVI); // /
//			break;
//		case 7:		// 7. R -> Eps
//			break;
//		case 8:		// 8. F -> (E)
//			ss.pop();
//			ss.push(T_R_PARENS);	// )
//			ss.push(N_E);			// E
//			ss.push(T_L_PARENS);	// (
//			break;
//		case 9:		// 9. F -> i
//			ss.pop();
//			ss.push(T_I);
//			break;
//
//		default:
//			cout << "You can't do that mate!" << endl;
//			//return 0;
//			break;
//		}
//	}
//}