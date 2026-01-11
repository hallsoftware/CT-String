/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iostream>
#include <vector>

// Compile-time file metadata
template <ct_str::FixedString Path>
struct FileEntry
{
	static constexpr auto path	   = ct_str::StringStore<Path>();
	static constexpr auto filename = ct_str::filename<Path>::c_str();
	static constexpr auto stem	   = ct_str::stem<Path>::c_str();
	static constexpr auto ext	   = ct_str::extension<Path>::c_str();
	static constexpr auto hash	   = ct_str::crc32<Path>();

	static constexpr bool has_extension = ct_str::has_extension<Path>();

	// Generate a unique ID for this file
	static constexpr uint32_t id() { return hash; }

	// Check file type by extension
	static constexpr bool is_header() { return ct_str::ends_with<Path, ".hpp">() || ct_str::ends_with<Path, ".h">(); }

	static constexpr bool is_source()
	{
		return ct_str::ends_with<Path, ".cpp">() || ct_str::ends_with<Path, ".c">() || ct_str::ends_with<Path, ".cc">();
	}

	static constexpr bool is_python() { return ct_str::ends_with<Path, ".py">(); }

	static void print_info()
	{
		std::cout << "File: " << path.view() << "\n";
		std::cout << "  Filename:  " << filename << "\n";
		std::cout << "  Stem:      " << stem << "\n";
		std::cout << "  Extension: " << ext << "\n";
		std::cout << "  ID:        0x" << std::hex << id() << std::dec << "\n";
		std::cout << "  Type:      ";
		if (is_header())
			std::cout << "Header";
		else if (is_source())
			std::cout << "Source";
		else if (is_python())
			std::cout << "Python";
		else
			std::cout << "Other";
		std::cout << "\n";
	}
};

// File registry - compile-time list of files
template <typename... Files>
struct FileRegistry
{
	static constexpr std::size_t count = sizeof...(Files);

	static void print_all()
	{
		std::cout << "File Registry (" << count << " files):\n";
		(Files::print_info(), ...);
	}

	static void print_headers()
	{
		std::cout << "Header Files:\n";
		((Files::is_header() ? (void)Files::print_info() : (void)0), ...);
	}

	static void print_sources()
	{
		std::cout << "Source Files:\n";
		((Files::is_source() ? (void)Files::print_info() : (void)0), ...);
	}
};

// Project files
using File1 = FileEntry<"include/ct_str.hpp">;
using File2 = FileEntry<"src/main.cpp">;
using File3 = FileEntry<"src/utils.cpp">;
using File4 = FileEntry<"include/details/fixed_string.hpp">;
using File5 = FileEntry<"scripts/build.py">;
using File6 = FileEntry<"README.md">;
using File7 = FileEntry<"CMakeLists.txt">;

using ProjectFiles = FileRegistry<File1, File2, File3, File4, File5, File6, File7>;

int main()
{
	std::cout << "========================================\n";
	std::cout << "  INTERMEDIATE FILE REGISTRY EXAMPLE\n";
	std::cout << "========================================\n\n";

	// Print all files
	std::cout << "=== All Files ===\n";
	ProjectFiles::print_all();
	std::cout << "\n";

	// Print headers only
	std::cout << "=== Header Files Only ===\n";
	ProjectFiles::print_headers();
	std::cout << "\n";

	// Print sources only
	std::cout << "=== Source Files Only ===\n";
	ProjectFiles::print_sources();
	std::cout << "\n";

	// Individual file info
	std::cout << "=== Individual File Info ===\n";
	std::cout << "Main source file:\n";
	File2::print_info();
	std::cout << "\n";

	// File comparison
	std::cout << "=== File Comparison ===\n";
	std::cout << "File1 ID: 0x" << std::hex << File1::id() << std::dec << "\n";
	std::cout << "File2 ID: 0x" << std::hex << File2::id() << std::dec << "\n";
	std::cout << "IDs are unique: " << (File1::id() != File2::id() ? "true" : "false") << "\n\n";

	// Extension checking
	std::cout << "=== Extension Checking ===\n";
	std::cout << "ct_str.hpp is header:      " << (File1::is_header() ? "true" : "false") << "\n";
	std::cout << "main.cpp is source:        " << (File2::is_source() ? "true" : "false") << "\n";
	std::cout << "build.py is python:        " << (File5::is_python() ? "true" : "false") << "\n";
	std::cout << "README.md has extension:   " << (File6::has_extension ? "true" : "false") << "\n";
	std::cout << "CMakeLists.txt has ext:    " << (File7::has_extension ? "true" : "false") << "\n\n";

	// Practical use case: dependency tracking
	std::cout << "=== Dependency Tracking Example ===\n";
	std::cout << "If '" << File1::filename << "' changes (ID: 0x" << std::hex << File1::id() << std::dec
			  << "), rebuild:\n";
	std::cout << "  - " << File2::filename << "\n";
	std::cout << "  - " << File3::filename << "\n\n";

	// Compile-time verification
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(File1::is_header());
	static_assert(File2::is_source());
	static_assert(File5::is_python());
	static_assert(ProjectFiles::count == 7);
	static_assert(File1::id() != File2::id());
	std::cout << "All static assertions passed!\n\n";

	return 0;
}