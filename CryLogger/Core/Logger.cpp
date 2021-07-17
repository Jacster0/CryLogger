#include "Logger.h"

Logger& Logger::Get() noexcept {
	static Logger logger;
	return logger;
}

void Logger::SetLevel(LogLevel lvl) {
	m_level = lvl;
}

void Logger::SetSourceLoc(const std::source_location& loc) noexcept {
	m_sourceLoc = loc;
}

void Logger::AttachSink(const std::shared_ptr<ISinkBase>& sink) noexcept {
	auto& logger = Logger::Get();
	logger.m_sinks.emplace(sink->GetName(), sink);
}

void Logger::RemoveSink(const std::string_view name) noexcept {
	auto& logger = Logger::Get();
	logger.m_sinks.erase(name);
}