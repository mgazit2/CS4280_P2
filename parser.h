/* Matan Gazit
 * CS 4280
 * Assignment 2
 * 04/12/21
 *
 * parser.h
 *
 * header file for the parser component of the 4280 compiler
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include "token.h"
#include "node.h"

using namespace std; // for readability

Node* parse(ifstream& file);

#endif
