/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("String Queries")
{
	TEST_CASE("at")
	{
		// Basic access
		static_assert(ct_str::at<"Hello", 0>() == 'H');
		static_assert(ct_str::at<"Hello", 1>() == 'e');
		static_assert(ct_str::at<"Hello", 4>() == 'o');
		CHECK(ct_str::at<"Hello", 0>() == 'H');
		CHECK(ct_str::at<"Hello", 4>() == 'o');

		// Different character types
		static_assert(ct_str::at<L"Wide", 0>() == L'W');
		static_assert(ct_str::at<u8"UTF8", 0>() == u8'U');
		static_assert(ct_str::at<u"UTF16", 0>() == u'U');
		static_assert(ct_str::at<U"UTF32", 0>() == U'U');
	}

	TEST_CASE("find")
	{
		// Basic find
		static_assert(ct_str::find<"Hello World", "World">() == 6);
		static_assert(ct_str::find<"Hello World", "Hello">() == 0);
		CHECK(ct_str::find<"Hello World", "World">() == 6);

		// Not found
		constexpr auto npos = std::string_view::npos;
		static_assert(ct_str::find<"Hello World", "xyz">() == npos);
		CHECK(ct_str::find<"Hello World", "xyz">() == npos);

		// Empty pattern
		static_assert(ct_str::find<"Hello", "">() == 0);

		// Pattern at end
		static_assert(ct_str::find<"Hello", "lo">() == 3);

		// Multiple occurrences (finds first)
		static_assert(ct_str::find<"abc abc abc", "abc">() == 0);

		// Start position
		static_assert(ct_str::find<"abc abc abc", "abc", 1>() == 4);
		static_assert(ct_str::find<"abc abc abc", "abc", 5>() == 8);
	}

	TEST_CASE("find_char")
	{
		// Basic find
		static_assert(ct_str::find_char<"Hello", 'e'>() == 1);
		static_assert(ct_str::find_char<"Hello", 'H'>() == 0);
		CHECK(ct_str::find_char<"Hello", 'o'>() == 4);

		// Not found
		constexpr auto npos = std::string_view::npos;
		static_assert(ct_str::find_char<"Hello", 'x'>() == npos);

		// Multiple occurrences
		static_assert(ct_str::find_char<"Hello", 'l'>() == 2);

		// Start position
		static_assert(ct_str::find_char<"Hello", 'l', 3>() == 3);
		static_assert(ct_str::find_char<"Hello", 'l', 4>() == npos);
	}

	TEST_CASE("rfind")
	{
		// Basic rfind
		static_assert(ct_str::rfind<"abc abc abc", "abc">() == 8);
		CHECK(ct_str::rfind<"abc abc abc", "abc">() == 8);

		// Not found
		constexpr auto npos = std::string_view::npos;
		static_assert(ct_str::rfind<"Hello World", "xyz">() == npos);

		// Single occurrence
		static_assert(ct_str::rfind<"Hello World", "World">() == 6);

		// At beginning
		static_assert(ct_str::rfind<"Hello", "He">() == 0);
	}

	TEST_CASE("rfind_char")
	{
		// Basic rfind
		static_assert(ct_str::rfind_char<"Hello", 'l'>() == 3);
		CHECK(ct_str::rfind_char<"Hello", 'l'>() == 3);

		// Not found
		constexpr auto npos = std::string_view::npos;
		static_assert(ct_str::rfind_char<"Hello", 'x'>() == npos);

		// Single occurrence
		static_assert(ct_str::rfind_char<"Hello", 'H'>() == 0);

		// Last character
		static_assert(ct_str::rfind_char<"Hello", 'o'>() == 4);
	}

	TEST_CASE("starts_with")
	{
		// Basic starts_with
		static_assert(ct_str::starts_with<"Hello World", "Hello">());
		static_assert(!ct_str::starts_with<"Hello World", "World">());
		CHECK(ct_str::starts_with<"Hello World", "Hello">());
		CHECK_FALSE(ct_str::starts_with<"Hello World", "World">());

		// Empty prefix
		static_assert(ct_str::starts_with<"Hello", "">());

		// Exact match
		static_assert(ct_str::starts_with<"Hello", "Hello">());

		// Longer prefix
		static_assert(!ct_str::starts_with<"Hi", "Hello">());

		// Case sensitive
		static_assert(!ct_str::starts_with<"Hello", "hello">());
	}

	TEST_CASE("ends_with")
	{
		// Basic ends_with
		static_assert(ct_str::ends_with<"Hello World", "World">());
		static_assert(!ct_str::ends_with<"Hello World", "Hello">());
		CHECK(ct_str::ends_with<"Hello World", "World">());
		CHECK_FALSE(ct_str::ends_with<"Hello World", "Hello">());

		// Empty suffix
		static_assert(ct_str::ends_with<"Hello", "">());

		// Exact match
		static_assert(ct_str::ends_with<"Hello", "Hello">());

		// Longer suffix
		static_assert(!ct_str::ends_with<"Hi", "Hello">());

		// Case sensitive
		static_assert(!ct_str::ends_with<"Hello", "ELLO">());
	}

	TEST_CASE("contains")
	{
		// Basic contains
		static_assert(ct_str::contains<"Hello World", "lo Wo">());
		static_assert(!ct_str::contains<"Hello World", "xyz">());
		CHECK(ct_str::contains<"Hello World", "lo Wo">());
		CHECK_FALSE(ct_str::contains<"Hello World", "xyz">());

		// At beginning
		static_assert(ct_str::contains<"Hello", "Hel">());

		// At end
		static_assert(ct_str::contains<"Hello", "llo">());

		// Entire string
		static_assert(ct_str::contains<"Hello", "Hello">());

		// Empty pattern
		static_assert(ct_str::contains<"Hello", "">());

		// Case sensitive
		static_assert(!ct_str::contains<"Hello", "hello">());
	}

	TEST_CASE("compare")
	{
		// Equal strings
		static_assert(ct_str::compare<"abc", "abc">() == 0);
		CHECK(ct_str::compare<"abc", "abc">() == 0);

		// Less than
		static_assert(ct_str::compare<"abc", "xyz">() < 0);
		CHECK(ct_str::compare<"abc", "xyz">() < 0);

		// Greater than
		static_assert(ct_str::compare<"xyz", "abc">() > 0);
		CHECK(ct_str::compare<"xyz", "abc">() > 0);

		// Different lengths
		static_assert(ct_str::compare<"abc", "abcd">() < 0);
		static_assert(ct_str::compare<"abcd", "abc">() > 0);

		// Empty strings
		static_assert(ct_str::compare<"", "">() == 0);
		static_assert(ct_str::compare<"", "a">() < 0);
		static_assert(ct_str::compare<"a", "">() > 0);

		// Case sensitive
		static_assert(ct_str::compare<"ABC", "abc">() < 0);	 // 'A' < 'a' in ASCII
	}
}