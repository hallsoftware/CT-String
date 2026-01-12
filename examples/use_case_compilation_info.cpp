/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iostream>

// Compilation unit info
#define COMP_UNIT ::ct_str::stem<__FILE__>::c_str()		 // compilation unit
#define COMP_FILE ::ct_str::filename<__FILE__>::c_str()	 // filename without path

// Compilation date info
#define COMP_YEAR  ::ct_str::substr<__DATE__, 7, 4>::c_str()  // could be used for producing copyright years
#define COMP_MONTH ::ct_str::substr<__DATE__, 0, 3>::c_str()
#define COMP_DAY   ::ct_str::trim<::ct_str::substr<__DATE__, 4, 2>::fwd>::c_str()

// Compilation time info
#define COMP_HOUR ::ct_str::substr<__TIME__, 0, 2>::c_str()
#define COMP_MIN  ::ct_str::substr<__TIME__, 3, 2>::c_str()
#define COMP_SEC  ::ct_str::substr<__TIME__, 6, 2>::c_str()

int main()
{
	std::cout << "========================================\n";
	std::cout << "     COMPILATION MACROS EXAMPLE\n";
	std::cout << "========================================\n\n";

	std::cout << "Compilation Unit:    " << COMP_UNIT << "\n";
	std::cout << "Source Filename:     " << COMP_FILE << "\n";
	std::cout << "Source File w/ path: " << __FILE__ << "\n\n";

	std::cout << "Date Components:\n";
	std::cout << "  Year:  " << COMP_YEAR << "\n";
	std::cout << "  Month: " << COMP_MONTH << "\n";
	std::cout << "  Day:   " << COMP_DAY << "\n";
	std::cout << "  Full:  " << __DATE__ << "\n\n";

	std::cout << "Time Components:\n";
	std::cout << "  Hour:  " << COMP_HOUR << "\n";
	std::cout << "  Min:   " << COMP_MIN << "\n";
	std::cout << "  Sec:   " << COMP_SEC << "\n";
	std::cout << "  Full:  " << __TIME__ << "\n";

	return 0;
}
