#pragma once

#include <string>
#include <source_location>

#include "../Core/LogLevels.h"

class ISinkBase {
public:
	ISinkBase() noexcept = default;
	virtual ~ISinkBase() = default;

	virtual void Emit(std::string_view message, LogLevel lvl, const std::source_location& loc) noexcept = 0;
protected:
	std::string m_name;
};

template<typename T>
class ISink : public ISinkBase {
public:
	ISink() noexcept = default;

	virtual void Emit(
		std::string_view message,
		LogLevel lvl,
		const std::source_location& loc) noexcept override
	{
		static_cast<T*>(this)->Emit(message, lvl, loc);
	}
};