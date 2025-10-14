
#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>

enum Type {SPECIAL, CHAR, INT, FLOAT, DOUBLE, ERROR};

class ScalarConverter {
private:
	ScalarConverter();
	ScalarConverter(const ScalarConverter& other);
	ScalarConverter& operator=(const ScalarConverter& other);
public:
	~ScalarConverter();
	static void convert(const std::string& literal);
};

#endif