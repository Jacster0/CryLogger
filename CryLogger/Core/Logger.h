#pragma once
#include <mutex>
#include <string>
#include <vector>
#include <format>
#include <memory>
#include <source_location>
#include <concepts>

#include "LogLevels.h"
#include "../Sinks/Sink.h"

template<typename T>
concept Emittable = requires(T t) {
	{ t.Emit(std::string{}, LogLevel::info, std::source_location::current()) };
};

class Logger {
public:
	[[nodiscard]] static Logger& Get() noexcept {
		static Logger logger;
		return logger;
	}

	[[nodiscard]] static constexpr auto NewLine() noexcept { return std::endl<char, std::char_traits<char>>; }

	template<std::derived_from<ISinkBase> T>
	static constexpr void AddSink(auto&&... args) noexcept 
		requires std::constructible_from<T, decltype(args)...> && Emittable<T>
	{
		std::scoped_lock lock(Logger::Get().m_sinkMutex);
		Logger::Get().m_sinks.emplace_back(std::make_unique<T>(std::forward<decltype(args)>(args)...));
	}

	static void AddSink(std::unique_ptr<ISinkBase>&& sink) noexcept {
		std::scoped_lock lock(Logger::Get().m_sinkMutex);
		Logger::Get().m_sinks.emplace_back(std::move(sink));
	}

	/// <summary>
	/// Removes all sinks of type T that is attached to the Logger
	/// </summary>
	template<std::derived_from<ISinkBase> T>
	static void RemoveSink() noexcept {
		std::scoped_lock lock(Logger::Get().m_sinkMutex);

		auto& logger = Logger::Get();

		logger.m_sinks.erase(std::remove_if( logger.m_sinks.begin(), logger.m_sinks.end(), 
			[] (const auto& sink) 
			{ 
				return typeid(*sink) == typeid(T); 
			}
		), logger.m_sinks.end());
	}

	constexpr void Log(LogLevel lvl, const std::source_location& loc, auto&&... args) const noexcept {
		std::scoped_lock lock(m_loggingMutex);

		const std::string& message = (std::stringstream{} << ... << args).str();

		for (const auto& sink : m_sinks) {
			sink->Emit(message, lvl, loc);
		}
	}

	constexpr void FormatLog(LogLevel lvl, const std::source_location& loc, std::string_view fmt, auto&&... args) const noexcept {
		std::scoped_lock lock(m_loggingMutex);

		const std::string message = std::format(fmt, std::forward<decltype(args)>(args)...);

		for (const auto& sink : m_sinks) {
			sink->Emit(message, lvl, loc);
		}
	}
private:
	Logger()                             = default;
	Logger(const Logger& rhs)            = delete;
	Logger& operator=(const Logger& rhs) = delete;
	Logger(Logger&& rhs)                 = delete;
	Logger& operator=(Logger&& rhs)      = delete;
	~Logger()                            = default;

	mutable std::mutex m_loggingMutex;
	std::mutex m_sinkMutex;
	std::vector<std::unique_ptr<ISinkBase>> m_sinks;
};

#define crylog_info(...)    Logger::Get().Log(LogLevel::info,    std::source_location::current(), __VA_ARGS__)
#define crylog_warning(...) Logger::Get().Log(LogLevel::warning, std::source_location::current(), __VA_ARGS__)
#define crylog_error(...)   Logger::Get().Log(LogLevel::error,   std::source_location::current(), __VA_ARGS__)

#define cryfmtlog_info(fmt, ...)    Logger::Get().FormatLog(LogLevel::info,    std::source_location::current(), fmt, __VA_ARGS__)
#define cryfmtlog_warning(fmt, ...) Logger::Get().FormatLog(LogLevel::warning, std::source_location::current(), fmt, __VA_ARGS__)
#define cryfmtlog_error(fmt, ...)   Logger::Get().FormatLog(LogLevel::error,   std::source_location::current(), fmt, __VA_ARGS__)
