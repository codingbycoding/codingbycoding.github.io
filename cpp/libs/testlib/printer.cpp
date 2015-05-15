//g++ -Wall -Werror -c -fPIC printer.cpp -o printer.o
//g++ -Wall -Werror -shared printer.o -o libprinter.so


#include <iostream>

#include "printer.h"


Printer::Printer() {
	
}

void Printer::print() {
	std::cout << "void Printer::print()" << std::endl;
}
