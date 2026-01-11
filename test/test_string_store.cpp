/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("StringStore")
{
	TEST_CASE("Basic storage and access")
	{
		using Str = ct_str::StringStore<"hello">;

		// Static access
		CHECK(Str::c_str() != nullptr);
		CHECK(Str::value != nullptr);

		// View access
		static_assert(Str::view() == "hello");
		CHECK(Str::view() == "hello");
	}

	TEST_CASE("Deduplication - same strings share storage")
	{
		using Str1 = ct_str::StringStore<"test">;
		using Str2 = ct_str::StringStore<"test">;

		// Same type means same instantiation
		static_assert(std::is_same_v<Str1, Str2>);

		// Same pointer
		CHECK(Str1::c_str() == Str2::c_str());
		CHECK(Str1::value == Str2::value);
	}

	TEST_CASE("Different strings have different storage")
	{
		using Str1 = ct_str::StringStore<"abc">;
		using Str2 = ct_str::StringStore<"xyz">;

		// Different types
		static_assert(!std::is_same_v<Str1, Str2>);

		// Different pointers
		CHECK(Str1::c_str() != Str2::c_str());
		CHECK(Str1::value != Str2::value);
	}

	TEST_CASE("Multi-character types")
	{
		using WStr	 = ct_str::StringStore<L"wide">;
		using U8Str	 = ct_str::StringStore<u8"utf8">;
		using U16Str = ct_str::StringStore<u"utf16">;
		using U32Str = ct_str::StringStore<U"utf32">;

		// Type verification
		static_assert(std::is_same_v<WStr::value_type, wchar_t>);
		static_assert(std::is_same_v<U8Str::value_type, char8_t>);
		static_assert(std::is_same_v<U16Str::value_type, char16_t>);
		static_assert(std::is_same_v<U32Str::value_type, char32_t>);

		// Access
		CHECK(WStr::c_str() != nullptr);
		CHECK(U8Str::c_str() != nullptr);
		CHECK(U16Str::c_str() != nullptr);
		CHECK(U32Str::c_str() != nullptr);
	}

	TEST_CASE("Empty string")
	{
		using Empty = ct_str::StringStore<"">;

		static_assert(Empty::view().empty());
		CHECK(Empty::view().empty());
		CHECK(Empty::c_str()[0] == '\0');
	}

	TEST_CASE("String with special characters")
	{
		using Special = ct_str::StringStore<"Line1\nLine2\tTab">;

		CHECK(Special::view().find('\n') != std::string_view::npos);
		CHECK(Special::view().find('\t') != std::string_view::npos);
	}
}