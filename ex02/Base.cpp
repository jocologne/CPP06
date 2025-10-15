
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

Base* generate(void) {
	std::srand(static_cast<unsigned int>(std::time(0)));
	int randomValue = std::rand() % 3;

	switch (randomValue) {
		case 0:
			std::cout << "Generated A" << std::endl;
			return new A();
		case 1:
			std::cout << "Generated B" << std::endl;
			return new B();
		case 2:
			std::cout << "Generated C" << std::endl;
			return new C();
		default:
			return NULL;
	}
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p)) {
		std::cout << "Identified as A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "Identified as B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "Identified as C" << std::endl;
	} else {
		std::cout << "Unknown type" << std::endl;
	}
}

#include <iostream>
#include <exception>

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "Identified as A" << std::endl;
		return;
	} catch (...) {}

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "Identified as B" << std::endl;
		return;
	} catch (...) {}

	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "Identified as C" << std::endl;
		return;
	} catch (...) {}

	std::cout << "Unknown type" << std::endl;
}