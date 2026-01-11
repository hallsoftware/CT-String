/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iostream>

int main()
{
	using namespace ct_str;

	std::cout << "========================================\n";
	std::cout << "   BASIC PATH MANIPULATION EXAMPLES\n";
	std::cout << "========================================\n\n";

	// === FILENAME EXTRACTION ===
	std::cout << "=== Filename Extraction ===\n";
	std::cout << "filename('/usr/local/bin/program'):         " << filename<"/usr/local/bin/program">::c_str() << "\n";
	std::cout << "filename('C:\\\\Windows\\\\System32\\\\cmd.exe'): "
			  << filename<"C:\\Windows\\System32\\cmd.exe">::c_str() << "\n";
	std::cout << "filename('document.pdf'):                   " << filename<"document.pdf">::c_str() << "\n";
	std::cout << "filename('/path/to/'):                      " << filename<"/path/to/">::c_str() << "\n\n";

	// === STEM AND EXTENSION ===
	std::cout << "=== Stem and Extension ===\n";
	std::cout << "stem('program.exe'):       " << stem<"program.exe">::c_str() << "\n";
	std::cout << "extension('program.exe'):  " << extension<"program.exe">::c_str() << "\n";
	std::cout << "stem('/path/to/file.txt'): " << stem<"/path/to/file.txt">::c_str() << "\n";
	std::cout << "extension('file.txt'):     " << extension<"file.txt">::c_str() << "\n";
	std::cout << "stem('archive.tar.gz'):    " << stem<"archive.tar.gz">::c_str() << "\n";
	std::cout << "extension('archive.tar.gz'): " << extension<"archive.tar.gz">::c_str() << "\n";
	std::cout << "stem('Makefile'):          " << stem<"Makefile">::c_str() << "\n";
	std::cout << "extension('Makefile'):     '" << extension<"Makefile">::c_str() << "'\n\n";

	// === PATH MANIPULATION ===
	std::cout << "=== Path Manipulation ===\n";
	std::cout << "remove_filename('/usr/bin/program'):          " << remove_filename<"/usr/bin/program">::c_str()
			  << "\n";
	std::cout << "replace_filename('/usr/bin/old', 'new'):      " << replace_filename<"/usr/bin/old", "new">::c_str()
			  << "\n";
	std::cout << "replace_extension('file.txt', '.cpp'):        " << replace_extension<"file.txt", ".cpp">::c_str()
			  << "\n";
	std::cout << "replace_extension('file.txt', 'hpp'):         " << replace_extension<"file.txt", "hpp">::c_str()
			  << "\n";
	std::cout << "replace_extension('Makefile', '.bak'):        " << replace_extension<"Makefile", ".bak">::c_str()
			  << "\n";
	std::cout << "replace_extension('file.txt', ''):            " << replace_extension<"file.txt", "">::c_str()
			  << "\n\n";

	// === PATH QUERIES ===
	std::cout << "=== Path Queries ===\n";
	std::cout << "has_root_path('/usr/bin'):           " << (has_root_path<"/usr/bin">() ? "true" : "false") << "\n";
	std::cout << "has_root_path('relative/path'):      " << (has_root_path<"relative/path">() ? "true" : "false")
			  << "\n";
	std::cout << "has_root_name('C:\\\\Windows'):         " << (has_root_name<"C:\\Windows">() ? "true" : "false")
			  << "\n";
	std::cout << "has_root_directory('/usr'):          " << (has_root_directory<"/usr">() ? "true" : "false") << "\n";
	std::cout << "has_root_directory('C:relative'):    " << (has_root_directory<"C:relative">() ? "true" : "false")
			  << "\n";
	std::cout << "has_relative_path('/usr/bin'):       " << (has_relative_path<"/usr/bin">() ? "true" : "false")
			  << "\n";
	std::cout << "has_parent_path('/usr/bin/program'): " << (has_parent_path<"/usr/bin/program">() ? "true" : "false")
			  << "\n";
	std::cout << "has_filename('/usr/bin/program'):    " << (has_filename<"/usr/bin/program">() ? "true" : "false")
			  << "\n";
	std::cout << "has_stem('program.exe'):             " << (has_stem<"program.exe">() ? "true" : "false") << "\n";
	std::cout << "has_extension('program.exe'):        " << (has_extension<"program.exe">() ? "true" : "false") << "\n";
	std::cout << "has_extension('Makefile'):           " << (has_extension<"Makefile">() ? "true" : "false") << "\n\n";

	// === PATH TYPE QUERIES ===
	std::cout << "=== Path Type Queries ===\n";
	std::cout << "is_absolute('/usr/bin'):        " << (is_absolute<"/usr/bin">() ? "true" : "false") << "\n";
	std::cout << "is_absolute('C:\\\\Windows'):      " << (is_absolute<"C:\\Windows">() ? "true" : "false") << "\n";
	std::cout << "is_absolute('relative/path'):   " << (is_absolute<"relative/path">() ? "true" : "false") << "\n";
	std::cout << "is_relative('relative/path'):   " << (is_relative<"relative/path">() ? "true" : "false") << "\n";
	std::cout << "is_relative('/usr/bin'):        " << (is_relative<"/usr/bin">() ? "true" : "false") << "\n\n";

	// === BUILDING PATHS ===
	std::cout << "=== Building Paths ===\n";
	std::cout << "Build path: " << append<"/usr", "/", "local", "/", "bin">::c_str() << "\n";
	std::cout << "Add extension: " << replace_extension<"Makefile", ".bak">::c_str() << "\n";
	std::cout << "Change file: " << replace_filename<"/path/to/old.txt", "new.cpp">::c_str() << "\n\n";

	// === COMPILE-TIME VERIFICATION ===
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(filename<"/usr/bin/program">::storage.data[0] == 'p');
	static_assert(has_extension<"file.txt">());
	static_assert(!has_extension<"Makefile">());
	static_assert(is_absolute<"/usr/bin">());
	static_assert(is_relative<"relative/path">());
	static_assert(has_root_name<"C:\\Windows">());
	std::cout << "All static assertions passed!\n\n";

	return 0;
}