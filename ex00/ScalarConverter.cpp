
#include "ScalarConverter.hpp"

//CANONICAL
ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}
 
//AUXILIARY
static bool isSpecialCase(const std::string& str) {
	if (str == "-inff" || str == "+inff" || str == "nanf" || str == "-inf" || str == "+inf" || str == "nan")
		return true;
	return false;
}

static bool isChar(const std::string& str) {
	if (str.length() == 1 && std::isprint(str[0]) && !std::isdigit(str[0]))
		return true;
	return false;
}

static bool isInt(const std::string& str) {
	if (str.empty())
		return false;
	size_t start = 0;
	if (str[start] == '-' || str[start] == '+')
		start++;
	if (start >= str.length())
		return false;
	for (size_t i = start; i < str.length(); i++) {
		if (!std::isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

static bool isDouble(const std::string& str) {
	if (str.empty())
		return false;
	if (isSpecialCase(str))
		return true;
	size_t start = 0;
	bool hasDecimal = false;
	bool hasDigit = false;
	if (str[start] == '-' || str[start] == '+')
		start++;
	for (size_t i = start; i < str.length(); i++) {
		if (str[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		} else if (isdigit(str[i])) {
			hasDigit = true;
		} else {
			return false;
		}
	}
	return hasDigit && hasDecimal;
}

static bool isFloat(const std::string& str) {
	if (str.empty())
		return false;
	if (str[str.length() - 1] != 'f')
		return false;
	std::string withoutF = str.substr(0, str.length() - 1);
	if (isSpecialCase(str))
		return true;
	bool hasDecimal = false;
	bool hasDigit = false;
	size_t start = 0;
	if (withoutF[start] == '-' || withoutF[start] == '+')
		start++;
	for (size_t i = start; i < withoutF.length(); i++) {
		if (withoutF[i] == '.') {
			if (hasDecimal)
				return false;
			hasDecimal = true;
		} else if (isdigit(withoutF[i])) {
			hasDigit = true;
		} else {
			return false;
		}
	}
	return hasDigit && hasDecimal;
}

static Type detectType(const std::string& str) {
	if (isSpecialCase(str))
		return SPECIAL;
	if (isChar(str))
		return CHAR;
	if (isInt(str))
		return INT;
	if (isFloat(str))
		return FLOAT;
	if (isDouble(str))
		return DOUBLE;
	return ERROR;
}

static void convertSpecial(const std::string& str) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (str == "-inff" || str == "-inf") {
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	} else if (str == "+inff" || str == "+inf") {
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	} else if (str == "nanf" || str == "nan") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
}

static void convertChar(const char c) {
	std::cout << "char: '" << c << "'"  << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
	std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
}

static void convertInt(const std::string& str) {
	long long value;
	std::istringstream iss(str);
	iss >> value;
	//Char conversion
	if (value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()) {
		std::cout << "char: impossible" << std::endl;
	} else if (value < 32 || value > 126) {
		std::cout << "char: Non displayable" << std::endl;
	} else {
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}
	//Int conversion
	if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	}
	//Float conversion
	float f = static_cast<float>(value);
	std::cout << "float: " << f;
	if (f == static_cast<int>(f) && f < 1e6 && f > -1e6)
		std::cout << ".0";
	std::cout << std::endl;
	//Double conversion
	double d = static_cast<double>(value);
	std::cout << "double: " << d;
	if (d == static_cast<int>(d) && d < 1e6 && d > -1e6)
		std::cout << ".0";
	std::cout << std::endl;
}

static void convertFloat(const std::string& str) {
	std::string withoutF = str.substr(0, str.length() -1);
	float value = std::atof(withoutF.c_str());
	//Char conversion
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || value > std::numeric_limits<char>::max()) {
		std::cout << "char: impossible" << std::endl;
	} else if (value < 32 || value > 126) {
		std::cout << "char: Non displayable" << std::endl;
	} else {
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}
	//Int conversion
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max()) {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	}
	//Float conversion
	std::cout << "float: " << value;
	if (value == static_cast<int>(value) && value < 1e6 && value > -1e6) {
		std::cout << ".0";
	}
	std::cout << "f" << std::endl;
	//Double conversion
	std::cout << "double: " << static_cast<double>(value);
	if (value == static_cast<int>(value) && value < 1e6 && value > -1e6) {
		std::cout << ".0";
	}
	std::cout << std::endl;
}

static void convertDouble(const std::string& str) {
	double value = std::atof(str.c_str());
	//Char conversion
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<char>::min() || std::numeric_limits<char>::max()) {
		std::cout << "char: impossible" << std::endl;		
	} else if (value < 32 || value > 126) {
		std::cout << "char: Non displayable" << std::endl;
	} else {
		std::cout << "char: '" << static_cast<char>(value) << "'" << std::endl;
	}
	//Int conversion
	if (std::isnan(value) || std::isinf(value) || value < std::numeric_limits<int>::min() || std::numeric_limits<int>::max()) {
		std::cout << "int: impossible" << std::endl;
	} else {
		std::cout << "int: " << static_cast<int>(value) << std::endl;
	}
	//Float conversion
	std::cout << "float: " << value;
	if (value == static_cast<int>(value) && value < 1e6 && value > -1e6) {
		std::cout << ".0";
	}
	std::cout << "f" << std::endl;
	//Double conversion
	std::cout << "double: " << value;
	if (value == static_cast<int>(value) && value < 1e6 && value > -1e6) {
		std::cout << ".0";
	}
	std::cout << std::endl;
}

static void errorInput(void) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

void ScalarConverter::convert(const std::string& str) {
	if (str.empty()) {
		std::cout << "Error: empty string" << std::endl;
		return;
	}
	Type type = detectType(str);
	switch (type) {
		case SPECIAL:
			convertSpecial(str);
			break;
		case CHAR:
			convertChar(str[0]);
			break;
		case INT:
			convertInt(str);
			break;
		case FLOAT:
			convertFloat(str);
			break;
		case DOUBLE:
			convertDouble(str);
			break;
		default:
			std::cout << "Error: invalid input." << std::endl;
			errorInput();
			break;
	}
}