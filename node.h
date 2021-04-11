/* Matan Gazit
 * CS 4280
 * Assignment 2
 * 04/12/21
 *
 * node.h
 *
 * header file including all necessary information for the node struct
 */

#ifndef NODE_H
#define NODE_H

#include "token.h"
#include <string>
#include <vector>

typedef struct Node
{
	string text;
	vector<token> token_vec;
	Node* child0;
	Node* child1;
	Node* child2;
	Node* child3;
} Node;

#endif
