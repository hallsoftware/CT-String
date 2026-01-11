/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iomanip>
#include <iostream>

int main()
{
	using namespace ct_str;

	std::cout << "========================================\n";
	std::cout << "       BASIC HASH USAGE EXAMPLES\n";
	std::cout << "========================================\n\n";

	// === CRC32 ===
	std::cout << "=== CRC32 Checksums ===\n";
	constexpr uint32_t crc1 = crc32<"Hello World">();
	constexpr uint32_t crc2 = crc32<"The quick brown fox jumps over the lazy dog">();
	constexpr uint32_t crc3 = crc32<"">();
	constexpr uint32_t crc4 = crc32<"123456789">();

	std::cout << "crc32('Hello World'):       0x" << std::hex << std::setw(8) << std::setfill('0') << crc1 << std::dec
			  << "\n";
	std::cout << "crc32('The quick brown...'): 0x" << std::hex << std::setw(8) << std::setfill('0') << crc2 << std::dec
			  << "\n";
	std::cout << "crc32(''):                  0x" << std::hex << std::setw(8) << std::setfill('0') << crc3 << std::dec
			  << "\n";
	std::cout << "crc32('123456789'):         0x" << std::hex << std::setw(8) << std::setfill('0') << crc4 << std::dec
			  << "\n\n";

	// Verify known CRC32 test vector
	static_assert(crc32<"123456789">() == 0xCBF43926, "CRC32 test vector failed!");

	// === SHA256 ===
	std::cout << "=== SHA256 Hashes ===\n";

	using hash1 = sha256<"Hello World">;
	using hash2 = sha256<"">;
	using hash3 = sha256<"abc">;

	std::cout << "sha256('Hello World'):\n  " << hash1::hex() << "\n\n";
	std::cout << "sha256(''):\n  " << hash2::hex() << "\n\n";
	std::cout << "sha256('abc'):\n  " << hash3::hex() << "\n\n";

	// Access raw bytes
	std::cout << "SHA256 hash size: " << hash1::size() << " bytes\n";
	std::cout << "First byte of sha256('abc'): 0x" << std::hex << std::setw(2) << std::setfill('0')
			  << static_cast<int>(hash3::value[0]) << std::dec << "\n\n";

	// === SHA512 ===
	std::cout << "=== SHA512 Hashes ===\n";

	using hash512_1 = sha512<"Hello World">;
	using hash512_2 = sha512<"">;
	using hash512_3 = sha512<"abc">;

	std::cout << "sha512('Hello World'):\n  " << hash512_1::hex() << "\n\n";
	std::cout << "sha512(''):\n  " << hash512_2::hex() << "\n\n";
	std::cout << "sha512('abc'):\n  " << hash512_3::hex() << "\n\n";

	std::cout << "SHA512 hash size: " << hash512_1::size() << " bytes\n\n";

	// === HASH COMPARISON ===
	std::cout << "=== Hash Comparison ===\n";
	static_assert(sha256<"test">::fwd != sha256<"Test">::fwd, "Different strings should have different hashes");
	static_assert(sha256<"test">::fwd == sha256<"test">::fwd, "Same strings should have identical hashes");
	std::cout << "Hash comparison works at compile time!\n";
	std::cout << "sha256('test') == sha256('test'):  true\n";
	std::cout << "sha256('test') == sha256('Test'):  false\n\n";

	// === PRACTICAL USE CASES ===
	std::cout << "=== Practical Use Cases ===\n\n";

	std::cout << "1. Compile-time file integrity checking:\n";
	std::cout << "   Expected: " << sha256<"expected_content">::hex() << "\n\n";

	std::cout << "2. Compile-time password hashing:\n";
	std::cout << "   Hash: " << sha256<"my_password">::hex() << "\n\n";

	std::cout << "3. Version tagging:\n";
	constexpr uint32_t version_hash = crc32<"v1.2.3">();
	std::cout << "   Version 'v1.2.3' CRC: 0x" << std::hex << std::setw(8) << std::setfill('0') << version_hash
			  << std::dec << "\n\n";

	std::cout << "4. Configuration verification:\n";
	using config_hash = sha256<"CONFIG_STRING">;
	std::cout << "   Config hash: " << config_hash::hex() << "\n\n";

	// === COMPILE-TIME VERIFICATION ===
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(crc32<"123456789">() == 0xCBF43926);
	static_assert(sha256<"abc">::size() == 32);
	static_assert(sha512<"abc">::size() == 64);
	std::cout << "All static assertions passed!\n\n";

	return 0;
}