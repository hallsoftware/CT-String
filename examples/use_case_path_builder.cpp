/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iostream>

// Compile-time path builder
template <ct_str::FixedString... Parts>
struct PathBuilder
{
	using path = ct_str::append<Parts...>;

	static constexpr auto c_str() { return path::c_str(); }

	static constexpr auto value() { return path::value; }

	// Get filename
	using filename_type = ct_str::filename<path::fwd>;

	// Get directory
	using directory_type = ct_str::remove_filename<path::fwd>;

	// Get stem and extension
	using stem_type		 = ct_str::stem<path::fwd>;
	using extension_type = ct_str::extension<path::fwd>;

	// Query functions
	static constexpr bool is_absolute() { return ct_str::is_absolute<path::fwd>(); }

	static constexpr bool has_extension() { return ct_str::has_extension<path::fwd>(); }
};

// Project structure paths
using ProjectRoot = ct_str::StringStore<ct_str::FixedString("/home/user/project")>;
using SrcDir	  = PathBuilder<ProjectRoot::fwd, "/src">;
using IncludeDir  = PathBuilder<ProjectRoot::fwd, "/include">;
using BuildDir	  = PathBuilder<ProjectRoot::fwd, "/build">;

int main()
{
	std::cout << "========================================\n";
	std::cout << "   INTERMEDIATE PATH BUILDER EXAMPLE\n";
	std::cout << "========================================\n\n";

	// Basic path building
	std::cout << "=== Basic Path Building ===\n";
	std::cout << "Project root:  " << ProjectRoot::c_str() << "\n";
	std::cout << "Source dir:    " << SrcDir::c_str() << "\n";
	std::cout << "Include dir:   " << IncludeDir::c_str() << "\n";
	std::cout << "Build dir:     " << BuildDir::c_str() << "\n\n";

	// Building file paths
	std::cout << "=== Building File Paths ===\n";
	using HeaderFile = PathBuilder<IncludeDir::path::fwd, "/ct_str.hpp">;
	using SourceFile = PathBuilder<SrcDir::path::fwd, "/main.cpp">;
	using ObjectFile = PathBuilder<BuildDir::path::fwd, "/main.o">;

	std::cout << "Header file:   " << HeaderFile::c_str() << "\n";
	std::cout << "Source file:   " << SourceFile::c_str() << "\n";
	std::cout << "Object file:   " << ObjectFile::c_str() << "\n\n";

	// Path decomposition
	std::cout << "=== Path Decomposition ===\n";
	std::cout << "Source file:   " << SourceFile::c_str() << "\n";
	std::cout << "  Directory:   " << SourceFile::directory_type::c_str() << "\n";
	std::cout << "  Filename:    " << SourceFile::filename_type::c_str() << "\n";
	std::cout << "  Stem:        " << SourceFile::stem_type::c_str() << "\n";
	std::cout << "  Extension:   " << SourceFile::extension_type::c_str() << "\n";
	std::cout << "  Is absolute: " << (SourceFile::is_absolute() ? "true" : "false") << "\n";
	std::cout << "  Has ext:     " << (SourceFile::has_extension() ? "true" : "false") << "\n\n";

	// Path manipulation
	std::cout << "=== Path Manipulation ===\n";
	using OriginalPath = PathBuilder<"/path/to/file.txt">;
	using ChangedExt   = ct_str::replace_extension<OriginalPath::path::fwd, ".md">;
	using ChangedFile  = ct_str::replace_filename<OriginalPath::path::fwd, "newfile.cpp">;
	using RemovedFile  = ct_str::remove_filename<OriginalPath::path::fwd>;

	std::cout << "Original:         " << OriginalPath::c_str() << "\n";
	std::cout << "Changed ext:      " << ChangedExt::c_str() << "\n";
	std::cout << "Changed file:     " << ChangedFile::c_str() << "\n";
	std::cout << "Removed filename: " << RemovedFile::c_str() << "\n\n";

	// Windows paths
	std::cout << "=== Windows Path Support ===\n";
	using WinRoot	= ct_str::StringStore<ct_str::FixedString("C:\\Users\\Public")>;
	using WinDocs	= PathBuilder<WinRoot::fwd, "\\Documents">;
	using WinFile	= PathBuilder<WinDocs::path::fwd, "\\report.docx">;
	using WinBackup = ct_str::replace_extension<WinFile::path::fwd, ".bak">;

	std::cout << "Windows root: " << WinRoot::c_str() << "\n";
	std::cout << "Documents:    " << WinDocs::c_str() << "\n";
	std::cout << "File:         " << WinFile::c_str() << "\n";
	std::cout << "Backup:       " << WinBackup::c_str() << "\n";
	std::cout << "Has root:     " << (ct_str::has_root_name<WinFile::path::fwd>() ? "true" : "false") << "\n\n";

	// Relative paths
	std::cout << "=== Relative Paths ===\n";
	using RelPath = PathBuilder<"docs/", "api/", "reference.md">;
	std::cout << "Relative path: " << RelPath::c_str() << "\n";
	std::cout << "Is absolute:   " << (RelPath::is_absolute() ? "true" : "false") << "\n";
	std::cout << "Is relative:   " << (ct_str::is_relative<RelPath::path::fwd>() ? "true" : "false") << "\n\n";

	// Practical example: Build system paths
	std::cout << "=== Build System Example ===\n";
	using CompilerPath = ct_str::StringStore<ct_str::FixedString("/usr/bin/g++")>;
	using OutputPath   = PathBuilder<BuildDir::path::fwd, "/output.exe">;
	using LogPath	   = ct_str::replace_extension<OutputPath::path::fwd, ".log">;

	std::cout << "Compiler:      " << CompilerPath::c_str() << "\n";
	std::cout << "Output binary: " << OutputPath::c_str() << "\n";
	std::cout << "Build log:     " << LogPath::c_str() << "\n\n";

	// Compile-time verification
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(SourceFile::has_extension());
	static_assert(ct_str::has_extension<"/path/file.txt">());
	static_assert(!ct_str::has_extension<"/path/Makefile">());
	static_assert(ct_str::is_absolute<"/usr/bin">());
	static_assert(ct_str::is_relative<"relative/path">());
	std::cout << "All static assertions passed!\n\n";

	return 0;
}