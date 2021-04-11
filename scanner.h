/*
 * Matan Gazit
 * CS 4280
 * 03/08/21
 * scanner.h
 */

#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <string>
#include <fstream>

using namespace std; // for readability

// reads next token from input file stream
token scanner(ifstream&);

#endif
