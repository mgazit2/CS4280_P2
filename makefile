parse: main.o fsa.o scanner.o testScanner.o parser.o
	g++ main.o fsa.o scanner.o parser.o  testScanner.o -o parser

main.o: main.cpp testScanner.h token.h fsa.h scanner.h parser.h
	g++ -c main.cpp

test_scanner.o: testScanner.cpp testScanner.h scanner.h token.h fsa.h
	g++ -c testScanner.cpp

parser.o: parser.cpp parser.h node.h token.h scanner.h
	g++ -c parser.cpp

scanner.o: scanner.cpp scanner.h token.h fsa.h 
	g++ -c scanner.cpp

fsa_table.o: fsa.cpp fsa.h
	g++ -c fsa.cpp

clean:
	rm -rf parser *.o
