/*
 * Matan Gazit
 * CS 4280
 * 03/08/21
 * fsa.cpp
 */

#include "fsa.h"
#include <cctype>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std; // for readability

//PROTOTYPES
int** initialize_table();

//GLOBALS
int** Table = initialize_table();

//IMPLEMENTATION

// Creates a new table
int** initialize_table() {
	int** Table = 0; // double pointer for double the dimensions
	Table = new int*[FINAL+ 1]; // allocate necessary amount of memory for 'Table'

	for (int i = 0; i < FINAL + 1; i++) {
			Table[i] = new int[INVALID + 1];
	}	
	
	// for loop is designed to fill in the FSA table with default values before manually adding the unique states
	for (int curr_state = 0; curr_state < FINAL; curr_state++) {
		for (int curr_label = 0; curr_label < INVALID + 1; curr_label++) {
			if (curr_state < EOF_STATE && curr_state > POSSIBLE_INTEGER) {
				if (curr_label == WS) {
					Table[curr_state][curr_label] = FINAL;
				}
				else if (curr_label == EOF_LABEL) {
					Table[curr_state][curr_label] = EOF_STATE;
				}
				else if (curr_label == INVALID) {
					Table[curr_state][curr_label] = FSA_ERROR_INVALID_CHAR;
				}
				else {
					Table[curr_state][curr_label] = FSA_ERROR_INVALID_CHAR;
				}
			}
		}
	}

	//UNIQUE CASES
	//May need to edit these as errors arise throughout this project
	
	//INITIAL state
	Table[INITIAL][WS] = INITIAL;
	Table[INITIAL][LETTER] = POSSIBLE_IDENTIFIER;
	Table[INITIAL][UNDERS] = POSSIBLE_IDENTIFIER;
	Table[INITIAL][INTEGER] = POSSIBLE_INTEGER;
	Table[INITIAL][COMMENT] = POSSIBLE_COMMENT;
	Table[INITIAL][EQUALS] = POSSIBLE_EQUALS;
	Table[INITIAL][L_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[INITIAL][R_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[INITIAL][COLON] = POSSIBLE_COLON;
	Table[INITIAL][ADD] = POSSIBLE_ADD;
	Table[INITIAL][SUBT] = POSSIBLE_SUBT;
	Table[INITIAL][MULT] = POSSIBLE_MULT;
	Table[INITIAL][DIV] = POSSIBLE_DIV;
	Table[INITIAL][MOD] = POSSIBLE_MOD;
	Table[INITIAL][DOT] = POSSIBLE_DOT;
	Table[INITIAL][L_PAREN] = POSSIBLE_L_PAREN;
	Table[INITIAL][R_PAREN] = POSSIBLE_R_PAREN;
	Table[INITIAL][COMMA] = POSSIBLE_COMMA;
	Table[INITIAL][L_CURLY] = POSSIBLE_L_CURLY;
	Table[INITIAL][R_CURLY] = POSSIBLE_R_CURLY;
	Table[INITIAL][SEMI] = POSSIBLE_SEMI_COLON;
	Table[INITIAL][L_SQUARE] = POSSIBLE_L_SQUARE;
	Table[INITIAL][R_SQUARE] = POSSIBLE_R_SQUARE;
	Table[INITIAL][EOF_LABEL] = EOF_STATE;
	Table[INITIAL][INVALID] = FSA_ERROR_INVALID_CHAR;

	Table[POSSIBLE_IDENTIFIER][WS] = FINAL;
	Table[POSSIBLE_IDENTIFIER][LETTER] =  POSSIBLE_IDENTIFIER;
	Table[POSSIBLE_IDENTIFIER][INTEGER] = POSSIBLE_IDENTIFIER;
	Table[POSSIBLE_IDENTIFIER][UNDERS] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][COMMENT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][EQUALS] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][L_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][R_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][COLON] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][ADD] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][SUBT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][MULT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][DIV] = FSA_ERROR_INVALID_CHAR;;
	Table[POSSIBLE_IDENTIFIER][MOD] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][DOT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][L_PAREN] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][R_PAREN] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][COMMA] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][L_CURLY] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][R_CURLY] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][SEMI] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][L_SQUARE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][R_SQUARE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_IDENTIFIER][EOF_LABEL] = EOF_STATE;
	Table[POSSIBLE_IDENTIFIER][INVALID] = FSA_ERROR_INVALID_CHAR;

	Table[POSSIBLE_INTEGER][WS] = FINAL;
	Table[POSSIBLE_INTEGER][LETTER] =  FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][INTEGER] = POSSIBLE_INTEGER;
	Table[POSSIBLE_INTEGER][UNDERS] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][COMMENT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][EQUALS] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][L_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][R_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][COLON] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][ADD] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][SUBT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][MULT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][DIV] = FSA_ERROR_INVALID_CHAR;;
	Table[POSSIBLE_INTEGER][MOD] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][DOT] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][L_PAREN] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][R_PAREN] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][COMMA] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][L_CURLY] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][R_CURLY] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][SEMI] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][L_SQUARE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][R_SQUARE] = FSA_ERROR_INVALID_CHAR;
	Table[POSSIBLE_INTEGER][EOF_LABEL] = EOF_STATE;
	Table[POSSIBLE_INTEGER][INVALID] = FSA_ERROR_INVALID_CHAR;

	Table[POSSIBLE_EQUALS][WS] = FINAL; // probably already part of the above algorithm, but felt right to put here
	Table[POSSIBLE_EQUALS][EQUALS] = POSSIBLE_EQUALITY;
	Table[POSSIBLE_EQUALS][L_ANGLE] = POSSIBLE_LESS_THAN;
	Table[POSSIBLE_EQUALS][R_ANGLE] = POSSIBLE_GREATER_THAN;

	Table[POSSIBLE_COLON][EQUALS] = POSSIBLE_ASSIGNMENT;

	Table[POSSIBLE_COMMENT][COMMENT] = FINAL; // scanner will ignore all future states until the next final comment

	Table[EOF_STATE][WS] = FINAL;
	Table[EOF_STATE][LETTER] = FINAL;
	Table[EOF_STATE][COMMENT] = FINAL;
	Table[EOF_STATE][INTEGER] = FINAL;
	Table[EOF_STATE][UNDERS] = FINAL;
	Table[EOF_STATE][COMMENT] = FINAL;
	Table[EOF_STATE][EQUALS] = FINAL;
	Table[EOF_STATE][L_ANGLE] = FINAL;
	Table[EOF_STATE][R_ANGLE] = FINAL;
	Table[EOF_STATE][COLON] = FINAL;
	Table[EOF_STATE][ADD] = FINAL;
	Table[EOF_STATE][SUBT] = FINAL;
	Table[EOF_STATE][MULT] = FINAL;
	Table[EOF_STATE][DIV] = FINAL;
	Table[EOF_STATE][MOD] = FINAL;
	Table[EOF_STATE][DOT] = FINAL;
	Table[EOF_STATE][L_PAREN] = FINAL;
	Table[EOF_STATE][R_PAREN] = FINAL;
	Table[EOF_STATE][COMMA] = FINAL;
	Table[EOF_STATE][L_CURLY] = FINAL;
	Table[EOF_STATE][R_CURLY] = FINAL;
	Table[EOF_STATE][SEMI] = FINAL;
	Table[EOF_STATE][L_SQUARE] = FINAL;
	Table[EOF_STATE][R_SQUARE] = FINAL;
	Table[EOF_STATE][EOF_LABEL] = FINAL;
	Table[EOF_STATE][INVALID] = FINAL;

	Table[FINAL][WS] = INITIAL;
	Table[FINAL][LETTER] = POSSIBLE_IDENTIFIER;
	Table[FINAL][INTEGER] = POSSIBLE_INTEGER;
	Table[FINAL][UNDERS] = POSSIBLE_IDENTIFIER;
	Table[FINAL][COMMENT] = POSSIBLE_COMMENT;
	Table[FINAL][EQUALS] = POSSIBLE_EQUALS;
	Table[FINAL][L_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[FINAL][R_ANGLE] = FSA_ERROR_INVALID_CHAR;
	Table[FINAL][COLON] = POSSIBLE_COLON;
	Table[FINAL][ADD] = POSSIBLE_ADD;
	Table[FINAL][SUBT] = POSSIBLE_SUBT;
	Table[FINAL][MULT] = POSSIBLE_MULT;
	Table[FINAL][DIV] = POSSIBLE_DIV;
	Table[FINAL][MOD] = POSSIBLE_MOD;
	Table[FINAL][DOT] = POSSIBLE_DOT;
	Table[FINAL][L_PAREN] = POSSIBLE_L_PAREN;
	Table[FINAL][R_PAREN] = POSSIBLE_R_PAREN;
	Table[FINAL][COMMA] = POSSIBLE_COMMA;
	Table[FINAL][L_CURLY] = POSSIBLE_L_CURLY;
	Table[FINAL][R_CURLY] = POSSIBLE_R_CURLY;
	Table[FINAL][SEMI] = POSSIBLE_SEMI_COLON;
	Table[FINAL][L_SQUARE] = POSSIBLE_L_SQUARE;
	Table[FINAL][R_SQUARE] = POSSIBLE_R_SQUARE;
	Table[FINAL][EOF_LABEL] = EOF_STATE;
	Table[FINAL][INVALID] = FSA_ERROR_INVALID_CHAR;

	return Table;
}

label get_label(char c) {

	//Base symbol cases
	if (isspace(c)) {
		return WS;
	}
	else if (isalpha(c)) {
		return LETTER;
	}
	else if (isdigit(c)) {
		return INTEGER;
	}
	//Unique symbol cases
	else if (c == '=') {
		return EQUALS;
	}
	else if (c == '_') {
		return UNDERS; 
	}
	else if (c == '<') {
		return L_ANGLE;
	}
	else if (c == '>') {
		return R_ANGLE;
	}
	else if (c == ':') {
		return COLON;
	}
	else if (c == '+') {
		return ADD;
	}
	else if (c == '-') {
		return SUBT;
	}
	else if (c == '*') {
		return MULT;
	}
	else if (c == '/') {
		return DIV;
	}
	else if (c == '$') {
		return COMMENT;
	}
	else if (c == '%') {
		return MOD;
	}
	else if (c == '.') {
		return DOT;
	}
	else if (c == '(') {
		return L_PAREN;
	}
	else if (c == ')') {
		return R_PAREN;
	}
	else if (c == ',') {
		return COMMA;
	}
	else if (c == '{') {
		return L_CURLY;
	}
	else if (c == '}') {
		return R_CURLY;
	}
	else if (c == ';') {
		return SEMI;
	}
	else if (c == '[') {
		return L_SQUARE;
	}
	else if (c == ']') {
		return R_SQUARE;
	}
	else if (c == char_traits<char>::eof()) {
		return EOF_LABEL; 
	}
	else {
		return INVALID;
	}
}

// this does not work properly, I found out
// taken directly from reference in readme
void print_table() {
	// this... is not actually in the right order...
	cout << setw(6) << " "
		<< setw(6) << "WS"
		<< setw(6) << "L"
		<< setw(6) << "INT"
		<< setw(6) << "_"
		<< setw(6) << "$"
		<< setw(6) << "="
		<< setw(6) << "<"
		<< setw(6) << ">"
		<< setw(6) << ":"
		<< setw(6) << "+"
		<< setw(6) << "-"
		<< setw(6) << "*"
		<< setw(6) << "/"
		<< setw(6) << "%"
		<< setw(6) << "."
		<< setw(6) << "("
		<< setw(6) << ")"
		<< setw(6) << ","
		<< setw(6) << "{"
		<< setw(6) << "}"
		<< setw(6) << ";"
		<< setw(6) << "["
		<< setw(6) << "]"
		<< setw(6) << "EOF"
		<< setw(6) << "INV"
		<< endl;

		for (int i = 0; i < FINAL + 1; i++) {
		 	cout << setw(6) << i;
		 	for (int j = 0; j < INVALID + 1; j++) {
		 		int curr_state = Table[i][j];

		 		if(curr_state == FINAL) {
		 			cout << setw(6) << 'F';
		 		}
		 		else if(curr_state == -1) {
		 			cout << setw(6) << "ERR";
		 		}
		 		else {
		 			cout << setw(6) << curr_state;
		 		}
		 	} 
			cout << endl;
		}
		cout << endl;
		cout << "ERR: Invalid character input detected by the scanner in the FSA" << endl;
		cout << "F: Final State" << endl;
		cout << endl;		
}
