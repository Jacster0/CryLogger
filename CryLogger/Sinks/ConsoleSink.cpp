#include "ConsoleSink.h"
#include "../CLI/Console.h"

void ConsoleSink::Emit(std::string_view message, LogLevel lvl, const std::source_location& loc) noexcept {
	switch (lvl) {
	using enum LogLevel;

	case info:
		Console::SetTextColor(ConsoleColor::Green);
		break;
	case warning:
		Console::SetTextColor(ConsoleColor::Yellow);
		break;
	case error:
		Console::SetTextColor(ConsoleColor::Red);
		break;
	}

	Console::WriteLine(message);
	Console::SetTextColor(ConsoleColor::White);
}