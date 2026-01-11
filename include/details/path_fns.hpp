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

template <FixedString Path>
consteval std::size_t find_last_separator()
{
	for (std::size_t i = Path.size(); i > 0; --i)
	{
		if (Path[i - 1] == '/' || Path[i - 1] == '\\')
			return i;
	}
	return 0;
}

template <FixedString Path>
consteval std::size_t find_first_separator()
{
	for (std::size_t i = 0; i < Path.size(); ++i)
	{
		if (Path[i] == '/' || Path[i] == '\\')
			return i;
	}
	return Path.size();
}

template <FixedString Path>
consteval std::size_t find_last_dot()
{
	std::size_t last_sep = find_last_separator<Path>();
	for (std::size_t i = Path.size(); i > last_sep; --i)
	{
		if (Path[i - 1] == '.')
			return i - 1;
	}
	return Path.size();
}

template <FixedString Path>
consteval bool has_drive_letter()
{
	return Path.size() >= 2 && ((Path[0] >= 'A' && Path[0] <= 'Z') || (Path[0] >= 'a' && Path[0] <= 'z')) &&
		   Path[1] == ':';
}

// === filename ===

template <FixedString Path>
consteval auto filename_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t pos = find_last_separator<Path>();
	constexpr std::size_t len = Path.size() - pos;

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		buf[i] = Path[pos + i];
	}
	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Path>
using filename = StringStore<filename_logic<Path>()>;

// === stem ===

template <FixedString Path>
consteval auto stem_logic()
{
	using CharT					  = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t sep_pos = find_last_separator<Path>();
	constexpr std::size_t dot_pos = find_last_dot<Path>();

	constexpr std::size_t start = sep_pos;
	constexpr std::size_t end	= (dot_pos > sep_pos && dot_pos != Path.size()) ? dot_pos : Path.size();
	constexpr std::size_t len	= end - start;

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < len; ++i)
	{
		buf[i] = Path[start + i];
	}
	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Path>
using stem = StringStore<stem_logic<Path>()>;

// === extension ===

template <FixedString Path>
consteval auto extension_logic()
{
	using CharT					  = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t dot_pos = find_last_dot<Path>();
	constexpr std::size_t sep_pos = find_last_separator<Path>();

	if constexpr (dot_pos == Path.size() || dot_pos <= sep_pos)
	{
		return FixedString<CharT, 1>("", 0);
	}
	else
	{
		constexpr std::size_t len = Path.size() - dot_pos;
		CharT				  buf[len + 1]{};
		for (std::size_t i = 0; i < len; ++i)
		{
			buf[i] = Path[dot_pos + i];
		}
		return FixedString<CharT, len + 1>(buf, len);
	}
}

template <FixedString Path>
using extension = StringStore<extension_logic<Path>()>;

// === remove_filename ===

template <FixedString Path>
consteval auto remove_filename_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t pos = find_last_separator<Path>();

	CharT buf[pos + 1]{};
	for (std::size_t i = 0; i < pos; ++i)
	{
		buf[i] = Path[i];
	}
	return FixedString<CharT, pos + 1>(buf, pos);
}

template <FixedString Path>
using remove_filename = StringStore<remove_filename_logic<Path>()>;

// === replace_filename ===

template <FixedString Path, FixedString NewFilename>
consteval auto replace_filename_logic()
{
	using CharT				  = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t pos = find_last_separator<Path>();
	constexpr std::size_t len = pos + NewFilename.size();

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < pos; ++i)
	{
		buf[i] = Path[i];
	}
	for (std::size_t i = 0; i < NewFilename.size(); ++i)
	{
		buf[pos + i] = NewFilename[i];
	}
	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Path, FixedString NewFilename>
using replace_filename = StringStore<replace_filename_logic<Path, NewFilename>()>;

// === replace_extension ===

template <FixedString Path, FixedString NewExt>
consteval auto replace_extension_logic()
{
	using CharT					   = std::remove_cvref_t<decltype(Path.data[0])>;
	constexpr std::size_t dot_pos  = find_last_dot<Path>();
	constexpr std::size_t sep_pos  = find_last_separator<Path>();
	constexpr std::size_t base_len = (dot_pos > sep_pos && dot_pos != Path.size()) ? dot_pos : Path.size();

	constexpr bool		  needs_dot = NewExt.size() > 0 && NewExt[0] != '.';
	constexpr std::size_t len		= base_len + (needs_dot ? 1 : 0) + NewExt.size();

	CharT buf[len + 1]{};
	for (std::size_t i = 0; i < base_len; ++i)
	{
		buf[i] = Path[i];
	}

	std::size_t write_pos = base_len;
	if constexpr (needs_dot)
	{
		buf[write_pos++] = '.';
	}

	for (std::size_t i = 0; i < NewExt.size(); ++i)
	{
		buf[write_pos + i] = NewExt[i];
	}

	return FixedString<CharT, len + 1>(buf, len);
}

template <FixedString Path, FixedString NewExt>
using replace_extension = StringStore<replace_extension_logic<Path, NewExt>()>;

// === Query functions ===

template <FixedString Path>
consteval bool has_root_path()
{
	return has_drive_letter<Path>() || (Path.size() > 0 && (Path[0] == '/' || Path[0] == '\\'));
}

template <FixedString Path>
consteval bool has_root_name()
{
	return has_drive_letter<Path>();
}

template <FixedString Path>
consteval bool has_root_directory()
{
	if constexpr (has_drive_letter<Path>())
	{
		return Path.size() > 2 && (Path[2] == '/' || Path[2] == '\\');
	}
	else
	{
		return Path.size() > 0 && (Path[0] == '/' || Path[0] == '\\');
	}
}

template <FixedString Path>
consteval bool has_relative_path()
{
	constexpr std::size_t root_end =
		has_drive_letter<Path>() ? (has_root_directory<Path>() ? 3 : 2) : (has_root_directory<Path>() ? 1 : 0);
	return Path.size() > root_end;
}

// NOTE: Per cppreference.com (https://en.cppreference.com/w/cpp/filesystem/path/parent_path)
//       and the Godbolt online compiler, the parent path of a root path ('/') is the root path.
//       Therefore, has_parent_path returns true for root paths.
template <FixedString Path>
consteval bool has_parent_path()
{
	return find_last_separator<Path>() > 0;
}

template <FixedString Path>
consteval bool has_filename()
{
	constexpr std::size_t pos = find_last_separator<Path>();
	return pos < Path.size();
}

template <FixedString Path>
consteval bool has_stem()
{
	constexpr std::size_t sep_pos = find_last_separator<Path>();
	constexpr std::size_t dot_pos = find_last_dot<Path>();
	return sep_pos < Path.size() && (dot_pos == Path.size() || dot_pos > sep_pos);
}

template <FixedString Path>
consteval bool has_extension()
{
	constexpr std::size_t dot_pos = find_last_dot<Path>();
	constexpr std::size_t sep_pos = find_last_separator<Path>();
	return dot_pos != Path.size() && dot_pos > sep_pos;
}

template <FixedString Path>
consteval bool is_absolute()
{
	if constexpr (has_drive_letter<Path>())
	{
		return has_root_directory<Path>();
	}
	else
	{
		return Path.size() > 0 && (Path[0] == '/' || Path[0] == '\\');
	}
}

template <FixedString Path>
consteval bool is_relative()
{
	return !is_absolute<Path>();
}

// === Legacy alias for backward compatibility ===

template <FixedString Path>
using basename = filename<Path>;

}  // namespace ct_str