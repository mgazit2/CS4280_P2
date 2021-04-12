/* Matan Gazit
 * CS 4280
 * 04/12/21
 * Assignment 2
 *
 * printTree.cpp
 *
 * main driver for parse tree traversal process
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "token.h"
#include "printTree.h"

using namespace std; // for readability

/* PROTOTYPES */
string print_node(Node*, int);
string tkstring(token);

void preorder(Node* root, int depth)
{
	if (root == NULL) return; 
	else
	{
		cout << print_node(root, depth) << endl;
		preorder(root -> child0, depth + 1);
		preorder(root -> child1, depth + 1);
		preorder(root -> child2, depth + 1);
		preorder(root -> child3, depth + 1);
		
	}	
}

string print_node(Node* root, int depth)
{
	ostringstream oss;
	for (int i = 0; i < depth; i++)
	{
		oss << " ";
	}
	oss << root -> text;
	for (vector<token>::iterator i = (root -> token_vec).begin(); i != (root -> token_vec).end(); i++)
	{
		oss << " ";
		oss << tkstring(*i);
	}
	return oss.str();
}

string tkstring(token tk)
{
	ostringstream oss;
	if (tk.token_instance != "")
	{
		oss << "TOKEN: " << tk.id << ", ";
		oss << "INSTANCE: " << tk.token_instance << ", ";
		oss << "LINE: " << tk.line;
	}
	return oss.str();
}
