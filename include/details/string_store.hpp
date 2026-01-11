/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#pragma once

#include "fixed_string.hpp"
#include <cstddef>
#include <string_view>

namespace ct_str
{

// === THE CANONICAL PROVIDER ===
template <FixedString Str>
struct StringStore
{
	using CharT					   = std::remove_cvref_t<decltype(Str.data[0])>;
	using value_type			   = CharT;
	static constexpr std::size_t N = sizeof(Str.data) / sizeof(CharT);

	static constexpr struct Storage
	{
		CharT data[N];
		consteval Storage()
			: data{}
		{
			for (std::size_t i = 0; i < N; ++i)
				data[i] = Str.data[i];
		}
	} storage{};

	static constexpr auto						   fwd	 = Str;
	static constexpr const CharT*				   value = storage.data;
	static constexpr const CharT*				   c_str() { return value; }
	static constexpr std::basic_string_view<CharT> view() { return {value, N > 0 ? N - 1 : 0}; }
};

}  // namespace ct_str