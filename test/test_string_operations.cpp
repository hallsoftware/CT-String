/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("String Operations")
{
	TEST_CASE("to_upper")
	{
		// Basic conversion
		using Upper1 = ct_str::to_upper<"hello">;
		static_assert(Upper1::view() == "HELLO");
		CHECK(Upper1::view() == "HELLO");

		// Already uppercase
		using Upper2 = ct_str::to_upper<"WORLD">;
		static_assert(Upper2::view() == "WORLD");

		// Mixed case
		using Upper3 = ct_str::to_upper<"HeLLo WoRLd">;
		static_assert(Upper3::view() == "HELLO WORLD");

		// Numbers and symbols unchanged
		using Upper4 = ct_str::to_upper<"abc123!@#">;
		static_assert(Upper4::view() == "ABC123!@#");

		// Empty string
		using Upper5 = ct_str::to_upper<"">;
		static_assert(Upper5::view() == "");

		// Wide char
		using WUpper = ct_str::to_upper<L"hello">;
		static_assert(std::is_same_v<WUpper::value_type, wchar_t>);
	}

	TEST_CASE("to_lower")
	{
		// Basic conversion
		using Lower1 = ct_str::to_lower<"HELLO">;
		static_assert(Lower1::view() == "hello");
		CHECK(Lower1::view() == "hello");

		// Already lowercase
		using Lower2 = ct_str::to_lower<"world">;
		static_assert(Lower2::view() == "world");

		// Mixed case
		using Lower3 = ct_str::to_lower<"HeLLo WoRLd">;
		static_assert(Lower3::view() == "hello world");

		// Numbers and symbols unchanged
		using Lower4 = ct_str::to_lower<"ABC123!@#">;
		static_assert(Lower4::view() == "abc123!@#");

		// UTF-8
		using U8Lower = ct_str::to_lower<u8"HELLO">;
		static_assert(std::is_same_v<U8Lower::value_type, char8_t>);
	}

	TEST_CASE("reverse")
	{
		// Basic reversal
		using Rev1 = ct_str::reverse<"hello">;
		static_assert(Rev1::view() == "olleh");
		CHECK(Rev1::view() == "olleh");

		// Palindrome
		using Rev2 = ct_str::reverse<"racecar">;
		static_assert(Rev2::view() == "racecar");

		// Single character
		using Rev3 = ct_str::reverse<"a">;
		static_assert(Rev3::view() == "a");

		// Empty
		using Rev4 = ct_str::reverse<"">;
		static_assert(Rev4::view() == "");

		// Numbers
		using Rev5 = ct_str::reverse<"12345">;
		static_assert(Rev5::view() == "54321");
	}

	TEST_CASE("substr")
	{
		// Basic substring
		using Sub1 = ct_str::substr<"Hello World", 0, 5>;
		static_assert(Sub1::view() == "Hello");
		CHECK(Sub1::view() == "Hello");

		using Sub2 = ct_str::substr<"Hello World", 6, 5>;
		static_assert(Sub2::view() == "World");

		// From middle
		using Sub3 = ct_str::substr<"Hello World", 3, 5>;
		static_assert(Sub3::view() == "lo Wo");

		// To end
		using Sub4 = ct_str::substr<"Hello World", 6, 100>;
		static_assert(Sub4::view() == "World");

		// Empty substring
		using Sub5 = ct_str::substr<"Hello", 0, 0>;
		static_assert(Sub5::view() == "");

		// Single character
		using Sub6 = ct_str::substr<"Hello", 1, 1>;
		static_assert(Sub6::view() == "e");
	}

	TEST_CASE("left")
	{
		using Left1 = ct_str::left<"Hello World", 5>;
		static_assert(Left1::view() == "Hello");
		CHECK(Left1::view() == "Hello");

		using Left2 = ct_str::left<"Hello", 10>;
		static_assert(Left2::view() == "Hello");

		using Left3 = ct_str::left<"Hello", 0>;
		static_assert(Left3::view() == "");
	}

	TEST_CASE("right")
	{
		using Right1 = ct_str::right<"Hello World", 5>;
		static_assert(Right1::view() == "World");
		CHECK(Right1::view() == "World");

		using Right2 = ct_str::right<"Hello", 10>;
		static_assert(Right2::view() == "Hello");

		using Right3 = ct_str::right<"Hello", 0>;
		static_assert(Right3::view() == "");
	}

	TEST_CASE("append")
	{
		// Two strings
		using App1 = ct_str::append<"Hello", " World">;
		static_assert(App1::view() == "Hello World");
		CHECK(App1::view() == "Hello World");

		// Three strings
		using App2 = ct_str::append<"One", "Two", "Three">;
		static_assert(App2::view() == "OneTwoThree");

		// Many strings
		using App3 = ct_str::append<"A", "B", "C", "D", "E">;
		static_assert(App3::view() == "ABCDE");

		// With empty strings
		using App4 = ct_str::append<"Hello", "", "World">;
		static_assert(App4::view() == "HelloWorld");

		// All empty
		using App5 = ct_str::append<"", "", "">;
		static_assert(App5::view() == "");
	}

	TEST_CASE("trim")
	{
		// Both sides
		using Trim1 = ct_str::trim<"  hello  ">;
		static_assert(Trim1::view() == "hello");
		CHECK(Trim1::view() == "hello");

		// Left only
		using Trim2 = ct_str::trim<"  hello">;
		static_assert(Trim2::view() == "hello");

		// Right only
		using Trim3 = ct_str::trim<"hello  ">;
		static_assert(Trim3::view() == "hello");

		// No whitespace
		using Trim4 = ct_str::trim<"hello">;
		static_assert(Trim4::view() == "hello");

		// All whitespace
		using Trim5 = ct_str::trim<"     ">;
		static_assert(Trim5::view() == "");

		// Tabs and newlines
		using Trim6 = ct_str::trim<"\t\nhello\r\n">;
		static_assert(Trim6::view() == "hello");
	}

	TEST_CASE("trim_left")
	{
		using TrimL1 = ct_str::trim_left<"  hello  ">;
		static_assert(TrimL1::view() == "hello  ");
		CHECK(TrimL1::view() == "hello  ");

		using TrimL2 = ct_str::trim_left<"hello">;
		static_assert(TrimL2::view() == "hello");
	}

	TEST_CASE("trim_right")
	{
		using TrimR1 = ct_str::trim_right<"  hello  ">;
		static_assert(TrimR1::view() == "  hello");
		CHECK(TrimR1::view() == "  hello");

		using TrimR2 = ct_str::trim_right<"hello">;
		static_assert(TrimR2::view() == "hello");
	}

	TEST_CASE("replace")
	{
		// First occurrence
		using Rep1 = ct_str::replace<"hello world", "world", "universe">;
		static_assert(Rep1::view() == "hello universe");
		CHECK(Rep1::view() == "hello universe");

		// Not found
		using Rep2 = ct_str::replace<"hello world", "xyz", "abc">;
		static_assert(Rep2::view() == "hello world");

		// Multiple occurrences (only first)
		using Rep3 = ct_str::replace<"abc abc abc", "abc", "xyz">;
		static_assert(Rep3::view() == "xyz abc abc");

		// Empty replacement
		using Rep4 = ct_str::replace<"hello world", "world", "">;
		static_assert(Rep4::view() == "hello ");
	}

	TEST_CASE("replace_all")
	{
		// All occurrences
		using RepAll1 = ct_str::replace_all<"abc abc abc", "abc", "xyz">;
		static_assert(RepAll1::view() == "xyz xyz xyz");
		CHECK(RepAll1::view() == "xyz xyz xyz");

		// Overlapping prevention
		using RepAll2 = ct_str::replace_all<"aaa", "aa", "b">;
		static_assert(RepAll2::view() == "ba");

		// Single occurrence
		using RepAll3 = ct_str::replace_all<"hello", "hello", "world">;
		static_assert(RepAll3::view() == "world");

		// Character replacement
		using RepAll4 = ct_str::replace_all<"foo_bar_baz", "_", "-">;
		static_assert(RepAll4::view() == "foo-bar-baz");
	}

	TEST_CASE("replace_n")
	{
		// Replace N occurrences
		using RepN1 = ct_str::replace_n<"a_b_c_d", "_", "-", 2>;
		static_assert(RepN1::view() == "a-b-c_d");
		CHECK(RepN1::view() == "a-b-c_d");

		// Replace 0
		using RepN2 = ct_str::replace_n<"a_b_c", "_", "-", 0>;
		static_assert(RepN2::view() == "a_b_c");

		// Replace more than exist
		using RepN3 = ct_str::replace_n<"a_b", "_", "-", 10>;
		static_assert(RepN3::view() == "a-b");

		// Replace 1
		using RepN4 = ct_str::replace_n<"a_b_c", "_", "-", 1>;
		static_assert(RepN4::view() == "a-b_c");
	}

	TEST_CASE("Operation chaining")
	{
		// Chain multiple operations
		using Chain1 = ct_str::to_upper<ct_str::trim<"  hello  ">::fwd>;
		static_assert(Chain1::view() == "HELLO");
		CHECK(Chain1::view() == "HELLO");

		using Chain2 = ct_str::reverse<ct_str::to_upper<"hello">::fwd>;
		static_assert(Chain2::view() == "OLLEH");

		using Chain3 = ct_str::replace_all<ct_str::to_lower<"HELLO_WORLD">::fwd, "_", " ">;
		static_assert(Chain3::view() == "hello world");

		// Complex chain
		using Chain4 = ct_str::to_upper<ct_str::trim<ct_str::replace_all<"  foo_bar  ", "_", " ">::fwd>::fwd>;
		static_assert(Chain4::view() == "FOO BAR");
	}
}