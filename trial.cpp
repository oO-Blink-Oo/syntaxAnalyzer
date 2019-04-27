//////#include <iostream>
//////#include <stack>
//////#include <map>
//////#include "Lexer.h"
//////#include <fstream>
//////#include <algorithm>
//////
////////PRODUCTION RULES FOR 2ND ITERATION : p. 117_3.13
////////N = { S, E, T, Q, F, R }
////////T = { i, =, +, -, *, / , (,), ep }
////////S = S
////////R = {
////////	// Q is like E'
////////	// R is like T'
////////		S->i = E
////////		E->TQ       // E -> TE'
////////		Q -> + TQ | -TQ | ep
////////		T->FR		 // T -> FT'
////////		R -> *FR | /FR | ep
////////		F -> (E) | i
////////}
//////
//////
//////enum Symbols {
//////	//TERMINAL SYMBOLS:
//////	T_PLUS,			// +
//////	T_MINUS,		// -
//////	T_ASTER,		// *
//////	T_DIVI,			// /
//////	T_L_PARENS,		// (
//////	T_R_PARENS,		// )
//////	T_I,			// i
//////	T_EOS,			// $
//////	T_ERROR,
//////
//////	//NONTERMINAL SYMBOLS:
//////	N_E,
//////	N_Q,
//////	N_T,
//////	N_R,
//////	N_F
//////};
//////
//////Symbols translateSymbol(char c) {
//////	switch (c)
//////	{
//////	case '+': return T_PLUS;
//////	case '-': return T_MINUS;
//////	case '*': return T_ASTER;
//////	case '/': return T_DIVI;
//////	case '(': return T_L_PARENS;
//////	case ')': return T_R_PARENS;
//////	case 'i': return T_I;
//////	case '$': return T_EOS;
//////	
//////	default:
//////		break;
//////	}
//////}
//////
//////string test() {
//////	string userInput;
//////	cout << "Please input a string to be tested for syntax analysis.\n";
//////	getline(cin, userInput);
//////	return userInput;
//////}
//////
////////FUNCTION PROTOTYPES:
//////string test();
//////
//////using namespace std;
//////
//////int main() {
//////	map <Symbols, map<Symbols, int>> table;
//////	stack<Symbols> ss;	// symbol
//////	string userString = test();
//////
//////	vector<tokenType> tokens = lexer(userString); // holds the lexed stringExp
//////
//////	char charPointer = 0;			// pointer for currentCharacter
//////
//////	// initialize the symbols stack
//////	ss.push(T_EOS); //initialize the stack with a $
//////	ss.push(N_E);		//push the starting node in the stack 
//////
//////	//set up the parsing table
//////	table[N_E][T_L_PARENS] = 0; // TQ
//////	table[N_E][T_I] = 1;		// TQ
//////	table[N_Q][T_PLUS] = 2;		// +TQ
//////	table[N_Q][T_MINUS] = 3;	// -TQ
//////	table[N_Q][T_R_PARENS] = 4; // EPSILON
//////	table[N_Q][T_EOS] = 5;		// EPSILON
//////	table[N_T][T_L_PARENS] = 6; // FR
//////	table[N_T][T_I] = 7;		// FR
//////	table[N_R][T_PLUS] = 8;		// EPSILON
//////	table[N_R][T_MINUS] = 9;	// EPSILON
//////	table[N_R][T_ASTER] = 10;	// *FR
//////	table[N_R][T_DIVI] = 11;	// /FR
//////	table[N_R][T_R_PARENS] = 12;// EPSILON
//////	table[N_R][T_EOS] = 13;		// EPSILON
//////	table[N_F][T_L_PARENS] = 14;// (E)
//////	table[N_F][T_I] = 15;		// i
//////	
//////	while (ss.size() > 0){
//////		//check if the top of the stack and the current character are equal to each other
//////		//if so, increment the characterPointer and pop the stack
//////		
//////		if (translateSymbol(userString[charPointer]) == ss.top()) {	//meaning the top of the stack is a terminal as well
//////			//output lexemename and tokenname
//////			charPointer++;
//////			ss.pop();
//////		} 
//////		else {
//////			//output the production rule
//////
//////			switch (table[ss.top()][translateSymbol(userString[charPointer])])
//////			{
//////				
//////			
//////			case 0:		// 0. E -> TQ
//////				ss.pop();
//////				ss.push(N_E); //E
//////				ss.push(N_Q); //Q
//////				ss.push(N_T); //T
//////				break;
//////			case 1:		// 1. Q -> +TQ
//////				ss.pop();
//////				ss.push(N_Q); //Q
//////				ss.push(N_Q); //Q
//////				ss.push(N_T); //T
//////				ss.push(T_PLUS); //+
//////				break;
//////			case 2:		// 2. Q -> -TQ
//////				ss.pop();
//////				ss.push(N_Q); //Q
//////				ss.push(N_Q); //Q
//////				ss.push(N_T); //T
//////				ss.push(T_MINUS); //-
//////				break;
//////			case 3:		// 3. Q -> Eps
//////				break;
//////			case 4:		// 4. T -> FR
//////				ss.pop();
//////				ss.push(N_R);	// R
//////				ss.push(N_F);	// F
//////				break;
//////			case 5:		// 5. R -> *FR
//////				ss.pop();
//////				ss.push(N_R);	 // R
//////				ss.push(N_F);	 // F
//////				ss.push(T_ASTER);// *
//////				break;
//////			case 6:		// 6. R -> /FR
//////				ss.pop();
//////				ss.push(N_R);	// R
//////				ss.push(N_F);	// F
//////				ss.push(T_DIVI); // /
//////				break;
//////			case 7:		// 7. R -> Eps
//////				break;
//////			case 8:		// 8. F -> (E)
//////				ss.pop();
//////				ss.push(T_R_PARENS);	// )
//////				ss.push(N_E);			// E
//////				ss.push(T_L_PARENS);	// (
//////				break;
//////			case 9:		// 9. F -> i
//////				ss.pop();
//////				ss.push(T_I);
//////				break;
//////			
//////			default:
//////				cout << "You can't do that mate!" << endl;
//////				return 0;
//////				break;
//////			}
//////		}
//////	}
//////
//////	cout << "PRINT HERE WHEN DONE" << endl;
//////
//////	return 0;
//////}
//////
////
////
////
////#include <iostream>
////#include <fstream>
////#include <string>
////#include <stack>
////#include <algorithm>
////#include "Lexer.h"
////
////using namespace std;
/////*
////variables needed:
////currChar
////*/
////
//////enum NonTerminals {
//////	E = 0,
//////	Q = 1,
//////	T = 2,
//////	R = 3,
//////	F = 4,
//////	ERROR = 5
//////};
////
////enum Symbols {
////	//TERMINAL SYMBOLS:
////	T_PLUS,			// +
////	T_MINUS,		// -
////	T_ASTER,		// *
////	T_DIVI,			// /
////	T_L_PARENS,		// (
////	T_R_PARENS,		// )
////	T_I,			// i
////	T_EOS,			// $
////	T_ERROR,
////
////	//NONTERMINAL SYMBOLS:
////	N_E,
////	N_Q,
////	N_T,
////	N_R,
////	N_F
////};
////
////Symbols translateSymbol(char c);
////
//////FUNCTION PROTOTYPES:
////string test();
////bool checkTerminal(string s);
////void errorMessage();
////int getCharacterCol(char c);
////int getProdRow(string s);
////char lexConvert(string s);
////Symbols translateSymbol(char c);
////
////
////string test() {
////	string userInput;
////	cout << "Please input a string to be tested for syntax analysis.\n";
////	getline(cin, userInput);
////	return userInput;
////}
////
////bool checkTerminal(string c) {
////	bool flag = false;
////	vector<string> terminals{ "+", "-", "*", "/", "(", ")", "i", "$" };
////	for (size_t i = 0; i < terminals.size(); i++) {
////		if (c == terminals[i]) {
////			flag = true;
////		}
////	}
////	return flag;
////}
////
////void errorMessage() {
////	cout << "ERROR ERROR ERROR.\n";
////}
////
////int getCharacterCol(char c) {
////	switch (c)
////	{
////	case '+':
////		return 0;
////		break;
////
////	case '-':
////		return 1;
////		break;
////
////	case '*':
////		return 2;
////		break;
////
////	case '/':
////		return 3;
////		break;
////
////	case '(':
////		return 4;
////		break;
////	case ')':
////		return 5;
////		break;
////	case 'i':
////		return 6;
////		break;
////	case '$':
////		return 7;
////		break;
////	default:
////		cout << "This is a default case for getCharacterCol.\n";
////		break;
////	}
////}
////
////char lexConvert(string s) {
////	if (s == "IDENTIFIER") {
////		return 'i';
////	}
////}
////
////int getProdRow(string s) {
////
////	switch (s[0]) {
////
////	case 'E':
////		return 0;
////		break;
////	case 'Q':
////		return 1;
////		break;
////	case 'T':
////		return 2;
////		break;
////	case 'R':
////		return 3;
////		break;
////	case 'F':
////		return 4;
////		break;
////	default:
////		cout << "This is a default case for getProdRow";
////		break;
////	}
////}
////
////string predictiveTable[5][8] = {
////	/* +       -      *      /     (     )     i     $  */
////	/*E*/{" ",    " ",   " ",   " ",  "TQ", " ",  "TQ", " "},
////	/*Q*/{"+TQ","-TQ",   " ",   " ",   " ", "Z",   " ", "Z"},
////	/*T*/{" ",    " ",   " ",   " ",  "FR", " ",  "FR", " "},
////	/*R*/{"Z",    "Z", "*FR", "/FR",   " ", "Z",   " ", "Z"},
////	/*F*/{" ",    " ",   " ",   " ", "(E)", " ",   "i", " "}
////};
////
////Symbols translateSymbol(char c) {
////	switch (c)
////	{
////	case '+': return T_PLUS;
////	case '-': return T_MINUS;
////	case '*': return T_ASTER;
////	case '/': return T_DIVI;
////	case '(': return T_L_PARENS;
////	case ')': return T_R_PARENS;
////	case 'i': return T_I;
////	case '$': return T_EOS;
////	default:
////		break;
////	}
////}
////
////int main() {
////
////	//outputting to a file
////	string outName = "out.txt";
////	ofstream outFile(outName);
////
////	//strings to be tested
////	string a = "a = b + c";
////	string b = "a = b + c;";
////	string c = "a = b + c ;"; //perfect case
////	string d = "a=b+c";
////	string e = "a=b+c;";
////
////	//VARIABLES NEEDED
////	//string stringExp = test(); // string that is being tested for syntax
////
////	vector<tokenType> tokens; // holds the lexed stringExp
////	tokens = lexer(c); // replace with stringExp after testing is done
////	stack<string> productionStack; // stack that holds the Production rules to be processed
////	int tokenPointer = 0; // to be incremented once the right character has been popped
////	//char incomingToken;
////
////	productionStack.push("$");//push $ onto the stack
////	c.push_back('$'); // push a $ at the end of the stringExp in this case string c
////	productionStack.push("E");//Push the root node in the stack
////
////
////	while (productionStack.size() != 0) { //while the stack is not empty
////		string topOfStack = productionStack.top();
////		tokenType currentToken = tokens[tokenPointer];
////
////		//char convertedID = lexConvert(currentToken.lexemeName);//make function that replaces IDENTIFIER TO i
////
////		int charCol = getCharacterCol(lexConvert(currentToken.lexemeName));
////		int prodRow = getProdRow(topOfStack);
////
////		if (checkTerminal(topOfStack)) { // if terminal
////			if (topOfStack == currentToken.lexemeName) { //PROBLEM HERE
////				//pop stack and go to next input token
////				productionStack.pop();
////				tokenPointer++;
////			}
////			else {
////				errorMessage(); //error
////			}
////		}
////		else {
////
////			if (predictiveTable[prodRow][charCol] != " ") { // not blank therefore there is a production rule associated on the right side
////				string ruleFromTable = " ";
////				ruleFromTable = predictiveTable[prodRow][charCol]; //this has the production rule now
////				productionStack.pop(); // pops the top of the stack
////				reverse(ruleFromTable.begin(), ruleFromTable.end());//reverse the order of the rule inside the table then push it
////
////				//cout << "PRINT SOMETHING\n";
////
////				for (size_t i = 1; i < ruleFromTable.size() + 1; i++) {
////					productionStack.push(static_cast<string>(ruleFromTable[i]));
////				}
////
////
////			}
////			else {
////				errorMessage();
////			}
////		}
////	}
////
////	return 0;
////}
////
////
//////int main() {
//////	//variables needed
//////	string userString = test(); // get a string input to be analyzed 
//////	vector<tokenType> tokens = lexer(userString);    //vector to hold tokens as they are being inputted
//////
//////	int tokenIndex = 0;  //Index used to step through token vector
//////
//////	bool printSwitch = true;
//////
//////	vector<tokenType> tokenList; //vector that holds all tokens once they have been read in initially
//////	tokenType currentToken;
//////
//////	//emter root node now
//////
//////	return 0;
//////}
////
//////for (size_t i = 0; i < tokens.size(); ++i) {
//////	if (tokens[i].lexemeName != "COMMENT") {
//////		cout << setw(15) << left << tokens[i].lexemeName << " =" << setw(15) << right << tokens[i].token << endl; // use outFile when done testing
//////	}
//////
//////}
//
//
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//int main() {

//	char word []= "Hello";
//	char * p;
//	p = word;
//
//	cout << *p << endl;	//H
//	p++;
//	cout << *p << endl; // e
//	return 0;
//}