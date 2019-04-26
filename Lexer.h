
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdio.h>


using namespace std;


struct tokenType {
	string token; // token name for the lexeme
	int lexeme;
	string lexemeName; // this prints out the actual lexeme character

};

vector<tokenType> lexer(string words);
int getFsmCol(char currentChar);
string getLexemeName(int lexeme);


//struct tokenType {
//	string token; // token name for the lexeme
//	int lexeme;
//	string lexemeName; // this prints out the actual lexeme character
//
//};
//
////FSM table
//int stateFSM[13][24] = {
//	/*state 0*/  {1, 3, 2 ,5, 6, 0, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 8, 8, 8, 8, 8, 8, 8},
//	/*state 1*/   {1, 11, 12, 2, 2, 2, 9, 2, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
//	/*Fstate 2*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*state 3*/   {10, 3, 10, 4, 10, 4, 10, 4, 10, 10, 10, 10, 10, 10, 10, 4, 4, 4, 4, 4, 4, 4, 4, 4},
//	/*Fstate 4*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*state 5*/   {10, 3, 10, 10, 10, 8, 10, 10, 10, 10, 10, 10, 10, 10 ,10 ,10 ,10, 10, 10 ,10 ,10 ,10, 10, 10},
//	/*state 6*/   {6, 6, 6, 6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
//	/*Fstate 7*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*Fstate 8*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*Fstate 9*/  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*Fstate 10*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//	/*state 11*/  {11, 11, 12, 10, 10, 12, 10, 8, 12, 10, 10, 10, 10, 12, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10},
//	/*Fstate 12*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0} };
