#pragma once

#include "Sink.h"

class ConsoleSink final : public ISink<ConsoleSink> {
public:
	explicit ConsoleSink(const std::string& name) noexcept : ISink(name) {};
	void Emit(std::string_view message, LogLevel lvl, const std::source_location& loc) noexcept;
};
