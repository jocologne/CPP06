
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <iostream>

int main() {
	Base* basePtr = generate();
	if (basePtr) {
		std::cout << "pointer: ";
		identify(basePtr);
		std::cout << "reference: ";
		identify(*basePtr);
		delete basePtr;
	} else {
		std::cerr << "Failed to generate a Base object." << std::endl;
	}
	return 0;
}