/*
 * Matan Gazit
 * CS4280
 * 03/08/21
 * fsa.h
 */

#ifndef FSA_H
#define FSA_H

const int FSA_ERROR_INVALID_CHAR = -1;

// Used to guess where the automaton is headed in the compilation
enum pos_state {
	INITIAL,
	POSSIBLE_IDENTIFIER,
	POSSIBLE_INTEGER,
	POSSIBLE_COMMENT, // comment tag at beginning and end of line, $$ 
	POSSIBLE_EQUALS,
	POSSIBLE_GREATER_THAN,
	POSSIBLE_LESS_THAN,
	POSSIBLE_EQUALITY,
	POSSIBLE_COLON,
	POSSIBLE_ADD,
	POSSIBLE_SUBT,
	POSSIBLE_MULT,
	POSSIBLE_DIV,
	POSSIBLE_ASSIGNMENT,
	POSSIBLE_MOD,
	POSSIBLE_DOT,
	POSSIBLE_L_PAREN,
	POSSIBLE_R_PAREN,
	POSSIBLE_COMMA,
	POSSIBLE_L_CURLY,
	POSSIBLE_R_CURLY,
	POSSIBLE_SEMI_COLON,
	POSSIBLE_L_SQUARE,
	POSSIBLE_R_SQUARE, 
  	EOF_STATE,
	FINAL	
};

// Labels for all the possible characters the compiler may encounter when deciphering code
// Any character cannot be matched up here, in one way or another, is considered an invalid character
// 	and an error will be returned to the user notifying them of this
enum label {
	WS, // /t /n ' '
	LETTER, // a-z A-Z
	INTEGER, // 0-9
	COMMENT, // $
	EQUALS, // =
	L_ANGLE, // <
	R_ANGLE, // >
	COLON, // :
	ADD, // +
	SUBT, // -
	MULT, // *
	DIV, // /
	MOD, // %
	DOT, // .
	L_PAREN, // (
	R_PAREN, // )
	COMMA, // ,
	L_CURLY, // {
	R_CURLY, // }
	SEMI,// ;
	L_SQUARE, // [
	R_SQUARE, // ]
	UNDERS, // _
	EOF_LABEL,
	INVALID
};

extern int ** Table; // returns number of possible values

void print_table(); // prints table for debugging purposes

label get_label(char c); // fetches a label for scanner character

#endif
