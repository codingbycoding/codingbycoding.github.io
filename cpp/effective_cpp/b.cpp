#include "b.h"

#include <iostream>


void B::print() const {
	std::cout << __func__ << std::endl;
}

B theB;
