#include "ct_str.hpp"
#include <iostream>

int main()
{
	using namespace ct_str;
	std::cout << "========================================\n";
	std::cout << "    COMPILE-TIME STRING OPERATIONS\n";
	std::cout << "    (Multi-Character Type Support)\n";
	std::cout << "========================================\n";

	// ===== BASIC OPERATIONS =====
	std::cout << "\n=== BASIC OPERATIONS (char) ===\n";
	constexpr const char* s1	= substr<"HELLO WORLD", 6, 5>::c_str();
	constexpr const char* s2	= to_upper<"world">::c_str();
	constexpr const char* lower = to_lower<"HELLO WORLD">::c_str();
	std::cout << "substr('HELLO WORLD', 6, 5):  '" << s1 << "'\n";
	std::cout << "to_upper('world'):            '" << s2 << "'\n";
	std::cout << "to_lower('HELLO WORLD'):      '" << lower << "'\n";

	static_assert(std::is_same_v<substr<"HELLO WORLD", 6, 5>, to_upper<"world">>);
	if (s1 == s2)
	{
		std::cout << "(+) Deduplication: Different operations producing same 'WORLD' share memory!\n\n";
	}

	std::cout << "========================================\n";
	std::cout << " MULTI-CHAR-TYPE CT STRING OPERATIONS\n";
	std::cout << "========================================\n";

	// ===== CHAR (REGULAR) =====
	std::cout << "\n=== CHAR (regular strings) ===\n";
	std::cout << "to_upper('hello world'): " << to_upper<"hello world">::c_str() << "\n";
	std::cout << "to_lower('HELLO'):       " << to_lower<"HELLO">::c_str() << "\n";
	std::cout << "reverse('Hello World'):  " << reverse<"Hello World">::c_str() << "\n";
	std::cout << "trim('  spaces  '):      '" << trim<"  spaces  ">::c_str() << "'\n";
	std::cout << "substr(..., 6, 5):       " << substr<"Hello World", 6, 5>::c_str() << "\n";
	std::cout << "left(..., 5):            " << left<"Hello World", 5>::c_str() << "\n";
	std::cout << "right(..., 5):           " << right<"Hello World", 5>::c_str() << "\n";

	// ===== CHAR8_T (UTF-8) =====
	std::cout << "\n=== CHAR8_T (UTF-8 strings) ===\n";
	std::cout << "to_upper:  " << reinterpret_cast<const char*>(to_upper<u8"hello utf8">::c_str()) << "\n";
	std::cout << "reverse:   " << reinterpret_cast<const char*>(reverse<u8"Hello UTF8">::c_str()) << "\n";
	std::cout << "left(5):   " << reinterpret_cast<const char*>(left<u8"Hello UTF8", 5>::c_str()) << "\n";
	std::cout << "right(4):  " << reinterpret_cast<const char*>(right<u8"Hello UTF8", 4>::c_str()) << "\n";
	std::cout << "trim:      '" << reinterpret_cast<const char*>(trim<u8"  utf8  ">::c_str()) << "'\n";

	// ===== WCHAR_T (WIDE STRINGS) =====
	std::cout << "\n=== WCHAR_T (wide strings) ===\n";
	std::wcout << L"to_upper:  " << to_upper<L"wide string">::c_str() << L"\n";
	std::wcout << L"to_lower:  " << to_lower<L"WIDE">::c_str() << L"\n";
	std::wcout << L"reverse:   " << reverse<L"Wide String">::c_str() << L"\n";
	std::wcout << L"substr:    " << substr<L"Wide String", 5, 6>::c_str() << L"\n";
	std::wcout << L"trim:      '" << trim<L"  wide  ">::c_str() << L"'\n";

	// ===== CHAR16_T (UTF-16) =====
	std::cout << "\n=== CHAR16_T (UTF-16 strings) ===\n";
	std::cout << "to_upper:  (UTF-16 - " << to_upper<u"utf16 text">::view().size() << " chars)\n";
	std::cout << "reverse:   (UTF-16 - " << reverse<u"UTF16 Text">::view().size() << " chars)\n";
	std::cout << "left(5):   (UTF-16 - " << left<u"UTF16 Text", 5>::view().size() << " chars)\n";

	// ===== CHAR32_T (UTF-32) =====
	std::cout << "\n=== CHAR32_T (UTF-32 strings) ===\n";
	std::cout << "to_upper:  (UTF-32 - " << to_upper<U"utf32 data">::view().size() << " chars)\n";
	std::cout << "reverse:   (UTF-32 - " << reverse<U"UTF32 Data">::view().size() << " chars)\n";
	std::cout << "right(4):  (UTF-32 - " << right<U"UTF32 Data", 4>::view().size() << " chars)\n";

	// ===== APPEND WITH SAME CHAR TYPE =====
	std::cout << "\n=== APPEND (same char type) ===\n";
	std::cout << "char:    " << append<"Hello", " ", "World">::c_str() << "\n";
	std::cout << "char8_t: " << reinterpret_cast<const char*>(append<u8"UTF8", u8" ", u8"Text">::c_str()) << "\n";
	std::wcout << L"wchar_t: " << append<L"Wide", L" ", L"String">::c_str() << L"\n";

	// ===== AT - CHARACTER ACCESS =====
	std::cout << "\n=== AT - CHARACTER ACCESS ===\n";
	constexpr char ch0 = at<"Hello", 0>();
	constexpr char ch1 = at<"Hello", 1>();
	constexpr char ch4 = at<"Hello", 4>();
	std::cout << "at('Hello', 0): '" << ch0 << "'\n";
	std::cout << "at('Hello', 1): '" << ch1 << "'\n";
	std::cout << "at('Hello', 4): '" << ch4 << "'\n";

	// ===== LEFT/RIGHT - SUBSTRING EXTRACTION =====
	std::cout << "\n=== LEFT/RIGHT - SUBSTRING EXTRACTION ===\n";
	constexpr auto left3   = left<"Hello World", 3>::c_str();
	constexpr auto left5   = left<"Hello World", 5>::c_str();
	constexpr auto left20  = left<"Hello", 20>::c_str();
	constexpr auto right3  = right<"Hello World", 3>::c_str();
	constexpr auto right5  = right<"Hello World", 5>::c_str();
	constexpr auto right20 = right<"Hello", 20>::c_str();
	std::cout << "left('Hello World', 3):  '" << left3 << "'\n";
	std::cout << "left('Hello World', 5):  '" << left5 << "'\n";
	std::cout << "left('Hello', 20):       '" << left20 << "' (clamped to length)\n";
	std::cout << "right('Hello World', 3): '" << right3 << "'\n";
	std::cout << "right('Hello World', 5): '" << right5 << "'\n";
	std::cout << "right('Hello', 20):      '" << right20 << "' (clamped to length)\n";

	// ===== APPEND - CONCATENATION =====
	std::cout << "\n=== APPEND - CONCATENATION ===\n";
	constexpr auto app2 = append<"Hello", " World">::c_str();
	constexpr auto app3 = append<"One", "Two", "Three">::c_str();
	constexpr auto app5 = append<"A", "B", "C", "D", "E">::c_str();
	constexpr auto path = append<"/usr/", "local/", "bin/", "program">::c_str();
	std::cout << "append('Hello', ' World'):        " << app2 << "\n";
	std::cout << "append('One', 'Two', 'Three'):    " << app3 << "\n";
	std::cout << "append('A'...'E'):                " << app5 << "\n";
	std::cout << "append(path components):          " << path << "\n";

	// Wide char append
	std::wcout << L"append(wide): " << append<L"Wide", L" ", L"String">::c_str() << L"\n";

	// ===== TRIM OPERATIONS =====
	std::cout << "\n=== TRIM OPERATIONS ===\n";
	constexpr auto trimmed	 = trim<"  Hello World  ">::c_str();
	constexpr auto trim_l	 = trim_left<"  Hello World  ">::c_str();
	constexpr auto trim_r	 = trim_right<"  Hello World  ">::c_str();
	constexpr auto trim_tabs = trim<"\t\n  Spaces and tabs  \r\n">::c_str();
	std::cout << "trim('  Hello World  '):          '" << trimmed << "'\n";
	std::cout << "trim_left('  Hello World  '):     '" << trim_l << "'\n";
	std::cout << "trim_right('  Hello World  '):    '" << trim_r << "'\n";
	std::cout << "trim(with tabs/newlines):         '" << trim_tabs << "'\n";

	// ===== REPLACE OPERATIONS =====
	std::cout << "\n=== REPLACE OPERATIONS ===\n";
	constexpr auto rep		 = replace<"All The World Says Hello World", "World", "Universe">::c_str();
	constexpr auto rep_all	 = replace_all<"foo_bar_baz", "_", "-">::c_str();
	constexpr auto rep_n0	 = replace_n<"foo_bar_baz_qux", "_", "-", 0>::c_str();
	constexpr auto rep_n1	 = replace_n<"foo_bar_baz_qux", "_", "-", 1>::c_str();
	constexpr auto rep_n2	 = replace_n<"foo_bar_baz_qux", "_", "-", 2>::c_str();
	constexpr auto rep_n_all = replace_n<"foo_bar_baz_qux", "_", "-", 10>::c_str();
	std::cout << "replace('All The World Says Hello World', 'World', 'Universe'): " << rep << "\n";
	std::cout << "replace_all('foo_bar_baz', '_', '-'):        " << rep_all << "\n";
	std::cout << "replace_n(..., 0):                           " << rep_n0 << "\n";
	std::cout << "replace_n(..., 1):                           " << rep_n1 << "\n";
	std::cout << "replace_n(..., 2):                           " << rep_n2 << "\n";
	std::cout << "replace_n(..., 10):                          " << rep_n_all << "\n";

	// ===== REVERSE =====
	std::cout << "\n=== REVERSE ===\n";
	constexpr auto rev1 = reverse<"Hello World">::c_str();
	constexpr auto rev2 = reverse<"racecar">::c_str();
	constexpr auto rev3 = reverse<"12345">::c_str();
	std::cout << "reverse('Hello World'): " << rev1 << "\n";
	std::cout << "reverse('racecar'):     " << rev2 << "\n";
	std::cout << "reverse('12345'):       " << rev3 << "\n";

	// ===== BASENAME - PATH EXTRACTION =====
	std::cout << "\n=== BASENAME - PATH EXTRACTION ===\n";
	constexpr auto base1 = basename<"/usr/local/bin/myprogram">::c_str();
	constexpr auto base2 = basename<"C:\\Users\\Documents\\file.txt">::c_str();
	constexpr auto base3 = basename<"relative/path/to/source.cpp">::c_str();
	constexpr auto base4 = basename<"no_path_file.h">::c_str();
	constexpr auto base5 = basename<"/trailing/slash/">::c_str();
	std::cout << "basename('/usr/local/bin/myprogram'):     " << base1 << "\n";
	std::cout << "basename('C:\\...\\file.txt'):            " << base2 << "\n";
	std::cout << "basename('relative/path/to/source.cpp'):  " << base3 << "\n";
	std::cout << "basename('no_path_file.h'):               " << base4 << "\n";
	std::cout << "basename('/trailing/slash/'):             " << base5 << "\n";

	// ===== FIND OPERATIONS =====
	std::cout << "\n=== FIND OPERATIONS ===\n";
	constexpr auto pos1 = find<"Hello World", "World">();
	constexpr auto pos2 = find<"Hello World", "xyz">();
	constexpr auto pos3 = find_char<"Hello World", 'o'>();
	constexpr auto pos4 = find_char<"Hello World", 'o', 5>();
	constexpr auto pos5 = rfind_char<"Hello World", 'o'>();
	constexpr auto pos6 = rfind<"one two one", "one">();
	std::cout << "find('Hello World', 'World'):       pos = " << pos1 << "\n";
	std::cout << "find('Hello World', 'xyz'):         pos = " << pos2 << " (npos)\n";
	std::cout << "find_char('Hello World', 'o'):      pos = " << pos3 << "\n";
	std::cout << "find_char('Hello World', 'o', 5):   pos = " << pos4 << "\n";
	std::cout << "rfind_char('Hello World', 'o'):     pos = " << pos5 << "\n";
	std::cout << "rfind('one two one', 'one'):        pos = " << pos6 << "\n";

	// ===== BOOLEAN TESTS =====
	std::cout << "\n=== BOOLEAN TESTS ===\n";
	constexpr bool sw1 = starts_with<"Hello World", "Hello">();
	constexpr bool sw2 = starts_with<"Hello World", "World">();
	constexpr bool ew1 = ends_with<"Hello World", "World">();
	constexpr bool ew2 = ends_with<"Hello World", "Hello">();
	constexpr bool c1  = contains<"Hello World", "lo Wo">();
	constexpr bool c2  = contains<"Hello World", "xyz">();
	std::cout << "starts_with('Hello World', 'Hello'): " << (sw1 ? "true" : "false") << "\n";
	std::cout << "starts_with('Hello World', 'World'): " << (sw2 ? "true" : "false") << "\n";
	std::cout << "ends_with('Hello World', 'World'):   " << (ew1 ? "true" : "false") << "\n";
	std::cout << "ends_with('Hello World', 'Hello'):   " << (ew2 ? "true" : "false") << "\n";
	std::cout << "contains('Hello World', 'lo Wo'):    " << (c1 ? "true" : "false") << "\n";
	std::cout << "contains('Hello World', 'xyz'):      " << (c2 ? "true" : "false") << "\n";

	// ===== COMPARE =====
	std::cout << "\n=== COMPARE ===\n";
	constexpr int cmp1 = compare<"abc", "abc">();
	constexpr int cmp2 = compare<"abc", "xyz">();
	constexpr int cmp3 = compare<"xyz", "abc">();
	constexpr int cmp4 = compare<"abc", "abcd">();
	std::cout << "compare('abc', 'abc'):  " << cmp1 << " (equal)\n";
	std::cout << "compare('abc', 'xyz'):  " << cmp2 << " (less)\n";
	std::cout << "compare('xyz', 'abc'):  " << cmp3 << " (greater)\n";
	std::cout << "compare('abc', 'abcd'): " << cmp4 << " (shorter)\n";
	// ===== CRC32 CHECKSUM =====
	std::cout << "\n=== CRC32 CHECKSUM ===\n";
	constexpr uint32_t crc1 = crc32<"Hello World">();
	constexpr uint32_t crc2 = crc32<"The quick brown fox jumps over the lazy dog">();
	constexpr uint32_t crc3 = crc32<"">();
	constexpr uint32_t crc4 = crc32<"123456789">();
	std::cout << "crc32('Hello World'):          0x" << std::hex << crc1 << std::dec << "\n";
	std::cout << "crc32('The quick brown...'):   0x" << std::hex << crc2 << std::dec << "\n";
	std::cout << "crc32(''):                     0x" << std::hex << crc3 << std::dec << "\n";
	std::cout << "crc32('123456789'):            0x" << std::hex << crc4 << std::dec << "\n";

	// ===== SHA256 HASH =====
	std::cout << "\n=== SHA256 HASH ===\n";
	constexpr auto sha256_1 = sha256<"Hello World">::value;
	constexpr auto sha256_2 = sha256<"">::value;
	constexpr auto sha256_3 = sha256<"abc">::value;

	std::cout << "sha256('Hello World'): ";
	for (int i = 0; i < 32; ++i)
	{
		if (sha256_1[i] < 16)
			std::cout << "0";
		std::cout << std::hex << static_cast<int>(sha256_1[i]);
	}
	std::cout << std::dec << "\n";

	std::cout << "sha256(''):            ";
	for (int i = 0; i < 32; ++i)
	{
		if (sha256_2[i] < 16)
			std::cout << "0";
		std::cout << std::hex << static_cast<int>(sha256_2[i]);
	}
	std::cout << std::dec << "\n";

	std::cout << "sha256('abc'):         ";
	for (int i = 0; i < 32; ++i)
	{
		if (sha256_3[i] < 16)
			std::cout << "0";
		std::cout << std::hex << static_cast<int>(sha256_3[i]);
	}
	std::cout << std::dec << "\n";

	// ===== SHA512 HASH =====
	std::cout << "\n=== SHA512 HASH ===\n";
	constexpr auto sha512_1 = sha512<"Hello World">::value;
	constexpr auto sha512_2 = sha512<"">::value;

	std::cout << "sha512('Hello World'):\n  ";
	for (int i = 0; i < 64; ++i)
	{
		if (sha512_1[i] < 16)
			std::cout << "0";
		std::cout << std::hex << static_cast<int>(sha512_1[i]);
		if (i == 31)
			std::cout << "\n  ";
	}
	std::cout << std::dec << "\n";

	std::cout << "sha512(''):\n  ";
	for (int i = 0; i < 64; ++i)
	{
		if (sha512_2[i] < 16)
			std::cout << "0";
		std::cout << std::hex << static_cast<int>(sha512_2[i]);
		if (i == 31)
			std::cout << "\n  ";
	}
	std::cout << std::dec << "\n";

	// ===== COMPLEX CHAINING EXAMPLES =====
	std::cout << "\n=== COMPLEX CHAINING EXAMPLES ===\n";
	constexpr auto chain1 = to_upper<trim<"  hello world  ">::fwd>::c_str();
	constexpr auto chain2 = reverse<to_upper<"hello">::fwd>::c_str();
	constexpr auto chain3 = replace_all<to_lower<"HELLO_WORLD_TEST">::fwd, "_", " ">::c_str();
	constexpr auto chain4 = trim<left<"  Hello World  ", 10>::fwd>::c_str();

	std::cout << "to_upper(trim('  hello world  ')):            '" << chain1 << "'\n";
	std::cout << "reverse(to_upper('hello')):                   '" << chain2 << "'\n";
	std::cout << "replace_all(to_lower('HELLO_WORLD_TEST')):    '" << chain3 << "'\n";
	std::cout << "trim(left('  Hello World  ', 10)):            '" << chain4 << "'\n";

	// ===== CHAINING OPERATIONS =====
	std::cout << "\n=== CHAINING OPERATIONS ===\n";
	std::cout << "to_upper(trim('  hello  ')):      '" << to_upper<trim<"  hello  ">::fwd>::c_str() << "'\n";
	std::cout << "reverse(to_upper('hello')):       '" << reverse<to_upper<"hello">::fwd>::c_str() << "'\n";
	std::cout << "trim(left('  Hello World  ', 10)): '" << trim<left<"  Hello World  ", 10>::fwd>::c_str() << "'\n";

	// ===== COMPILE-TIME VERIFICATION =====
	std::cout << "\n=== COMPILE-TIME VERIFICATION ===\n";

	static_assert(basename<"/usr/local/bin/myprogram">::storage.data[0] == 'm');
	static_assert(to_lower<"ABC">::storage.data[0] == 'a');
	static_assert(to_upper<"xyz">::storage.data[0] == 'X');
	static_assert(starts_with<"Hello", "Hel">());
	static_assert(ends_with<"World", "ld">());
	static_assert(contains<"Hello World", "lo W">());
	static_assert(compare<"abc", "abc">() == 0);
	static_assert(at<"Test", 0>() == 'T');
	static_assert(crc32<"123456789">() == 0xCBF43926);
	static_assert(to_upper<u8"abc">::storage.data[0] == u8'A');
	static_assert(to_upper<L"wide">::storage.data[0] == L'W');
	static_assert(reverse<"abc">::storage.data[0] == 'c');
	static_assert(trim<"  spaces  ">::view().size() == 6);
	static_assert(to_upper<u"utf16">::storage.data[0] == u'U');
	static_assert(to_upper<U"utf32">::storage.data[0] == U'U');

	// ===== COMPILE-TIME VERIFICATION =====
	std::cout << "\n=== ADDITIONS ===\n";

	// SHA256 - returns a ByteStore<FixedBytes<32>>
	using hash = ct_str::sha256<"Hello, World!">;

	// Access raw bytes
	const uint8_t* bytes = hash::value;
	std::cout << "Size: " << hash::size() << " bytes\n";  // 32

	// Get hex string representation
	std::cout << "SHA256: " << hash::hex() << "\n";
	// Output: dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f

	// SHA512 - returns a ByteStore<FixedBytes<64>>
	using hash512 = ct_str::sha512<"Hello, World!">;
	std::cout << "SHA512: " << hash512::hex() << "\n";

	// Compare hashes at compile time
	static_assert(ct_str::sha256<"test">::fwd != ct_str::sha256<"Test">::fwd);

	// Path operations - filename extraction
	std::cout << "=== Path Operations ===" << std::endl;
	std::cout << "Filename (Unix): " << ct_str::filename<"/usr/local/bin/program.exe">::value << std::endl;
	std::cout << "Filename (Windows): " << ct_str::filename<"C:\\Users\\Name\\file.txt">::value << std::endl;
	std::cout << "Filename (no path): " << ct_str::filename<"document.pdf">::value << std::endl;
	std::cout << std::endl;

	// Stem and extension
	std::cout << "=== Stem and Extension ===" << std::endl;
	std::cout << "Stem: " << ct_str::stem<"/path/to/file.txt">::value << std::endl;
	std::cout << "Extension: " << ct_str::extension<"/path/to/file.txt">::value << std::endl;
	std::cout << "Stem (no ext): " << ct_str::stem<"/path/to/README">::value << std::endl;
	std::cout << "Extension (no ext): " << ct_str::extension<"/path/to/README">::value << std::endl;
	std::cout << "Stem (multiple dots): " << ct_str::stem<"archive.tar.gz">::value << std::endl;
	std::cout << "Extension (multiple dots): " << ct_str::extension<"archive.tar.gz">::value << std::endl;
	std::cout << std::endl;

	// Path manipulation
	std::cout << "=== Path Manipulation ===" << std::endl;
	std::cout << "Remove filename: " << ct_str::remove_filename<"/usr/local/bin/program">::value << std::endl;
	std::cout << "Replace filename: " << ct_str::replace_filename<"/usr/bin/old", "new">::value << std::endl;
	std::cout << "Replace extension: " << ct_str::replace_extension<"file.txt", ".cpp">::value << std::endl;
	std::cout << "Replace extension (add): " << ct_str::replace_extension<"Makefile", ".bak">::value << std::endl;
	std::cout << "Replace extension (remove): " << ct_str::replace_extension<"file.txt", "">::value << std::endl;
	std::cout << std::endl;

	// Path queries - has_* functions
	std::cout << "=== Path Query Functions ===" << std::endl;
	constexpr auto unix_path = "/usr/local/bin/program.exe";
	constexpr auto win_path	 = "C:\\Users\\Name\\file.txt";
	constexpr auto rel_path	 = "docs/readme.md";
	constexpr auto no_ext	 = "Makefile";

	std::cout << "has_root_path ('" << unix_path << "'): " << ct_str::has_root_path<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << "has_root_name ('" << win_path << "'): " << ct_str::has_root_name<"C:\\Users\\Name\\file.txt">()
			  << std::endl;
	std::cout << "has_root_directory ('" << unix_path
			  << "'): " << ct_str::has_root_directory<"/usr/local/bin/program.exe">() << std::endl;
	std::cout << "has_relative_path ('" << rel_path << "'): " << ct_str::has_relative_path<"docs/readme.md">()
			  << std::endl;
	std::cout << "has_parent_path ('" << unix_path << "'): " << ct_str::has_parent_path<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << "has_filename ('" << unix_path << "'): " << ct_str::has_filename<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << "has_stem ('" << unix_path << "'): " << ct_str::has_stem<"/usr/local/bin/program.exe">() << std::endl;
	std::cout << "has_extension ('" << unix_path << "'): " << ct_str::has_extension<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << "has_extension ('" << no_ext << "'): " << ct_str::has_extension<"Makefile">() << std::endl;
	std::cout << std::endl;

	// Path type queries
	std::cout << "=== Path Type Queries ===" << std::endl;
	std::cout << "is_absolute ('" << unix_path << "'): " << ct_str::is_absolute<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << "is_absolute ('" << win_path << "'): " << ct_str::is_absolute<"C:\\Users\\Name\\file.txt">()
			  << std::endl;
	std::cout << "is_relative ('" << rel_path << "'): " << ct_str::is_relative<"docs/readme.md">() << std::endl;
	std::cout << "is_relative ('" << unix_path << "'): " << ct_str::is_relative<"/usr/local/bin/program.exe">()
			  << std::endl;
	std::cout << std::endl;

	// Backward compatibility
	std::cout << "=== Backward Compatibility ===" << std::endl;
	std::cout << "basename (legacy): " << ct_str::basename<"/path/to/file.txt">::value << std::endl;

	// ===== COMPILE-TIME VERIFICATION =====
	std::cout << "\n=== SUMMARY ===\n";

	std::cout << "(+) All static_assert checks passed!\n";
	std::cout << "(+) Works with char, char8_t, wchar_t, char16_t, char32_t!\n";

	std::cout << "\n========================================\n";

	return 0;
}
