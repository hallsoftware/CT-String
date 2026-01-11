/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <iostream>
#include <unordered_map>

// Compile-time configuration system using ct_str
template <ct_str::FixedString Key>
struct ConfigEntry
{
	static constexpr auto key  = ct_str::StringStore<Key>();
	static constexpr auto hash = ct_str::crc32<Key>();

	template <typename T>
	static void set(T value)
	{
		get_storage()[hash] = value;
	}

	template <typename T>
	static T get()
	{
		return get_storage()[hash];
	}

private:
	static std::unordered_map<uint32_t, int>& get_storage()
	{
		static std::unordered_map<uint32_t, int> storage;
		return storage;
	}
};

// Define configuration keys at compile time
using MaxConnections = ConfigEntry<"max_connections">;
using Timeout		 = ConfigEntry<"timeout_seconds">;
using BufferSize	 = ConfigEntry<"buffer_size">;
using LogLevel		 = ConfigEntry<"log_level">;

int main()
{
	std::cout << "========================================\n";
	std::cout << "   SIMPLE CONFIGURATION KEY EXAMPLE\n";
	std::cout << "========================================\n\n";

	// Configuration keys are compile-time constants
	std::cout << "=== Compile-Time Key Information ===\n";
	std::cout << "MaxConnections key:  '" << MaxConnections::key.view() << "'\n";
	std::cout << "MaxConnections hash: 0x" << std::hex << MaxConnections::hash << std::dec << "\n\n";

	std::cout << "Timeout key:         '" << Timeout::key.view() << "'\n";
	std::cout << "Timeout hash:        0x" << std::hex << Timeout::hash << std::dec << "\n\n";

	// Set configuration values
	std::cout << "=== Setting Configuration Values ===\n";
	MaxConnections::set(100);
	Timeout::set(30);
	BufferSize::set(8192);
	LogLevel::set(2);

	std::cout << "Configuration values set.\n\n";

	// Retrieve configuration values
	std::cout << "=== Retrieving Configuration Values ===\n";
	std::cout << "max_connections:  " << MaxConnections::get<int>() << "\n";
	std::cout << "timeout_seconds:  " << Timeout::get<int>() << " seconds\n";
	std::cout << "buffer_size:      " << BufferSize::get<int>() << " bytes\n";
	std::cout << "log_level:        " << LogLevel::get<int>() << "\n\n";

	// Compile-time key comparison
	std::cout << "=== Compile-Time Key Comparison ===\n";
	static_assert(MaxConnections::hash != Timeout::hash, "Different keys should have different hashes");
	static_assert(ConfigEntry<"max_connections">::hash == MaxConnections::hash, "Same key should have same hash");
	std::cout << "Key hashes are unique and deterministic!\n\n";

	// Benefits of compile-time keys
	std::cout << "=== Benefits ===\n";
	std::cout << "- Keys are validated at compile time\n";
	std::cout << "- No runtime string hashing overhead\n";
	std::cout << "- Typos in key names cause compile errors\n";
	std::cout << "- Keys can be used in constexpr contexts\n";

	return 0;
}