#include "Core/Logger.h"
#include "Sinks/Sinks.h"

#include <iostream>

void init_logger() noexcept {
	Logger::AddSink<ConsoleSink>();
	Logger::AddSink<ManagedLoggerSink>();
}

int main() {
	init_logger();

	cryfmtlog_info("{}", "Hello");
	cryfmtlog_warning("{}", "World");
	cryfmtlog_error("{}", "!");

	std::cin.get();
}


