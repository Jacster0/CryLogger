# CryLogger
Modern Logger written in C++20 and C#

This is a Logger that I made for my Game Engine called Crystal (Hence why this logger is called CryLogger, don't confuse it with CryEngine!).
The core logger is written in C++ but there is also a WPF application written in C# which is used to output the logging messages to the WPF gui.
Communication between the core logger and the WPF logger is done with IPC using Named pipes.
## Code example

```cpp
#include "Core/Logger.h"
#include "Sinks/Sinks"

int main() {
	//Attaching this sink to the logger will output logging messages to the Windows command line
	Logger::AddSink<ConsoleSink>();
	//Attaching this sink to the logger will output logging messages to the WPF GUI.
	Logger::AddSink<ManagedLoggerSink>();

	//Normal logging
	crylog_info("Hello");
	crylog_warning("World");
	crylog_error("!");

	//Format logging
	cryfmtlog_info("{}", "Hello");
	cryfmtlog_warning("{}", "World");
	cryfmtlog_error("{}", "!");
	
	//Removing sinks is this easy!
	Logger::RemoveSink<ConsoleSink>();
	Logger::RemoveSink<ManagedLoggerSink>();
}
```

# Screenshots

Logging to a WPF gui using the ManagedLoggerSink
[![](CryLogger/Resources/Screenshots/ManagedLogger.PNG?raw=true)](#)

Logging to the CMD using the ConsoleSink
[![](CryLogger/Resources/Screenshots/ConsoleLogger.PNG?raw=true)](#)
