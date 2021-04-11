/*
 * Matan Gazit
 * CS 4280
 * 03/08/21
 * scanner.cpp
 */

#include "scanner.h"
#include "fsa.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iostream>

using namespace std; // for readability

//PROTOTYPES
token gen_token(int state, string word, int line);
token_ID check_for_kw(string word);

//GLOBALS
const int kw_num = 14; // number of keywords our language uses
const string kw_constructor[] = { 
	"begin", "end",
	"loop", "whole",
	"void", "exit",
	"getter", "outter",
	"main", "if",
	"then", "assign",
	"data", "proc"
};
const vector<string> key_words(kw_constructor, kw_num + kw_constructor); // easier to look through a cpp vector than a simple array
									 // vectors have a number of different unique method implmenetations
									 // found in <algorithm>
								
//SCANNER IMPLEMENTATION
token scanner(ifstream& file) {

	static int _curr_line = 1; // variable tracks our current line number in the file
	static char _c = file.get();
	label curr_label = get_label(_c);
	static char _last_char = -1;
	string curr_word; // stores the current word being scanned
	int curr_state;
	int next_state;

	curr_state = INITIAL;
	
	while (curr_state != EOF_STATE) {
		
		if (_last_char == '\n') _curr_line++;

		next_state = Table[curr_state][curr_label];
		
		// comment loop check
		if (curr_state == POSSIBLE_COMMENT && next_state == FINAL) {
		
			// ready variables for comment loop entry
			curr_state = next_state;
			_last_char = _c;
			_c = file.get();
			curr_label = get_label(_c);
			next_state = Table[curr_state][curr_label];

			// comment loop continues till another 'FINAL' 'POSSIBLE_COMMENT' state is found
			while (curr_state != POSSIBLE_COMMENT && next_state != FINAL) {
				
				if (_last_char == '\n') _curr_line++; // line tracking continues while in comment loop
				
				next_state = Table[curr_state][curr_label];

				if (next_state == FSA_ERROR_INVALID_CHAR) next_state = INITIAL;
				
				curr_state = next_state;
				_last_char = _c;
				_c = file.get();
				curr_label = get_label(_c);
				//next_state = Table[curr_state][curr_label];
				
			} // end comment loop

			// update variables accordingly before continuing scanner loop
			curr_state = INITIAL;
			curr_word = "";
			continue; // leave this block and continue the loop 			

		} // end comment if block

		// check for possible error in the next state
		// exit before state is updated w/ an error
		if (next_state == FSA_ERROR_INVALID_CHAR) {
		
			ostringstream oss; // from cstd: objects of this class use a string buffer that contains a sequence of characters.		
			oss << "Scanner : Error: FSA_ERROR_INVALID_CHAR at line " << _curr_line << ": "
				<< _c << " is not a valid input while in state " << curr_state << endl
				<< "Revise input and run scanner again..." << endl;
			perror(oss.str().c_str());
			exit(1);

		}
		else if (next_state == FINAL) {
			// generate token
			token tk;
			tk = gen_token(curr_state, curr_word, _curr_line);
			cout << "Token ID: " << tk.id << endl;
			cout << "Token Instance: " << tk.token_instance << endl;
			cout << "Token Line: " << tk.line << endl;
			return gen_token(curr_state, curr_word, _curr_line);
			curr_word = ""; // reset word variable

		}
		else if (next_state == EOF_STATE) {
			
			if (curr_word != "") {

				// if curr_word is not an empty string
				// return a token of whatever this last word is
				// loop will end once condition is checked next iteration
				token tk;
                      	  	tk = gen_token(curr_state, curr_word, _curr_line);
                        	cout << "Token ID: " << tk.id << endl;
                        	cout << "Token Instance: " << tk.token_instance << endl;
                        	cout << "Token Line: " << tk.line << endl;
				return gen_token(curr_state, curr_word, _curr_line);
				curr_word = ""; // reset word variable
			
			}

		}
		else {

			if (curr_label != WS) {
		
				curr_word += _c; // add to the current word for possible future token generation

			}

		}

		curr_state = next_state;
		_last_char = _c;
		_c = file.get();
		curr_label = get_label(_c);

	} // end scanner while loop	

	// once loop exits, return the eof_tk 
	token tk;
        tk = gen_token(curr_state, "", _curr_line);
        cout << "Token ID: " << tk.id << endl;
        cout << "Token Instance: " << tk.token_instance << endl;
        cout << "Token Line: " << tk.line << endl;
	
	// returns end of file token
	return gen_token(curr_state, "", _curr_line);
	
}

token gen_token(int state, string word, int line) {

	token t;
	switch (state) {
		case POSSIBLE_IDENTIFIER:
			// check for keyword here
			t.id = check_for_kw(word);
			if (t.id == ident_tk) {
				t.token_instance = word;
			}
			break;
		case POSSIBLE_INTEGER:
			t.id = num_tk;
			t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_COMMENT:
			t.id = comment_tk;
			t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_EQUALS:
			t.id = equals_tk;
			t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_GREATER_THAN:
			t.id = greater_than_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_LESS_THAN:
			t.id = less_than_tk;
			t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_ASSIGNMENT:
			t.id = assignment_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_ADD:
			t.id = add_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_SUBT:
			t.id = subt_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_MULT:
			t.id = mult_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_DIV:
			t.id = div_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_MOD:
			t.id = mod_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_COLON:
			t.id = colon_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_SEMI_COLON:
			t.id = semi_colon_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_DOT:
			t.id = dot_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_COMMA:
			t.id = comma_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_L_PAREN:
			t.id = l_paren_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_R_PAREN:
			t.id = r_paren_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_L_CURLY:
			t.id = l_curly_tk;
                        t.token_instance = token_names[t.id];
                        break;
		case POSSIBLE_R_CURLY:
			t.id = r_curly_tk;
                        t.token_instance = token_names[t.id];           
                        break;
		case POSSIBLE_L_SQUARE:
			t.id = l_square_tk;
                        t.token_instance = token_names[t.id];       
                        break;
		case POSSIBLE_R_SQUARE:
			t.id = r_square_tk;
                        t.token_instance = token_names[t.id];           
                        break;
		case POSSIBLE_EQUALITY:
			t.id = equality_tk;
			t.token_instance = token_names[t.id];
			break;
		case EOF_STATE:
			t.id = eof_tk;
			t.token_instance = token_names[t.id];
                        break;
		default:
			ostringstream oss;
			oss << "Scanner : Error: Could not generate a token from invalid state.." << endl
                                << "Revise input and run scanner again..." << endl;
                        perror(oss.str().c_str());			
			exit(1);
	}	
	
	t.line = line;	
	return t;

}

// helper method to gen_token()
// purpose of this method is to check whether input string is reserved
// if input string is not matched up to a token_names[] string, return 'ident_tk'
// done using the cpp const_iterator and find() (from <algorithm>)
token_ID check_for_kw(string word) {

	vector<string>::const_iterator i = find(key_words.begin(), key_words.end(), word); // look for word
		
	// if the iterator reached the end (pointing to tail of vector not last element)
	// return 'ident_tk' for token naming
	if (i == key_words.end()) return ident_tk;
	else {
		int kw_index = i - key_words.begin();
		switch(kw_index) {
			case 0:
				return begin_tk;
				break;
			case 1:
				return end_tk;
                                break;
			case 2:
				return whole_tk;
                                break;
			case 3:
				return loop_tk;
                                break;
                        case 4:
				return void_tk;
                                break;
                        case 5:
				return getter_tk;
                                break;
			case 6:
				return outter_tk;
                                break;
                        case 7:
				return exit_tk;
                                break;
                        case 8:
				return main_tk;
                                break;
			case 9:
				return if_tk;
                                break;
                        case 10:
				return then_tk;
                                break;
                        case 11:
				return assign_tk;
                                break;
			case 12:
				return data_tk;
                                break;
                        case 13:
				return proc_tk;
       	                        break;
			default:
				ostringstream oss;
				oss << "Scanner : Error : Could not determine token_ID of " << word << endl
					<< "Revise input and run scanner again..." << endl;
				perror(oss.str().c_str());
				exit(1);

		}			
	}
}
