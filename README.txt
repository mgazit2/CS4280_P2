Matan Gazit
CS 4280
03/08/21
README.txt

! USING OPTION 3 (FSA TABLE) !

Lexical Definitions

	Case sensitive
	Each scanner error should display "SCANNER ERROR: " followed by details including the line number if counted
	Alphabet
		all English letters (upper and lower), digits, plus the extra characters as seen below, plus WS
		No other characters allowed and they should generate errors
	Identifiers
	begin with a lower case letter or an underscore ( _ )
		continue with any number of letters (uppercase or lowercase) or digits, 8 significant total
		you may assume no identifier is longer than 8 characters (in testing)
	Keywords (reserved, suggested individual tokens)
		begin end loop whole void exit getter outter main if then assign data proc 
	Operators and delimiters group (all single character except ==  => := and =<)
		=  =>  =< ==  : :=  +  -  *  /   %  . (  ) , { } ; [ ]
	Integers
		any sequence of decimal digits, no sign, no decimal point, up to 8 significant
		you may assume no number longer than 8 characters (in testing)
	Comments start with and $$ end with $$.

Make:
	To compile this project, simply type 'make' into your command line while in the project directory
	To clean up the directory, simply type 'make clean' into your command line while in the project directory

Issues:

	I misread the rubric and do not have test scanner file being called from main...

	There is little time between token generation, but the program doe iterate through everything one by one as opposed to saving all the tokens to some sort of list and printing
	
	Encountered an issue where the tokens were becoming as long the file, fixed this by reseting the 'curr_word' variable at certain points
	Encountered an issue where comment characters were trailing off in the next word after exiting a comment block in the input file, fixed by resetting word before exiting comment block

	It is important to note that FINAL and INVALID should always be last in their respective enum lists, as it allows for simple traversal through all possible states

	Comment loop implementation is messy, but functions accordingly in *most cases. I say most, because I'm not good at testing code.

	print_table() does not work as I realized too late that it relied on everything being written to the order of the states as they were added to 'fsa.h', decided not to fix as it was
		not an integral part of the code...

References:

	Used the following repositories to help in building the general framework of the scanner. Implementation of the nuances of our language were done by me building off what was in this project:
		https://github.com/rocksalad/CS4280Compilers/tree/master/P1
		https://github.com/TGrossman90/Compiler-Project-CS4280/blob/master/scanner.cpp
		https://github.com/tlunmp/CS4280-P1/blob/master/scanner.c
		https://github.com/jeffcaljr/CS4280_Project_4/find/master

	For understanding oss:
		http://www.cplusplus.com/reference/sstream/ostringstream/

	The <algorithm> documentation for the find() implementation in the code:
		http://www.cplusplus.com/reference/algorithm/
		http://www.cplusplus.com/reference/algorithm/find/

	const_iterator documentation:
		https://en.cppreference.com/w/cpp/container/vector/begin
