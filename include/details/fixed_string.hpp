/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#pragma once

#include <compare>
#include <cstddef>

namespace ct_str
{

// Fixed-size character array templated on character type
template <typename CharT, std::size_t N>
struct FixedString
{
	CharT data[N]{};
	using value_type = CharT;

	consteval FixedString() = default;

	// Constructor for string literals
	consteval FixedString(const CharT (&str)[N])
	{
		for (std::size_t i = 0; i < N; ++i)
			data[i] = str[i];
	}

	// Constructor for copying from internal buffers
	consteval FixedString(const CharT* str, std::size_t len)
	{
		for (std::size_t i = 0; i < len; ++i)
			data[i] = str[i];
		data[len] = CharT{};
	}

	constexpr std::size_t size() const { return N > 0 ? N - 1 : 0; }
	constexpr std::size_t length() const { return N > 0 ? N - 1 : 0; }
	constexpr CharT		  operator[](std::size_t i) const { return data[i]; }

	auto operator<=>(const FixedString&) const = delete;
};

// Deduction guides for different character types
template <std::size_t N>
FixedString(const char (&str)[N]) -> FixedString<char, N>;

template <std::size_t N>
FixedString(const char8_t (&str)[N]) -> FixedString<char8_t, N>;

template <std::size_t N>
FixedString(const wchar_t (&str)[N]) -> FixedString<wchar_t, N>;

template <std::size_t N>
FixedString(const char16_t (&str)[N]) -> FixedString<char16_t, N>;

template <std::size_t N>
FixedString(const char32_t (&str)[N]) -> FixedString<char32_t, N>;

}  // namespace ct_str