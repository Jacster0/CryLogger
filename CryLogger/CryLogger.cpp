#include "Core/Logger.h"
#include "Sinks/Sinks.h"

void init_logger() noexcept {
	Logger::AttachSink<ConsoleSink, "ConsoleLogger">();
	Logger::AttachSink<ManagedLoggerSink, "ManagedLogger">();
}

int main() {
	init_logger();

	cryfmtlog_info("{}", "Hello");
	cryfmtlog_warning("{}", "World");
	cryfmtlog_error("{}", "!");

	std::cin.get();
}


