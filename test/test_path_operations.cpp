/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("Path Operations")
{
	TEST_CASE("filename")
	{
		// Unix paths
		using File1 = ct_str::filename<"/usr/local/bin/program">;
		static_assert(File1::view() == "program");
		CHECK(File1::view() == "program");

		using File2 = ct_str::filename<"/path/to/file.txt">;
		static_assert(File2::view() == "file.txt");

		// Windows paths
		using File3 = ct_str::filename<"C:\\Windows\\System32\\cmd.exe">;
		static_assert(File3::view() == "cmd.exe");

		// No path
		using File4 = ct_str::filename<"document.pdf">;
		static_assert(File4::view() == "document.pdf");

		// Trailing slash
		using File5 = ct_str::filename<"/path/to/">;
		static_assert(File5::view() == "");

		// Root only
		using File6 = ct_str::filename<"/">;
		static_assert(File6::view() == "");

		// Mixed separators
		using File7 = ct_str::filename<"/usr/local\\bin/program">;
		static_assert(File7::view() == "program");
	}

	TEST_CASE("stem")
	{
		// Basic stem
		using Stem1 = ct_str::stem<"file.txt">;
		static_assert(Stem1::view() == "file");
		CHECK(Stem1::view() == "file");

		using Stem2 = ct_str::stem<"/path/to/document.pdf">;
		static_assert(Stem2::view() == "document");

		// No extension
		using Stem3 = ct_str::stem<"Makefile">;
		static_assert(Stem3::view() == "Makefile");

		// Multiple dots
		using Stem4 = ct_str::stem<"archive.tar.gz">;
		static_assert(Stem4::view() == "archive.tar");

		// Dot at beginning
		using Stem5 = ct_str::stem<".gitignore">;
		static_assert(Stem5::view() == ".gitignore");

		// Hidden file with extension
		using Stem6 = ct_str::stem<".config.ini">;
		static_assert(Stem6::view() == ".config");

		// Path with stem
		using Stem7 = ct_str::stem<"/usr/bin/program.exe">;
		static_assert(Stem7::view() == "program");
	}

	TEST_CASE("extension")
	{
		// Basic extension
		using Ext1 = ct_str::extension<"file.txt">;
		static_assert(Ext1::view() == ".txt");
		CHECK(Ext1::view() == ".txt");

		using Ext2 = ct_str::extension<"document.pdf">;
		static_assert(Ext2::view() == ".pdf");

		// No extension
		using Ext3 = ct_str::extension<"Makefile">;
		static_assert(Ext3::view() == "");

		// Multiple dots
		using Ext4 = ct_str::extension<"archive.tar.gz">;
		static_assert(Ext4::view() == ".gz");

		// Path with extension
		using Ext5 = ct_str::extension<"/usr/bin/program.exe">;
		static_assert(Ext5::view() == ".exe");

		// Hidden file
		using Ext6 = ct_str::extension<".gitignore">;
		static_assert(Ext6::view() == "");

		// Hidden file with extension
		using Ext7 = ct_str::extension<".config.ini">;
		static_assert(Ext7::view() == ".ini");
	}

	TEST_CASE("remove_filename")
	{
		// Basic removal
		using Remove1 = ct_str::remove_filename<"/usr/bin/program">;
		static_assert(Remove1::view() == "/usr/bin/");
		CHECK(Remove1::view() == "/usr/bin/");

		using Remove2 = ct_str::remove_filename<"C:\\Users\\file.txt">;
		static_assert(Remove2::view() == "C:\\Users\\");

		// No path
		using Remove3 = ct_str::remove_filename<"file.txt">;
		static_assert(Remove3::view() == "");

		// Root only
		using Remove4 = ct_str::remove_filename<"/file">;
		static_assert(Remove4::view() == "/");

		// Already ends with separator
		using Remove5 = ct_str::remove_filename<"/path/to/">;
		static_assert(Remove5::view() == "/path/to/");
	}

	TEST_CASE("replace_filename")
	{
		// Basic replacement
		using Replace1 = ct_str::replace_filename<"/usr/bin/old", "new">;
		static_assert(Replace1::view() == "/usr/bin/new");
		CHECK(Replace1::view() == "/usr/bin/new");

		using Replace2 = ct_str::replace_filename<"C:\\Users\\old.txt", "new.txt">;
		static_assert(Replace2::view() == "C:\\Users\\new.txt");

		// No original filename
		using Replace3 = ct_str::replace_filename<"/path/to/", "file.txt">;
		static_assert(Replace3::view() == "/path/to/file.txt");

		// No path
		using Replace4 = ct_str::replace_filename<"old.txt", "new.txt">;
		static_assert(Replace4::view() == "new.txt");

		// Empty replacement
		using Replace5 = ct_str::replace_filename<"/usr/bin/program", "">;
		static_assert(Replace5::view() == "/usr/bin/");
	}

	TEST_CASE("replace_extension")
	{
		// Basic replacement
		using ReplaceExt1 = ct_str::replace_extension<"file.txt", ".cpp">;
		static_assert(ReplaceExt1::view() == "file.cpp");
		CHECK(ReplaceExt1::view() == "file.cpp");

		// Without leading dot
		using ReplaceExt2 = ct_str::replace_extension<"file.txt", "hpp">;
		static_assert(ReplaceExt2::view() == "file.hpp");

		// Add extension
		using ReplaceExt3 = ct_str::replace_extension<"Makefile", ".bak">;
		static_assert(ReplaceExt3::view() == "Makefile.bak");

		// Remove extension
		using ReplaceExt4 = ct_str::replace_extension<"file.txt", "">;
		static_assert(ReplaceExt4::view() == "file");

		// With path
		using ReplaceExt5 = ct_str::replace_extension<"/path/to/file.txt", ".md">;
		static_assert(ReplaceExt5::view() == "/path/to/file.md");

		// Multiple dots
		using ReplaceExt6 = ct_str::replace_extension<"archive.tar.gz", ".zip">;
		static_assert(ReplaceExt6::view() == "archive.tar.zip");
	}

	TEST_CASE("has_root_path")
	{
		// Unix absolute paths
		static_assert(ct_str::has_root_path<"/usr/bin">());
		CHECK(ct_str::has_root_path<"/usr/bin">());

		// Windows drive letters
		static_assert(ct_str::has_root_path<"C:\\Windows">());
		static_assert(ct_str::has_root_path<"D:relative">());

		// Relative paths
		static_assert(!ct_str::has_root_path<"relative/path">());
		static_assert(!ct_str::has_root_path<"file.txt">());
		CHECK_FALSE(ct_str::has_root_path<"relative/path">());
	}

	TEST_CASE("has_root_name")
	{
		// Windows drive letters
		static_assert(ct_str::has_root_name<"C:\\Windows">());
		static_assert(ct_str::has_root_name<"D:file.txt">());
		CHECK(ct_str::has_root_name<"C:\\Windows">());

		// Unix paths (no root name)
		static_assert(!ct_str::has_root_name<"/usr/bin">());
		static_assert(!ct_str::has_root_name<"relative/path">());
		CHECK_FALSE(ct_str::has_root_name<"/usr/bin">());
	}

	TEST_CASE("has_root_directory")
	{
		// Unix absolute paths
		static_assert(ct_str::has_root_directory<"/usr/bin">());
		static_assert(ct_str::has_root_directory<"/">());
		CHECK(ct_str::has_root_directory<"/usr/bin">());

		// Windows absolute paths
		static_assert(ct_str::has_root_directory<"C:\\Windows">());

		// Windows relative with drive
		static_assert(!ct_str::has_root_directory<"C:relative">());

		// Relative paths
		static_assert(!ct_str::has_root_directory<"relative/path">());
		CHECK_FALSE(ct_str::has_root_directory<"relative/path">());
	}

	TEST_CASE("has_relative_path")
	{
		// Paths with components after root
		static_assert(ct_str::has_relative_path<"/usr/bin">());
		static_assert(ct_str::has_relative_path<"C:\\Windows\\System32">());
		CHECK(ct_str::has_relative_path<"/usr/bin">());

		// Pure relative paths
		static_assert(ct_str::has_relative_path<"relative/path">());

		// Root only
		static_assert(!ct_str::has_relative_path<"/">());
		static_assert(!ct_str::has_relative_path<"C:\\">());
	}

	TEST_CASE("has_parent_path")
	{
		// Paths with parent
		static_assert(ct_str::has_parent_path<"/usr/bin/program">());
		static_assert(ct_str::has_parent_path<"dir/file.txt">());
		CHECK(ct_str::has_parent_path<"/usr/bin/program">());

		// No parent
		static_assert(!ct_str::has_parent_path<"file.txt">());
		static_assert(ct_str::has_parent_path<"/">());
		CHECK_FALSE(ct_str::has_parent_path<"file.txt">());
	}

	TEST_CASE("has_filename")
	{
		// Paths with filename
		static_assert(ct_str::has_filename<"/usr/bin/program">());
		static_assert(ct_str::has_filename<"file.txt">());
		CHECK(ct_str::has_filename<"/usr/bin/program">());

		// No filename
		static_assert(!ct_str::has_filename<"/usr/bin/">());
		static_assert(!ct_str::has_filename<"/">());
		CHECK_FALSE(ct_str::has_filename<"/usr/bin/">());
	}

	TEST_CASE("has_stem")
	{
		// Paths with stem
		static_assert(ct_str::has_stem<"file.txt">());
		static_assert(ct_str::has_stem<"Makefile">());
		static_assert(ct_str::has_stem<"/path/to/file.txt">());
		CHECK(ct_str::has_stem<"file.txt">());

		// Empty path
		static_assert(!ct_str::has_stem<"">());

		// Directory only
		static_assert(!ct_str::has_stem<"/path/to/">());
	}

	TEST_CASE("has_extension")
	{
		// Paths with extension
		static_assert(ct_str::has_extension<"file.txt">());
		static_assert(ct_str::has_extension<"archive.tar.gz">());
		static_assert(ct_str::has_extension<"/path/to/file.cpp">());
		CHECK(ct_str::has_extension<"file.txt">());

		// No extension
		static_assert(!ct_str::has_extension<"Makefile">());
		static_assert(!ct_str::has_extension<".gitignore">());
		static_assert(!ct_str::has_extension<"/path/to/dir/">());
		CHECK_FALSE(ct_str::has_extension<"Makefile">());
	}

	TEST_CASE("is_absolute")
	{
		// Unix absolute paths
		static_assert(ct_str::is_absolute<"/usr/bin">());
		static_assert(ct_str::is_absolute<"/">());
		CHECK(ct_str::is_absolute<"/usr/bin">());

		// Windows absolute paths
		static_assert(ct_str::is_absolute<"C:\\Windows">());
		static_assert(ct_str::is_absolute<"D:\\">());

		// Relative paths
		static_assert(!ct_str::is_absolute<"relative/path">());
		static_assert(!ct_str::is_absolute<"file.txt">());
		static_assert(!ct_str::is_absolute<"C:relative">());
		CHECK_FALSE(ct_str::is_absolute<"relative/path">());
	}

	TEST_CASE("is_relative")
	{
		// Relative paths
		static_assert(ct_str::is_relative<"relative/path">());
		static_assert(ct_str::is_relative<"file.txt">());
		static_assert(ct_str::is_relative<"../parent">());
		CHECK(ct_str::is_relative<"relative/path">());

		// Absolute paths
		static_assert(!ct_str::is_relative<"/usr/bin">());
		static_assert(!ct_str::is_relative<"C:\\Windows">());
		CHECK_FALSE(ct_str::is_relative<"/usr/bin">());
	}
}