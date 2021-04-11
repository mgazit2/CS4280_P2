/*
 * Matan Gazit
 * CS 4280
 * 03/08/21
 * main.cpp
 */

#include "fsa.h"
#include "scanner.h"
#include "testScanner.h"
#include "token.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std; // for readability

int main (int argc, char** argv) {

	//print_table();
	
	string file_name;	

	if (argc == 1) {

		perror("Main : Error : Input file [datafile] required!");
		exit(1);
	
	}
	else if (argc > 2) {

		perror("Main : Error : Too many command line arguments!");
		exit(1);
	
	}
	else {

		file_name = string(argv[1]);	
	
	}

	ifstream data_file;
	data_file.open(file_name.c_str(), fstream::in);

	// check if file opened w/ no issues
	if (!data_file.good() || !data_file.is_open()) {

		perror("Main : Error : Could not open [datafile]!");
		exit(1);
	
	}
	if (data_file.peek() == ifstream::traits_type::eof()) {

		perror("Main : Error : Input file is empty!");
		exit(1);

	}
	
	print_table();
	//scanner(data_file);
	test_scanner(data_file);
	return 0;
}
