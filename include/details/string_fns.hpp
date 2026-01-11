/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str. hpp for full license text.
*/

#pragma once

#include "fixed_string.hpp"
#include "string_store.hpp"
#include <cstddef>

namespace ct_str
{

// === HELPER FUNCTIONS FOR SIZE CALCULATION ===

template <FixedString Str>
consteval std::size_t find_first_non_space()
{
	using CharT = std::remove_cvref_t<decltype(Str.data[0])>;
	for (std::size_t i = 0; i < Str.size(); ++i)
	{
		CharT c = Str[i];
		if (c != CharT{' '} && c != CharT{'\t'} && c != CharT{'\n'} && c != CharT{'\r'})
			return i;
	}
	return Str.size();
}

template <FixedString Str>
consteval std::size_t find_last_non_space()
{
	using CharT = std::remove_cvref_t<decltype(Str.data[0])>;
	for (std::size_t i = Str.size(); i > 0; --i)
	{
		CharT c = Str[i - 1];
		if (c != CharT{' '} && c != CharT{'\t'} && c != CharT{'\n'} && c != CharT{'\r'})
			return i;
	}
	return 0;
}

template <FixedString Str, FixedString Pattern>
consteval std::size_t find_first_occurrence()
{
	constexpr std::size_t str_len = Str.size();
	constexpr std::size_t pat_len = Pattern.size();

	if (pat_len == 0 || pat_len > str_len)
		return str_len;

	for (std::size_t i = 0; i <= str_len - pat_len; ++i)
	{
		bool match = true;
		for (std::size_t j = 0; j < pat_len; ++j)
		{
			if (Str[i + j] != Pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
			return i;
	}
	return str_len;
}

template <FixedString Str, FixedString Pattern>
consteval std::size_t count_occurrences()
{
	constexpr std::size_t str_len = Str.size();
	constexpr std::size_t pat_len = Pattern.size();

	if (pat_len == 0)
		return 0;

	std::size_t count = 0;
	std::size_t pos	  = 0;
	while (pos <= str_len - pat_len)
	{
		bool match = true;
		for (std::size_t j = 0; j < pat_len; ++j)
		{
			if (Str[pos + j] != Pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			++count;
			pos += pat_len;
		}
		else
		{
			++pos;
		}
	}
	return count;
}

template <FixedString Str, FixedString Pattern, std::size_t N>
consteval std::size_t count_n_occurrences()
{
	constexpr std::size_t str_len = Str.size();
	constexpr std::size_t pat_len = Pattern.size();

	if (pat_len == 0)
		return 0;

	std::size_t count = 0;
	std::size_t pos	  = 0;
	while (pos <= str_len - pat_len && count < N)
	{
		bool match = true;
		for (std::size_t j = 0; j < pat_len; ++j)
		{
			if (Str[pos + j] != Pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			++count;
			pos += pat_len;
		}
		else
		{
			++pos;
		}
	}
	return count;
}

// === TRANSFORMATION LOGIC FUNCTIONS ===

template <FixedString Str, std::size_t Start, std::size_t Length>
consteval auto substr_logic()
{
	using CharT						   = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t str_len	   = Str.size();
	constexpr std::size_t actual_start = (Start < str_len) ? Start : str_len;
	constexpr std::size_t max_len	   = str_len - actual_start;
	constexpr std::size_t actual_len   = (Length < max_len) ? Length : max_len;

	CharT buf[actual_len + 1]{};
	for (std::size_t i = 0; i < actual_len; ++i)
		buf[i] = Str[actual_start + i];

	return FixedString<CharT, actual_len + 1>(buf, actual_len);
}

template <FixedString Str>
consteval auto to_upper_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t N	  = sizeof(Str.data) / sizeof(CharT);
	constexpr std::size_t len = Str.size();
	CharT				  buf[N]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		CharT c = Str[i];
		// Only works for ASCII-like characters
		buf[i] = (c >= CharT{'a'} && c <= CharT{'z'}) ? static_cast<CharT>(c - 32) : c;
	}
	return FixedString<CharT, N>(buf, len);
}

template <FixedString Str>
consteval auto to_lower_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t N	  = sizeof(Str.data) / sizeof(CharT);
	constexpr std::size_t len = Str.size();
	CharT				  buf[N]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		CharT c = Str[i];
		buf[i]	= (c >= CharT{'A'} && c <= CharT{'Z'}) ? static_cast<CharT>(c + 32) : c;
	}
	return FixedString<CharT, N>(buf, len);
}

template <FixedString Str>
consteval auto reverse_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t N	  = sizeof(Str.data) / sizeof(CharT);
	constexpr std::size_t len = Str.size();
	CharT				  buf[N]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		buf[i] = Str[len - 1 - i];
	}
	return FixedString<CharT, N>(buf, len);
}

template <FixedString Str, std::size_t NChars>
consteval auto left_logic()
{
	using CharT						 = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t len		 = Str.size();
	constexpr std::size_t actual_len = (NChars < len) ? NChars : len;

	CharT buf[actual_len + 1]{};
	for (std::size_t i = 0; i < actual_len; ++i)
	{
		buf[i] = Str[i];
	}
	return FixedString<CharT, actual_len + 1>(buf, actual_len);
}

template <FixedString Str, std::size_t NChars>
consteval auto right_logic()
{
	using CharT						 = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t len		 = Str.size();
	constexpr std::size_t actual_len = (NChars < len) ? NChars : len;
	constexpr std::size_t start		 = len - actual_len;

	CharT buf[actual_len + 1]{};
	for (std::size_t i = 0; i < actual_len; ++i)
	{
		buf[i] = Str[start + i];
	}
	return FixedString<CharT, actual_len + 1>(buf, actual_len);
}

template <FixedString... Strs>
consteval auto append_logic()
{
	using CharT					= std::remove_cvref_t<decltype((Strs.data[0], ...))>;
	constexpr std::size_t total = (Strs.size() + ...);
	CharT				  buf[total + 1]{};
	std::size_t			  offset = 0;

	auto append_one = [&]<FixedString S>() {
		for (std::size_t i = 0; i < S.size(); ++i)
		{
			buf[offset++] = S[i];
		}
	};
	(append_one.template operator()<Strs>(), ...);

	return FixedString<CharT, total + 1>(buf, total);
}

template <FixedString Str>
consteval auto trim_left_logic()
{
	using CharT					= std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t start = find_first_non_space<Str>();
	constexpr std::size_t len	= Str.size() - start;

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		buf[i] = Str[start + i];
	}
	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Str>
consteval auto trim_right_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t end = find_last_non_space<Str>();

	CharT buf[end + 1]{};
	for (std::size_t i = 0; i < end; ++i)
	{
		buf[i] = Str[i];
	}
	return FixedString<CharT, end + 1>(buf, end);
}

template <FixedString Str>
consteval auto trim_logic()
{
	using CharT					= std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t start = find_first_non_space<Str>();
	constexpr std::size_t end	= find_last_non_space<Str>();
	constexpr std::size_t len	= (end > start) ? (end - start) : 0;

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		buf[i] = Str[start + i];
	}
	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Str, FixedString Pattern, FixedString Replacement>
consteval auto replace_logic()
{
	using CharT						 = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t str_len	 = Str.size();
	constexpr std::size_t pat_len	 = Pattern.size();
	constexpr std::size_t rep_len	 = Replacement.size();
	constexpr std::size_t pos		 = find_first_occurrence<Str, Pattern>();
	constexpr std::size_t result_len = (pos < str_len) ? (str_len - pat_len + rep_len) : str_len;

	CharT buf[result_len + 1]{};

	if (pos < str_len)
	{
		// Copy before pattern
		for (std::size_t i = 0; i < pos; ++i)
			buf[i] = Str[i];
		// Copy replacement
		for (std::size_t i = 0; i < rep_len; ++i)
			buf[pos + i] = Replacement[i];
		// Copy after pattern
		for (std::size_t i = pos + pat_len; i < str_len; ++i)
		{
			buf[i - pat_len + rep_len] = Str[i];
		}
	}
	else
	{
		// Pattern not found, copy original
		for (std::size_t i = 0; i < str_len; ++i)
			buf[i] = Str[i];
	}

	return FixedString<CharT, result_len + 1>(buf, result_len);
}

template <FixedString Str, FixedString Pattern, FixedString Replacement>
consteval auto replace_all_logic()
{
	using CharT						 = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t str_len	 = Str.size();
	constexpr std::size_t pat_len	 = Pattern.size();
	constexpr std::size_t rep_len	 = Replacement.size();
	constexpr std::size_t count		 = count_occurrences<Str, Pattern>();
	constexpr std::size_t result_len = str_len - (count * pat_len) + (count * rep_len);

	CharT buf[result_len + 1]{};

	std::size_t src_pos = 0;
	std::size_t dst_pos = 0;

	while (src_pos < str_len)
	{
		bool match = false;
		if (pat_len > 0 && src_pos <= str_len - pat_len)
		{
			match = true;
			for (std::size_t j = 0; j < pat_len; ++j)
			{
				if (Str[src_pos + j] != Pattern[j])
				{
					match = false;
					break;
				}
			}
		}

		if (match)
		{
			for (std::size_t i = 0; i < rep_len; ++i)
			{
				buf[dst_pos++] = Replacement[i];
			}
			src_pos += pat_len;
		}
		else
		{
			buf[dst_pos++] = Str[src_pos++];
		}
	}

	return FixedString<CharT, result_len + 1>(buf, result_len);
}

template <FixedString Str, FixedString Pattern, FixedString Replacement, std::size_t N>
consteval auto replace_n_logic()
{
	using CharT						 = std::remove_cvref_t<decltype(Str.data[0])>;
	constexpr std::size_t str_len	 = Str.size();
	constexpr std::size_t pat_len	 = Pattern.size();
	constexpr std::size_t rep_len	 = Replacement.size();
	constexpr std::size_t count		 = count_n_occurrences<Str, Pattern, N>();
	constexpr std::size_t result_len = str_len - (count * pat_len) + (count * rep_len);

	CharT buf[result_len + 1]{};

	std::size_t src_pos		 = 0;
	std::size_t dst_pos		 = 0;
	std::size_t replacements = 0;

	while (src_pos < str_len)
	{
		bool match = false;
		if (pat_len > 0 && src_pos <= str_len - pat_len && replacements < N)
		{
			match = true;
			for (std::size_t j = 0; j < pat_len; ++j)
			{
				if (Str[src_pos + j] != Pattern[j])
				{
					match = false;
					break;
				}
			}
		}

		if (match)
		{
			for (std::size_t i = 0; i < rep_len; ++i)
			{
				buf[dst_pos++] = Replacement[i];
			}
			src_pos += pat_len;
			++replacements;
		}
		else
		{
			buf[dst_pos++] = Str[src_pos++];
		}
	}

	return FixedString<CharT, result_len + 1>(buf, result_len);
}

// === NON-TRANSFORMATIVE HELPERS (CONSTEVAL VALUES) ===

template <FixedString Str, std::size_t Pos>
consteval auto at()
{
	static_assert(Pos < Str.size(), "at(): position out of bounds");
	return Str[Pos];
}

template <FixedString Str, FixedString Pattern, std::size_t StartPos = 0>
consteval std::size_t find()
{
	constexpr std::size_t str_len = Str.size();
	constexpr std::size_t pat_len = Pattern.size();
	if (pat_len == 0)
		return StartPos;
	if (pat_len > str_len || StartPos >= str_len)
		return str_len;

	for (std::size_t i = StartPos; i <= str_len - pat_len; ++i)
	{
		bool match = true;
		for (std::size_t j = 0; j < pat_len; ++j)
		{
			if (Str[i + j] != Pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
			return i;
	}
	return static_cast<std::size_t>(-1);
}

template <FixedString Str, auto Ch, std::size_t StartPos = 0>
consteval std::size_t find_char()
{
	constexpr std::size_t str_len = Str.size();
	for (std::size_t i = StartPos; i < str_len; ++i)
	{
		if (Str[i] == Ch)
			return i;
	}
	return static_cast<std::size_t>(-1);
}

template <FixedString Str, FixedString Pattern>
consteval std::size_t rfind()
{
	constexpr std::size_t str_len = Str.size();
	constexpr std::size_t pat_len = Pattern.size();
	if (pat_len == 0)
		return static_cast<std::size_t>(-1);
	if (pat_len > str_len)
		return static_cast<std::size_t>(-1);

	for (std::size_t i = str_len - pat_len + 1; i > 0; --i)
	{
		bool match = true;
		for (std::size_t j = 0; j < pat_len; ++j)
		{
			if (Str[i - 1 + j] != Pattern[j])
			{
				match = false;
				break;
			}
		}
		if (match)
			return i - 1;
	}
	return static_cast<std::size_t>(-1);
}

template <FixedString Str, auto Ch>
consteval std::size_t rfind_char()
{
	for (std::size_t i = Str.size(); i > 0; --i)
	{
		if (Str[i - 1] == Ch)
			return i - 1;
	}
	return static_cast<std::size_t>(-1);
}

template <FixedString Str, FixedString Pattern>
consteval bool starts_with()
{
	if (Pattern.size() > Str.size())
		return false;
	for (std::size_t i = 0; i < Pattern.size(); ++i)
	{
		if (Str[i] != Pattern[i])
			return false;
	}
	return true;
}

template <FixedString Str, FixedString Pattern>
consteval bool ends_with()
{
	if (Pattern.size() > Str.size())
		return false;
	std::size_t offset = Str.size() - Pattern.size();
	for (std::size_t i = 0; i < Pattern.size(); ++i)
	{
		if (Str[offset + i] != Pattern[i])
			return false;
	}
	return true;
}

template <FixedString Str, FixedString Pattern>
consteval bool contains()
{
	return find<Str, Pattern>() < Str.size();
}

template <FixedString Str1, FixedString Str2>
consteval int compare()
{
	std::size_t len1	= Str1.size();
	std::size_t len2	= Str2.size();
	std::size_t min_len = (len1 < len2) ? len1 : len2;
	for (std::size_t i = 0; i < min_len; ++i)
	{
		if (Str1[i] < Str2[i])
			return -1;
		if (Str1[i] > Str2[i])
			return 1;
	}
	return (len1 < len2) ? -1 : (len1 > len2 ? 1 : 0);
}

// === API ALIASES ===

template <FixedString Str, std::size_t Start, std::size_t Length>
using substr = StringStore<substr_logic<Str, Start, Length>()>;

template <FixedString Str>
using to_upper = StringStore<to_upper_logic<Str>()>;

template <FixedString Str>
using to_lower = StringStore<to_lower_logic<Str>()>;

template <FixedString Str>
using reverse = StringStore<reverse_logic<Str>()>;

template <FixedString Str, std::size_t NChars>
using left = StringStore<left_logic<Str, NChars>()>;

template <FixedString Str, std::size_t NChars>
using right = StringStore<right_logic<Str, NChars>()>;

template <FixedString... Strs>
using append = StringStore<append_logic<Strs...>()>;

template <FixedString Str>
using trim_left = StringStore<trim_left_logic<Str>()>;

template <FixedString Str>
using trim_right = StringStore<trim_right_logic<Str>()>;

template <FixedString Str>
using trim = StringStore<trim_logic<Str>()>;

template <FixedString Str, FixedString Pattern, FixedString Replacement>
using replace = StringStore<replace_logic<Str, Pattern, Replacement>()>;

template <FixedString Str, FixedString Pattern, FixedString Replacement>
using replace_all = StringStore<replace_all_logic<Str, Pattern, Replacement>()>;

template <FixedString Str, FixedString Pattern, FixedString Replacement, std::size_t N>
using replace_n = StringStore<replace_n_logic<Str, Pattern, Replacement, N>()>;

}  // namespace ct_str