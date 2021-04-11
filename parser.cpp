/* Matan Gazit
 * CS 4280
 * Assignment 2
 * 04/12/21
 *
 * parser.cpp
 *
 * main code repository for all necessary parser methods used by the compiler to parse a document
 * parser returns error if ANY language error is found in the input document
 */

#include <string>
#include <sstream>
#include <cstdlib>
#include "parser.h"
#include "scanner.h"

/* PROTOTYPES */
void error_hndlr(string);
Node* start_parse(ifstream&);
Node* vars(ifstream&);
Node* block(ifstream&);
Node* gen_node(string);
Node* stats(ifstream&);
Node* in(ifstream&);
Node* out(ifstream&);
Node* assign(ifstream&);
Node* loop(ifstream&);
Node* go_to(ifstream&);
Node* iF(ifstream&);
Node* expr(ifstream&);
Node* RO(ifstream&);
Node* stat(ifstream&);
Node* mStat(ifstream&);
Node* n(ifstream&);
Node* a(ifstream&);
Node* m(ifstream&);
Node* r(ifstream&);


using namespace std; // for readability

/* GLOBALS */
static token tk;

Node* parse(ifstream& file)
{
	Node* parse_tree;
	//tk = scanner(file);
	parse_tree = start_parse(file);
	if (tk.id != eof_tk) error_hndlr("PARSE FAILED\n");
	return parse_tree;
}

void error_hndlr(string error_txt)
{
	ostringstream oss;
	oss << "Error at line " << tk.line << ": " << error_txt << " Found " << tk.token_instance;
	perror(oss.str().c_str());
	exit(1);
}

Node* start_parse(ifstream& file)
{
	Node* new_node = gen_node("PROGRAM START");
	tk = scanner(file);
	new_node -> child0 = vars(file);
	new_node -> child1 = block(file);
	return new_node;
}

Node* vars(ifstream& file)
{
	Node* new_node = gen_node("VARS");
	if (tk.id != num_tk) return new_node;
	else
	{
		tk = scanner(file);
		if (tk.id == ident_tk)
		{
			(new_node -> token_vec).push_back(tk);
			tk = scanner(file);
			new_node -> child0 = vars(file);
			return new_node;
		}
		else
		{
			error_hndlr("EXPECTED IDENTIFIER\n");
		}
	}
}

Node* block(ifstream& file)
{
	Node* new_node = gen_node("BLOCK");
	if (tk.id == begin_tk)
	{
		tk = scanner(file);
		new_node -> child0 = vars(file);
		new_node -> child1 = stats(file);
		if (tk.id == end_tk)
		{
			tk = scanner(file);
			return new_node;
		}
		else error_hndlr("EXPECTED END\n");
		
	}
	else error_hndlr("EXPECTED BEGIN\n");
}

Node* stats(ifstream& file)
{
	Node* new_node = gen_node("STATS");
	new_node -> child0 = stat(file);
	new_node -> child1 = mStat(file);
	return new_node;
}

Node* stat(ifstream& file)
{
	Node* new_node = gen_node("STAT");
	if (tk.id == getter_tk)
	{
		new_node -> child0 = in(file);
		return new_node;
	}
	else if (tk.id == outter_tk)
	{
		new_node -> child0 = out(file);
		return new_node;
	}
	else if	(tk.id == begin_tk)
	{
		new_node -> child0 = block(file);
		return new_node;
	}
	else if(tk.id == if_tk)
	{
		new_node -> child0 = iF(file);
		return new_node;
	}
	else if(tk.id == loop_tk)
	{
		new_node -> child0 = loop(file);
		return new_node;
	}
	else if(tk.id == ident_tk)
	{
		new_node -> child0 = assign(file);
		return new_node;
	}
	else if(tk.id == proc_tk)
	{
		new_node -> child0 = go_to(file);
		return new_node;
	}
	else error_hndlr("EXPECTED STAT\n");
}

Node* mStat(ifstream& file)
{
	Node* new_node = gen_node("mSTAT");
	if (tk.id != getter_tk
		&& tk.id != outter_tk
		&& tk.id != begin_tk
		&& tk.id != if_tk
		&& tk.id != loop_tk
		&& tk.id != ident_tk
		&& tk.id != proc_tk)
	{
		return new_node;
	}
	else
	{
		new_node -> child0 = stat(file);
		new_node -> child1 = mStat(file);
		return new_node;
	}
}

Node* in(ifstream& file)
{
	Node* new_node = gen_node("IN");
	if (tk.id == getter_tk)
	{
		tk = scanner(file);
		if (tk.id == ident_tk)
		{
			(new_node -> token_vec).push_back(tk);
			tk = scanner(file);
			if (tk.id == semi_colon_tk)
			{
				tk = scanner(file);
				return new_node;
			}
			else error_hndlr("EXPECTED SEMICOLON\n");
		}
		else error_hndlr("EXPECTED IDENTIFIER\n");
	}
	else error_hndlr("EXPECTED GETTER\n");
}

Node* out(ifstream& file)
{
	Node* new_node = gen_node("OUT");
	if (tk.id = outter_tk)
	{
		tk = scanner(file);
		new_node -> child0 = expr(file);
		return new_node;
	}
	else error_hndlr("EXPECTED OUTTER");
}

Node* iF(ifstream& file)
{
	Node* new_node = gen_node("IF");
	if (tk.id == if_tk)
	{
		tk = scanner(file);
		if (tk.id == l_square_tk)
		{
			tk = scanner(file);
			new_node -> child0 = expr(file);
			new_node -> child1 = RO(file);
			new_node -> child2 = expr(file);
			tk = scanner(file);
			if (tk.id == r_square_tk)
			{
				tk = scanner(file);
				if (tk.id == then_tk)
				{
					tk = scanner(file);
					new_node -> child3 = stat(file);
					return new_node;	
				}
				else error_hndlr("EXPECTED THEN\n");
			}
			else error_hndlr("EXPECTED R SQUARE\n");	
		}
		else error_hndlr("EXPECTED L SQUARE\n");
	}
	else error_hndlr("EXPECTED IF\n");
}

Node* loop(ifstream& file)
{
	Node* new_node = gen_node("LOOP");
	if (tk.id == loop_tk)
	{
		tk = scanner(file);
		if (tk.id == l_square_tk)
		{
			tk = scanner(file);
			new_node -> child0 = expr(file);
			new_node -> child1 = RO(file);
			new_node -> child2 = expr(file);
			tk = scanner(file);
			if (tk.id == r_square_tk)
			{
				tk = scanner(file);
				new_node -> child3 = stat(file);
				return new_node;
			}
			else error_hndlr("EXPECTED R SQUARE\n");
		}
		else error_hndlr("EXPECTED L SQUARE\n");
	}
	else error_hndlr("EXPECTED LOOP\n");
}

Node* assign(ifstream& file)
{
	Node* new_node = gen_node("ASSIGN\n");
	if (tk.id == ident_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		if (tk.id == assignment_tk)
		{
			tk = scanner(file);
			new_node -> child0 = expr(file);
			if (tk.id == semi_colon_tk)
			{
				tk = scanner(file);
				return new_node;
			}
			else error_hndlr("EXPECTED SEMICOLON\n");
		}
		else error_hndlr("EXPECTED ASSIGNMENT\n");
	}
	else error_hndlr("EXPECTED IDENT\n");
}

Node* go_to(ifstream& file)
{

}

Node* expr(ifstream& file)
{
	Node* new_node = gen_node("EXPR");
	new_node -> child0 = n(file);
	if (tk.id == subt_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		new_node -> child1 = expr(file);
	}
	return new_node;
}

Node* n(ifstream& file)
{
	Node* new_node = gen_node("N");
	new_node -> child0 = a(file);
	if (tk.id == mult_tk || tk.id == div_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		new_node -> child1 = n(file);
	}
	return new_node;
}

Node* a(ifstream& file)
{
	Node* new_node = gen_node("A");
	new_node -> child0 = m(file);
	if (tk.id == add_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		new_node -> child1 = a(file);
	}
	return new_node;
}

Node* m(ifstream& file)
{
	Node* new_node = gen_node("M");
	if (tk.id == mult_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		new_node -> child0 = m(file);
	}
	else
	{
		new_node -> child0 = r(file);
	}
	
}

Node* r(ifstream& file)
{
	Node* new_node = gen_node("R");
	if (tk.id == l_paren_tk)
	{
		tk = scanner(file);
		new_node -> child0 = expr(file);
		if (tk.id == r_paren_tk)
		{
			tk = scanner(file);
			return new_node;
		}
		else error_hndlr("EXPECTED R PAREN");	
	}
	else if (tk.id == ident_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		return new_node;
	}
	else if (tk.id == num_tk)
	{
		(new_node -> token_vec).push_back(tk);
		tk = scanner(file);
		return new_node;
	}
	else error_hndlr("EXPECTED L PAREN, IDENT, OR NUM\n");
}

Node* RO(ifstream& file)
{

}

Node* gen_node(string txt)
{
	Node* new_node = new Node();
	new_node -> text = txt;
	new_node -> child0 = NULL;
	new_node -> child1 = NULL;
	new_node -> child2 = NULL;
	new_node -> child3 = NULL;
	return new_node;
}
