/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("FixedString")
{
	TEST_CASE("Construction and basic properties")
	{
		// Default construction
		constexpr ct_str::FixedString<char, 1> empty("");
		static_assert(empty.size() == 0);
		static_assert(empty.data[0] == '\0');

		// From string literal
		constexpr ct_str::FixedString str = "hello";
		static_assert(str.size() == 5);
		static_assert(str.data[0] == 'h');
		static_assert(str.data[4] == 'o');
		static_assert(str.data[5] == '\0');

		// Multi-character types
		constexpr ct_str::FixedString wstr = L"wide";
		static_assert(wstr.size() == 4);
		static_assert(std::is_same_v<decltype(wstr)::value_type, wchar_t>);

		constexpr ct_str::FixedString u8str = u8"utf8";
		static_assert(u8str.size() == 4);
		static_assert(std::is_same_v<decltype(u8str)::value_type, char8_t>);

		constexpr ct_str::FixedString u16str = u"utf16";
		static_assert(u16str.size() == 5);
		static_assert(std::is_same_v<decltype(u16str)::value_type, char16_t>);

		constexpr ct_str::FixedString u32str = U"utf32";
		static_assert(u32str.size() == 5);
		static_assert(std::is_same_v<decltype(u32str)::value_type, char32_t>);
	}

	TEST_CASE("Indexing and access")
	{
		constexpr ct_str::FixedString str = "test";

		// Compile-time indexing
		static_assert(str[0] == 't');
		static_assert(str[1] == 'e');
		static_assert(str[2] == 's');
		static_assert(str[3] == 't');

		// Runtime indexing
		CHECK(str[0] == 't');
		CHECK(str[3] == 't');
	}

	TEST_CASE("Special characters")
	{
		constexpr ct_str::FixedString special = "Hello\nWorld\t!";
		static_assert(special.size() == 13);
		static_assert(special[5] == '\n');
		static_assert(special[11] == '\t');
		CHECK(special[5] == '\n');
		CHECK(special[11] == '\t');
	}
}