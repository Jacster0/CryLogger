#pragma once

#include "Sink.h"

class ConsoleSink final : public ISink<ConsoleSink> {
public:
	ConsoleSink() noexcept = default;
	void Emit(std::string_view message, LogLevel lvl, const std::source_location& loc) noexcept;
};
