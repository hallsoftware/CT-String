/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#pragma once

#include <cstddef>
#include <cstdint>

namespace ct_str
{

// Fixed-size byte array for compile-time byte data
template <std::size_t N>
struct FixedBytes
{
	uint8_t data[N]{};

	consteval FixedBytes() = default;

	consteval FixedBytes(const uint8_t (&arr)[N])
	{
		for (std::size_t i = 0; i < N; ++i)
			data[i] = arr[i];
	}

	consteval FixedBytes(const uint8_t* arr, std::size_t len)
	{
		for (std::size_t i = 0; i < len && i < N; ++i)
			data[i] = arr[i];
	}

	constexpr std::size_t size() const { return N; }
	constexpr uint8_t	  operator[](std::size_t i) const { return data[i]; }

	auto operator<=>(const FixedBytes&) const = default;
};

// Deduction guide
template <std::size_t N>
FixedBytes(const uint8_t (&)[N]) -> FixedBytes<N>;

// === THE CANONICAL BYTE PROVIDER ===
template <FixedBytes Bytes>
struct ByteStore
{
	static constexpr std::size_t N = sizeof(Bytes.data);

	static constexpr struct Storage
	{
		uint8_t data[N];
		consteval Storage()
			: data{}
		{
			for (std::size_t i = 0; i < N; ++i)
				data[i] = Bytes.data[i];
		}
	} storage{};

	static constexpr auto			fwd	  = Bytes;
	static constexpr const uint8_t* value = storage.data;
	static constexpr std::size_t	size() { return N; }

	// Convert to hex string at compile time
	static constexpr auto hex()
	{
		struct HexStorage
		{
			char data[N * 2 + 1]{};
			consteval HexStorage()
			{
				constexpr char hex_chars[] = "0123456789abcdef";
				for (std::size_t i = 0; i < N; ++i)
				{
					data[i * 2]		= hex_chars[(Bytes.data[i] >> 4) & 0x0F];
					data[i * 2 + 1] = hex_chars[Bytes.data[i] & 0x0F];
				}
				data[N * 2] = '\0';
			}
			static constexpr std::size_t size() { return N * 2; }
			static constexpr std::size_t length() { return N * 2; }
		};
		static constexpr HexStorage hex_storage{};
		return hex_storage.data;
	}
};

}  // namespace ct_str