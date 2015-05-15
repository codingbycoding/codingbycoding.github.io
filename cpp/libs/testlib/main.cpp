//g++ -Wall -Werror -L. -lprinter main.cpp -o main.linux

#include "printer.h"


int main() {

	Printer printer;
	printer.print();
	
	return 0;
}
