/*
G={N,T,S,R}

PRODUCTION RULES FOR 1ST ITERATION: p. 116_3.9

N = {E, T, F}
T = {+, -, *, /, (, ), i}
S = E
R = {
		E -> E + T | E - T | T
		T -> T * F | T / F | F
		F -> (E) | i
}




PRODUCTION RULES FOR 2ND ITERATION: p. 117_3.13
N = {S, E, T, Q, F, R}
T = {i, =, +, -, *, /, (, ), ep}
S = S
R = {
		S -> i = E
		E -> TQ
		Q -> +TQ | -TQ | ep
		T -> FR
		R -> *FR | /FR | ep
		F -> (E) | i
}
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main() {
	ofstream outFile("out.txt");

	cout << "Hello World! \n";
	cout << "The file has just been made! \n";
	outFile << "Hello World! \n";

	return 0;
}