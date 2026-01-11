/*
Copyright 2025 by Kevin Hall.
BSD-3-Clause License - See ct_str.hpp for full license text.
*/

#include "ct_str.hpp"
#include <chrono>
#include <iostream>
#include <source_location>

// Compile-time log message formatter
template <ct_str::FixedString Level, ct_str::FixedString Message>
struct LogEntry
{
	// Format: [LEVEL] Message (file:line)
	using formatted = ct_str::append<"[", Level, "] ", Message>;

	static constexpr auto level			= Level;
	static constexpr auto message		= ct_str::StringStore<Message>();
	static constexpr auto formatted_msg = formatted::c_str();
	static constexpr auto hash			= ct_str::crc32<Message>();
};

// Log level tags
using InfoTag  = ct_str::StringStore<ct_str::FixedString("INFO")>;
using WarnTag  = ct_str::StringStore<ct_str::FixedString("WARN")>;
using ErrorTag = ct_str::StringStore<ct_str::FixedString("ERROR")>;
using DebugTag = ct_str::StringStore<ct_str::FixedString("DEBUG")>;

// Compile-time log functions
template <ct_str::FixedString Message>
void log_info()
{
	using Entry = LogEntry<"INFO", Message>;
	std::cout << Entry::formatted_msg << "\n";
}

template <ct_str::FixedString Message>
void log_warn()
{
	using Entry = LogEntry<"WARN", Message>;
	std::cout << Entry::formatted_msg << "\n";
}

template <ct_str::FixedString Message>
void log_error()
{
	using Entry = LogEntry<"ERROR", Message>;
	std::cout << Entry::formatted_msg << "\n";
}

template <ct_str::FixedString Message>
void log_debug()
{
	using Entry = LogEntry<"DEBUG", Message>;
	std::cout << Entry::formatted_msg << "\n";
}

// Compile-time log message deduplication counter
template <ct_str::FixedString Message>
struct LogCounter
{
	static inline int count = 0;

	static void increment() { ++count; }

	static int get() { return count; }
};

int main()
{
	std::cout << "========================================\n";
	std::cout << "   INTERMEDIATE LOGGER EXAMPLE\n";
	std::cout << "========================================\n\n";

	// Basic logging
	std::cout << "=== Basic Logging ===\n";
	log_info<"Application started">();
	log_info<"Loading configuration">();
	log_warn<"Configuration file not found, using defaults">();
	log_error<"Failed to connect to database">();
	log_debug<"Connection attempt #1">();
	std::cout << "\n";

	// Log message hashing
	std::cout << "=== Log Message Hashing ===\n";
	using Msg1 = LogEntry<"INFO", "Application started">;
	using Msg2 = LogEntry<"ERROR", "Failed to connect to database">;

	std::cout << "Message 1: '" << Msg1::message.view() << "'\n";
	std::cout << "Hash:      0x" << std::hex << Msg1::hash << std::dec << "\n\n";

	std::cout << "Message 2: '" << Msg2::message.view() << "'\n";
	std::cout << "Hash:      0x" << std::hex << Msg2::hash << std::dec << "\n\n";

	// Message deduplication
	std::cout << "=== Message Deduplication ===\n";
	using repeated_msg = ct_str::StringStore<"Repeated log message">;

	for (int i = 0; i < 3; ++i)
	{
		LogCounter<repeated_msg::fwd>::increment();
		std::cout << "[INFO] " << repeated_msg::c_str() << " (occurrence #" << LogCounter<repeated_msg::fwd>::get()
				  << ")\n";
	}
	std::cout << "\n";

	// Compile-time log filtering
	std::cout << "=== Compile-Time Log Level Filtering ===\n";
#ifdef ENABLE_DEBUG_LOGS
	log_debug<"Debug logging is enabled">();
#else
	std::cout << "(Debug logs compiled out)\n";
#endif
	std::cout << "\n";

	// Log message chaining
	std::cout << "=== Log Message Composition ===\n";
	using ComponentName = ct_str::StringStore<ct_str::FixedString("DatabaseModule")>;
	using Action		= ct_str::StringStore<ct_str::FixedString("Connection established")>;
	using ComposedMsg	= ct_str::append<ComponentName::fwd, ": ", Action::fwd>;

	std::cout << "[INFO] " << ComposedMsg::c_str() << "\n\n";

	// Performance analysis
	std::cout << "=== Performance Benefits ===\n";
	std::cout << "- Log level tags deduplicated in binary\n";
	std::cout << "- Message formatting done at compile time\n";
	std::cout << "- No runtime string allocation\n";
	std::cout << "- Messages can be filtered at compile time\n";
	std::cout << "- Unique hashes enable fast log analysis\n\n";

	// Compile-time verification
	std::cout << "=== Compile-Time Verification ===\n";
	static_assert(LogEntry<"INFO", "test">::hash == ct_str::crc32<"test">());
	static_assert(ct_str::compare<LogEntry<"INFO", "msg">::level, "INFO">() == 0);
	std::cout << "All static assertions passed!\n\n";

	return 0;
}