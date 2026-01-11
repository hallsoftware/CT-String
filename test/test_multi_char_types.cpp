/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("Multi-Character Types")
{
	TEST_CASE("wchar_t operations")
	{
		// Basic operations
		using WUpper = ct_str::to_upper<L"hello">;
		static_assert(std::is_same_v<decltype(WUpper::fwd)::value_type, wchar_t>);
		CHECK(WUpper::c_str() != nullptr);

		using WLower = ct_str::to_lower<L"HELLO">;
		static_assert(std::is_same_v<decltype(WLower::fwd)::value_type, wchar_t>);

		using WReverse = ct_str::reverse<L"hello">;
		static_assert(std::is_same_v<decltype(WReverse::fwd)::value_type, wchar_t>);

		using WTrim = ct_str::trim<L"  hello  ">;
		static_assert(std::is_same_v<decltype(WTrim::fwd)::value_type, wchar_t>);

		// Append
		using WAppend = ct_str::append<L"Hello", L" ", L"World">;
		static_assert(std::is_same_v<decltype(WAppend::fwd)::value_type, wchar_t>);
	}

	TEST_CASE("char8_t operations")
	{
		// Basic operations
		using U8Upper = ct_str::to_upper<u8"hello">;
		static_assert(std::is_same_v<decltype(U8Upper::fwd)::value_type, char8_t>);
		CHECK(U8Upper::c_str() != nullptr);

		using U8Lower = ct_str::to_lower<u8"HELLO">;
		static_assert(std::is_same_v<decltype(U8Lower::fwd)::value_type, char8_t>);

		using U8Reverse = ct_str::reverse<u8"hello">;
		static_assert(std::is_same_v<decltype(U8Reverse::fwd)::value_type, char8_t>);

		using U8Trim = ct_str::trim<u8"  hello  ">;
		static_assert(std::is_same_v<decltype(U8Trim::fwd)::value_type, char8_t>);

		// Append
		using U8Append = ct_str::append<u8"Hello", u8" ", u8"World">;
		static_assert(std::is_same_v<decltype(U8Append::fwd)::value_type, char8_t>);
	}

	TEST_CASE("char16_t operations")
	{
		// Basic operations
		using U16Upper = ct_str::to_upper<u"hello">;
		static_assert(std::is_same_v<decltype(U16Upper::fwd)::value_type, char16_t>);
		CHECK(U16Upper::c_str() != nullptr);

		using U16Lower = ct_str::to_lower<u"HELLO">;
		static_assert(std::is_same_v<decltype(U16Lower::fwd)::value_type, char16_t>);

		using U16Reverse = ct_str::reverse<u"hello">;
		static_assert(std::is_same_v<decltype(U16Reverse::fwd)::value_type, char16_t>);

		using U16Trim = ct_str::trim<u"  hello  ">;
		static_assert(std::is_same_v<decltype(U16Trim::fwd)::value_type, char16_t>);

		// Append
		using U16Append = ct_str::append<u"Hello", u" ", u"World">;
		static_assert(std::is_same_v<decltype(U16Append::fwd)::value_type, char16_t>);
	}

	TEST_CASE("char32_t operations")
	{
		// Basic operations
		using U32Upper = ct_str::to_upper<U"hello">;
		static_assert(std::is_same_v<decltype(U32Upper::fwd)::value_type, char32_t>);
		CHECK(U32Upper::c_str() != nullptr);

		using U32Lower = ct_str::to_lower<U"HELLO">;
		static_assert(std::is_same_v<decltype(U32Lower::fwd)::value_type, char32_t>);

		using U32Reverse = ct_str::reverse<U"hello">;
		static_assert(std::is_same_v<decltype(U32Reverse::fwd)::value_type, char32_t>);

		using U32Trim = ct_str::trim<U"  hello  ">;
		static_assert(std::is_same_v<decltype(U32Trim::fwd)::value_type, char32_t>);

		// Append
		using U32Append = ct_str::append<U"Hello", U" ", U"World">;
		static_assert(std::is_same_v<decltype(U32Append::fwd)::value_type, char32_t>);
	}

	TEST_CASE("Type preservation through operations")
	{
		// Chaining preserves type
		using WChain = ct_str::to_upper<ct_str::trim<L"  hello  ">::fwd>;
		static_assert(std::is_same_v<decltype(WChain::fwd)::value_type, wchar_t>);

		using U8Chain = ct_str::reverse<ct_str::to_lower<u8"HELLO">::fwd>;
		static_assert(std::is_same_v<decltype(U8Chain::fwd)::value_type, char8_t>);

		using U16Chain = ct_str::trim<ct_str::reverse<u"hello  ">::fwd>;
		static_assert(std::is_same_v<decltype(U16Chain::fwd)::value_type, char16_t>);

		using U32Chain = ct_str::to_lower<ct_str::to_upper<U"hello">::fwd>;
		static_assert(std::is_same_v<decltype(U32Chain::fwd)::value_type, char32_t>);
	}

	TEST_CASE("Query functions with different char types")
	{
		// wchar_t
		static_assert(ct_str::starts_with<L"Hello", L"Hel">());
		static_assert(ct_str::ends_with<L"Hello", L"llo">());
		static_assert(ct_str::contains<L"Hello World", L"Wor">());

		// char8_t
		static_assert(ct_str::starts_with<u8"Hello", u8"Hel">());
		static_assert(ct_str::ends_with<u8"Hello", u8"llo">());
		static_assert(ct_str::contains<u8"Hello World", u8"Wor">());

		// char16_t
		static_assert(ct_str::starts_with<u"Hello", u"Hel">());
		static_assert(ct_str::ends_with<u"Hello", u"llo">());
		static_assert(ct_str::contains<u"Hello World", u"Wor">());

		// char32_t
		static_assert(ct_str::starts_with<U"Hello", U"Hel">());
		static_assert(ct_str::ends_with<U"Hello", U"llo">());
		static_assert(ct_str::contains<U"Hello World", U"Wor">());
	}

	TEST_CASE("Path operations with different char types")
	{
		// wchar_t paths
		using WFile = ct_str::filename<L"/path/to/file.txt">;
		static_assert(std::is_same_v<decltype(WFile::fwd)::value_type, wchar_t>);

		using WStem = ct_str::stem<L"file.txt">;
		static_assert(std::is_same_v<decltype(WStem::fwd)::value_type, wchar_t>);

		using WExt = ct_str::extension<L"file.txt">;
		static_assert(std::is_same_v<decltype(WExt::fwd)::value_type, wchar_t>);

		// char8_t paths
		using U8File = ct_str::filename<u8"/path/to/file.txt">;
		static_assert(std::is_same_v<decltype(U8File::fwd)::value_type, char8_t>);
	}
}