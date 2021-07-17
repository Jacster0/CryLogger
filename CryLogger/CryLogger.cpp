#include "Core/Logger.h"
#include "Sinks/ConsoleSink.h"
#include "Sinks/ManagedLoggerSink.h"

void init_logger() noexcept {
	Logger::AttachSink(std::make_shared<ConsoleSink>("ConsoleLogger"));
	Logger::AttachSink(std::make_shared<ManagedLoggerSink>("ManagedLogger"));
}

int main() {
	init_logger();

	crylog_info("Hello");
	crylog_warning("World");
	crylog_error("!");

	cryfmtlog_info("{}", "Hello");
	cryfmtlog_warning("{}", "World");
	cryfmtlog_error("{}", "!");
}


