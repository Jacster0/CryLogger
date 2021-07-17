#pragma once
#include <mutex>
#include <string>
#include <format>
#include <memory>
#include <unordered_map>
#include <source_location>

#include "LogLevels.h"
#include "../Sinks/Sink.h"

class Logger {
public:
	[[nodiscard]] static Logger& Get() noexcept;
	[[nodiscard]] static constexpr auto NewLine() noexcept { return std::endl<char, std::char_traits<char>>; }

	static void AttachSink(const std::shared_ptr<ISinkBase>& sink) noexcept;
	static void RemoveSink(const std::string_view name) noexcept;

	void Log(LogLevel lvl, const std::source_location& loc, auto&&... args) noexcept;
	void FormatLog(LogLevel lvl, std::string_view fmt, const std::source_location& loc, auto&&... args) noexcept;
private:
	Logger()                             = default;
	Logger(const Logger& rhs)            = delete;
	Logger& operator=(const Logger& rhs) = delete;
	Logger(Logger&& rhs)                 = delete;
	Logger& operator=(Logger&& rhs)      = delete;
	~Logger()                            = default;

	void InternalLog(LogLevel lvl, const std::source_location& loc, auto&&... args) const noexcept;
	void InternalFormatLog(LogLevel lvl, std::string_view fmt, const std::source_location& loc, auto&&... args) const noexcept;

	std::mutex m_loggingMutex;
	static std::mutex m_sinkMutex;
	std::unordered_map<std::string_view, std::shared_ptr<ISinkBase>> m_sinks;
};

void Logger::Log(LogLevel lvl, const std::source_location& loc, auto && ...args) noexcept {
	std::scoped_lock lock(m_loggingMutex);
	InternalLog(lvl, loc, std::forward<decltype(args)>(args)...);
}

void Logger::InternalLog(LogLevel lvl, const std::source_location& loc, auto&&... args) const noexcept {
	std::stringstream ss;
	(ss << ... << args);

	const std::string message = ss.str();

	for (const auto& [key, sink] : m_sinks) {
		sink->Emit(message, lvl, loc);
	}
}

void Logger::FormatLog(LogLevel lvl, std::string_view fmt, const std::source_location& loc, auto && ...args) noexcept {
	std::scoped_lock lock(m_loggingMutex);
	InternalFormatLog(lvl, fmt, loc, std::forward<decltype(args)>(args)...);
}

void Logger::InternalFormatLog(LogLevel lvl, std::string_view fmt, const std::source_location& loc, auto&&... args) const noexcept {
	std::string message = std::format(fmt, std::forward<decltype(args)>(args)...);

	for (const auto& [key, sink] : m_sinks) {
		sink->Emit(message, lvl, loc);
	}
}

#define crylog_info(...)    Logger::Get().Log(LogLevel::info, std::source_location::current(), __VA_ARGS__)
#define crylog_warning(...) Logger::Get().Log(LogLevel::warning, std::source_location::current(), __VA_ARGS__)
#define crylog_error(...)   Logger::Get().Log(LogLevel::error, std::source_location::current(), __VA_ARGS__)

#define cryfmtlog_info(fmt, ...)    Logger::Get().FormatLog(LogLevel::info, fmt, std::source_location::current(), __VA_ARGS__)
#define cryfmtlog_warning(fmt, ...) Logger::Get().FormatLog(LogLevel::warning, fmt, std::source_location::current(), __VA_ARGS__)
#define cryfmtlog_error(fmt, ...)   Logger::Get().FormatLog(LogLevel::error, fmt, std::source_location::current(), __VA_ARGS__)