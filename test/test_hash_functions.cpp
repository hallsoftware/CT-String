/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include <cstring>
#include <ostream>
#include "doctest.h"
#include "ct_str.hpp"

TEST_SUITE("Hash Functions")
{
	TEST_CASE("CRC32")
	{
		// Known test vectors
		static_assert(ct_str::crc32<"">() == 0x00000000);
		static_assert(ct_str::crc32<"123456789">() == 0xCBF43926);
		CHECK(ct_str::crc32<"">() == 0x00000000);
		CHECK(ct_str::crc32<"123456789">() == 0xCBF43926);

		// Basic strings
		constexpr uint32_t crc1 = ct_str::crc32<"Hello World">();
		constexpr uint32_t crc2 = ct_str::crc32<"Hello World">();
		static_assert(crc1 == crc2);  // Same input = same output
		CHECK(crc1 == crc2);

		// Different strings
		constexpr uint32_t crc3 = ct_str::crc32<"Hello">();
		constexpr uint32_t crc4 = ct_str::crc32<"World">();
		static_assert(crc3 != crc4);
		CHECK(crc3 != crc4);

		// Case sensitivity
		static_assert(ct_str::crc32<"hello">() != ct_str::crc32<"Hello">());

		// Long strings
		constexpr uint32_t long_crc = ct_str::crc32<"The quick brown fox jumps over the lazy dog">();
		CHECK(long_crc != 0);
	}

	TEST_CASE("SHA256")
	{
		// Basic hash
		using Hash1 = ct_str::sha256<"Hello World">;
		using Hash2 = ct_str::sha256<"Hello World">;

		// Size verification
		static_assert(Hash1::size() == 32);
		CHECK(Hash1::size() == 32);

		// Same input produces same hash
		static_assert(Hash1::fwd == Hash2::fwd);
		CHECK(std::memcmp(Hash1::value, Hash2::value, 32) == 0);

		// Different inputs produce different hashes
		using Hash3 = ct_str::sha256<"Different">;
		static_assert(Hash1::fwd != Hash3::fwd);
		CHECK(std::memcmp(Hash1::value, Hash3::value, 32) != 0);

		// Empty string
		using EmptyHash = ct_str::sha256<"">;
		static_assert(EmptyHash::size() == 32);

		// Known test vector for empty string
		// SHA256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
		using Empty = ct_str::sha256<"">;
		CHECK(std::string(Empty::hex()) == "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

		// Known test vector for "abc"
		// SHA256("abc") = ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad
		using ABC = ct_str::sha256<"abc">;
		CHECK(std::string(ABC::hex()) == "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");

		// Case sensitivity
		using LowerHash = ct_str::sha256<"hello">;
		using UpperHash = ct_str::sha256<"HELLO">;
		static_assert(LowerHash::fwd != UpperHash::fwd);
	}

	TEST_CASE("SHA512")
	{
		// Basic hash
		using Hash1 = ct_str::sha512<"Hello World">;
		using Hash2 = ct_str::sha512<"Hello World">;

		// Size verification
		static_assert(Hash1::size() == 64);
		CHECK(Hash1::size() == 64);

		// Same input produces same hash
		static_assert(Hash1::fwd == Hash2::fwd);
		CHECK(std::memcmp(Hash1::value, Hash2::value, 64) == 0);

		// Different inputs produce different hashes
		using Hash3 = ct_str::sha512<"Different">;
		static_assert(Hash1::fwd != Hash3::fwd);
		CHECK(std::memcmp(Hash1::value, Hash3::value, 64) != 0);

		// Empty string
		using EmptyHash = ct_str::sha512<"">;
		static_assert(EmptyHash::size() == 64);

		// Known test vector for empty string
		using Empty = ct_str::sha512<"">;
		CHECK(
			std::string(Empty::hex()) ==
			"cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e");

		// Case sensitivity
		using LowerHash = ct_str::sha512<"hello">;
		using UpperHash = ct_str::sha512<"HELLO">;
		static_assert(LowerHash::fwd != UpperHash::fwd);
	}

	TEST_CASE("Hash comparison")
	{
		// CRC32 determinism
		static_assert(ct_str::crc32<"test">() == ct_str::crc32<"test">());
		static_assert(ct_str::crc32<"test">() != ct_str::crc32<"Test">());

		// SHA256 determinism
		static_assert(ct_str::sha256<"test">::fwd == ct_str::sha256<"test">::fwd);
		static_assert(ct_str::sha256<"test">::fwd != ct_str::sha256<"Test">::fwd);

		// SHA512 determinism
		static_assert(ct_str::sha512<"test">::fwd == ct_str::sha512<"test">::fwd);
		static_assert(ct_str::sha512<"test">::fwd != ct_str::sha512<"Test">::fwd);
	}

	TEST_CASE("Long string hashing")
	{
		using long_string =
			ct_str::StringStore<"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor "
								"incididunt ut labore et dolore magna aliqua.">;

		// CRC32
		constexpr uint32_t long_crc = ct_str::crc32<long_string::fwd>();
		CHECK(long_crc != 0);

		// SHA256
		using LongSHA256 = ct_str::sha256<long_string::fwd>;
		static_assert(LongSHA256::size() == 32);

		// SHA512
		using LongSHA512 = ct_str::sha512<long_string::fwd>;
		static_assert(LongSHA512::size() == 64);
	}
}