#include <iostream>
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


enum Symbols {
	//TERMINAL SYMBOLS:
	T_PLUS,			// +
	T_MINUS,		// -
	T_ASTER,		// *
	T_DIVI,			// /
	T_L_PARENS,		// (
	T_R_PARENS,		// )
	T_I,			// i
	T_EOS,			// $
	T_ERROR,

	//NONTERMINAL SYMBOLS:
	N_E,
	N_Q,
	N_T,
	N_R,
	N_F
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
	case '$': return T_EOS;
	
	default:
		break;
	}
}

string test() {
	string userInput;
	cout << "Please input a string to be tested for syntax analysis.\n";
	getline(cin, userInput);
	return userInput;
}

//FUNCTION PROTOTYPES:
string test();

using namespace std;

int main() {
	map <Symbols, map<Symbols, int>> table;
	stack<Symbols> ss;	// symbol
	string userString = test();

	char charPointer = 0;			// pointer for currentCharacter

	// initialize the symbols stack
	ss.push(T_EOS); //initialize the stack with a $
	ss.push(N_E);		//push the starting node in the stack 

	//set up the parsing table
	table[N_E][T_L_PARENS] = 0; // TQ
	table[N_E][T_I] = 1;		// TQ
	table[N_Q][T_PLUS] = 2;		// +TQ
	table[N_Q][T_MINUS] = 3;	// -TQ
	table[N_Q][T_R_PARENS] = 4; // EPSILON
	table[N_Q][T_EOS] = 5;		// EPSILON
	table[N_T][T_L_PARENS] = 6; // FR
	table[N_T][T_I] = 7;		// FR
	table[N_R][T_PLUS] = 8;		// EPSILON
	table[N_R][T_MINUS] = 9;	// EPSILON
	table[N_R][T_ASTER] = 10;	// *FR
	table[N_R][T_DIVI] = 11;	// /FR
	table[N_R][T_R_PARENS] = 12;// EPSILON
	table[N_R][T_EOS] = 13;		// EPSILON
	table[N_F][T_L_PARENS] = 14;// (E)
	table[N_F][T_I] = 15;		// i
	
	while (ss.size() > 0){
		//check if the top of the stack and the current character are equal to each other
		//if so, increment the characterPointer and pop the stack
		
		if (translateSymbol(userString[charPointer]) == ss.top()) {	//meaning the top of the stack is a terminal as well
			//output lexemename and tokenname
			charPointer++;
			ss.pop();
		} 
		else {
			//output the production rule

			switch (table[ss.top()][translateSymbol(userString[charPointer])])
			{
				
			
			case 0:		// 0. E -> TQ
				break;
			case 1:		// 1. Q -> +TQ
				break;
			case 2:		// 2. Q -> -TQ
				break;
			case 3:		// 3. Q -> Eps
				break;
			case 4:		// 4. T -> FR
				ss.pop();
				ss.push(N_R);	// R
				ss.push(N_F);	// F
				break;
			case 5:		// 5. R -> *FR
				ss.pop();
				ss.push(N_R);	 // R
				ss.push(N_F);	 // F
				ss.push(T_ASTER);// *
				break;
			case 6:		// 6. R -> /FR
				ss.pop();
				ss.push(N_R);	// R
				ss.push(N_F);	// F
				ss.push(T_DIVI); // /
				break;
			case 7:		// 7. R -> Eps
				break;
			case 8:		// 8. F -> (E)
				ss.pop();
				ss.push(T_R_PARENS);	// )
				ss.push(N_E);			// E
				ss.push(T_L_PARENS);	// (
				break;
			case 9:		// 9. F -> i
				ss.pop();
				ss.push(T_I);
				break;
			
			default:
				cout << "You can't do that mate!" << endl;
				return 0;
				break;
			}
		}
	}

	cout << "PRINT HERE WHEN DONE" << endl;

	return 0;
}

