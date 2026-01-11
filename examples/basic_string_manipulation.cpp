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
	std::cout << "  BASIC STRING MANIPULATION EXAMPLES\n";
	std::cout << "========================================\n\n";

	// === CASE CONVERSION ===
	std::cout << "=== Case Conversion ===\n";
	std::cout << "to_upper('hello world'): " << to_upper<"hello world">::c_str() << "\n";
	std::cout << "to_lower('HELLO WORLD'): " << to_lower<"HELLO WORLD">::c_str() << "\n\n";

	// === SUBSTRING OPERATIONS ===
	std::cout << "=== Substring Operations ===\n";
	std::cout << "substr('Hello World', 0, 5):  " << substr<"Hello World", 0, 5>::c_str() << "\n";
	std::cout << "substr('Hello World', 6, 5):  " << substr<"Hello World", 6, 5>::c_str() << "\n";
	std::cout << "left('Hello World', 5):       " << left<"Hello World", 5>::c_str() << "\n";
	std::cout << "right('Hello World', 5):      " << right<"Hello World", 5>::c_str() << "\n\n";

	// === CONCATENATION ===
	std::cout << "=== Concatenation ===\n";
	std::cout << "append('Hello', ' ', 'World'): " << append<"Hello", " ", "World">::c_str() << "\n";
	std::cout << "append('A', 'B', 'C', 'D'):    " << append<"A", "B", "C", "D">::c_str() << "\n\n";

	// === TRIMMING ===
	std::cout << "=== Trimming Whitespace ===\n";
	std::cout << "trim('  hello  '):       '" << trim<"  hello  ">::c_str() << "'\n";
	std::cout << "trim_left('  hello  '):  '" << trim_left<"  hello  ">::c_str() << "'\n";
	std::cout << "trim_right('  hello  '): '" << trim_right<"  hello  ">::c_str() << "'\n\n";

	// === REVERSAL ===
	std::cout << "=== String Reversal ===\n";
	std::cout << "reverse('Hello World'): " << reverse<"Hello World">::c_str() << "\n";
	std::cout << "reverse('12345'):       " << reverse<"12345">::c_str() << "\n\n";

	// === REPLACEMENT ===
	std::cout << "=== Find and Replace ===\n";
	std::cout << "replace('Hello World', 'World', 'Universe'):     "
			  << replace<"Hello World", "World", "Universe">::c_str() << "\n";
	std::cout << "replace_all('foo_bar_baz', '_', '-'):            " << replace_all<"foo_bar_baz", "_", "-">::c_str()
			  << "\n";
	std::cout << "replace_n('a_b_c_d', '_', '-', 2):               " << replace_n<"a_b_c_d", "_", "-", 2>::c_str()
			  << "\n\n";

	// === SEARCHING ===
	std::cout << "=== Searching ===\n";
	std::cout << "find('Hello World', 'World'):    pos = " << find<"Hello World", "World">() << "\n";
	std::cout << "find('Hello World', 'xyz'):      pos = " << find<"Hello World", "xyz">() << " (not found)\n";
	std::cout << "find_char('Hello World', 'o'):   pos = " << find_char<"Hello World", 'o'>() << "\n";
	std::cout << "rfind('one two one', 'one'):     pos = " << rfind<"one two one", "one">() << "\n\n";

	// === STRING TESTS ===
	std::cout << "=== String Tests ===\n";
	std::cout << "starts_with('Hello World', 'Hello'): " << (starts_with<"Hello World", "Hello">() ? "true" : "false")
			  << "\n";
	std::cout << "ends_with('Hello World', 'World'):   " << (ends_with<"Hello World", "World">() ? "true" : "false")
			  << "\n";
	std::cout << "contains('Hello World', 'lo Wo'):    " << (contains<"Hello World", "lo Wo">() ? "true" : "false")
			  << "\n\n";

	// === COMPARISON ===
	std::cout << "=== String Comparison ===\n";
	std::cout << "compare('abc', 'abc'):  " << compare<"abc", "abc">() << " (equal)\n";
	std::cout << "compare('abc', 'xyz'):  " << compare<"abc", "xyz">() << " (less than)\n";
	std::cout << "compare('xyz', 'abc'):  " << compare<"xyz", "abc">() << " (greater than)\n\n";

	// === CHAINING OPERATIONS ===
	std::cout << "=== Chaining Operations ===\n";
	std::cout << "to_upper(trim('  hello  ')):         '" << to_upper<trim<"  hello  ">::fwd>::c_str() << "'\n";
	std::cout << "reverse(to_upper('hello')):          '" << reverse<to_upper<"hello">::fwd>::c_str() << "'\n";
	std::cout << "replace_all(to_lower('A_B_C'), '_'): '" << replace_all<to_lower<"A_B_C">::fwd, "_", " ">::c_str()
			  << "'\n\n";

	// === COMPILE-TIME VERIFICATION ===
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(to_upper<"hello">::storage.data[0] == 'H');
	static_assert(to_lower<"HELLO">::storage.data[0] == 'h');
	static_assert(starts_with<"Hello", "Hel">());
	static_assert(ends_with<"World", "ld">());
	static_assert(contains<"Hello World", "lo W">());
	static_assert(compare<"abc", "abc">() == 0);
	static_assert(find<"Hello World", "World">() == 6);
	std::cout << "All static assertions passed!\n\n";

	return 0;
}